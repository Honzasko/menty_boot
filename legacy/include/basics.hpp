#include <stdint.h>
#pragma once

struct bootinfo {
    uint8_t driveNumber;
    uint16_t mmap_lenght;
    uint16_t second_length; //in 512-byte sectors
}__attribute__((packed));

namespace basics {
    int strlen(const char* text);
    int strcmp(const char* a, const char* b, int len);
}