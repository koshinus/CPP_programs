#include "logger.hpp"


const char * error_messages[] =
{
    "ALL_CORRECT: everything is fine.\n",
    "UNKNOWN_COMMAND: wrong first symbol in received message.\n",
    "INCORRECT_ID: please check the datablock id.\n",
    "OUT_OF_MEMORY: system haven't enough memory to allocate this datablock.\n",
    "OUT_OF_RANGE: please check offset and data length of delivered message.\n",
    "NO_DATA_RECEIVED: received message have no data.\n",
    "NO_DATA_SEND: sending message have no data.\n",
    "RECEIVING_ERROR: ",
    "SENDING_ERROR: "
};

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
    close();
    open();
}

void RiDE_logger::log(ERROR error_type, const char * info)
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
    if (info)
        fprintf(log_file, "%s\n", info);
}

bool RiDE_logger::time_to_close()
{
    return std::uint64_t(clock() - log_creation_time) >= MAX_LOG_TIME;
}
