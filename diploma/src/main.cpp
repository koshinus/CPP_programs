/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: vadim
 *
 * Created on 7 декабря 2017 г., 7:23
 */
#include "RiDE_server.hpp"
#include <omp.h>

/*
 *
 */
int main(int argc, char** argv)
{
    char message[40];
    boost::asio::io_service serv;
    RiDE_logger logger;
    RiDE_server server(serv, logger);
    logger.open();
    serv.run();
//    #pragma omp parallel sections
//    {
//        #pragma omp section
//        {
//            while(1)
//            {
////                if (!server.started())
////                    server_start(server);
//                if (logger.time_to_close())
//                    logger.reopen();
//            }
//        }
//        #pragma omp section
//        {
//            while(1)
//            {
//                scanf("%s", message);
//                if (!strcmp(message, "server_stop"))
//                {
//                    server.stop();
//                    logger.close();
//                    exit(0);
//                }
//            }
//        }
//    }
}
