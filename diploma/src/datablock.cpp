#include "datablock.hpp"

datablock::datablock(uint64_t _id, uint64_t _len):
    id(_id),
    len(_len)
{
    data = new char[len];
}

datablock::datablock(datablock & other):
    id(other.id),
    len(other.len)
{
    data = new char[len];
}

datablock & datablock::operator=(datablock & other)
{
    if (this == &other)
        return *this;
    delete [] data;
    id = other.id;
    len = other.len;
    data = new char[len];
    return *this;
}

datablock::datablock(datablock && other):
    id(other.id),
    len(other.len)
{
    data = other.data;
    other.data = nullptr;
}

datablock::~datablock()
{
    delete [] data;
}
