#pragma once
#include <stdint.h>

#define PRIMARY_BUS 0x1F0
#define SECONDARY_BUS 0x1F0
#define DATA_REGISTER 0
#define ERROR_REGISTER 1
#define FEATURES_REGISTER 1
#define SECTOR_COUNT_REGISTER 2
#define LBAlo 3
#define LBAmid 4
#define LBAhi 5
#define DRIVE 6
#define STATUS 7
#define COMMAND 7
#define MASTER_DRIVE 0xA0
#define SLAVE_DRIVE 0xB0
#define IDENTIFY 0xEC
#define READ_LBA48 0x24
#define READ_LBA28 0x20


typedef struct {
uint16_t bus;
uint16_t dev;
uint8_t type;
uint8_t LBA48;
uint32_t MaxLBA;
}Disk;


void Identify(Disk *d,uint16_t bus,uint8_t slave);
uint8_t Read(Disk *d,uint32_t LBA,uint16_t num,uint32_t addr);