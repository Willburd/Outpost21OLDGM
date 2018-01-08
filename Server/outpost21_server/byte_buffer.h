#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include <iostream>
#include <string.h>
#include <cstring>

enum buffer_types {
    buffer_u8,
    buffer_u16,
    buffer_u32,

    buffer_s8,
    buffer_s16,
    buffer_s32,

    buffer_f32,
    buffer_string
};


class byte_buffer  {
    int buffer_place = 0;

    public:
    std::size_t received = 0;
    char data[255];

    unsigned int buffer_get_pos();

    void buffer_debug();

    uint8_t buffer_read_u8();
    uint16_t buffer_read_u16();
    uint32_t buffer_read_u32();
    float buffer_read_f32();
    std::string buffer_read_string();

    void buffer_write_u8(uint8_t input);
    void buffer_write_u16(uint16_t input);
    void buffer_write_u32(uint32_t input);
    void buffer_write_f32(float input);
    void buffer_write_string(std::string input);
};

#endif
