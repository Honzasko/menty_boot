#include <stdint.h>
#include <uchar.h>
#include "include/asm.h"
#include "include/video.h"
#include "include/disk.h"
#include "include/gpt.h"
#include "include/fat.h"

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
    PartitionTableHeader gpt;
    uint8_t check =  Read(&disk, 1, 1, (uint32_t)&gpt);
    if(check != 0)
    {
        print(&v, "Failed to load Partition Header");
        HALT;
    }
    if(strcmp(gpt.Signature, "EFI PART", 8) != 1)
    {
        print(&v,"\n ");
        print_lenght(&v, gpt.Signature, 8);
        print(&v, "\n Invalid GPT");
        HALT;
    }
    print(&v, "\nDisk GUID:");
    for(int i = 0;i < 16;i++)
    {
        print_hex(&v, (uint8_t)gpt.Disk_GUID[i] & 0xFF, 0);
        if (i == 3 || i == 5 || i == 7 || i == 9) printChar(&v, '-');
    }


    uint8_t check2 =  Read(&disk, gpt.PartitionEntryLBALow, 32, (uint32_t)0x00000500);
    if(check2 != 0)
    {
        print(&v, "Failed to load Partition Entries");
        HALT;
    }

    PartitionEntry *entries = (PartitionEntry*)0x00000500;
    EFI_GUID efi;
    efi.data1 = 0xC12A7328;
    efi.data2 = 0xF81F;
    efi.data3 = 0x11D2;
    efi.data4[0] = 0xBA;
    efi.data4[1] = 0x4B;
    efi.data4[2] = 0x00;
    efi.data4[3] = 0xA0;
    efi.data4[4] = 0xC9;
    efi.data4[5] = 0x3E;
    efi.data4[6] = 0xC9;
    efi.data4[7] = 0x3B;

uint32_t efi_partition = 0;
uint8_t  efi_partition_found = 0;

for(uint32_t i = 0;i < gpt.NumOfPartitionEntries;i++)
{

    if(efi.data1 == entries[i].PartitionTypeGUID.data1 && efi.data2 == entries[i].PartitionTypeGUID.data2 && efi.data3 == entries[i].PartitionTypeGUID.data3 && strcmp(efi.data4, entries[i].PartitionTypeGUID.data4, 8))
    {
        
        efi_partition_found = 1;
        break;
    }
    efi_partition++; 
}
if(efi_partition_found != 1)
{
    print(&v, "\nEfi partition not found");
    HALT;
}

uint32_t LBAefi = entries[efi_partition].StartingLBALow;
print(&v, "\nLBA EFI Start:");
print_num(&v, LBAefi);


BPB_FAT32 bpb;

uint8_t check3 = Read(&disk, LBAefi, 1, (uint32_t)&bpb);
if(check3 != 0)
{
    print(&v, "\nFailed to load BIOS Parameter Block\nAta error code:");
    print_hex(&v, check3,1);
    HALT;
}

print(&v, "\n ");
print_num(&v,bpb.base.OEMIdentifier[0]);

}


