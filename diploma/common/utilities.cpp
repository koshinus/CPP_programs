#include <iostream>
#include <cstdio>
#include "utilities.hpp"

void fill_buffer_for_placing(char * buf, std::uint64_t id, std::uint64_t block_len,
                             std::uint64_t offset, std::uint64_t data_len, char * data)
{
    rep64 nr1, nr2, nr3, nr4;
    buf[0] = 'p';
    nr1.num = id;
    nr2.num = block_len;
    nr3.num = offset;
    nr4.num = data_len;
    for(int i = 0; i < 8; i++)
    {
        //bytes
        //1 2 3 4 5 6 7 8 | 9 10 11 12 13 14 15 16 | 17 18 19 20 21 22 23 24 | 25 26 27 28 29 30 31 32
        buf[i+1]  = nr1.representation[i];
        buf[i+9]  = nr2.representation[i];
        buf[i+17] = nr3.representation[i];
        buf[i+25] = nr4.representation[i];
    }
    std::uint64_t full_offset = sizeof(char) + sizeof(id) + sizeof(block_len)
            + sizeof(offset) + sizeof(data_len);
    strncpy(buf + full_offset, data, data_len);
}


void fill_buffer_for_transmition(char * buf, std::uint64_t id, std::uint64_t offset,
                                 std::uint64_t len, std::uint32_t address, std::uint16_t port)
{
    rep64 nr1, nr2, nr3;
    rep32 nr4;
    rep16 nr5;
    buf[0] = 't';
    nr1.num = id;
    nr2.num = offset;
    nr3.num = len;
    nr4.num = address;
    nr5.num = port;
    for(int i = 0; i < 4; i++)
        buf[i+1] = nr4.representation[i];
    buf[5] = nr5.representation[0];
    buf[6] = nr5.representation[1];
    for(int i = 0; i < 8; i++)
    {
        buf[i+7]  = nr1.representation[i];
        buf[i+15] = nr2.representation[i];
        buf[i+23] = nr3.representation[i];
    }
    //31 == sizeof(type)+sizeof(nr1)+..+sizeof(nr5)
    buf[31] = '\0';
}

void fill_buffer(char * buf, char type, std::uint64_t id, std::uint64_t block_len, std::uint64_t offset,
        std::uint64_t data_len, std::uint32_t address, std::uint16_t port, char * data)
{
    if (type == 'p')
        fill_buffer_for_placing(buf, id, block_len, offset, data_len, data);
    else
        fill_buffer_for_transmition(buf, id, offset, data_len, address, port);
}


void parse_buffer(const char * buf)
{
    std::uint64_t id, offset, data_len, block_len;
    std::uint32_t remote_addr;
    std::uint16_t remote_port;
    // Check the first byte in received buffer
    if (*buf == 'p')
    {
        buf++; // Skip 'p'
        id        = ((std::uint64_t *)buf)[0];
        block_len = ((std::uint64_t *)buf)[1];
        offset    = ((std::uint64_t *)buf)[2];
        data_len  = ((std::uint64_t *)buf)[3];
        char * data_ptr = (char *)(buf + sizeof(id) + sizeof(offset) + sizeof(data_len) + sizeof(block_len));
        printf("ID = %lu\nBLEN = %lu\nOFFSET = %lu\nDLEN = %lu\nDATA = %s\n", id, block_len, offset, data_len, data_ptr);
    }
    else if (*buf == 't')
    {
        buf++; // Skip 't'
        remote_addr = ((std::uint32_t *)buf)[0];
        buf += sizeof(remote_addr); // Skip "remote machine address"-bytes in buffer
        remote_port = ((std::uint16_t *)buf)[0];
        buf += sizeof(remote_port); // Skip "remote machine port"-bytes in buffer
        id        = ((std::uint64_t *)buf)[0];
        offset    = ((std::uint64_t *)buf)[1];
        data_len  = ((std::uint64_t *)buf)[2];
        printf("ID = %lu\nOFFSET = %lu\nDLEN = %lu\nADDR = %u\nPORT = %hu\n", id, offset, data_len, remote_addr, remote_port);
    }
}
