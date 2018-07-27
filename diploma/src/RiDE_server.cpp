#include "RiDE_server.hpp"
#include <boost/crc.hpp>
#include <iostream>

RiDE_server::RiDE_server(boost::asio::io_service & io_service, RiDE_logger & logger):
    m_socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 6868)),
    m_logger(logger),
    m_started(true)
{
    m_socket.set_option(boost::asio::socket_base::reuse_address(true));
    start_receive();
}

bool RiDE_server::started() const
{
    return m_started;
}

void RiDE_server::stop_receive()
{
    m_socket.get_io_service().stop();
}

void RiDE_server::start_receive()
{
    if (!m_started)
        m_started = true;
    if (m_socket.get_io_service().stopped())
        m_socket.get_io_service().reset();
    m_socket.async_receive(boost::asio::buffer(m_recv_buf, BUF_SIZE),
            [this](const boost::system::error_code & e, size_t received)
            {
                if (!received)
                    m_logger.log(NO_DATA_RECEIVED, nullptr);
                if (e)
                    m_logger.log(RECEIVING_ERROR, e.message().c_str());
                parse_buffer(m_recv_buf, received);
            });
}

void RiDE_server::placing(uint64_t id, uint64_t block_len, uint64_t offset, uint64_t data_len, char * data_ptr)
{
    auto it = m_datas.find(id);
    if (it != m_datas.end())
    {
        if(it->second.size() < offset + data_len)
            m_logger.log(OUT_OF_RANGE, nullptr);
        else
            std::copy(data_ptr, data_ptr + data_len, it->second.data() + offset);
    }
    else
    {
        if (block_len < offset + data_len)
            m_logger.log(OUT_OF_RANGE, nullptr);
        m_datas.emplace(std::piecewise_construct, std::make_tuple(id), std::make_tuple(block_len));
        std::copy(data_ptr, data_ptr + data_len, m_datas[id].begin() + offset);
    }
    start_receive();
}

void RiDE_server::transmition(std::uint32_t addr, std::uint16_t port, std::uint64_t id, std::uint64_t offset, std::uint64_t length)
{
    namespace asio_ip = boost::asio::ip;
    asio_ip::udp::socket send_sock(m_socket.get_io_service());
    send_sock.open(boost::asio::ip::udp::v4());
    send_sock.set_option(boost::asio::socket_base::broadcast(true));
    asio_ip::udp::endpoint dest(asio_ip::address::from_string(inet_ntoa((in_addr){.s_addr = htobe32(addr)})), port);
    auto it = m_datas.find(id);
    if (it == m_datas.end())
        m_logger.log(INCORRECT_ID, nullptr);
    else
    {
        if (it->second.size() < offset + length)
            m_logger.log(OUT_OF_RANGE, nullptr);
        else
        {
            std::cout << it->second.size() << '-' << it->second.capacity() << '-' << it->second.data() << std::endl;
            fill_buffer(m_send_buf, 'p', id, it->second.capacity(), offset, length, 0, 0, reinterpret_cast<char *>(it->second.data()));
            std::uint64_t full_offset = sizeof(char) + sizeof(id)
                    + sizeof(it->second.capacity()) + sizeof(offset) + sizeof(length) + length;
            send_sock.async_send_to(boost::asio::buffer(m_send_buf, full_offset), dest,
                                [this, &dest](const boost::system::error_code & e, size_t bytes_transfered)
                                {
                                    if (!bytes_transfered)
                                        m_logger.log(NO_DATA_SEND, nullptr);
                                    if (e)
                                        m_logger.log(SENDING_ERROR, e.message().c_str());
                                    start_receive();
                                });
        }
    }
    start_receive();
}

bool RiDE_server::validate_checksum(char *buf, size_t bytes_received)
{
    boost::crc_32_type result;
    boost::crc_32_type::value_type incoming_checksum = ((boost::crc_32_type::value_type *)buf)[0];
    result.process_bytes(buf + sizeof(boost::crc_32_type::value_type), bytes_received);
    return result.checksum() == incoming_checksum;
}

void/*ERROR*/ RiDE_server::parse_buffer(char * buf, size_t bytes_received)
{
    std::uint64_t id, offset, data_len, block_len, full_offset;
    std::uint32_t remote_addr;
    std::uint16_t remote_port;
    // Check the first byte in received buffer
    if (*buf == 'p')
    {
        buf++; // Skip 'p'
        id          = ((uint64_t *)buf)[0];
        block_len   = ((uint64_t *)buf)[1];
        offset      = ((uint64_t *)buf)[2];
        data_len    = ((uint64_t *)buf)[3];
        std::cout << id << '-' << block_len << '-' << offset << '-' << data_len << std::endl;
        full_offset = sizeof(id) + sizeof(offset) + sizeof(data_len) + sizeof(block_len);
        if (bytes_received < full_offset + data_len + sizeof(char))
            m_logger.log(OUT_OF_RANGE, nullptr);
        char * data_ptr = (char *)(buf + full_offset);
        placing(id, block_len, offset, data_len, data_ptr);
    }
    else if (*buf == 't')
    {
        buf++; // Skip 't'
        remote_addr = ((uint32_t *)buf)[0];
        buf += sizeof(remote_addr); // Skip "remote machine address"-bytes in buffer
        remote_port = ((uint16_t *)buf)[0];
        buf += sizeof(remote_port); // Skip "remote machine port"-bytes in buffer
        id        = ((uint64_t *)buf)[0];
        offset    = ((uint64_t *)buf)[1];
        data_len  = ((uint64_t *)buf)[2];
        std::cout << id << '-' << offset << '-' << data_len << '-' << remote_addr << '-' << remote_port << std::endl;
        full_offset = sizeof(id) + sizeof(offset) + sizeof(data_len) +
                        sizeof(remote_addr) + sizeof(remote_port);
        if (bytes_received < full_offset + sizeof(char))
            m_logger.log(OUT_OF_RANGE, nullptr);
        transmition(remote_addr, remote_port, id, offset, data_len);
    }
    else
        m_logger.log(UNKNOWN_COMMAND, nullptr);
}
