// test.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "server.hpp"
#include "client.hpp"
#include <boost/thread.hpp>
#include <thread>

int _tmain(int argc, _TCHAR* argv[])
{
    int n;
    std::string ar[] = {"The boost::asio::buffer() function provides a convenient way "
                        "to create the buffer classes, where the size of the buffer is "
                        "deduced from the type possible.", 
                        "When Boost.Asio is able to deduce the buffer length, then Boost.", 
                        "The compiler expects to get an int and not an initializer-list, "
                        "that's the reason for the error.", 
                        "The fundamental question becomes how does one know how much memory "
                        "to allocate, if Boost.Asio does not transmit the size."};
    std::string str = "The compiler expects to get an int and not an initializer-list, that's the reason for the error.";
   
    try
    {
        io_service server_service, client_service, service;
        echo_server server(server_service);
        getline(std::cin, str);
        if (str == "1")
        {
            while (true)
            {
                getline(std::cin, str);
                if (str == "exit")
                {
                    server.stop_accept();
                    break;
                }
                echo_client client(client_service, str);
                client.start();
                client_service.run();
            }
        }
        else while (true)
        {
            getline(std::cin, str);
            if (str == "exit")
                break;
            std::vector<boost::shared_ptr<echo_client>> clients;
            std::vector<std::thread> threads;
            for (int i = 0; i < 4; i++)
            {
                echo_client client(service, ar[i]);
                clients.push_back(boost::make_shared<echo_client>(client));
                clients[i]->start();
                threads.push_back(std::thread([&service]() { service.run(); }));
            }
            for (auto & t : threads)
                t.join();
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cin >> n;
    return 0;
}

