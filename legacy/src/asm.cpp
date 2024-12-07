#include "../include/asm.hpp"
#include <stdint.h>

void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

uint16_t inw(uint16_t port) {
    uint16_t data;
    asm volatile ("inw %1, %0" : "=a" (data) : "d" (port));
    return data;
}

void outw(unsigned short port, unsigned short data) {
    asm volatile ("outw %0, %1" : : "a"(data), "Nd"(port));
}

void io_wait()
{
    outb(0x80, 0);
}