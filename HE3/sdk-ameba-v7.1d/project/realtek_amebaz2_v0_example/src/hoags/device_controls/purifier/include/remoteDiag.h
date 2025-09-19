#ifndef REMOTE_DIAG_H
#define REMOTE_DIAG_H

#include <stdbool.h>
#include <stdio.h>
#include "objects.h"
#include "hoags_config.h"
#include "packets.h"
#include "purifier.h"
#include "cloudConnect.h"
#include "LED.h"

//Reneses info
#define TOTAL_ROW_SIZE 2522
#define COLUMN_SIZE 132
unsigned char xmodem_data[1][COLUMN_SIZE];
#define RENESAS_VERSION_NUMBER "0.00.00.24"

#define HE3_IMAGE_SIZE 0x145000 //1300KB

#define MAX_RETRY_LIMIT 3

#define DEFAULT_BOTTLE_WATER_CUST 35
#define DEFAULT_GLASS_WATER_CUST 10

#define CONTROL_HEADER 0XDD
#define RD_REQ_HEADER 0xFA

#define CTRL_ACK_HEADER 0xAC
#define RD_RES_HEADER 0xFB

#define RENESAS_UPGRADE_ACK 0x06
#define RENESAS_UPGRADE_NACK 0x15
#define FINAL_ACK 0x06
#define SUCCESS 0
#define FAIL -1


enum WP_CMD {
    WP_CMD_POWER_CONTROL,
	WP_CMD_NORMAL_CONTROL,
	WP_CMD_HOT_CONTROL,
	WP_CMD_WARM_CONTROL,
    WP_CMD_REMOTE_DIAG,
    WP_CMD_SET_TEMPERATURE,
    WP_CMD_DEVICE_ANALYSIS,
    WP_CMD_PERIODIC_DATA,
    WP_CMD_DATETIME_SET,
    WP_CMD_FILTER_RESET,
    WP_CMD_FILTER_SETTING_VIA_TIME,
    WP_CMD_FILTER_SETTING_VIA_WATER,
    WP_CMD_INLET_TDS_SETTING,
    WP_CMD_RESET_WATER_CONSUMPTION = 50
};

enum WP_CMD_FILTER_SETTING_CONTROL {
    WP_CARBON = 1,
    WP_SEDIMENTARY,
    WP_RO,
    WP_ALKALINE,
    WP_MINERAL,
    WP_COPPER
};



enum WP_CMD_FILTER_RESET_CONTROL {
    WP_NO_RESET,
    WP_OVERALL_FILTER_RESET,
    WP_SEDIMENTARY_FILTER_RESET,
    WP_RO_FILTER_RESET,
    WP_ALKALINE_FILTER,
    WP_MINERAL_FILTER,
    WP_COPPER_FILTER
};

enum WP_CMD_WATER_CONTROL {
    WP_WATER_ON,
    WP_WATER_OFF
};

enum controlRenesas {
    ALL_OPS_DISABLED = 0,
    NORMAL_WATER_ON,
    WARM_WATER_ON,
    HOT_WATER_ON,
};

enum remoteDiagnostics{
    RD_START = 1,
};

enum deviceAnalysis{
    START_ANALYSIS= 1,
};


enum actionTags{
    CONTROL_TAG = 1,
    DIAGNOSTICS_TAG
};

// Define the states for the state machine
typedef enum {
    SM_MCU_IFC_IDLE,
    SM_MCU_IFC_CONTROL_REPLY_WAIT,
    SM_MCU_IFC_DIAG_START_WAIT,
    SM_MCU_IFC_DIAG_RESP_WAIT,
    SM_MCU_IFC_RENESAS_UPDATE_WAIT,
    SM_MCU_IFC_RENESAS_BOOT_ACK_WAIT,
} State;




typedef enum {
    SOURCE_APP,
    SOURCE_CLOUD,
    SOURCE_MCU,
    SOURCE_TIMER,
    SOURCE_REQUEST,
    SOURCE_RENESASUPDATE,
    SOURCE_ACKWAIT
} Source;

typedef enum {
    REMOTE_CONTROL,
    DIAGNOSTICS_CONTROL,
    TIMER_EXPIRED,
    MCU_MSG,
    MCU_UPDATE,
    BOOTLOADER
} MessageId;

struct hdcpRd {
    uint8_t header;
    uint16_t len;
    uint16_t checksum;
    uint16_t seq_num;
    uint16_t last_seq_num;
    uint8_t payload[128];
} __attribute__((packed));

typedef struct {
    Source msgSource;
    MessageId msgId;
    struct hdcpRd msgPayload;
} sControlMessage;

// Structure to manage the state machine
typedef struct {
    State current_state; // Current state
    int source; 
    int retry_count;       // Retry count for transitions
    bool ack_received;     // Flag to check if ack is received
    int expected_seq;      // Expected sequence number for the diagnostic responses
    int timer;             // Timer for state transitions
    sControlMessage lastMessage;
    int diag_command_index;
    char diagResponse[(sizeof(xmodem_data) / sizeof(xmodem_data[0]))][sizeof(xmodem_data[0])];
} state_machine_t;

QueueHandle_t getPurifierQueueDataHandle();
void sendDataToApp(char Data[],int flag);
void payloadToString(uint8_t payload[],char strData[],int payloadLen);
#endif // STATE_MACHINE_H
