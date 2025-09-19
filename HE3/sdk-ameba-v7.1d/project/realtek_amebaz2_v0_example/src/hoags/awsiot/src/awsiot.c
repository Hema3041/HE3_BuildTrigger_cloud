#include "cJSON.h"
#include "awsiot.h"
#include "packets.h"
#include "env.h"
#include "packets.h"
#include "dataCollector.h"
//#include "hoagsLittleFS.h"
//#include "semphr.h"

#if ENABLE_AWSIOT_UI_CONTROLS

MQTTClient client;
Network network;

struct hoagsMqtt hqttAck = {MT_PING, "ack"};
extern QueueHandle_t pubDataAnalQueueHandle;
extern unsigned char vfAck[24];
extern unsigned char atombergAck[62];
extern unsigned char ambAck[15];
extern unsigned char vdAck[15];
extern unsigned char omniAck[15];
#if VGUARD_NEW_FAN
extern unsigned char vgAck[8];
char vg_dp_fansp = 0x24;
char vg_dp_mode = 0x18;
#endif
extern unsigned char lvprAck[26];
extern void* hoagsMalloc(size_t sz);
//extern uint32_t vTaskStackSize(void);
char* mallocAck;
char* mallocvdAck;
char* mallocomniAck;
char dp = 0x04;
char dp_ = 0x05;
char f_dp = 0x06;
char m_dp = 0x05;
//extern char univMacid[13];
//extern QueueHandle_t subUiControlQueueHandle;

char pubUiControlTopic[128];//hoags/<custname>/<prodtype>/<prodmodel>/<macid>/<AWSIOT_UI_CONTROL_TOPIC>
char pubDataAnalTopic[128];//hoags/<custname>/<prodtype>/<prodmodel>/<macid>/<AWSIOT_DATA_ANALYTIC_TOPIC>
char subUiControlTopic[128];//hoags/<custname>/<prodtype>/<prodmodel>/<macid>/<AWSIOT_UI_CONTROL_TOPIC>
char pubPing[128];//hoags/<custname>/<macid>/<friendlyname>Ack
char subPing[128];//hoags/<custname>/<macid>/<friendlyname>
char pubUiControlAckTopic[128];//hoags/<custname>/<prodtype>/<prodmodel>/<macid>/<AWSIOT_UI_CONTROL_ACK_TOPIC>
char pubUiControlAckNotifyTopic[128];//hoags/<custname>/<prodtype>/<prodmodel>/<macid>/Notify
char content[32];
//char oldPath[128];
//char newPath[128];
//char macid[16];
char clientId[32];
long long startTime;

extern BOOL isAckReceived;
struct hdcp hdcpRecObj;

//Suvarna: Moved from dataCollector to here, make it global for now
char* data = NULL;
int counter = 0;//for testing
char counterStr[8];
char mode[8];
char filter[8];
char power[8];
char time_S[16];

//unsigned char sendbuf[MQTT_PAYLOAD_LEN_MAX], readbuf[512];

cJSON_Hooks memoryHook;

cJSON* dataAnalyticInfo =	NULL;
cJSON* staticAnalyticInfo = NULL;
cJSON* dynamicAnalyticInfo = NULL;
cJSON* cpuAnalyticInfo = NULL;
cJSON* memoryAnalyticInfo = NULL;
cJSON* fileSysAnalyticInfo = NULL;
cJSON* modeAnalyticInfo = NULL;
cJSON* setAnalyticInfo = NULL;
cJSON* fanAnalyticInfo = NULL;
cJSON* tempAnalyticInfo = NULL;
cJSON* udtAnalyticInfo = NULL;
cJSON* voiceControlAnalyticInfo = NULL;
cJSON* appControlAnalyticInfo = NULL;
cJSON* bleControlAnalyticInfo = NULL;
cJSON* remoteControlAnalyticInfo = NULL;

static void messageArrivedUIControl(MessageData *data)
{
	unpackAWSIoT(data->message->payload, &hdcpRecObj);
	printAWSIoT(&hdcpRecObj);
	HOAGS_INFO("MQTT arrived on %s=%d\n", data->topicName->lenstring.data, data->message->payloadlen);
	#if VIRTUALFOREST_AC || AMBER_AC || AMBER_AIRCOOLER || HAVELLS_AC || OMNI_AC
	controlAWSIoT(&hdcpRecObj);
	#elif VERSADEVICES_SUPERFAN_IOT || VGUARD_FAN || ATOMBERG_FAN || VGUARD_NEW_FAN
	controlFanAWSIoT(&hdcpRecObj);
	#elif HOAGS_DEMO_LIGHT
	controlLightAWSIoT(&hdcpRecObj);
	#elif HINDWARE_CHIMNEY || LIVPURE_CHIMNEY
	controlChimneyAWSIoT(&hdcpRecObj);
	#endif
}

static void messageArrivedPing(MessageData *data)
{
    HOAGS_INFO("MQTT arrived on %s=%d\n", data->topicName->lenstring.data, data->message->payloadlen);
	int rc = 0;
    if(strncmp((char*)data->message->payload, "ping", 4) == 0)
    {
        HOAGS_INFO("\n");
        //char *ack = "ack";
        //struct hoagsMqtt hqtt = {MT_PING, ack};
        //xQueueSend(pubDataAnalQueueHandle, &hqtt, xQUEUE_TIMEOUT);
        MQTTMessage message;
        message.qos = QOS1;
        message.retained = 0;
        message.payload = "ack";
        message.payloadlen = 3;
        if ((rc = MQTTPublish(&client, pubPing, &message)) != 0) //pubDataAnalTopic
        {
            HOAGS_ERR("Return code from MQTT publish is %d\n", rc);
        }
		else
		{
			free(message.payload);
		}
        createPowerUsageData();
        sendAckToCloud();
    }
}

#if 0
void NetworkInitHoags(Network *n)
{
	n->my_socket = -1;
	n->mqttread = FreeRTOS_read;
	n->mqttwrite = FreeRTOS_write;
	n->disconnect = FreeRTOS_disconnect;

#if (MQTT_OVER_SSL)
	n->use_ssl = 1;
	n->ssl = NULL;
	n->conf = NULL;
	n->rootCA = AWS_IOT_ROOT_CA;
	n->clientCA = AWS_IOT_CLIENT_CA;
	n->private_key = AWS_IOT_PRIVATE_KEY;
	n->ciphersuites = NULL;
#endif
}
#endif

