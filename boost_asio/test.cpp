// test.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <mutex>
#include "server.hpp"
#include "client.hpp"
#include <boost/thread.hpp>
#include <thread>
#include <mutex>
#include <array>

class printer
{
    std::mutex m;
public:
    void print_msg(std::string &s)
    {
        std::lock_guard<std::mutex> lock_(m);
        std::cout << s << std::endl;
    }
    void print_msg(int n)
    {
        std::lock_guard<std::mutex> lock_(m);
        std::cout << n << std::endl;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    std::array<std::string, 4> ar{ { "The boost::asio::buffer() function provides a convenient way "
        "to create the buffer classes, where the size of the buffer is "
        "deduced from the type possible.",
        "When Boost.Asio is able to deduce the buffer length, then Boost.",
        "The compiler expects to get an int and not an initializer-list, "
        "that's the reason for the error.",
        "The fundamental question becomes how does one know how much memory "
        "to allocate, if Boost.Asio does not transmit the size." } };
    std::string str = "The compiler expects to get an int and not an initializer-list, that's the reason for the error.";
    /*
    std::array<int, 10> ar1{ { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 } };
    std::vector<std::thread> threads;
    printer pr;
    for (int i = 0; i < 4; i++)
    {
        threads.push_back(std::thread([&pr, i, &ar]()
        {
            pr.print_msg(ar[i]);
            std::chrono::milliseconds duration(500);
            std::this_thread::sleep_for(duration);
            pr.print_msg(ar[i]);
        }));
    }
    for (std::thread &t : threads)
        t.join();
    */
    try
    {
        io_service service_server;
        echo_server server(service_server);
        getline(std::cin, str);
        if (str == "1")
        {
            std::thread t1([&service_server]() { service_server.run(); });
            while (true)
            {
                getline(std::cin, str);
                if (str == "exit")
                {
                    server.stop_accept();
                    break;
                }
                io_service service_client;
                echo_client client(service_client, str);
                std::thread t2([&service_client]() { service_client.run(); });
                t2.join();
            }
            t1.join();
        }
        else
        {
            ///*
            std::thread main_thread([&service_server]() { service_server.run(); });
            while (true)
            {
                getline(std::cin, str);
                if (str == "exit")
                {
                    server.stop_accept();
                    break;
                }
                std::vector<std::unique_ptr<io_service>> clients_services;
                std::vector<std::unique_ptr<echo_client>> clients;
                std::vector<std::thread> threads;
                for (int i = 0; i < 4; i++)
                {
                    clients_services.emplace_back(new io_service());
                    //echo_client client(*clients_services[i], ar[i]);
                    clients.emplace_back(new echo_client(*clients_services[i], ar[i]));
                    threads.push_back(std::thread([i, &clients_services]() { clients_services[i]->run(); }));
                }
                for (auto & t : threads)
                    t.join();
            }
            main_thread.join();
            std::cout << "Main thread exit" << std::endl;
            //*/
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    system("pause");
    return 0;
}
