#include "stdafx.h"
#include "client.hpp"


//echo_client::echo_client() {}

echo_client::echo_client(io_service &service, std::string &str) :
        endp(ip::address::from_string("127.0.0.1"), 2001),
        msg(str),
        sock_(boost::shared_ptr<sock> (new sock(service)))
        {
            buf[BUF_SIZE] = '\0';
        }


echo_client::echo_client(const echo_client &cl) : 
        msg(cl.msg),
        sock_(cl.sock_),
        endp(cl.endp)
{}

void echo_client::start()
{
    //if (sock_->get_io_service().stopped())
    //    sock_->get_io_service().reset();
    sock_->async_connect(endp, 
        [this](const boost::system::error_code &ec) mutable
        {
            if (ec)
            {
                std::cerr << "Connection error: " << ec << std::endl;
                return;
            }
            start_write(0, 1);
        });
}

void echo_client::start_read(size_t msg_size, size_t pos)
{
    sock_->async_read_some(buffer(buf, msg_size), 
        [this, pos](const boost::system::error_code &ec, size_t recieved)
        {
            if (ec)
            {
                std::cerr << "Reading error: " << ec << std::endl;
                return;
            }
            start_write(pos + recieved, recieved);
        });
}

void echo_client::start_write(size_t pos, size_t recieved)
{
    if (!recieved)
    {
        //sock_->close();
        return;
    }
    if (pos)
        std::cout << "Recieved from server: " << buf << std::endl;
    size_t msg_size = (BUF_SIZE < msg.size() - pos) ? BUF_SIZE : msg.size() - pos;
    //std::copy(msg.begin() + pos, msg.begin() + pos + msg_size, buf);
    for (size_t i = 0; i < msg_size; i++)
        buf[i] = msg[i + pos];
    buf[msg_size] = '\0';
    sock_->async_write_some(buffer(buf, msg_size), 
        [this, msg_size, pos](const boost::system::error_code &ec, size_t)
        {
            if (ec)
            {
                std::cerr << "Writing error: " << ec << std::endl;
                return;
            }
            start_read(msg_size, pos);
        });
}