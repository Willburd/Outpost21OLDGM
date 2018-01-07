#include "byte_buffer.h"

void byte_buffer::buffer_debug() {
    //transmit debug?
    std::cout << "sizeof: " << (int)received << std::endl;
    std::cout << "Numbs: ";
    for(unsigned int i = 0; i < 20; i++) {
         std::cout << (int)data[i] << ",";
    }
    std::cout << std::endl;

    std::cout << "Chars: ";
    for(unsigned int i = 0; i < 20; i++) {
         std::cout << data[i] << ",";
    }
    std::cout << std::endl;
}


unsigned int byte_buffer::buffer_get_pos() {
    return buffer_place;
}


uint8_t  byte_buffer::buffer_read_u8() {
    return data[buffer_place];
    buffer_place += 1;
}

uint16_t byte_buffer::buffer_read_u16() {
    uint16_t collected;

    char b[] = {data[buffer_place],data[buffer_place+1]};
    memcpy(&collected, &b, 2);
    return collected;

    buffer_place += 2;
}

uint32_t byte_buffer::buffer_read_u32() {
    uint32_t collected;

    char b[] = {data[buffer_place],data[buffer_place+1],data[buffer_place+2],data[buffer_place+3]};
    memcpy(&collected, &b, 4);
    return collected;

    buffer_place += 4;
}

float byte_buffer::buffer_read_f32() {
    float collected;

    char b[] = {data[buffer_place],data[buffer_place+1],data[buffer_place+2],data[buffer_place+3]};
    memcpy(&collected, &b, 4);
    return collected;

    buffer_place += 4;
}


std::string byte_buffer::buffer_read_string() {
    std::string wip_string = "";
    std::cout << "ripping char: " << data[buffer_place] << std::endl;
    std::cout << "buffer pos: " << buffer_place << std::endl;

    while(data[buffer_place] != 0) {
        char get_char = data[buffer_place];
        std::cout << "ripping char: " << get_char << std::endl;
        wip_string += get_char;
        buffer_place += 1;
    }
    return wip_string;
}



void  byte_buffer::buffer_write_u8(uint8_t input) {
    data[buffer_place] = input;
    buffer_place += 1;
}

void byte_buffer::buffer_write_u16(uint16_t input) {
    data[buffer_place  ] = (char)(input & 0xFF);
    data[buffer_place+1] = (char)((input >> 8) & 0xFF);
    buffer_place += 2;
}

void byte_buffer::buffer_write_u32(uint32_t input) {
    data[buffer_place] = (char)(input & 0xFF);
    data[buffer_place+1] = (char)((input >> 8) & 0xFF);
    data[buffer_place+2] = (char)((input >> 16) & 0xFF);
    data[buffer_place+3] = (char)((input >> 24) & 0xFF);
    buffer_place += 4;
}

void byte_buffer::buffer_write_f32(float input) {
    unsigned char c[ 4];
    std::memcpy(c, &input, 4);

    data[buffer_place  ] = c[0];
    data[buffer_place+1] = c[1];
    data[buffer_place+2] = c[2];
    data[buffer_place+3] = c[3];
    buffer_place += 4;
}

