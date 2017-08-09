#include "stdafx.h"
#include "client.hpp"

echo_client::echo_client(io_service &service, std::string &str) :
        endp(ip::address::from_string("127.0.0.1"), 2001),
        msg(str),
        sock_(new sock(service))
        {
            buf[BUF_SIZE] = '\0';
            start();
        }


echo_client::echo_client(const echo_client &cl) :
        msg(cl.msg),
        sock_(cl.sock_),
        endp(cl.endp)
{}

void echo_client::start()
{
    sock_->async_connect(endp, 
        [this](const boost::system::error_code &ec)
        {
            if (ec)
            {
                m.lock();
                std::cerr << "Client connection error: " << ec << std::endl;
                m.unlock();
                return;
            }
            start_write(0, 1);
        });
}
void echo_client::start_read(size_t msg_size, size_t pos)
{
    sock_->async_read_some(buffer(buf, msg_size),
        [this, pos](const boost::system::error_code &ec, size_t received)
        {
            if (ec)
            {
                m.lock();
                std::cerr << "Client reading error: " << ec << std::endl;
                m.unlock();
                return;
            }
            if (!received)
            {
                m.lock();
                std::cout << "Client read ended." << std::endl;
                m.unlock();
                return;
            }
            start_write(pos + received, received);
        });
}

void echo_client::start_write(size_t pos, size_t received)
{
    if (pos)
    {
        m.lock();
        std::cout << "Recieved from server: " << buf << std::endl;
        m.unlock();
    }
    size_t msg_size = (BUF_SIZE < msg.size() - pos) ? BUF_SIZE : msg.size() - pos;
    for (size_t i = 0; i < msg_size; i++)
        buf[i] = msg[i + pos];
    buf[msg_size] = '\0';
    sock_->async_write_some(buffer(buf, msg_size),
        [this, msg_size, pos](const boost::system::error_code &ec, size_t)
        {
            if (ec)
            {
                m.lock();
                std::cerr << "Client writing error: " << ec << std::endl;
                m.unlock();
                return;
            }
            start_read(msg_size, pos);
        });
}