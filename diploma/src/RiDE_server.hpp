#pragma once

#include <uv.h>
#include <cstring>
#include <cstdint>
#include <ctime>
#include "datablock.hpp"
#include "logger.hpp"

class RiDE_server
{
    datablock *   * datas;
    uint64_t        datas_capacity;
    uint64_t        datas_length;
    uv_loop_t     * event_loop;
    uv_udp_t        recv_socket;
    RiDE_logger   * logger;
    bool            started;
    void datas_configure();
    void datas_reset();
    void on_alloc(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf);
    void on_recv(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags);
    void on_send(uv_udp_send_t* req, int status);
    void transmition(uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length);
    void placing(uint64_t id, uint64_t offset, uint64_t length, char * data_ptr);
    void allocation(uint64_t id, uint64_t length);
    void parsing_buffer(const char * buf);
public:
    RiDE_server(RiDE_logger * logger);
    void start();
    void stop();
    bool is_started();
};
