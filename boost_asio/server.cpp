#include "stdafx.h"
#include "server.hpp"

echo_server::echo_server(io_service &service) :
    started(false),
    connection_id(0),
    endp(ip::tcp::v4(), 2001),
    acc(service, endp),
    service(service)
    {
        acc.set_option(ip::tcp::acceptor::reuse_address(true));
        start_accept();
    };

void echo_server::start_accept()
{
    if (!started) 
        started = true;
    if (service.stopped())
        service.reset();
    connection con_(service);
    connections.insert(std::make_pair(++connection_id, con_));
    acc.async_accept(*con_.sock_ptr, endp,
            [this](const boost::system::error_code &ec)
            { 
                if (ec)
                {
                    m.lock();
                    std::cerr << "Server accepting error: " << ec << std::endl;
                    m.unlock();
                    return;
                }
                start_read(connection_id);
                start_accept();
            });
};

void echo_server::start_read(size_t id)
{
    
    if (!started)
        return;
    connections[id].sock_ptr->async_read_some(buffer(connections[id].buf, BUF_SIZE),
        [id, this](const boost::system::error_code &ec, size_t received)
        {
            if (!received)
            {
                m.lock();
                std::cout << "Server read ended." << std::endl;
                m.unlock();
                close_connection(id, const_cast<boost::system::error_code &>(ec));
                return;
            }
            if (ec)
            {
                m.lock();
                std::cerr << "Server reading error: " << ec << std::endl;
                m.unlock();
                close_connection(id, const_cast<boost::system::error_code &>(ec));
                return;
            }
            start_write(id, received);
        });
};

void echo_server::start_write(size_t id, size_t bytes_write)
{
    if (!started)
        return;
    connections[id].buf[bytes_write] = '\0';
    m.lock();
    std::cout << "[connection " << id << ": " << connections[id].buf << ']' << std::endl;
    m.unlock();
    connections[id].sock_ptr->async_write_some(buffer(connections[id].buf, bytes_write),
        [id, this](const boost::system::error_code &ec, size_t)
        {
            if (ec) 
            {
                m.lock();
                std::cerr << "Server writing error: " << ec << std::endl;
                m.unlock();
                return; 
            }
            start_read(id);
        });
};

void echo_server::close_connection(size_t id, boost::system::error_code &ec)
{
    connections[id].sock_ptr->close(ec);
    connections.erase(id);
    m.lock();
    std::cout << "[connection " << id << " closed]" << std::endl;
    m.unlock();
    if (connections.empty())
        service.stop();
};

void echo_server::stop_accept()
{
    if (started) started = false;
    connections.clear();
    service.stop();
};