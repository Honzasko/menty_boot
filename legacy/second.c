#include <stdint.h>
#include "include/video.h"
#include "include/disk.h"

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


void boot_Main(uint32_t ptrBootInfo) {
    struct bootinfo info = *(struct bootinfo*)ptrBootInfo;
    v.cursor = 0;
    v.color = 0x0f;

    
    uint32_t n = info.driveNumber;

    print(&v, "Test\nnum:");
    print_hex(&v, n);
    print(&v, "\nDrive: ");
    IOregisters properties;
    print(&v, "Primary Master");
    Command(&properties,PRIMARY_IO,MASTER_DRIVE,IDENTIFY);
    uint16_t lba48 = (properties.Data[83] >> 10) & 1;
    uint32_t sectorCount = 0;
    uint8_t cl = properties.LBAmiddle;
    uint8_t ch = properties.LBAhigh;
    print(&v, "\nDevice type: ");
    if(cl == 0x14 && ch == 0xEB) print( &v, "PATAPI");
    else if(cl == 0x69 && ch == 0x96) print( &v, "SATAPI");
    else if(cl == 0 && ch == 0) print( &v, "PATA");
    else if(cl == 0x3c && ch == 0xc3) print( &v, "SATA");


    if(lba48 == 1){
        print(&v, "\nLBA48 mode is supported");
        sectorCount = (uint32_t)properties.Data[100] | (uint32_t)properties.Data[101] << 16;
    }
    else {
        print(&v, "\nLBA48 mode is not supported");
        sectorCount = (uint32_t)properties.Data[60] | (uint32_t)properties.Data[61] << 16;
    }
    print(&v, "\nSector count: ");
    print_num(&v, sectorCount);

    IOregisters read;

    uint32_t LBA = 52;
    read.SectorCount = 1;
    if(lba48 != 1)
    {
        read.LBAlow = LBA & 0xFF;
        read.LBAmiddle = (LBA >> 8) & 0xFF;
        read.LBAhigh = (LBA >> 16) & 0xFF;
        Command(&read,PRIMARY_IO,0xE0 ,READ_LBA28);
    }
    else {
                read.LBAlow = LBA & 0xFFFF;
                read.LBAmiddle = (LBA >> 16) & 0xFFFF;
                Command(&read,PRIMARY_IO,0x40 ,READ_LBA48);
    }
    uint32_t err = read.Error;
        if(err == 0)
        {
            print(&v, "\nSector text:");
            print(&v, (const char*)&read.Data);
        }
        else {
                    print(&v, "\nDisk operation error: ");
                    switch (err) {
                        case 1: print(&v,"Adress mark not found");break;
                        case 2: print(&v,"Track zero not found");break;
                        case 4: print(&v, "Aborted");break;
                        case 8: print(&v, "Media change request");break;
                        case 16: print(&v, "ID not found");break;
                        case 32: print(&v, "Media changed");break;
                        case 64: print(&v,"Uncorrectable data error");break;
                        case 128: print(&v,"Bad Block detected");break;
                    }
        }
}
