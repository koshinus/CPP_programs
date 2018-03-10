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
#include "RiDE_server.h"

/*
 * 
 */
int main(int argc, char** argv)
{
    RiDE_logger logger;
    RiDE_server server(&logger)
    logger.open();
    while(1)
    {
        if (!server.is_started())
            server.start();
        if (logger.time_to_close())
            logger.reopen(logger);
    }
    logger.close(logger);
    return 0;
}