void prepareTopics(/*char pubUiControlTopic[], char pubDataAnalTopic[], char subUiControlTopic[]*/)
{
	
	strcat(pubUiControlTopic, "hoags");
	strcat(pubUiControlTopic, "/");

	char envData[16];
	memset(envData, 0, sizeof(envData));
	getEnvItem(ENV_CUSTNAME, envData);
	strcat(pubUiControlTopic, "");

	strcpy(subPing, pubUiControlTopic);

	memset(envData, 0, sizeof(envData));
	getEnvItem(ENV_PRODTYPE, envData);
	strcat(pubUiControlTopic, "/");
	strcat(pubUiControlTopic, envData);

	memset(envData, 0, sizeof(envData));
	getEnvItem(ENV_PRODMODEL, envData);
	strcat(pubUiControlTopic, "/");
	strcat(pubUiControlTopic, envData);

	//memset(macid, 0, sizeof(macid));
	//getMACID();
	strcat(pubUiControlTopic, "/");
	strcat(pubUiControlTopic, umObj.macid);
	strcat(pubUiControlTopic, "/");

	strcat(subPing, "/");
	strcat(subPing, umObj.macid);

	memset(envData, 0, sizeof(envData));
	getEnvItem(ENV_FRIENDLYNAME, envData);
	strcat(subPing, "/");
	strcat(subPing, envData);

	strcpy(pubPing, subPing);
	strcat(pubPing, "Ack");

	strcpy(pubDataAnalTopic, pubUiControlTopic);
	strcpy(subUiControlTopic, pubUiControlTopic);
	strcpy(pubUiControlAckTopic, pubUiControlTopic);

	strcpy(pubUiControlAckNotifyTopic, pubUiControlAckTopic);
	strcat(pubUiControlAckNotifyTopic, "Notify");

	strcat(pubUiControlTopic, AWSIOT_UI_CONTROL_TOPIC);
	strcat(pubDataAnalTopic, AWSIOT_DATA_ANALYTIC_TOPIC);
	strcat(subUiControlTopic, AWSIOT_UI_CONTROL_TOPIC);
	strcat(pubUiControlAckTopic, AWSIOT_UI_CONTROL_ACK_TOPIC);

}
#if ATOMBERG_FAN
BOOL initStaticJson()
{
	startTime = xTaskGetTickCount();
	
	memoryHook.malloc_fn = hoagsMalloc;
	memoryHook.free_fn = free;
	cJSON_InitHooks(&memoryHook);
	
	if((dataAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating dataAnalyticInfo object\n");
		return FALSE;
	}

	if((staticAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating staticAnalyticInfo object\n");
		return FALSE;
	}

	if((dynamicAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating dynamicAnalyticInfo object\n");
		return FALSE;
	}

	if((cpuAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating cpuAnalyticInfo object\n");
		return FALSE;
	}

	if((memoryAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating memoryAnalyticInfo object\n");
		return FALSE;
	}

	if((fileSysAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating fileSysAnalyticInfo object\n");
		return FALSE;
	}

	if((modeAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating modeAnalyticInfo object\n");
		return FALSE;
	}
	if((setAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating setAnalyticInfo object\n");
		return FALSE;
	}
	if((fanAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating fanAnalyticInfo object\n");
		return FALSE;
	}

	if((tempAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating tempAnalyticInfo object\n");
		return FALSE;
	}

	if((udtAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating udtAnalyticInfo object\n");
		return FALSE;
	}

	if((voiceControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating voiceControlAnalyticInfo object\n");
		return FALSE;
	}

	if((appControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating appControlAnalyticInfo object\n");
		return FALSE;
	}

	if((bleControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating bleControlAnalyticInfo object\n");
		return FALSE;
	}

	if((remoteControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating remoteControlAnalyticInfo object\n");
		return FALSE;
	}

	char* content[16];

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_CUSTNAME,content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_CUST_NAME, content);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_PRODTYPE,content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_PRODUCT_TYPE, content);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_PRODMODEL,content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_PRODUCT_MODEL, content);

	//memset(content, 0, sizeof(content));
	//getMACID();
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_MACID, umObj.macid);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_USERID,content);

	memset(content, 0, sizeof(content));
	fwversion_read(content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_VERSION, content);

	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_LOCATION, "");
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_UPTIME, "");
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_LASTUPDATE, "");
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_CYCLES, "");	

	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_FAN_SLEEP, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_FAN_TIMER, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_FAN_SPEED, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_FAN_LED, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_FAN_POWER, "");

	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_MODE, modeAnalyticInfo);
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_POWERUSAGE, "");

	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_FILTER_CLEAN, "");

	cJSON_AddStringToObject(udtAnalyticInfo, DYNAMIC_UDT_TRAINING_COUNT, "");
	cJSON_AddStringToObject(udtAnalyticInfo, DYNAMIC_UDT_USERS_COUNT, "");
	cJSON_AddStringToObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_ON, "");
	cJSON_AddStringToObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_OFF, "");
	cJSON_AddItemToObject(udtAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL, voiceControlAnalyticInfo);
	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_UDT, udtAnalyticInfo);

	cJSON_AddStringToObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_ON, "");
	cJSON_AddStringToObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_OFF, "");
	cJSON_AddItemToObject(appControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL, bleControlAnalyticInfo);
	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_APP, appControlAnalyticInfo);

	cJSON_AddStringToObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_ON, "");
	cJSON_AddStringToObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_OFF, "");
	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_REMOTE, remoteControlAnalyticInfo);
	
	cJSON_AddItemToObject(dataAnalyticInfo, STATIC, staticAnalyticInfo);
	cJSON_AddItemToObject(dataAnalyticInfo, DYNAMIC, dynamicAnalyticInfo);

	return TRUE;
}

#elif VERSADEVICES_SUPERFAN_IOT
BOOL initStaticJson()
{
	startTime = xTaskGetTickCount();
	
	memoryHook.malloc_fn = hoagsMalloc;
	memoryHook.free_fn = free;
	cJSON_InitHooks(&memoryHook);
	
	if((dataAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating dataAnalyticInfo object\n");
		return FALSE;
	}

	if((staticAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating staticAnalyticInfo object\n");
		return FALSE;
	}

	if((dynamicAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating dynamicAnalyticInfo object\n");
		return FALSE;
	}

	if((cpuAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating cpuAnalyticInfo object\n");
		return FALSE;
	}

	if((memoryAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating memoryAnalyticInfo object\n");
		return FALSE;
	}

	if((fileSysAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating fileSysAnalyticInfo object\n");
		return FALSE;
	}

	if((modeAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating modeAnalyticInfo object\n");
		return FALSE;
	}
	if((setAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating setAnalyticInfo object\n");
		return FALSE;
	}
	if((fanAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating fanAnalyticInfo object\n");
		return FALSE;
	}

	if((udtAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating udtAnalyticInfo object\n");
		return FALSE;
	}

	if((voiceControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating voiceControlAnalyticInfo object\n");
		return FALSE;
	}

	if((appControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating appControlAnalyticInfo object\n");
		return FALSE;
	}

	if((bleControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating bleControlAnalyticInfo object\n");
		return FALSE;
	}

	if((remoteControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating remoteControlAnalyticInfo object\n");
		return FALSE;
	}

	char* content[16];

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_CUSTNAME,content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_CUST_NAME, content);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_PRODTYPE,content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_PRODUCT_TYPE, content);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_PRODMODEL,content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_PRODUCT_MODEL, content);

	//memset(content, 0, sizeof(content));
	//getMACID();
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_MACID, umObj.macid);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_USERID,content);

	memset(content, 0, sizeof(content));
	memcpy(content, VERSION_BUILD_STR, sizeof(VERSION_BUILD_STR));
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_VERSION, content);

	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_LOCATION, "");
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_UPTIME, "");
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_LASTUPDATE, "");
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_CYCLES, "");	

	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_FAN_TIMER, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_FAN_SPEED, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_FAN_POWER, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_ECO, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_ACMIX, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_WELLNESS, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_REVRSE, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_FINETUNE, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_BREEZE, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_ACFAN, "");


	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_MODE, modeAnalyticInfo);
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_POWERUSAGE, "");

	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_FILTER_CLEAN, "");

	cJSON_AddStringToObject(udtAnalyticInfo, DYNAMIC_UDT_TRAINING_COUNT, "");
	cJSON_AddStringToObject(udtAnalyticInfo, DYNAMIC_UDT_USERS_COUNT, "");
	cJSON_AddStringToObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_ON, "");
	cJSON_AddStringToObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_OFF, "");
	cJSON_AddItemToObject(udtAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL, voiceControlAnalyticInfo);
	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_UDT, udtAnalyticInfo);

	cJSON_AddStringToObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_ON, "");
	cJSON_AddStringToObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_OFF, "");
	cJSON_AddItemToObject(appControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL, bleControlAnalyticInfo);
	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_APP, appControlAnalyticInfo);

	cJSON_AddStringToObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_ON, "");
	cJSON_AddStringToObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_OFF, "");
	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_REMOTE, remoteControlAnalyticInfo);
	
	cJSON_AddItemToObject(dataAnalyticInfo, STATIC, staticAnalyticInfo);
	cJSON_AddItemToObject(dataAnalyticInfo, DYNAMIC, dynamicAnalyticInfo);

	return TRUE;
}

