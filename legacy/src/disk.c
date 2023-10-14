#include "../include/disk.h"
#include "../include/asm.h"
#include <stdint.h>


uint8_t error = 0;

void ATAsleep(uint16_t bus, uint8_t driveType)
{
    uint8_t busy = inb(0x1F7) >> 7;
    uint8_t drq = inb(0x1F7) >> 3;
    error = 0;
    while((busy & 1) == 1  || (drq & 1) == 0) {
        if(inb(bus+ERROR_REGISTER) == 1)
        {
            error = 1;
            return;
        }
        busy = inb(0x1F7) >> 7;
        drq = inb(0x1F7) >> 3;        
    }
}

void Command(IOregisters* properties, uint16_t bus, uint8_t driveType,uint8_t command){
    if(command == IDENTIFY)
    {
    outb(bus, driveType);
    outb(bus+SECTOR_COUNT_REGISTER, 0);
    outb(bus+LBAlo,0);
    outb(bus+LBAmid, 0);
    outb(bus+LBAhi,0);
    }
    else if(command == READ_LBA48)
    {
        outb(0x40, driveType);
        outw(bus+SECTOR_COUNT_REGISTER, properties->SectorCount);
        outw(bus+LBAlo,properties->LBAlow);
        outw(bus+LBAmid, properties->LBAmiddle);
        outw(bus+LBAhi,properties->LBAhigh);
    }
    else if(command == READ_LBA28)
    {
        outb(0x1F6,driveType);
        outb(bus+SECTOR_COUNT_REGISTER,(unsigned char)(properties->SectorCount & 0xFF));
        outb(bus+LBAlo,(unsigned char)(properties->LBAlow & 0xFF));
        outb(bus+LBAmid,(unsigned char)(properties->LBAmiddle & 0xFF));
        outb(bus+LBAhi,(unsigned char)(properties->LBAhigh & 0xFF));
    }

    outb(bus+COMMAND,command);
    ATAsleep(bus,driveType);
    if(error == 1)
    {
        properties->Error = inb(bus+ERROR_REGISTER);
        return;
    }

    for(int i = 0;i < 256;i++)
    {
            properties->Data[i] = inw(PRIMARY_IO);
    }

    if(command == IDENTIFY)
    {
        properties->LBAmiddle = inb(bus+LBAmid);
        properties->LBAhigh = inb(bus+LBAhi);
    }
}
