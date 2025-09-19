#ifndef PURIFIER_H
#define PURIFIER_H
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sntp/sntp.h>
#include "env.h"
#include "device_controls/purifier/include/remoteDiag.h"
#include "flashWritePurifier.h"

#define PERIODIC_DATA_TAG "0005"
#define DATETAG "0001"
#define WCTAG "0002"
#define ALARM_TAG "0003"
#define FILTER_CLEAN "0004"

#define WARM_WATER_MIN_RANGE 30
#define WARM_WATER_MAX_RANGE 50

#define HOT_WATER_MIN_RANGE 55
#define HOT_WATER_MAX_RANGE 85

#define START_BYTE 0x1A
#define STOP_BYTE 0x2A

uint16_t calculate_checksum(const struct hdcpRd *blePkt, const size_t size);
void waterControl(const char* payload, const size_t len,int levelIndex);
// void initiateRemoteDiag(Source src);
uint8_t hexToInt(const char *hexStr);
// void sendTemperatureToReneses(Source src);
void setTemperature(const char* payload, const size_t len);
// void initiateDeviceAnalysis(Source src);

#endif