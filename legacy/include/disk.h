#pragma once
#include <cstdint>
#include <stdint.h>

struct BPB_fat32 {
uint16_t  jmp1;
char jmp2;
uint32_t OEMidentfier_1;
uint32_t OEMidentfier_2;
uint16_t BytesPerSector; 
uint8_t SectorsPerCluster;
uint16_t ReservedSectors;
uint8_t numOfFATs;
uint16_t numOfRootDirEntries;
uint16_t totalSectors;
uint16_t MediaDescriptor;
uint16_t numSecsPerFat;
uint16_t numSecsPerTrack;
uint16_t numHeads;
uint32_t numOfHiddenSectors;
uint32_t LargeSectorCount;
uint32_t SectorsPerFat;
uint16_t flags;
uint16_t FATVersion;
uint32_t clusterNumOfroot;
uint8_t driveNumber;
uint16_t FSINFO_secnum;
uint16_t    BackUpBootSectors;
uint32_t    Reserved1;
uint32_t Reserved2;
uint32_t Reserved3;
uint8_t flagNT;
uint8_t signature;
uint32_t VolumeID;
char VolumeLabelString[8];
};