#ifndef __BLE_PACKETS_H__
#define __BLE_PACKETS_H__

#include "hoags_config.h"
#include <stdint.h>
// #include "fan.h"
// #include "light.h"
// #include "ac.h"
// #include "mic.h"


typedef enum {
    BLE_SUCCESS,
    BLE_FAILURE
} error_code_e;

enum ACTION {

	OTA_BIN = 100,
	/*rehan : begin changes*/
	//for device credentials
	DEV_NAME = 103,
	DEV_PASS,
	DEV_USERID,	
	ALEXA_AUTH_TOKEN,
	PRODUCT_ID,
	REBOOT,
	FACTORY_RESET,
	MODEL_RESET,
	DEV_TO_MCU_INFO,
	MCU_TO_DEV_INFO,

#if 	VIRTUALFOREST_AC
	VIRTUALFOREST_TX,
#endif

	STATUS_DATA = 500,	//UDT app request for device status
	PING = 501,
	DIAG_START,
	DIAG_STOP,
	DEV_TYPE,
	DEV_LOCATION,

	BLE_PASSWORD = 600,       // for ble password implementation

	WIFI_CONFIG = 700,
	MACID_SET,
	OTA_BOOT_BIN = 702,  //shaik: for ota boot

	SCHEDULER = 800,

	//for device controls
	DEV_JSON = 1000,
	FAN_CTRL,
	LIGHT_CTRL,
	AC_CTRL,
	AIRCOOLER_CTRL = 1004,
	CHIMNEY_CTRL,
	PURIFIER_CTRL,
	DEV_SERIAL_NO,
	/*rehan : end chagnes*/
    DEFAULT = 65535
};

struct file_info_t {
    uint16_t action;
    char *filename;
    uint8_t* fileBuffer;
    uint8_t* fbPos;
    uint32_t checksum;
    uint32_t total_size;
    uint32_t end_seq;
    uint32_t prev_seq_no;
    uint32_t params;
    uint8_t append;
	uint8_t* pDecompressBuf;
    struct file_info_t *pNext;
};


struct wifiConnect {
	char ssid[32];
	char password[32];
};


struct ble_passkey
{
	char app_input_passkey[5];	        //input from app  
	char stored_passkey[5];             // storing pass key             
};

enum WIFI_CMD_MODE {
    WIFI_CMD_MODE_SCANLIST,     //0
    WIFI_CMD_MODE_CONNECT,      //1
    WIFI_CMD_MODE_DISCONNECT    //2
};

enum BLE_PASS_MODE{
	FIRST_CONNECTION,
	SET_NEW_PASSWORD,
	NOT_FIRST_CONNECTION
};


enum notifyType {
	STATUS_FLAG,
	DIAG_FLAG,
	POLLACK_FLAG,
	SSID_LIST,
	CONNECTION_STATUS,
	SCAN_STATUS,

	EVENT_SCHEDULE,
	NOTIFICATION,	
	BLE_PASSKEY_STATUS
};


enum DEV_CMD_STATE {
    WAKEWORD_DETECTED,  //Wakeword is detected
    COMMAND_DETECTED,   //LED off
    COMMAND_NOT_DETECTED, // LED off
    SOMETHING_IS_WRONG,	//fast blink
    OTA_OR_MODEL_TRANSFER,	// No indication
    MIC_MUTED,	// LED on 
    WIFI_DISCONNECTED,	// No indication
    SETUP_IN_ACTION,	// slow breathe
    WIFI_OR_BLE_CONNECTED,	// No indication
};

enum CONNECTIONnotifyType{
	CONNECTION_FAILED,
	CONNECTION_SUCESS,
	CONNECTION_DUPLICATE
};

enum BLEPASSKEYnotifyType{
	INITIAL_BLE_SUCCESS,
	INITIAL_BLE_FAILED,
	PASSKEY_MATCHES,
	PASSKEY_NOT_MATCHES,
	PASSWORD_SUCCESS,
	PASSWORD_FAILED,
	PASSWORD_INVALID
};

