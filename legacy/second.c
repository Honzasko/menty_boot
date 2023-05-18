#include <stdint.h>
#include "include/video.h"
struct video v;

struct bootinfo {
	uint8_t driveNumber;
};

int strlen(const char* text)
{
    int len = 0;
    while(text[len] != 0) len++;
    return len;
}


void boot_Main(uint32_t ptrBootInfo)
{
	struct bootinfo info = *(struct bootinfo*)ptrBootInfo;
    v.cursor = 0;
    v.color = 0x0f;
	uint32_t n = info.driveNumber;
    print(&v, "Test\nnum:");
	print_hex(&v,n);
}
