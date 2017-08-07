#include "stdafx.h"
#include "server.hpp"
#include <thread>
#include <mutex>

echo_server::echo_server(io_service &service) :
    started(false),
    connection_id(0),
    endp(ip::tcp::v4(), 2001),
    acc(service, endp),
    service(service)
    {
        std::thread t([&service]() { service.run(); });
        t.join();
        start_accept();
    };

void echo_server::start_accept()
{
    if (!started) 
        started = true;
    if (service.stopped())
        service.reset();
    connection con_(acc.get_io_service());
    connection_id++;
    connections.insert(std::make_pair(connection_id, con_));
    acc.async_accept(*con_.sock_ptr, endp, 
                        [this](const boost::system::error_code &ec)
                        { 
                            if (!ec)
                            {
                                start_read(connection_id);
                                start_accept();
                            }
                        });
};

void echo_server::start_read(size_t id)
{
    if (!started) 
        return;
    size_t availible = connections[id].sock_ptr->available();
    size_t need_to_read = (availible > BUF_SIZE)? BUF_SIZE : availible;
    connections[id].buf[need_to_read] = '\0';
    connections[id].sock_ptr->async_read_some(buffer(connections[id].buf, need_to_read),
                                [id, need_to_read, this](const boost::system::error_code &ec, size_t)
                                {
                                    if (!ec) start_write(id, need_to_read);
                                    else return;
                                    //else close_connection(id);
                                });
};

void echo_server::start_write(size_t id, size_t bytes_write)
{
    if (!started)
        return;
    if (!bytes_write)
    {
        close_connection(id);
        return;
    }
/*
    {    
        std::mutex m;
        std::lock_guard<std::mutex> lock(m);
        std::cout << "[connection " << id << ": " << connections[id].buf << ']' << std::endl;
    }
*/
    std::cout << "[connection " << id << ": " << connections[id].buf << ']' << std::endl;
    connections[id].sock_ptr->async_write_some(buffer(connections[id].buf, bytes_write),
                                [id, this](const boost::system::error_code &ec, size_t)
                                {
                                    if (!ec) start_read(id);
                                    else return;
                                    //else close_connection(id);
                                });
};

void echo_server::close_connection(size_t id)
{
    connections.erase(id);
    std::cout << "[connection " << id << " closed]" << std::endl;
    if (connections.empty())
        service.stop();
};

void echo_server::stop_accept()
{
    if (started) started = false;
    connections.clear();
    service.stop();
};