enum OTA_BOOTnotifyType {
	OTA_BOOT_ERASING,
	OTA_BOOT_WRITING,
	OTA_BOOT_SUCCESS,
	OTA_BOOT_FAILED,
	OTA_BOOT_REBOOT
};

enum OTAnotifyType {
	OTA_ERASING,
	OTA_WRITING,
	OTA_SUCCESS,
	OTA_FAILED,
	OTA_REBOOT
};

enum DEVICE_TYPE {
	NO_DEVICE,
	FAN,
	LIGHT,
	AC
};

enum PAYLOAD_UI_INTENSITY {
	POW_OFF,	//0
	POW_ON,		//1
	LOW,		//10
	LOW_MEDIUM, //20
	MEDIUM,		//50
	MEDIUM_HIGH, //70
	HIGH		//100
};

enum PAYLOAD_UI_COLOR {
	NO_COLOR,
	RED,
	GREEN,
	BLUE 
};

enum CAPABILITY {
    CAP_NONE,   //BLE + LocalVoice + OTA
    CAP_WIFI,   //BLE + LocalVoice + OTA + WiFi(Network setup)
    CAP_CLOUD,  //BLE + LocalVoice + OTA + WiFi(Network setup) + Cloud Config
    CAP_WWA     //BLE + LocalVoice + OTA + WiFi(Network setup) + Cloud Config + WWA + WWG
};


struct dev_info {
	enum DEVICE_TYPE dev;
	enum PAYLOAD_UI_INTENSITY intensity;
	enum PAYLOAD_UI_COLOR color;
}__attribute__((packed));

//Suvarna: Response packets
struct hdcpr
{
	unsigned short majorVersion;
	unsigned short minorVersion;
	char custName[16];
	char prodModel[16];
	char prodType[16];
	char friendlyName[16];
	short micStatus;
	short powerControl;
	short modeControl;
	short speedControl;
	short tempControl;
	short airCoolerModeValue;
	unsigned int lfsSize;
	char ssid[16];
	uint16_t capability;
	char mac_id[13];
	short ledControl;
	short buzControl;
	short revControl;
	char stored_passkey[4];
	char serialNo[20];
}__attribute__((packed));

struct hdcp {
    uint8_t header;         //eg,. ff
    uint16_t action;        
    uint16_t len;           // eg,. 128
    uint16_t seq_num;       // eg,. 1,2,3...
    uint32_t checksum;      // crc

	uint8_t	total_level;
	uint8_t level[5];

	uint32_t total_size;
	uint32_t params;		//miscellenous use, for example., original binary size before compression
	uint8_t payload[128];

} __attribute__((packed));

struct meta_data {
	struct hdcp *cp;
	unsigned char* fileBuffer;
	char* filename;
	uint8_t* fbPos;
    uint32_t bufferFillSize;  //shaik:
	size_t prev_seq_no;
	size_t end_seq;
	uint8_t append;
	uint8_t resetFlag;
	uint32_t flashAddress; //shaik: store ota flashAddress
	
}__attribute__((packed));

enum HOAGS_BLE_RESP
{
	ALL_FINE,
	PACKET_MISSED,
	INTEGRITY_FAILED,
	WRITE_ERROR,
	UNKNOWN_ERROR,
};


// struct device {
// 	enum ACTION type;
// 	union {
// 		struct devFanStruct f;
// 		struct devLightStruct l;
// 		struct devLightFanStruct fl;
// 		struct devACStruct a;
// 	} devstruct;
// };

struct all_dev_info {
	struct dev_info dev1;
	struct dev_info dev2;
	
}__attribute__((packed));



void unpack(uint8_t* buffer);
// void unpackPayload(uint8_t* payload);
// void pack();
//void print();

void resetMetaData();
void initMetaData();

void init();

void initBuffer();
void fillBuffer();
void deserialize();

void HoagsOTA();

void wifiAction();

void action(void);
void ble_device_disconnected ();

#endif //__BLE_PACKETS_H__


