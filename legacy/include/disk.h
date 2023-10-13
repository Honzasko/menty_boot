#pragma once
#include <stdint.h>

#define TYPE_MASTER 1
#define TYPE_SLAVE 2
#define PRIMARY_BUS 0x1F6
#define PRIMARY_IO 0x1F0
#define DATA_REGISTER 0
#define ERROR_REGISTER 1
#define FEATURES_REGISTER 1
#define SECTOR_COUNT_REGISTER 2
#define LBAlo 3
#define LBAmid 4
#define LBAhi 5
#define COMMAND 7
#define MASTER_DRIVE 0xA0
#define IDENTIFY 0xEC
#define READ_LBA48 0x24
#define READ_LBA28 0x20

typedef struct {
uint16_t Data[256];
uint16_t Error;
uint16_t Features;
uint16_t SectorCount;
uint16_t LBAlow;
uint16_t LBAmiddle;
uint16_t LBAhigh;
uint8_t  Drive;
uint8_t Status;
uint8_t Command;
uint8_t DriveType;
}IOregisters;


void Command(IOregisters* properties, uint16_t bus, uint8_t driveType,uint8_t command);