#elif VGUARD_NEW_FAN
BOOL initStaticJson()
{
	startTime = xTaskGetTickCount();
	
	memoryHook.malloc_fn = hoagsMalloc;
	memoryHook.free_fn = free;
	cJSON_InitHooks(&memoryHook);
	
	if((dataAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating dataAnalyticInfo object\n");
		return FALSE;
	}

	if((staticAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating staticAnalyticInfo object\n");
		return FALSE;
	}

	if((dynamicAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating dynamicAnalyticInfo object\n");
		return FALSE;
	}

	if((cpuAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating cpuAnalyticInfo object\n");
		return FALSE;
	}

	if((memoryAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating memoryAnalyticInfo object\n");
		return FALSE;
	}

	if((fileSysAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating fileSysAnalyticInfo object\n");
		return FALSE;
	}

	if((modeAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating modeAnalyticInfo object\n");
		return FALSE;
	}
	if((setAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating setAnalyticInfo object\n");
		return FALSE;
	}
	if((fanAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating fanAnalyticInfo object\n");
		return FALSE;
	}

	if((udtAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating udtAnalyticInfo object\n");
		return FALSE;
	}

	if((voiceControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating voiceControlAnalyticInfo object\n");
		return FALSE;
	}

	if((appControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating appControlAnalyticInfo object\n");
		return FALSE;
	}

	if((bleControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating bleControlAnalyticInfo object\n");
		return FALSE;
	}

	if((remoteControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating remoteControlAnalyticInfo object\n");
		return FALSE;
	}

	char* content[16];

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_CUSTNAME,content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_CUST_NAME, content);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_PRODTYPE,content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_PRODUCT_TYPE, content);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_PRODMODEL,content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_PRODUCT_MODEL, content);

	//memset(content, 0, sizeof(content));
	//getMACID();
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_MACID, umObj.macid);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_USERID,content);

	memset(content, 0, sizeof(content));
	fwversion_read(content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_VERSION, content);

	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_LOCATION, "");
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_UPTIME, "");
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_LASTUPDATE, "");
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_CYCLES, "");	

	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_FAN_TIMER, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_FAN_SPEED, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_FAN_POWER, "");;
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_REVRSE, "");


	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_MODE, modeAnalyticInfo);
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_POWERUSAGE, "");

	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_FILTER_CLEAN, "");

	cJSON_AddStringToObject(udtAnalyticInfo, DYNAMIC_UDT_TRAINING_COUNT, "");
	cJSON_AddStringToObject(udtAnalyticInfo, DYNAMIC_UDT_USERS_COUNT, "");
	cJSON_AddStringToObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_ON, "");
	cJSON_AddStringToObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_OFF, "");
	cJSON_AddItemToObject(udtAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL, voiceControlAnalyticInfo);
	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_UDT, udtAnalyticInfo);

	cJSON_AddStringToObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_ON, "");
	cJSON_AddStringToObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_OFF, "");
	cJSON_AddItemToObject(appControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL, bleControlAnalyticInfo);
	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_APP, appControlAnalyticInfo);

	cJSON_AddStringToObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_ON, "");
	cJSON_AddStringToObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_OFF, "");
	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_REMOTE, remoteControlAnalyticInfo);
	
	cJSON_AddItemToObject(dataAnalyticInfo, STATIC, staticAnalyticInfo);
	cJSON_AddItemToObject(dataAnalyticInfo, DYNAMIC, dynamicAnalyticInfo);

	return TRUE;
}

#else
BOOL initStaticJson()
{
	startTime = xTaskGetTickCount();
	
	memoryHook.malloc_fn = malloc;
	memoryHook.free_fn = free;
	cJSON_InitHooks(&memoryHook);
	
	if((dataAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating dataAnalyticInfo object\n");
		return FALSE;
	}

	if((staticAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating staticAnalyticInfo object\n");
		return FALSE;
	}

	if((dynamicAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating dynamicAnalyticInfo object\n");
		return FALSE;
	}

	if((cpuAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating cpuAnalyticInfo object\n");
		return FALSE;
	}

	if((memoryAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating memoryAnalyticInfo object\n");
		return FALSE;
	}

	if((fileSysAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating fileSysAnalyticInfo object\n");
		return FALSE;
	}

	if((modeAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating modeAnalyticInfo object\n");
		return FALSE;
	}
	if((setAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating setAnalyticInfo object\n");
		return FALSE;
	}
	if((fanAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating fanAnalyticInfo object\n");
		return FALSE;
	}

	if((tempAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating tempAnalyticInfo object\n");
		return FALSE;
	}

	if((udtAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating udtAnalyticInfo object\n");
		return FALSE;
	}

	if((voiceControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating voiceControlAnalyticInfo object\n");
		return FALSE;
	}

	if((appControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating appControlAnalyticInfo object\n");
		return FALSE;
	}

	if((bleControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating bleControlAnalyticInfo object\n");
		return FALSE;
	}

	if((remoteControlAnalyticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating remoteControlAnalyticInfo object\n");
		return FALSE;
	}

	char* content[16];

	memset(content, 0, sizeof(content));
	//getEnvItem(ENV_CUSTNAME,content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_CUST_NAME, content);

	memset(content, 0, sizeof(content));
	//getEnvItem(ENV_PRODTYPE,content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_PRODUCT_TYPE, content);

	memset(content, 0, sizeof(content));
	//getEnvItem(ENV_PRODMODEL,content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_PRODUCT_MODEL, content);

	//memset(content, 0, sizeof(content));
	//getMACID();
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_MACID, "112233445566"/*umObj.macid*/);

	memset(content, 0, sizeof(content));
	//getEnvItem(ENV_USERID,content);

	memset(content, 0, sizeof(content));
	//fwversion_read(content);
	cJSON_AddStringToObject(staticAnalyticInfo, STATIC_VERSION, content);

	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_LOCATION, "");
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_UPTIME, "");
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_LASTUPDATE, "");
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_CYCLES, "");	

	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_SWING, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_TURBO, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_SLEEP, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_DISPLAY, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_ECO, "");
	cJSON_AddStringToObject(modeAnalyticInfo, DYNAMIC_MODE_CONDA, "");

	cJSON_AddItemToObject(modeAnalyticInfo, DYNAMIC_MODE_SET, setAnalyticInfo);
	cJSON_AddItemToObject(modeAnalyticInfo, DYNAMIC_MODE_FAN, fanAnalyticInfo);
	cJSON_AddItemToObject(modeAnalyticInfo, DYNAMIC_MODE_TEMP, tempAnalyticInfo);

	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_MODE, modeAnalyticInfo);
	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_POWERUSAGE, "");

	cJSON_AddStringToObject(dynamicAnalyticInfo, DYNAMIC_FILTER_CLEAN, "");

	cJSON_AddStringToObject(udtAnalyticInfo, DYNAMIC_UDT_TRAINING_COUNT, "");
	cJSON_AddStringToObject(udtAnalyticInfo, DYNAMIC_UDT_USERS_COUNT, "");
	cJSON_AddStringToObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_ON, "");
	cJSON_AddStringToObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_OFF, "");
	cJSON_AddItemToObject(udtAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL, voiceControlAnalyticInfo);
	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_UDT, udtAnalyticInfo);

	cJSON_AddStringToObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_ON, "");
	cJSON_AddStringToObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_OFF, "");
	cJSON_AddItemToObject(appControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL, bleControlAnalyticInfo);
	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_APP, appControlAnalyticInfo);

	cJSON_AddStringToObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_ON, "");
	cJSON_AddStringToObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_OFF, "");
	cJSON_AddItemToObject(dynamicAnalyticInfo, DYNAMIC_REMOTE, remoteControlAnalyticInfo);
	
	cJSON_AddItemToObject(dataAnalyticInfo, STATIC, staticAnalyticInfo);
	cJSON_AddItemToObject(dataAnalyticInfo, DYNAMIC, dynamicAnalyticInfo);

	return TRUE;
}
#endif

