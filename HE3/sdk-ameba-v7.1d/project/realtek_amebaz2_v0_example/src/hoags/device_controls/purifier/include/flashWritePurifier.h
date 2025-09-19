#ifndef FLASH_WRITE_PURIFIER_H
#define FLASH_WRITE_PURIFIER_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "device_lock.h"
#include "FreeRTOS.h"
#include "hoags_config.h"
#include "cloudConnect.h"
#include "remoteDiag.h"

#define FLASH_PARTITION_SIZE    (4 * 1024)
#define TOTAL_DAYS_COUNT   15
#define TRUE 1
#define FALSE 0

#define RESET_TIME_INTERVEL 4 // time in minutes
#define LITRE_WISE_STORING  10 //10 means 1 litre

#define WC_FLASH_START_ADDRESS 0x0039F000 //allocated 216 kb size + 8kb for total water consumption

typedef enum {
    HOAGS_SUCCESS,
    HOAGS_FAILURE
}eHoagsError;

typedef struct flash_inc_data_ {
    char isFree;
    char unusable;
    uint16_t *pStartAddress;
    uint16_t *pEndAddress;
    uint16_t *pCurrentAddress;
    uint32_t date;
    uint16_t currentValue;
} flash_data_info;


#define WATER_CONSUMPTION_CLOUD_SEND_INTERVEL 10 * 2

void makeCloudPeriodicPacket(unsigned char packet[],uint16_t cloudWc, uint16_t alarmValue, uint8_t filterLife);

#define SECTOR1_BASE_ADDR       0x3D5000
#define SECTOR2_BASE_ADDR       (SECTOR1_BASE_ADDR + FLASH_PARTITION_SIZE)

#define SECTOR_MARKER_USED      0xFAFA
#define SECTOR_MARKER_FREE      0xFBFB

typedef struct{
    uint16_t *pStartAddress;
    uint16_t *pEndAddress;
    uint16_t *pCurrentAddress;
    uint16_t currentValue;
} totalWcStruct;

void storeTotalWaterConsumption(uint16_t newValue);

#endif