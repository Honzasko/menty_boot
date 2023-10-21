#pragma once
#include <stdint.h>

typedef struct {
uint8_t jmpnop[3];
uint8_t OEMIdentifier[8];
uint16_t BytesPerSector;
uint8_t SectorsPerCluster;
uint16_t NumberOfReservedSectors;
uint8_t NumberOfFATs;
uint16_t NumberOfRootDirectories;
uint16_t TotalSectors;
uint8_t Media;
uint16_t Reserved;
uint16_t SectorsPerTrack;
uint16_t NumberOfHeads;
uint32_t HiddenSectors;
uint32_t LargeSectorCount;
}BPB;

typedef struct {
BPB base;
uint32_t SectorsPerFat;
uint16_t Flags;
uint16_t Version;
uint32_t ClusterNumberRootDir;
uint32_t SectorNumberFSInfo;
uint32_t SectorNumberBackupBootSector;
uint8_t Reserved[12];
uint8_t DriveNumber;
uint8_t Reserved2;
uint8_t Signature;
uint32_t VolumeID;
uint8_t VolumeLabel[11];
uint8_t SystemIdentifier[8]; //Specs says never trust
uint8_t zero[421];
}BPB_FAT32;

typedef struct {
uint32_t LeadSignature;
uint8_t Reserved[480];
uint32_t AnotherSignature;
uint32_t LastKnowfreeClustersCount;
uint32_t StartAvaibleClusterNumber;
uint8_t Reserved2[12];
uint32_t TrailSignature;
}FSInfo;