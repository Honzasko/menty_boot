#include "../include/disk.h"
#include "../include/asm.h"
#include <stdint.h>


uint8_t error = 0;

void ATAsleep(uint16_t bus)
{
    uint8_t busy = inb(bus+STATUS) >> 7;
    uint8_t drq = inb(bus+STATUS) >> 3;
    error = 0;
    //waiting for drive to be ready for  data
    while((busy & 1) == 1  || (drq & 1) == 0) {
        if(inb(bus+ERROR_REGISTER) == 1)
        {
            //error detected,return from function
            error = 1;
            return;
        }
        busy = inb(0x1F7) >> 7;
        drq = inb(0x1F7) >> 3;        
    }
}

void Identify(Disk *d,uint16_t bus,uint8_t slave)
{
    //tell the bus if is used master or slave
    if(slave == 1)
    {
        outb(bus+DRIVE,SLAVE_DRIVE);
        d->dev = SLAVE_DRIVE;
    }
    else {
        outb(bus+DRIVE, MASTER_DRIVE);
        d->dev = MASTER_DRIVE;
    }
    //setting up registers
    outb(bus+SECTOR_COUNT_REGISTER,0);
    outb(bus+LBAlo,0);
    outb(bus+LBAmid, 0);
    outb(bus+LBAhi,0);
    outb(bus+COMMAND, IDENTIFY);
    //identifying drive
    uint16_t data[256];
    for(int i = 0;i < 256;i++)
    {
            data[i] = inw(bus+DATA_REGISTER);
    }
    d->bus = bus;

    //the 10th bit of 83th uint16 in returned identify data set if LBA48 is supported or not and then get max lba from right place
    d->LBA48 = (data[83] >> 10) & 1;
    if(d->LBA48 == 1)
    {
            d->MaxLBA = (uint64_t)data[100] | (uint64_t)data[101] << 16 | (uint64_t)data[102] << 32 | (uint64_t)data[103] << 48;
    }
    else {
            d->MaxLBA = (uint64_t )data[60] | (uint64_t)data[61] << 16;
    }

}

uint8_t Read(Disk *d,uint32_t LBA,uint16_t num,uint32_t addr)
{
    //check if LBA48 is supported,if yes it will use LBA48 mode otherwise it will use LBA28 mode
    if(d->LBA48 == 1)
    {
        if(d->dev == MASTER_DRIVE)
        {
            outb(d->bus+DRIVE,0x40);
        }
        else {
            outb(d->bus+DRIVE,0x50);
        }
        uint16_t LBAmiddle =   (uint16_t)(LBA<< 16) & 0xFFFF;
        outw(d->bus+SECTOR_COUNT_REGISTER, num);
        outw(d->bus+LBAlo,(uint16_t)LBA & 0xFFFF);
        if(LBAmiddle > 0) outw(d->bus+LBAmid,LBAmiddle);
        outb(d->bus+COMMAND,READ_LBA48);
    }
    else {
        if(d->dev == MASTER_DRIVE)
        {
            outb(d->bus+DRIVE,0xE0);
        }
        else {
            outb(d->bus+DRIVE,0xF0);
        }
        outw(d->bus+SECTOR_COUNT_REGISTER, num);
        outb(d->bus+LBAlo,(uint8_t)LBA & 0xFF);
        outw(d->bus+LBAmid,(uint8_t)(LBA << 8) & 0xFF);
        outw(d->bus+LBAhi, (uint8_t)(LBA << 16) & 0xFF);
        outb(d->bus+COMMAND,READ_LBA28);
    }
    //wait until drive is ready to send data and check for error
    ATAsleep(d->bus);
    if(error == 1)
    {
        return inb(d->bus+ERROR_REGISTER);
    }

    //return the data
    //the driver count that the user has drive with 512 bytes sector size
    uint16_t *data = (uint16_t*)addr;
    for(int i = 0; i < (256*num);i++)
    {
        data[i] = inw(d->bus+DATA_REGISTER);
    }

    return 0;
}