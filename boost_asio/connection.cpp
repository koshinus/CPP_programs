// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*
#include <numeric>
#include <string>
#include <iostream>
#include <algorithm>
#include <boost/asio.hpp>
using namespace std;
using namespace boost::asio;
using sock_ptr = boost::shared_ptr<ip::tcp::socket>;
const size_t BUF_SIZE = 20;

//int _tmain(int argc, _TCHAR* argv[])
int start(io_service &service)
{
    string s;
    char buf[BUF_SIZE + 1]; buf[BUF_SIZE] = '\0';
    getline(cin, s);
    size_t counter = 0;
    sock_ptr sock(new ip::tcp::socket(service));
    ip::tcp::endpoint endp(ip::address::from_string("127.0.0.1"), 2001);
    auto handler = [](boost::system::error_code &ec) { if (ec) return; };
    sock->async_connect(endp, handler);
    while ( counter < s.size() )
    {
        int readed = (BUF_SIZE < s.size() - counter) ? BUF_SIZE : s.size() - counter;
        copy(s.begin() + counter, s.begin() + counter + readed, buf);
        buf[readed] = '\0';
        counter += BUF_SIZE;
        sock->async_write_some(buffer(buf), handler);
        sock->async_read_some(buf, handler);
        cout << buf << endl;
    }
    service.run();
    cin >> counter;
    return 0;
}
*/


/*
void start_read(boost::shared_ptr<sock> sock_, char * buf, size_t buf_size, size_t pos, size_t str_size)
{
    sock_->async_receive(buffer(buf, buf_size), [=](const boost::system::error_code &ec, size_t received)
                                                {
                                                    if (ec)
                                                    {
                                                        std::cerr << "Send error " << ec << std::endl;
                                                        return;
                                                    }
                                                    if (!received)
                                                    {
                                                        std::cerr << "Connection closed" << std::endl;
                                                        return;
                                                    }
                                                    size_t new_pos = pos + received;
                                                    if (new_pos >= str_size)
                                                    {
                                                        sock_->close();
                                                        sock_->get_io_service().stop();
                                                        std::cout << "OK" << std::endl;
                                                        return;
                                                    }
                                                    start_read(sock_, buf, buf_size, new_pos, str_size);
                                                });
}
*/

/*
boost::shared_ptr<sock> socket(new sock(service));
auto socket = boost::make_shared<sock>(service);
char buf[BUF_SIZE];
socket->async_connect(endp, [&str, socket, &buf](const boost::system::error_code &ec)
                            {
                                if (ec)
                                {
                                    std::cerr << "Send error " << ec << std::endl;
                                    return;
                                }
                                std::cout << "CONNECTED " << ec << std::endl;
                                socket->async_send(buffer(str), [](const boost::system::error_code &ec, size_t)
                                                                {
                                                                    if (!ec) return;
                                                                    std::cerr << "Send error " << ec << std::endl;
                                                                });
                                start_read(socket, buf, sizeof(buf), 0, str.size());
                            });
std::thread t([&service]() { service.run(); });
t.join();
*/

/*
void start(boost::shared_ptr<sock> socket, const boost::system::error_code &ec)
{
std::string str;
std::cout << "Enter your string: " << std::endl;
std::cin >> str;
if (str == "exit")
{
socket->close();
socket->get_io_service().stop();
return;
}
else
{
char buf[BUF_SIZE];
start_write(socket, ec, buf, 0);
}
}

void start_write(boost::shared_ptr<sock> socket, const boost::system::error_code &ec, char *buf, size_t readed)
{
if (ec)
{
std::cerr << "Write error " << ec << std::endl;
return;
}
socket->async_write_some(buffer());
start_read(socket, ec, buf, readed);
}

void start_read(boost::shared_ptr<sock> socket, const boost::system::error_code &ec, char *buf, size_t readed)
{
if (ec)
{
std::cerr << "Read error " << ec << std::endl;
return;
}
socket->async_read_some(buffer());
start_write(socket, ec, buf, readed);
}

boost::shared_ptr<sock> socket(new sock(service));
socket->async_connect(endp, [socket](const boost::system::error_code &ec)
{
if (ec)
{
std::cerr << "Connect error " << ec << std::endl;
return;
}
std::cout << "CONNECTED" << std::endl;
start(socket, ec);
});
*/

/*
sock sockets[4] { sock(service), sock(service), sock(service), sock(service) };
for (int i = 0; i < 4; i++)
{
sockets[i].async_connect(endp, [](const boost::system::error_code &ec) { if (!ec) return; });
sockets[i].async_send(buffer(ar[i]), [](const boost::system::error_code &ec, size_t) { if (!ec) return; });
}
for (int i = 0; i < 4; i++)
boost::thread([&service]() { service.run(); });
*/