#if ATOMBERG_FAN
BOOL updateAnalJson()
{
	memset(content, 0, sizeof(content));
	getEnvItem(ENV_LOCATION,content);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_LOCATION, cJSON_CreateString(content));
	memset(content, 0, sizeof(content));
	sprintf(time_S, "%lld", (xTaskGetTickCount()-startTime)/1000);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_UPTIME, cJSON_CreateString(time_S));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_LASTUPDATE, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_CYCLES, cJSON_CreateString(counterStr));
	char strrr[64];
	char value1=atombergAck[28];
	char value2=atombergAck[29];
	char value3=atombergAck[30];
	char value4=atombergAck[31];
	char value5=atombergAck[32];
	sprintf(strrr, "%c%c%c%c%c", value1, value2,value3, value4, value5);;
	if(strcmp(strrr, "power") == 0){
		sprintf(mode, "%c", atombergAck[35]);
		cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_FAN_POWER, cJSON_CreateString(mode));
		memset(mode, 0, sizeof(mode));
	}
	else if (strcmp(strrr, "speed") == 0)
	{
		sprintf(mode, "%c", atombergAck[35]);
		cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_FAN_SPEED, cJSON_CreateString(mode));
		memset(mode, 0, sizeof(mode));
	}
	else if (strcmp(strrr, "timer") == 0)
	{
		sprintf(mode, "%c", atombergAck[35]);
		cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_FAN_TIMER, cJSON_CreateString(mode));
		memset(mode, 0, sizeof(mode));
	}
	else if (strcmp(strrr, "sleep") == 0)
	{
		sprintf(mode, "%c", atombergAck[35]);
		cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_FAN_SLEEP, cJSON_CreateString(mode));
		memset(mode, 0, sizeof(mode));
	}
	else if (strcmp(strrr, "led\":") == 0)
	{
		sprintf(mode, "%c", atombergAck[33]);
		cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_FAN_LED, cJSON_CreateString(mode));
		memset(mode, 0, sizeof(mode));
	}

	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_MODE, modeAnalyticInfo);

	//filterClean
	sprintf(filter, "%02x", vfAck[20]);
	if(strcmp(filter,"01") == 0) //Suvarna: Filter-change notification
		createFilterChange();

	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_FILTER_CLEAN, cJSON_CreateString(filter));
	memset(filter, 0, sizeof(filter));

	//powerUsage
	sprintf(power,"%02x",vfAck[21]);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_POWERUSAGE, cJSON_CreateString(power));
	memset(power, 0, sizeof(power));

	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_TRAINING_COUNT, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_USERS_COUNT, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL, voiceControlAnalyticInfo);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_UDT, udtAnalyticInfo);

	cJSON_ReplaceItemInObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(appControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL, bleControlAnalyticInfo);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_APP, appControlAnalyticInfo);

	cJSON_ReplaceItemInObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_REMOTE, remoteControlAnalyticInfo);

	cJSON_ReplaceItemInObject(dataAnalyticInfo, STATIC, staticAnalyticInfo);
	cJSON_ReplaceItemInObject(dataAnalyticInfo, DYNAMIC, dynamicAnalyticInfo);
}
#elif VGUARD_NEW_FAN
BOOL updateAnalJson()
{
	memset(content, 0, sizeof(content));
	getEnvItem(ENV_LOCATION,content);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_LOCATION, cJSON_CreateString(content));
	memset(content, 0, sizeof(content));
	sprintf(time_S, "%lld", (xTaskGetTickCount()-startTime)/1000);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_UPTIME, cJSON_CreateString(time_S));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_LASTUPDATE, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_CYCLES, cJSON_CreateString(counterStr));

	//FAN LEVEL
	if (vgAck != NULL) {
        if (vgAck[3] == vg_dp_fansp) {
			sprintf(mode, "%02x", vgAck[1]);
			if (strcmp(mode, "11") == 0) {
				printf("Mode: LOW SPEED\n");
			} else if (strcmp(mode, "31") == 0) {
				printf("Mode: LOW-MEDIUM SPEED\n");
			}else if (strcmp(mode, "35") == 0) {
				printf("Mode: MEDIUM SPEED\n");
			}else if (strcmp(mode, "74") == 0) {
				printf("Mode: MEDIUM-HIGH SPEED\n");
			} else if (strcmp(mode, "59") == 0) {
				printf("Mode: HIGH SPEED\n"); 
			} else {
				printf("Mode: Unknown in mode\n");
			}
			memset(mode, 0, sizeof(mode));
		}

		//Modes
		if (vgAck[3] == vg_dp_mode)
		{
			sprintf(mode, "%02x", vgAck[1]);
			if (strcmp(mode, "01") == 0) {
				cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_NORMAL, cJSON_CreateString(mode));
				printf("Mode: Normal Mode\n");
			} else if (strcmp(mode, "02") == 0) {
				cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_BREEZE, cJSON_CreateString(mode));
				printf("Mode: Breeze Mode\n");
			} else if (strcmp(mode, "03") == 0) {
				cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_SLEEP, cJSON_CreateString(mode));
				printf("Mode: Sleep Mode\n");
			}else {
				printf("Mode: Unknown in mode\n");
			}
			memset(mode, 0, sizeof(mode));
		}

		}else{
			return FALSE;
		}


	//filterClean
	sprintf(filter, "%02x", vgAck[4]);
	if(strcmp(filter,"0C") == 0) //Suvarna: Filter-change notification
		createFilterChange();

	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_FILTER_CLEAN, cJSON_CreateString(filter));
	memset(filter, 0, sizeof(filter));

	//powerUsage
	sprintf(power,"%02x",vgAck[4]);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_POWERUSAGE, cJSON_CreateString(power));
	memset(power, 0, sizeof(power));

	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_TRAINING_COUNT, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_USERS_COUNT, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL, voiceControlAnalyticInfo);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_UDT, udtAnalyticInfo);

	cJSON_ReplaceItemInObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(appControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL, bleControlAnalyticInfo);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_APP, appControlAnalyticInfo);

	cJSON_ReplaceItemInObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_REMOTE, remoteControlAnalyticInfo);

	cJSON_ReplaceItemInObject(dataAnalyticInfo, STATIC, staticAnalyticInfo);
	cJSON_ReplaceItemInObject(dataAnalyticInfo, DYNAMIC, dynamicAnalyticInfo);
}

