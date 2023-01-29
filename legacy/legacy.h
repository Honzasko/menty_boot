#pragma once
#include <stdint.h>

typedef struct _registers {
    uint16_t ax,bx,cx,dx,di,si;
}Registers;

Registers bios(uint16_t function,Registers arguments);