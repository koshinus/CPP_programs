#pragma once

#include <cstdio>
#include <cstdint>
#include "utilities.hpp"

class RiDE_logger
{
    const uint64_t MAX_LOG_TIME = 10*60*60; // 10 hours
    const uint64_t MAX_LOG_SIZE = 100*1024*1024; // 100 Mb
    FILE * log_file;
    time_t log_creation_time;
    uint64_t current_log_size;
public:
    void open();
    void close();
    void reopen();
    void log(ERROR error_type);
    bool time_to_close();
};

void open_log_file(RiDE_logger * log);
void close_log_file(RiDE_logger * log);
void reopen_log_file(RiDE_logger * log);
void log_an_error(RiDE_logger * log, ERROR error_type);