#elif VERSADEVICES_SUPERFAN_IOT
BOOL updateAnalJson()
{
	memset(content, 0, sizeof(content));
	getEnvItem(ENV_LOCATION,content);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_LOCATION, cJSON_CreateString(content));
	memset(content, 0, sizeof(content));
	sprintf(time_S, "%lld", (xTaskGetTickCount()-startTime)/1000);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_UPTIME, cJSON_CreateString(time_S));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_LASTUPDATE, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_CYCLES, cJSON_CreateString(counterStr));
	
	//FAN LEVEL
	if (mallocvdAck != NULL) {
        if (mallocvdAck[5] == f_dp) {
		sprintf(mode, "%02x", mallocvdAck[11]);
		if (strcmp(mode, "21") == 0) {
			printf("Mode: LOW SPEED\n");
		} else if (strcmp(mode, "42") == 0) {
			printf("Mode: MEDIUM SPEED\n");
		} else if (strcmp(mode, "63") == 0) {
			printf("Mode: HIGH SPEED\n"); 
		} else {
			printf("Mode: Unknown in mode\n");
		}
		memset(mode, 0, sizeof(mode));
		}

		//power
		sprintf(mode, "%02x", mallocvdAck[6]);
		cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_FAN_POWER, cJSON_CreateString(mode));
		memset(mode, 0, sizeof(mode));



		//MODES
		if (mallocvdAck[5] == m_dp) 
		{
		sprintf(mode, "%02x", mallocvdAck[10]);
		if (strcmp(mode, "01") == 0) {
			cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_ECO, cJSON_CreateString(mode));
			printf("Mode: eco mode\n");
		} else if (strcmp(mode, "02") == 0) {
			cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_ACMIX, cJSON_CreateString(mode));
			printf("Mode: AC MIX\n");
		} else if (strcmp(mode, "07") == 0) {
			cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_ACFAN, cJSON_CreateString(mode));
			printf("Mode: DUO COOL\n");
		} else if (strcmp(mode, "03") == 0) {
			cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_WELLNESS, cJSON_CreateString(mode));
			printf("Mode: WELLNESS\n");
		} else if (strcmp(mode, "06") == 0) {
			cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_BREEZE, cJSON_CreateString(mode));
			printf("Mode: BREEZE\n");
		} else if (strcmp(mode, "04") == 0) {
			cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_REVRSE, cJSON_CreateString(mode));
			printf("Mode: REVERSE\n");
		} else if (strcmp(mode, "05") == 0) {
			cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_FINETUNE, cJSON_CreateString(mode));
			printf("Mode: FINE TUNE\n");
		} else {
			printf("Mode: Unknown in mode\n");
		}
		memset(mode, 0, sizeof(mode));
		}
		}else{
			return FALSE;
		}
	
	//filterClean
	sprintf(filter, "%02x", mallocvdAck[6]);
	if(strcmp(filter,"01") == 0) //Suvarna: Filter-change notification
		createFilterChange();

	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_FILTER_CLEAN, cJSON_CreateString(filter));
	memset(filter, 0, sizeof(filter));

	//powerUsage
	sprintf(power,"%02x",mallocvdAck[6]);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_POWERUSAGE, cJSON_CreateString(power));
	memset(power, 0, sizeof(power));


	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_TRAINING_COUNT, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_USERS_COUNT, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL, voiceControlAnalyticInfo);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_UDT, udtAnalyticInfo);

	cJSON_ReplaceItemInObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(appControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL, bleControlAnalyticInfo);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_APP, appControlAnalyticInfo);

	cJSON_ReplaceItemInObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_REMOTE, remoteControlAnalyticInfo);

	cJSON_ReplaceItemInObject(dataAnalyticInfo, STATIC, staticAnalyticInfo);
	cJSON_ReplaceItemInObject(dataAnalyticInfo, DYNAMIC, dynamicAnalyticInfo);
}
#else
BOOL updateAnalJson()
{
	memset(content, 0, sizeof(content));
	getEnvItem(ENV_LOCATION,content);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_LOCATION, cJSON_CreateString(content));
	memset(content, 0, sizeof(content));
	sprintf(time_S, "%lld", (xTaskGetTickCount()-startTime)/1000);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_UPTIME, cJSON_CreateString(time_S));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_LASTUPDATE, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_CYCLES, cJSON_CreateString(counterStr));
	
	//mode
	sprintf(mode, "%02x", vfAck[5]);
	updateData(setAnalyticInfo,vfAck,5);
	memset(mode, 0, sizeof(mode));

	//temp
	sprintf(mode, "%02x", vfAck[6]);
	updateData(tempAnalyticInfo,vfAck,6);
	memset(mode, 0, sizeof(mode));

	//fan level
	sprintf(mode, "%02x", vfAck[10]);
	updateData(fanAnalyticInfo,vfAck,10);
	memset(mode, 0, sizeof(mode));

	//swing
	sprintf(mode, "%02x", vfAck[18]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_SWING, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//turbo
	sprintf(mode, "%02x", vfAck[13]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_TURBO, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//sleep
	sprintf(mode, "%02x", vfAck[13]);
	
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_SLEEP, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//display
	sprintf(mode, "%02x", vfAck[13]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_DISPLAY, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//eco
	sprintf(mode, "%02x", vfAck[13]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_ECO, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//conda
	sprintf(mode, "%02x", vfAck[14]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_CONDA, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_TEMP, tempAnalyticInfo);

	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_FAN, fanAnalyticInfo);

	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_SET, setAnalyticInfo);

	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_MODE, modeAnalyticInfo);

	//filterClean
	sprintf(filter, "%02x", vfAck[20]);
	if(strcmp(filter,"01") == 0) //Suvarna: Filter-change notification
		createFilterChange();

	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_FILTER_CLEAN, cJSON_CreateString(filter));
	memset(filter, 0, sizeof(filter));

	//powerUsage
	sprintf(power,"%02x",vfAck[21]);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_POWERUSAGE, cJSON_CreateString(power));
	memset(power, 0, sizeof(power));

	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_TRAINING_COUNT, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_USERS_COUNT, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL, voiceControlAnalyticInfo);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_UDT, udtAnalyticInfo);

	cJSON_ReplaceItemInObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(appControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL, bleControlAnalyticInfo);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_APP, appControlAnalyticInfo);

	cJSON_ReplaceItemInObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_REMOTE, remoteControlAnalyticInfo);

	cJSON_ReplaceItemInObject(dataAnalyticInfo, STATIC, staticAnalyticInfo);
	cJSON_ReplaceItemInObject(dataAnalyticInfo, DYNAMIC, dynamicAnalyticInfo);
}
#endif

#if AMBER_AC
BOOL updateAnalJsonAmb()
{
	memset(content, 0, sizeof(content));
	getEnvItem(ENV_LOCATION,content);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_LOCATION, cJSON_CreateString(content));
	memset(content, 0, sizeof(content));
	sprintf(time_S, "%lld", (xTaskGetTickCount()-startTime)/1000);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_UPTIME, cJSON_CreateString(time_S));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_LASTUPDATE, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_CYCLES, cJSON_CreateString(counterStr));
	
	//mode
	if (mallocAck != NULL) {
        if (mallocAck[6] == dp) {

		sprintf(mode, "%02x", mallocAck[10]);
		if (strcmp(mode, "00") == 0) {
			printf("Mode: Auto\n");
		} else if (strcmp(mode, "01") == 0) {
			printf("Mode: Cool\n");
		} else if (strcmp(mode, "03") == 0) {
			printf("Mode: DRY\n");
		} else if (strcmp(mode, "04") == 0) {
			printf("Mode: FAN\n");
		} else {
			printf("Mode: Unknown in mode\n");
		}
		memset(mode, 0, sizeof(mode));
	}

	//temp
	sprintf(mode, "%02x", mallocAck[6]);

	//fan level
	if(mallocAck[6] == dp_)
	{
        sprintf(mode, "%02x",  mallocAck[10]);
        //cJSON_ReplaceItemInObject(setAnalyticInfo, mallocAck, 6 );
		if (strcmp(mode, "00") == 0) {
			printf("Mode: Auto\n");
        } else if (strcmp(mode, "01") == 0) {
            printf("Mode: Low\n");
        } else if (strcmp(mode, "02") == 0) {
            printf("Mode: Medium\n");
        } else if (strcmp(mode, "03") == 0) {
            printf("Mode: High\n");
        } else {
            printf("Mode: Unknown in fan\n");
    }
    memset(mode, 0, sizeof(mode));
	}
	}else{
			//printf("mallocACK is NULL\n");
			return FALSE;
		}

	//swing
	sprintf(mode, "%02x", mallocAck[6]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_SWING, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//turbo
	sprintf(mode, "%02x", mallocAck[6]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_TURBO, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//sleep
	sprintf(mode, "%02x", mallocAck[6]);
	
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_SLEEP, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//display
	sprintf(mode, "%02x", mallocAck[6]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_DISPLAY, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	
	//auto
	sprintf(mode, "%02x", mallocAck[6]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_AUTO, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//DRY;
	sprintf(mode, "%02x", mallocAck[6]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_DRY, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//COOL
	sprintf(mode, "%02x", mallocAck[6]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_COOL, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));




	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_TEMP, tempAnalyticInfo);

	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_FAN, fanAnalyticInfo);

	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_SET, setAnalyticInfo);

	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_MODE, modeAnalyticInfo);

	//filterClean
	sprintf(filter, "%02x", mallocAck[6]);
		createFilterChange();

	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_FILTER_CLEAN, cJSON_CreateString(filter));
	memset(filter, 0, sizeof(filter));

	//powerUsage
	sprintf(power,"%02x",mallocAck[6]);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_POWERUSAGE, cJSON_CreateString(power));
	memset(power, 0, sizeof(power));

	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_TRAINING_COUNT, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_USERS_COUNT, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL, voiceControlAnalyticInfo);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_UDT, udtAnalyticInfo);

	cJSON_ReplaceItemInObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(appControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL, bleControlAnalyticInfo);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_APP, appControlAnalyticInfo);

	cJSON_ReplaceItemInObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_REMOTE, remoteControlAnalyticInfo);

	cJSON_ReplaceItemInObject(dataAnalyticInfo, STATIC, staticAnalyticInfo);
	cJSON_ReplaceItemInObject(dataAnalyticInfo, DYNAMIC, dynamicAnalyticInfo);
}

