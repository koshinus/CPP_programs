#pragma once

#include "datablock.hpp"
#include "logger.hpp"
#include <map>
#include <boost/asio.hpp>
#include <algorithm>

class RiDE_server
{
public:
    RiDE_server(boost::asio::io_service & io_service, RiDE_logger & logger);
    void stop_receive();
    bool started() const;

private:

    void start_receive();
    bool validate_checksum(char * buf, size_t bytes_to_check);
    void parse_buffer(char * buf, size_t bytes_received);
    void placing(uint64_t id, uint64_t block_len, uint64_t offset, uint64_t data_len, char * data_ptr);
    void transmition(uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length);

    boost::asio::ip::udp::socket                        m_socket;
    RiDE_logger &                                       m_logger;
    bool                                                m_started = false;
    std::map<uint64_t, std::vector<int8_t>>             m_datas;
    const int                                           BUF_SIZE = 4096;
    char                                                m_recv_buf[4096];
    char                                                m_send_buf[4096];
};
