#ifndef __HOAGS_DATA_COLLECTOR_H__
#define __HOAGS_DATA_COLLECTOR_H__

#include "hoags_config.h"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

//Online-Offline Status
#define REGISTER_CUSTNAME    "custname"
#define REGISTER_PRODTYPE    "prodtype"
#define REGISTER_MACID       "macid"
#define REGISTER_USERID      "userid"
#define REGISTER_FRIENDLYNAME "friendlyname"

//Static Data
#define STATIC  "static"
#define STATIC_MACID           "macid"
#define STATIC_PRODUCT_TYPE    "prodtype"
#define STATIC_PRODUCT_MODEL    "prodmodel"
#define STATIC_CUST_NAME       "custname"
#define STATIC_VERSION      "fwversion"

//Dynamic Data
#define DYNAMIC                     "dynamic"
#define DYNAMIC_CPU                 "cpu"
#define DYNAMIC_CPU_TEMP            "temp"
#define DYNAMIC_CPU_USAGE           "usage"
#define DYNAMIC_MEMORY              "memory"
#define DYNAMIC_MEMORY_USAGE        "usage"
#define DYNAMIC_FILESYSTEM          "filesystem"
#define DYNAMIC_FILESYSTEM_USAGE    "usage"
#define DYNAMIC_LOCATION            "location"
#define DYNAMIC_UPTIME              "uptime"
#define DYNAMIC_LASTUPDATE          "lastupdate"
#define DYNAMIC_CYCLES              "cycles"

#define DYNAMIC_MODE                "mode"
#define DYNAMIC_MODE_SET           "set" //index 5
#define DYNAMIC_MODE_TEMP           "temp" //index 6
#define DYNAMIC_MODE_DRY            "dry"
#define DYNAMIC_MODE_FAN            "fan" //index10
#define DYNAMIC_MODE_SWING          "swing" //index18
#define DYNAMIC_MODE_TURBO          "turbo" // index13
#define DYNAMIC_MODE_SLEEP          "sleep" // index13
#define DYNAMIC_MODE_DISPLAY        "display" // index13
#define DYNAMIC_MODE_ECO            "eco" // index13
#define DYNAMIC_MODE_CONDA          "conda" //index14
#define DYNAMIC_MODE_AUTO            "auto"
#define DYNAMIC_MODE_COOL            "cool"
#define DYNAMIC_MODE_ACMIX           "ac_mix"
#define DYNAMIC_MODE_WELLNESS        "wellness"
#define DYNAMIC_MODE_REVRSE           "reverse"
#define DYNAMIC_MODE_FINETUNE         "finetune"
#define DYNAMIC_MODE_BREEZE           "breeze"
#define DYNAMIC_MODE_ACFAN            "duo cool"
#define DYNAMIC_MODE_NORMAL           "normal"



#define DYNAMIC_FAN_SPEED           "speed"
#define DYNAMIC_FAN_TIMER           "timer"
#define DYNAMIC_FAN_SLEEP           "sleep"
#define DYNAMIC_FAN_POWER           "power"
#define DYNAMIC_FAN_LED             "led"

#define DYNAMIC_FILTER_CLEAN     "filterClean" //index 20
#define DYNAMIC_POWERUSAGE          "powerusage" //index21
#define DYNAMIC_UDT                 "udt"
#define DYNAMIC_UDT_TRAINING_COUNT  "training count"
#define DYNAMIC_UDT_USERS_COUNT     "users count"
#define DYNAMIC_UDT_VOICE_CONTROL   "voice control"
#define DYNAMIC_UDT_VOICE_CONTROL_ON    "on"
#define DYNAMIC_UDT_VOICE_CONTROL_OFF   "off"
#define DYNAMIC_APP                     "app"
#define DYNAMIC_APP_BLE_CONTROL         "ble control"
#define DYNAMIC_APP_BLE_CONTROL_ON      "on"
#define DYNAMIC_APP_BLE_CONTROL_OFF     "off"
#define DYNAMIC_REMOTE                  "remote"
#define DYNAMIC_REMOTE_ON               "on"
#define DYNAMIC_REMOTE_OFF               "off"
#define DYNAMIC_CRASH_COUNT             "crash count"

enum mqttAction
{
    HOAGS_PUBLISH, 
    HOAGS_DONT_PUBLISH,
    HOAGS_SUBSCRIBE,
    HOAGS_DONT_SUBSCRIBE
};

#define MQTT_PAYLOAD_LEN_MAX    1024

char* getAckPacketDataString(void);

#if 0
{
   "static":{
      "macid":"",
      "fwversion":"",
      "prodtype":"",
      "prodmodel":"",
      "custname":""
   },
   "dynamic":{
      "cpu":{
         "temp":"",
         "usage":""
      },
      "memory":{
         "usage":""
      },
      "filesystem":{
         "usage":""
      },
      "location":"",
      "uptime":"",
      "lastupdate":"",
      "cycles":"",
      "mode":{
         "high":"",
         "breeze":""
      },
      "powerusage":"",
      "udt":{
         "training count":"",
         "users count":"",
         "voice control":{
            "on":"4",
            "off":"5"
         }
      },
      "app":{
         "ble control":{
            "on":"5",
            "off":"6"
         }
      },
      "remote":{
         "on":"6",
         "off":"7"
      },
      "crash count":"11"
   }
}
#endif
#endif

































