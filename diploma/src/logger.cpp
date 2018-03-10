#include "logger.hpp"

void RiDE_logger::open()
{
    char filename[40];
    struct tm *timenow;
    log_creation_time = time(NULL);
    timenow = gmtime(&log_creation_time);
    strftime(filename, sizeof(filename), "log/SERVER_%Y-%m-%d_%H:%M:%S", timenow);
    log_file = fopen(filename, "w");
    current_log_size = 0;
}

void RiDE_logger::close()
{
    fclose(log_file);
    current_log_size = 0;
}

void RiDE_logger::reopen()
{
    log->close(log);
    log->open(log);
}

void RiDE_logger::log(ERROR error_type)
{
    char time_string[20];
    struct tm *timenow;

    time_t error_time = time(NULL);
    timenow = gmtime(&error_time);

    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", timenow);

    // All strings here are null-terminated, so we need to deduct
    // summary size of null-terminators except the last one
    uint64_t current_err_msg_size = sizeof("ERROR| ")                       +
                                    sizeof(time_string)                     +
                                    sizeof(" of type ")                     +
                                    sizeof(error_messages[(int)error_type]) -
                                    sizeof('\0') * 3;
    if(current_log_size + current_err_msg_size >= MAX_LOG_SIZE)
        reopen();
    current_log_size += current_err_msg_size;
    fprintf(log_file, "ERROR| %s of type %s", time_string, error_messages[(int)error_type]);
}

bool RiDE_logger::time_to_close()
{
    return clock() - log_creation_time >= MAX_LOG_TIME;
}