#elif OMNI_AC
BOOL updateAnalJsonOmni()
{
	memset(content, 0, sizeof(content));
	getEnvItem(ENV_LOCATION,content);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_LOCATION, cJSON_CreateString(content));
	memset(content, 0, sizeof(content));
	sprintf(time_S, "%lld", (xTaskGetTickCount()-startTime)/1000);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_UPTIME, cJSON_CreateString(time_S));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_LASTUPDATE, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_CYCLES, cJSON_CreateString(counterStr));
	
	//mode
	if (mallocomniAck != NULL) {
        if (mallocomniAck[6] == dp) {

		sprintf(mode, "%02x", mallocomniAck[10]);
		if (strcmp(mode, "00") == 0) {
			printf("Mode: Auto\n");
		} else if (strcmp(mode, "01") == 0) {
			printf("Mode: Cool\n");
		} else if (strcmp(mode, "03") == 0) {
			printf("Mode: DRY\n");
		} else if (strcmp(mode, "04") == 0) {
			printf("Mode: FAN\n");
		} else {
			printf("Mode: Unknown in mode\n");
		}
		memset(mode, 0, sizeof(mode));
	}

	//temp
	sprintf(mode, "%02x", mallocomniAck[6]);

	//fan level
	if(mallocomniAck[6] == dp_)
	{
        sprintf(mode, "%02x",  mallocomniAck[10]);
        //cJSON_ReplaceItemInObject(setAnalyticInfo, mallocAck, 6 );
		if (strcmp(mode, "03") == 0) {
			printf("Mode: Auto\n");
        } else if (strcmp(mode, "00") == 0) {
            printf("Mode: Low\n");
        } else if (strcmp(mode, "01") == 0) {
            printf("Mode: Medium\n");
        } else if (strcmp(mode, "02") == 0) {
            printf("Mode: High\n");
        } else {
            printf("Mode: Unknown in fan\n");
    }
    memset(mode, 0, sizeof(mode));
	}
	}else{
			return FALSE;
		}

	//swing
	sprintf(mode, "%02x", mallocomniAck[6]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_SWING, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//turbo
	sprintf(mode, "%02x", mallocomniAck[6]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_TURBO, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//sleep
	sprintf(mode, "%02x", mallocomniAck[6]);
	
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_SLEEP, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//display
	sprintf(mode, "%02x", mallocomniAck[6]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_DISPLAY, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	
	//auto
	sprintf(mode, "%02x", mallocomniAck[6]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_AUTO, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//DRY;
	sprintf(mode, "%02x", mallocomniAck[6]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_DRY, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));

	//COOL
	sprintf(mode, "%02x", mallocomniAck[6]);
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_COOL, cJSON_CreateString(mode));
	memset(mode, 0, sizeof(mode));
	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_TEMP, tempAnalyticInfo);

	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_FAN, fanAnalyticInfo);

	cJSON_ReplaceItemInObject(modeAnalyticInfo, DYNAMIC_MODE_SET, setAnalyticInfo);

	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_MODE, modeAnalyticInfo);

	//filterClean
	sprintf(filter, "%02x", mallocomniAck[6]);
		createFilterChange();

	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_FILTER_CLEAN, cJSON_CreateString(filter));
	memset(filter, 0, sizeof(filter));

	//powerUsage
	sprintf(power,"%02x",mallocomniAck[6]);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_POWERUSAGE, cJSON_CreateString(power));
	memset(power, 0, sizeof(power));

	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_TRAINING_COUNT, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_USERS_COUNT, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(voiceControlAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(udtAnalyticInfo, DYNAMIC_UDT_VOICE_CONTROL, voiceControlAnalyticInfo);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_UDT, udtAnalyticInfo);

	cJSON_ReplaceItemInObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(bleControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(appControlAnalyticInfo, DYNAMIC_APP_BLE_CONTROL, bleControlAnalyticInfo);
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_APP, appControlAnalyticInfo);

	cJSON_ReplaceItemInObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_ON, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(remoteControlAnalyticInfo, DYNAMIC_REMOTE_OFF, cJSON_CreateString(counterStr));
	cJSON_ReplaceItemInObject(dynamicAnalyticInfo, DYNAMIC_REMOTE, remoteControlAnalyticInfo);

	cJSON_ReplaceItemInObject(dataAnalyticInfo, STATIC, staticAnalyticInfo);
	cJSON_ReplaceItemInObject(dataAnalyticInfo, DYNAMIC, dynamicAnalyticInfo);
}

#endif


static void messageArrived(MessageData* data)
{
	mqtt_printf(MQTT_INFO, "Message arrived on topic %s: %s\n", data->topicName->lenstring.data, (char *)data->message->payload);
}


