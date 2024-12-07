#include <stdint.h>
#include <uchar.h>
#include "include/asm.hpp"
#include "include/video.hpp"
#include "include/disk.hpp"
#include "include/gpt.hpp"
#include "include/fat.hpp"
#include "include/mmap.hpp"

struct video_info v;

struct bootinfo {
    uint8_t driveNumber;
    uint16_t mmap_lenght;
}__attribute__((packed));

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


extern "C" void boot_Main(uint32_t ptrBootInfo) {
    struct bootinfo info = *(struct bootinfo*)ptrBootInfo;
    v.cursor = 0;
    v.color = 0x0f;

    
    uint32_t n = info.driveNumber;

    video::print(&v, "Test\nnum:");
    video::print_hex(&v, n,1);
    Disk disk;
    switch (n) {
        case 0x80: Identify(&disk, PRIMARY_BUS, 0);break;
        case 0x81: Identify(&disk, PRIMARY_BUS, 1);break;
        case 0x82: Identify(&disk, SECONDARY_BUS, 0);break;
        case 0x83: Identify(&disk, SECONDARY_BUS, 1);break;
    }
    video::print(&v, "\nMax LBA: ");
    video::print_num(&v, disk.MaxLBA);
    video::print(&v, "\n");
    
    MMAP_entry* mmap = (MMAP_entry*)(0x0000510);
    for (uint16_t i = 0; i < info.mmap_lenght;i++) {
        video::print(&v, "Base: ");
        video::print_hex(&v, mmap[i].BaseAdress_Low, 1);
        video::print(&v, " Length: ");
        video::print_hex(&v, mmap[i].Lenght_Low, 1);
        video::print(&v, " Type: ");
        switch (mmap[i].Type) {
            case 1: video::print(&v, " Available");break;
            case 2: video::print(&v, " Reserved");break;
            case 3: video::print(&v, " ACPI");break;
            case 4: video::print(&v, " ACPI NVS");break;
        }
        video::print(&v, "\n");
    }
    

}


