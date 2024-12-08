#include <cstdint>
#include <stdint.h>
#pragma once
typedef struct{
    uint32_t BaseAdress_Low;
    uint32_t BaseAdress_High;
    uint32_t Lenght_Low;
    uint32_t Lenght_High;
    uint32_t Type;
    uint32_t ACPI;
}__attribute__((packed)) MMAP_entry;

namespace memory {
    typedef struct {
        uint32_t start;
        uint32_t length;
        uint32_t free;
        uint32_t next;
    }block;

    void init(uint32_t bootinfo,uint32_t mmap,uint32_t mmap_length);
    uint32_t malloc(uint32_t size);
    void free(uint32_t addr);
}