#ifndef _HOAGS_CONFIG_H_
#define _HOAGS_CONFIG_H_
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "ble_set_id.h"
#include "section_config.h"
#include "version.h"

#define HE3_NEW_BAUDRATE 115200
#define HE3_OLD_BAUDRATE 9600

#define AWS_ANALYTICS_ENABLE            1
#define WATCHDOG_ENABLE             1

#define ENV_START_ADDR  0x00398000
#define ENV_TOTAL_SIZE  0x00007000   //28kb

#define LFSVERSIONFILE                  "version"

#define FALLBACK_CUSTNAME            "hoags"
#define FALLBACK_PRODTYPE            "na"
#define FALLBACK_PRODMODEL           "na" 

#define LOOP_HERE   	while(TRUE)                         \
                        {                                   \
                            HOAGS_ERR("In loop here\n");    \
                            vTaskDelay(5000);               \
                        }                                   \


// #define I2C_TIMEOUT                 500 //in ms

// #define HOAGS_GPIO_LED_DEMO             1
// #define GPIO_LED_RED_DEMO	            PB_4   //TA5 For Lamp-electronica:PA_28
// #define GPIO_LED_GREEN_DEMO	            PB_3   //TA4 For Lamp-electronica:PA_29
// #define GPIO_LED_BLUE_DEMO	            PB_5   //TA3 For Lamp-electronica:PA_30

// #define CPU_STAT_PRINT_FREQ             2000 
// #define HOAGS_CPU_STATS                 0
// #define HOAGS_RAM_STATS                 0
// #define HOAGS_RAM_PRINT_DELAY           2000

// #define MAX_ENV_COUNT                   256

#define PWM_CHANNEL_LED                 4
#define PWM_CHANNEL_FAN                 2
#define PWM_PIN_LED                     PA_28   //CS
#define PWM_PIN_FAN                     PA_29   //CLK
#define PWM_PERIOD_LED                  100
#define PWM_PERIOD_FAN                  100

// #define PWM_CHANNEL_HTAP_LED            2      //Htap
// #define PWM_PERIOD_HTAP_LED             100     //Htap

// #define HOAGS_AUTOMATION                0 
// #define HOAGS_DECOMPRESSION_ENABLE      1

// #define HOAGS_MIC_TWO_CHANNEL           0
// #define HOAGS_AUDIO_GAIN                1
// #define HOAGS_AUDIO_GAIN_FACTOR         1.5

// #define HOAGS_UART_DUMP                 0
// #define HOAGS_SPEEX_NR                  1

#define HOAGS_WIFI_BLE_ENABLE           1

// #define LIFESPAN_INFINITE               -1
// #define LIFESPAN_OVER                   0
// #define LIFESPAN_UPDATE_INTERVAL        3        //Suvarna: in secs

// #define UI_MAX_PIN                  6
// #define UI_MAX_PARAMS               20
// #define UI_MAP_FILE                "ui_map.bin"

// #define RTK_HDCP0                          PA_28 
// #define RTK_HDCP1                          PA_29
// #define RTK_HDCP2                          PA_30
// #define RTK_HDCP3                          PA_31
// #define RTK_UI0                            PB_2
// #define RTK_UI1                            PB_3

// #define HTAP_WW_LED                        PA_22
// #define HTAP_MINI_WW_LED                   PA_17
// #define HTAP_MODULE                         0

#ifndef HOAGS_LOG_LEVEL
#error "HOAGS_LOG_LEVEL is not defined"
#endif

#if !VIRTUALFOREST_AC && !VERSADEVICES_SUPERFAN && !VERSADEVICES_SUPERFAN_IOT && !HOAGS_DEMO_LIGHT && !AMBER_AC && !AMBER_AIRCOOLER && !HAVELLS_HANDTUNED && !RR_KABLES && !POLYCAB_FAN && !HAVELLS_AC && !VGUARD_FAN && !UNISEMI && !HINDWARE_CHIMNEY && !LIVPURE_CHIMNEY && !ATOMBERG_FAN && !LIVPURE_PURIFIER
#error "PLEASE ENABLE ANY ONE PRODUCT TYPES"
#endif

