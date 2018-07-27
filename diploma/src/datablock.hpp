#pragma once

#include <cstdint>

struct datablock
{
    uint64_t id;
    uint64_t len;
    char * data;

    datablock(uint64_t id, uint64_t len);
    datablock(datablock & block);
    datablock & operator=(datablock & block);
    datablock(datablock && block);
    ~datablock();
};
