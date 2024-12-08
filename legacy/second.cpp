#include <cstdint>
#include <stdint.h>
#include "include/video.hpp"
#include "include/disk.hpp"
#include "include/memory.hpp"
#include "include/basics.hpp"

struct video_info v;



extern "C" void boot_Main(uint32_t ptrBootInfo) {
    bootinfo *inf = reinterpret_cast<struct bootinfo*>(ptrBootInfo);
    bootinfo info = *inf;
    v.cursor = 0;
    v.color = 0x0f;

    
    uint32_t n = info.driveNumber;

    video::print(&v, "Test\nnum:");
    video::print_hex(&v, n,1);
    video::print(&v, "\n");
    Disk disk;
    switch (n) {
        case 0x80: ATA::Identify(&disk, PRIMARY_BUS, 0);break;
        case 0x81: ATA::Identify(&disk, PRIMARY_BUS, 1);break;
        case 0x82: ATA::Identify(&disk, SECONDARY_BUS, 0);break;
        case 0x83: ATA::Identify(&disk, SECONDARY_BUS, 1);break;
    }
    if (disk.available) {
            video::print(&v, "Max LBA: ");
            video::print_num(&v, disk.MaxLBA);
            video::print(&v, "\n");
    }
    
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