#define DO_NOTHING                      do {} while(0)

#define HOAGS_LOGGER_ERR                1
#define HOAGS_LOGGER_WARN               2
#define HOAGS_LOGGER_DBG                3
#define HOAGS_LOGGER_INFO               4

#define ENABLE_AC   1
#define ENABLE_FAN  1
#define ENABLE_LIGHT    1
#define ENABLE_AIRCOOLER    1
#define ENABLE_SENSORY      1
#define ENABLE_RECORD       1
#define ENABLE_WATCHDOG     1
#define ENABLE_CHIMNEY  1

#define ENABLE_AWSIOT_DATA_ANALYTICS    1
#define ENABLE_AWSIOT_UI_CONTROLS   1
#define ENABLE_AWSMQTT_CLOUD_CONNECT    0

#define HDCP_PAYLOAD_LEN_MAX    128

#define CMD_DETECTION_TIIMEOUT  3500

#define IMG_IMG2_OTA1_ADDR 0x800E000

struct univMacid
{
    char macid[13];
    unsigned char isFetched;
};

extern struct univMacid umObj;


#define xQUEUE_TIMEOUT		2000
//extern SemaphoreHandle_t mutexMac;

#define PREFIX_FN   "HOAGS_"
#if VIRTUALFOREST_AC
#define PREFIX_FN   "MEPL__"
#elif VERSADEVICES_SUPERFAN || VERSADEVICES_SUPERFAN_IOT
#define PREFIX_FN   "VRSA__"
#elif HAVELLS_HANDTUNED
#define PREFIX_FN	"HVLS__"
#elif POLYCAB_FAN
#define PREFIX_FN   "POLY__"
#elif AMBER_AIRCOOLER || AMBER_AC
#define PREFIX_FN   "AMBR__"
#elif RR_KABLES
#define PREFIX_FN   "RRKA__"
#elif VGUARD_FAN
#define PREFIX_FN   "VGRD__"
#elif HINDWARE_CHIMNEY
#define PREFIX_FN   "HNDW__"
#elif UNISEMI
#define PREFIX_FN   "UNSM__"
#elif ATOMBERG_FAN
#define PREFIX_FN   "ATBG__"
#elif LIVPURE_CHIMNEY || LIVPURE_PURIFIER
#define PREFIX_FN   "LVPR__"
#endif

#define HOAGS_CONFIG            1

#define HOAGS_MAN(format, ...)                                     \
    do {                                                           \
        printf("%s:%d:" format, __func__, __LINE__, ##__VA_ARGS__); \
         \
    } while (0)

#define HOAGS_MAN_RAW(format, ...)                                     \
    do {                                                                \
        printf(format, ##__VA_ARGS__);                                  \
    } while (0)

#if HOAGS_LOG_LEVEL >= HOAGS_LOGGER_ERR
#define HOAGS_ERR(format, ...)                                   \
    do {                                                           \
        printf("%s:%d:" format, __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#else
#define HOAGS_ERR(...)                  DO_NOTHING 
#endif

#if HOAGS_LOG_LEVEL >= HOAGS_LOGGER_WARN
#define HOAGS_WARN(format, ...)                                    \
    do {                                                           \
        printf("%s:%d:" format, __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#else
#define HOAGS_WARN(...)                  DO_NOTHING 
#endif

#if HOAGS_LOG_LEVEL >= HOAGS_LOGGER_DBG
#define HOAGS_DBG(format, ...)                                     \
    do {                                                           \
        printf("%s:%d:" format, __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#else
#define HOAGS_DBG(...)                  DO_NOTHING 
#endif

#if HOAGS_LOG_LEVEL >= HOAGS_LOGGER_INFO
#define HOAGS_INFO(format, ...)                                    \
    do {                                                           \
        printf("%s:%d:" format, __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#else
#define HOAGS_INFO(...)                  DO_NOTHING 
#endif

#endif 
