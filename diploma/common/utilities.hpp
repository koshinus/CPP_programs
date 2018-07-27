#pragma once
#include <cstdint>
#include <cstring>

typedef enum err {ALL_CORRECT, UNKNOWN_COMMAND, INCORRECT_ID, OUT_OF_MEMORY, OUT_OF_RANGE,
                  NO_DATA_RECEIVED, NO_DATA_SEND, RECEIVING_ERROR, SENDING_ERROR} ERROR;


typedef union num_representation_64
{
    uint64_t num;
    char representation[8];
} rep64;

typedef union num_representation_32
{
    uint32_t num;
    char representation[4];
} rep32;

typedef union num_representation_16
{
    uint16_t num;
    char representation[2];
} rep16;

void fill_buffer(char * buf, char type, std::uint64_t id, std::uint64_t block_len, std::uint64_t offset,
        std::uint64_t data_len, std::uint32_t address, std::uint16_t port, char * data);

void fill_buffer_for_placing(char * buf, std::uint64_t id, std::uint64_t block_len,
                             std::uint64_t offset, std::uint64_t data_len, char * data);

void fill_buffer_for_transmition(char * buf, std::uint64_t id, std::uint64_t offset,
                                 std::uint64_t len, std::uint32_t address, std::uint16_t port);

void parse_buffer(const char * buf);
