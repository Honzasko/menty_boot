#pragma once
#include <stdint.h>
#include <uchar.h>

typedef struct {
char Signature[8];
uint32_t Revision;
uint32_t headerSize;
uint32_t headerCRC32;
uint32_t Reserved;
uint32_t MyLBALow;
uint32_t MyLBAHigh;
uint32_t AlternateLBALow;
uint32_t AlternateLBAHigh;
uint32_t FirstUsableLBALow;
uint32_t FirstUsableLBAHigh;
uint32_t LastUsableLBALow;
uint32_t LastUsableLBAHigh;
char Disk_GUID[16];
uint32_t PartitionEntryLBALow;
uint32_t PartitionEntryLBAHigh;
uint32_t NumOfPartitionEntries;
uint32_t SizeOfPartitionentry;
uint8_t zero[428];
}PartitionTableHeader;

typedef struct {
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    char data4[8];
}EFI_GUID;

typedef struct {
EFI_GUID PartitionTypeGUID;
EFI_GUID UniquePartitionGUID;
uint32_t StartingLBALow;
uint32_t StartingLBAHigh;
uint32_t EndingLBALow;
uint32_t EndingLBAHigh;
uint32_t AttributesLow;
uint32_t AttributesHigh;
char16_t PartitionName[36];
}PartitionEntry;