unsigned char readbuf[170];  //256
unsigned char sendbuf[256]; //128
extern xTaskHandle CreatedTask;
BOOL initAWSIOTCore()
{
	memset(pubUiControlTopic, 0, sizeof(pubUiControlTopic));
	memset(pubDataAnalTopic, 0, sizeof(pubDataAnalTopic));
	memset(subUiControlTopic, 0, sizeof(subUiControlTopic));
	prepareTopics(/*pubUiControlTopic, pubDataAnalTopic, subUiControlTopic*/);
	HOAGS_INFO("pubUiControlTopic=%s\n", pubUiControlTopic);
	HOAGS_INFO("pubDataAnalTopic=%s\n", pubDataAnalTopic);
	HOAGS_INFO("subUiControlTopic=%s\n", subUiControlTopic);
	HOAGS_INFO("pubUiControlAckTopic=%s\n", pubUiControlAckTopic);
	HOAGS_INFO("pubUiControlAckNotifyTopic=%s\n", pubUiControlAckNotifyTopic);
	HOAGS_INFO("pubPing=%s\n", pubPing);
	HOAGS_INFO("subPing=%s\n", subPing);

	HOAGS_ERR("xPortGetFreeHeapSize=%d\n", xPortGetFreeHeapSize());
	struct hoagsMqtt hqtt;
	int rc = 0, count = 0;
	MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
	
	memset(readbuf, 0x00, sizeof(readbuf));
	memset(sendbuf, 0x00, sizeof(sendbuf));
	HOAGS_ERR("xPortGetFreeHeapSize=%d\n", xPortGetFreeHeapSize());
	//mbedtls_debug_set_threshold(4);
    NetworkInit(&network);
	MQTTClientInit(&client, &network, 8000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));
	HOAGS_ERR("xPortGetFreeHeapSize=%d\n", xPortGetFreeHeapSize());
	
	while (TRUE) 
	{
		HOAGS_INFO("Wait Wi-Fi to be connected\n");
		
        while(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS) {
			printf("Wifi not connected yet!\n");
			vTaskDelay(5000 / portTICK_PERIOD_MS);
		}
		HOAGS_ERR("xPortGetFreeHeapSize=%d\n", xPortGetFreeHeapSize());
		HOAGS_INFO("Wi-Fi connected\n");
		
		HOAGS_INFO("Connect Network \"%s\"\n", AWS_IOT_CORE_ENDPOINT);

		vTaskDelete(CreatedTask);//Suvarna: Don't remove it(done for memory optimization)
		freeEnvTask();
		vTaskDelay(2000);

		HOAGS_ERR("xPortGetFreeHeapSize=%d\n", xPortGetFreeHeapSize());
		while ((rc = NetworkConnect(&network, (char *)AWS_IOT_CORE_ENDPOINT, AWS_IOT_CORE_MQTT_PORT)) != 0) {
			HOAGS_DBG("Return code from network connect is %d\n", rc);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
		
		//HOAGS_INFO("\n");

		console_init();//Suvarna: Don't remove it(done for memory optimization)
		HOAGS_INFO("\n");
		envTask();
		HOAGS_INFO("\n");
		vTaskDelay(2000);
		HOAGS_INFO("\n");

		HOAGS_ERR("xPortGetFreeHeapSize=%d\n", xPortGetFreeHeapSize());
		HOAGS_INFO("\"%s\" Connected\n", AWS_IOT_CORE_ENDPOINT);

		//strcat(connectData.clientID.cstring, &(macid[0]));
		memset(clientId, 0, sizeof(clientId));
		strcat(clientId, HOAGS_CLIENT_ID);
		//getMACID();
		strcat(clientId, umObj.macid);
		connectData.MQTTVersion = HOAGS_MQTT_VERSION;
		connectData.clientID.cstring = clientId;

		HOAGS_ERR("xPortGetFreeHeapSize=%d\n", xPortGetFreeHeapSize());
		HOAGS_INFO("Device Clientid=%s\n", connectData.clientID.cstring);

		HOAGS_INFO("Start MQTT connection\n");
		
		while ((rc = MQTTConnect(&client, &connectData)) != 0) {
			HOAGS_DBG("Return code from MQTT connect is %d\n", rc);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}

		HOAGS_ERR("xPortGetFreeHeapSize=%d\n", xPortGetFreeHeapSize());
		HOAGS_INFO("MQTT Connected\n");

		mqtt_printf(MQTT_INFO, "Subscribe to Topic: %s", subUiControlTopic);
		if ((rc = MQTTSubscribe(&client, subUiControlTopic, QOS1, messageArrivedUIControl)) != 0) {
			mqtt_printf(MQTT_INFO, "Return code from MQTT subscribe is %d\n", rc);
		}

		mqtt_printf(MQTT_INFO, "Subscribed to Topic: %s", subPing);
	    if ((rc = MQTTSubscribe(&client, subPing, QOS1, messageArrived)) != 0) 
		{
		   mqtt_printf(MQTT_INFO, "Return code from MQTT subscribe is %d\n", rc);
          
		}

	   mqtt_printf(MQTT_INFO, "Publish Topics: %s", "hoags/analytics");

		size_t counter = 0;
		char* data = NULL;

		//moved from dataCollector json
		if(initStaticJson() == FALSE)
		{
			HOAGS_ERR("Error initStaticJson, returning\n");
			vTaskDelete(NULL);
			return;
		}
#if 1
		do {
			//watchdog_refresh();

			++counter;
			hqtt.id = MT_NONE;
			hqtt.data = "";
			struct hoagsMqtt* hqttPtr;
			//HOAGS_INFO("hqtt.id=%d(%p) hqtt.data=%s(%p)(%02x)\n", hqtt.id, &(hqtt.id), hqtt.data, hqtt.data, *(hqtt.data));
			if(xQueueReceive(pubDataAnalQueueHandle, &hqttPtr, 0) == pdTRUE)//If timeout is not 0, then messageArrived callback is not hitting
			{	
				hqtt.id = hqttPtr->id;
				hqtt.data = hqttPtr->data;
				//HOAGS_INFO("hqtt=%p hqtt.id=%d(%p) hqtt.data=%s(%p)(%02x)\n", &hqtt, hqtt.id, &(hqttPtr->id), hqtt.data, hqtt.data, *(hqtt.data));
				//HOAGS_INFO("hqttPtr=%p hqttPtr->id=%d(%p) hqttPtr->data=%s(%p)(%02x)\n", hqttPtr, hqttPtr->id, &(hqttPtr->id), hqttPtr->data, hqttPtr->data, *(hqttPtr->data));
				HOAGS_INFO("Received, id=%d data=%s\ndataLen:%ld\n", hqtt.id, hqtt.data, strlen(hqtt.data));
			}
			else	
			{
				HOAGS_ERR("Queue is empty\n");
			}
			//HOAGS_INFO("hqtt.id=%d(%p) hqtt.data=%s(%p)(%02x)\n", hqtt.id, &(hqtt.id), hqtt.data, hqtt.data, *(hqtt.data));
			MQTTMessage message;
			message.qos = QOS1;
			message.retained = 0;
			message.payload = hqtt.data;
			message.payloadlen = strlen(hqtt.data);

			switch(hqtt.id)
			{
				case MT_REGISTER:
					HOAGS_INFO("Publishing to %s\n", REGISTER_TOPIC);
					if ((rc = MQTTPublish(&client, REGISTER_TOPIC, &message)) != 0) 
					{
						HOAGS_ERR("Return code from MQTT publish is %d\n", rc);
					}
					else
					{
						HOAGS_ERR("Published success: for MT_REGISTER\n");
						free(message.payload);
					}
					
					break;
#if AWS_ANALYTICS_ENABLE				
				case MT_POWERUSAGE:
					HOAGS_INFO("Publishing to %s:%s\n", pubUiControlAckNotifyTopic, hqtt.data);
					if ((rc = MQTTPublish(&client, pubUiControlAckNotifyTopic, &message)) != 0) 
					{
						HOAGS_ERR("Return code from MQTT publish is %d\n", rc);
					}
					else
					{
						HOAGS_ERR("Published success: for MT_POWERUSAGE\n");
						free(message.payload);
					}
				
					break;
				case MT_GASLEAK:
					HOAGS_INFO("Publishing to %s:%s\n", pubUiControlAckNotifyTopic, hqtt.data);
					if ((rc = MQTTPublish(&client, pubUiControlAckNotifyTopic, &message)) != 0) 
					{
						HOAGS_ERR("Return code from MQTT publish is %d\n", rc);
					}
				    else{
						HOAGS_ERR("Published success: for MT_GASLEAK\n");
                        free(message.payload);
					}
					break;
				
				case MT_FILTERCHANGE:
					HOAGS_INFO("Publishing to %s:%s\n", pubUiControlAckNotifyTopic, hqtt.data);
					if ((rc = MQTTPublish(&client, pubUiControlAckNotifyTopic, &message)) != 0) 
					{
						HOAGS_ERR("Return code from MQTT publish is %d\n", rc);
					}
					else
					{
						HOAGS_ERR("Published success: for MT_FILTERCHANGE\n");
						free(message.payload);
					}
					break;
#endif				
				case MT_PING:
					HOAGS_INFO("Publishing to %s:%s\n", pubPing, hqtt.data);
					if ((rc = MQTTPublish(&client, pubPing, &message)) != 0) //pubDataAnalTopic
					{
						HOAGS_ERR("Return code from MQTT publish is %d\n", rc);
					}
					else
					{
						HOAGS_ERR("Published success: for MT_PING\n");
						free(message.payload);
					}
					
					break;
#if AWS_ANALYTICS_ENABLE				
				
					case MT_ANALYTICS:
					#if AMBER_AC
					updateAnalJsonAmb();
					#elif OMNI_AC
					updateAnalJsonOmni();
					#else
					updateAnalJson();
					#endif
					data = cJSON_Print(dataAnalyticInfo);
					message.payload = data;
					message.payloadlen = strlen(data);
					HOAGS_INFO("Publishing to %s\n", ANALYTIC_TOPIC);
					if ((rc = MQTTPublish(&client, ANALYTIC_TOPIC, &message)) != 0) //pubDataAnalTopic
					{
						HOAGS_ERR("Return code from MQTT publish is %d\n", rc);
					}
					else
					{
						HOAGS_ERR("Published success: for ANALYTIC_TOPIC\n");
						free(message.payload);
					}
					
					break;
#endif			
	
				case MT_UIACK:
				{
					#if 1
					if(isAckReceived)
					{
						char *strrr;
						#if ATOMBERG_FAN
						strrr = hoagsMalloc(256);
						sprintf(strrr, "Poll:%d:%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
									0, 
									*(atombergAck+0), *(atombergAck+1), *(atombergAck+2), *(atombergAck+3),	*(atombergAck+4), *(atombergAck+5), *(atombergAck+6), *(atombergAck+7),
									*(atombergAck+8), *(atombergAck+9), *(atombergAck+10), *(atombergAck+11), *(atombergAck+12), *(atombergAck+13), *(atombergAck+14), *(atombergAck+15),
									*(atombergAck+16), *(atombergAck+17), *(atombergAck+18), *(atombergAck+19), *(atombergAck+20), *(atombergAck+21), *(atombergAck+22), *(atombergAck+23), *(atombergAck+24), *(atombergAck+25),
									*(atombergAck+26), *(atombergAck+27), *(atombergAck+28), *(atombergAck+29),	*(atombergAck+30), *(atombergAck+31), *(atombergAck+32), *(atombergAck+33),
									*(atombergAck+34), *(atombergAck+35), *(atombergAck+36), *(atombergAck+37), *(atombergAck+38), *(atombergAck+39), *(atombergAck+40), *(atombergAck+41),
									*(atombergAck+42), *(atombergAck+43), *(atombergAck+44), *(atombergAck+45), *(atombergAck+46), *(atombergAck+47), *(atombergAck+48), *(atombergAck+49), *(atombergAck+50), *(atombergAck+51),
									*(atombergAck+52), *(atombergAck+53), *(atombergAck+54), *(atombergAck+55), *(atombergAck+56), *(atombergAck+57), *(atombergAck+58), *(atombergAck+59), *(atombergAck+60), *(atombergAck+61));

						#elif VIRTUALFOREST_AC
						strrr = hoagsMalloc(256);
						sprintf(strrr, "Poll:%d:%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
											0, 
											*(vfAck+0), *(vfAck+1), *(vfAck+2), *(vfAck+3),	*(vfAck+4), *(vfAck+5), *(vfAck+6), *(vfAck+7),
											*(vfAck+8), *(vfAck+9), *(vfAck+10), *(vfAck+11), *(vfAck+12), *(vfAck+13), *(vfAck+14), *(vfAck+15),
											*(vfAck+16), *(vfAck+17), *(vfAck+18), *(vfAck+19), *(vfAck+20), *(vfAck+21), *(vfAck+22), *(vfAck +23));

						#elif VERSADEVICES_SUPERFAN_IOT
						char *pPacket = getAckPacketDataString();
						strrr = hoagsMalloc(10 + strlen(pPacket));
						sprintf(strrr, "Poll:%d:%s", 0, pPacket);
						
						#elif AMBER_AC || OMNI_AC
                        char *pPacket = getAckPacketDataString();
                        strrr = hoagsMalloc(10 + strlen(pPacket));
                        sprintf(strrr, "Poll:%d:%s", 0, pPacket);

						#elif LIVPURE_CHIMNEY
						sprintf(strrr, "Poll:%d:%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
									0, 
									*(lvprAck+0), *(lvprAck+1), *(lvprAck+2), *(lvprAck+3),	*(lvprAck+4), *(lvprAck+5), *(lvprAck+6), *(lvprAck+7),
									*(lvprAck+8), *(lvprAck+9), *(lvprAck+10), *(lvprAck+11), *(lvprAck+12), *(lvprAck+13), *(lvprAck+14), *(lvprAck+15),
									*(lvprAck+16), *(lvprAck+17), *(lvprAck+18), *(lvprAck+19), *(lvprAck+20), *(lvprAck+21), *(lvprAck+22), *(lvprAck+23), *(lvprAck+24), *(lvprAck+25));

						#elif VGUARD_NEW_FAN
						strrr = hoagsMalloc(20);
						sprintf(strrr, "Poll:%d:%02x%02x%02x%02x%02x%02x%02x%02x",
								0,
								*(vgAck+0), *(vgAck+1), *(vgAck+2), *(vgAck+3),	*(vgAck+4), *(vgAck+5), *(vgAck+6), *(vgAck+7));

						#endif

						message.payload = strrr;
						message.payloadlen = strlen(strrr);
						HOAGS_ERR("Publishing to %s:%s\n", pubUiControlAckTopic, message.payload);
						//HOAGS_INFO("%s\n", strrr);
						if ((rc = MQTTPublish(&client, pubUiControlAckTopic, &message)) != 0) 
						{
							HOAGS_ERR("Return code from MQTT publish is %d\n", rc);
						}
						else
						{
						    HOAGS_ERR("Published success: for pubUiControlAckTopic\n");
							free(message.payload);
						}
					}
                    #endif
					#if 0
					if(isAckReceived == 0)
					{
						char strrr[64];
							sprintf(strrr, "Poll:%d:%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
													0, 
													*(mallocAck+0), *(mallocAck+1), *(mallocAck+2), *(mallocAck+3),	*(mallocAck+4), *(mallocAck+5), *(mallocAck+6), *(mallocAck+7), *(mallocAck+8), *(mallocAck+9), *(mallocAck+10), *(mallocAck+11), *(mallocAck+12),
													*(mallocAck+13), *(mallocAck+14));
							message.payload = strrr;
							message.payloadlen = strlen(strrr);
							HOAGS_INFO("Publishing to %s:%s\n", pubUiControlAckTopic, message.payload);
							HOAGS_ERR("%s\n", strrr);
							if ((rc = MQTTPublish(&client, pubUiControlAckTopic, &message)) != 0) 
							{
								HOAGS_ERR("Return code from MQTT publish is %d\n", rc);
							}
					}
					#endif
				}	
					break;
				
				default:
					//keepalive(&client);//Suvarna: This pings MQTT
					
					break;

			}
			
			#if 1//Suvarna: Avoid sending huge analytic data just for discovery
			#if AWS_ANALYTICS_ENABLE
			#if AMBER_AC
			updateAnalJsonAmb();
			#elif OMNI_AC
			updateAnalJsonOmni();
			#else
			//updateAnalJson();
			#endif
			
			// data = cJSON_Print(dataAnalyticInfo);
			// message.payload = data;
			// message.payloadlen = strlen(data);
			message.payload = "{}";
			message.payloadlen = strlen("{}");
			#else
			// message.payload = "{}";
			// message.payloadlen = strlen("{}");
			#endif
			//HOAGS_INFO("Publishing to %s data=%s\n", ANALYTIC_TOPIC, data);
			// if ((rc = MQTTPublish(&client, ANALYTIC_TOPIC, &message)) != 0) //pubDataAnalTopic
			// {
			// 	HOAGS_ERR("Return code from MQTT publish is %d\n", rc);
			// }
			// else
			// {
			// 	HOAGS_ERR("Published success: for ANALYTIC_TOPIC\n");
			// 	free(message.payload);
			// }
			#endif
			vTaskDelay(2000);

		} while(!(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS));   //((((wifi_get_join_status() == RTW_JOINSTATUS_SUCCESS) && (*(u32 *)LwIP_GetIP(0) != IP_ADDR_INVALID))));
#endif
		//MQTTDisconnect(&client);
	}

    return TRUE;
}

