#include <stdint.h>
#include <uchar.h>
#include "include/asm.h"
#include "include/video.h"
#include "include/disk.h"
#include "include/gpt.h"
#include "include/fat.h"
#include "include/mmap.h"

struct video v;

struct bootinfo {
    uint8_t driveNumber;
};

int strlen(const char* text) {
    int len = 0;
    while (text[len] != 0)
        len++;
    return len;
}

int strcmp(const char* a, const char* b, int len) {
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}


void boot_Main(uint32_t ptrBootInfo) {
    struct bootinfo info = *(struct bootinfo*)ptrBootInfo;
    v.cursor = 0;
    v.color = 0x0f;

    
    uint32_t n = info.driveNumber;

    print(&v, "Test\nnum:");
    print_hex(&v, n,1);
    Disk disk;
    switch (n) {
        case 0x80: Identify(&disk, PRIMARY_BUS, 0);break;
        case 0x81: Identify(&disk, PRIMARY_BUS, 1);break;
        case 0x82: Identify(&disk, SECONDARY_BUS, 0);break;
        case 0x83: Identify(&disk, SECONDARY_BUS, 1);break;
    }
    print(&v, "\nMax LBA: ");
    print_num(&v, disk.MaxLBA);
    print(&v, "\n");
    
    MMAP_entry* mmap = (MMAP_entry*)0x00000500;
    print_num(&v, mmap->Type);


}


