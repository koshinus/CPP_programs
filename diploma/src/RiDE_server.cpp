#include "RiDE_server.hpp"

RiDE_server::RiDE_server(RiDE_logger * logger_):
    logger(logger_)
{
}

void RiDE_server::datas_configure()
{
    datas_capacity = 2;
    datas_length = 0;
    datas = new (datablock *)[datas_capacity];
}

void RiDE_server::datas_reset(RiDE_server * server)
{
    for(uint64_t i = 0; i < datas_length; i++)
        delete datas[i];
    delete [] datas;
}

void RiDE_server::on_alloc(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf)
{
    buf->base = new char[suggested_size + 1];
    buf->len = suggested_size;
    buf->base[suggested_size] = '\0';
}

void RiDE_server::on_recv(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags)
{
    if (nread > 0)
        parsing_buffer(rcvbuf->base);
    else
        logger->log(NO_DATA_RECEIVED);
    delete [] rcvbuf->base;
}

void RiDE_server::on_send(uv_udp_send_t* req, int status)
{

}

void RiDE_server::start()
{
    datas_configure();
    started = true;
    struct sockaddr_in addr;
    event_loop = uv_default_loop();
    uv_udp_init(event_loop, &recv_socket);
    uv_ip4_addr("127.0.0.1", 11000, &addr);
    uv_udp_bind(&recv_socket, (const struct sockaddr *)&addr, UV_UDP_REUSEADDR);
    uv_udp_recv_start(&recv_socket, on_alloc, on_recv);
    uv_run(event_loop, UV_RUN_DEFAULT);
}

void RiDE_server::stop()
{
    uv_udp_recv_stop(&recv_socket);
    started = false;
    datas_reset(server);
}

bool RiDE_server::is_started()
{
    return started;
}

void/*ERROR*/ RiDE_server::transmition(uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length)
{
    uv_udp_send_t send_socket;
    struct in_addr ip_addr;
    ip_addr.s_addr = addr;
    struct sockaddr_in send_addr;
    
    uv_udp_init(event_loop, &send_socket);
    uv_ip4_addr(inet_ntoa(ip_addr), port, &send_addr);
    uv_udp_bind(&send_socket, (const struct sockaddr *)&send_addr, 0);
    uv_udp_set_broadcast(&send_socket, 1);
    uv_buf_t * send_buf;
    for (uint64_t i = 0; i < datas_length; i++)
    {
        if (datas[i]->id == id)
        {
            send_buf->base = new char[length];
            strncpy(send_buf->base, datas[id]->data + offset, length);
            send_buf->len = length;
            uv_udp_send(&send_socket, &recv_socket, (const uv_buf_t *)send_buf, 1, (const struct sockaddr *)&send_addr, server->on_send);
            delete [] send_buf->base;
            return;
        }
        else
            logger->log(INCORRECT_ID);
    }
    //return ALL_CORRECT;
}

void/*ERROR*/ RiDE_server::placing(uint64_t id, uint64_t offset, uint64_t length, char * data_ptr)
{
    for(uint64_t i = 0; i < datas_length; i++)
        if(datas[i]->id == id)
        {
            if(datas[i]->len < offset + length)
            {
                logger->log(OUT_OF_RANGE);
                return;
                //return OUT_OF_RANGE;
            }
            else
            {
                strncpy(datas[i]->data + offset, data_ptr, length);
                return;
                //return ALL_CORRECT;
            }
        }
    logger->log(INCORRECT_ID);
    return;
    //return INCORRECT_ID;
}

void/*ERROR*/ RiDE_server::allocation(uint64_t id, uint64_t length)
{
    for(uint64_t i = 0; i < datas_length; i++)
        if(datas[i]->id == id)
        {
            logger->log(ALREADY_ALLOCATED);
            return;
            //return ALREADY_ALLOCATED;
        }
    datablock * block = new datablock(id, length);
    // datablock_alloc and malloc/realloc return NULL
    // if system haven't enough memory for allocation
    if (!block)
    {
        logger->log(OUT_OF_MEMORY);
        return;
        //return OUT_OF_MEMORY;
    }
    if(datas_length == datas_capacity)
    {
        datas_capacity *= 2;
        datablock ** new_datas = new (datablock **)[datas_capacity];
        if(!new_datas)
        {
            logger->log(OUT_OF_MEMORY);
            return;
            //return OUT_OF_MEMORY;
        }
        for(uint64_t i = 0; i < datas_length; i++)
            new_datas[i] = datas[i];
        delete [] datas;
        datas = new_datas;
    }
    datas[datas_length] = block;
    datas_length++;
    //return ALL_CORRECT;
}

void/*ERROR*/ RiDE_server::parsing_buffer(const char * buf)
{
    uint64_t id, offset, length;
    uint32_t host_addr;
    uint16_t host_port;
    // Check the first byte in received buffer
    switch(*buf)
    {
        // Command "beXtoh( ((uintX_t *)buf)[] )" interprets next X bits
        // as unsigned number and convert it to endian of the calling machine
        case 'a':
        {
            buf++; // Skip 'a'
            id        = be64toh( ((uint64_t *)buf)[0] );
            length    = be64toh( ((uint64_t *)buf)[1] );
            allocation(id, length);
            //return allocate(id, length);
            break;
        }
        case 'p':
        {
            buf++; // Skip 'p'
            id        = be64toh( ((uint64_t *)buf)[0] );
            offset    = be64toh( ((uint64_t *)buf)[1] );
            length    = be64toh( ((uint64_t *)buf)[2] );
            char * data_ptr = (char *)(buf + sizeof(id) + sizeof(offset) + sizeof(length));
            placing(id, offset, length, data_ptr);
            //return place(server, id, offset, length, data_ptr);
            break;
        }
        case 't':
        {
            buf++; // Skip 't'
            host_addr = be32toh( ((uint32_t *)buf)[0] );
            buf += sizeof(host_addr); // Skip "host address"-bytes in buffer
            host_port = be16toh( ((uint16_t *)buf)[0] );
            buf += sizeof(host_port); // Skip "host port"-bytes in buffer
            id        = be64toh( ((uint64_t *)buf)[0] );
            offset    = be64toh( ((uint64_t *)buf)[1] );
            length    = be64toh( ((uint64_t *)buf)[2] );
            transmition(host_addr, host_port, id, offset, length);
            //return transmit(host_addr, host_port, id, offset, length);
            break;
        }
        default :
            logger->log(UNKNOWN_COMMAND);
            //return UNKNOWN_COMMAND;
            break;
    }
}