#if 0
int publishToAWSIot(char* topicName, char* data)
{
	HOAGS_INFO("topicName=%s data=%s len=%d\n", topicName, data, strlen(data));
	int rc = 0, count = 0;
    while (1) {
		MQTTMessage message;
		char payload[300];

		if (++count == 0) {
			count = 1;
		}

		message.qos = QOS1;
		message.retained = 0;
		message.payload = payload;
		sprintf(payload, "hello from different function %d", count);
		message.payloadlen = strlen(payload);

		printf("Suvarna payload=%s payloadLen=%d\n", payload, strlen(payload));

		if ((rc = MQTTPublish(&client, AWSIOT_DATA_ANALYTIC_TOPIC, &message)) != 0) {
			mqtt_printf(MQTT_INFO, "Return code from MQTT publish is %d\n", rc);
		}
		#if 0
		if ((rc = MQTTYield(&client, 1000)) != 0) {
			mqtt_printf(MQTT_INFO, "Return code from yield is %d\n", rc);
		}
		#endif
		vTaskDelay(5000);
	}

    return rc;
}
#endif


void startAWSIOT(void)
{
	xTaskCreate(initAWSIOTCore,	/* The function that implements the task. */
				"initAWSIOTCore",			/* Just a text name for the task to aid debugging. */
				1200,	/* The stack size is defined in FreeRTOSIPConfig.h. */
				NULL,		/* The task parameter, not used in this case. */
				tskIDLE_PRIORITY+4,		/* The priority assigned to the task is defined in FreeRTOSConfig.h. */
				NULL);				/* The task handle is not used. */
}

#endif
