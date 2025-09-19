#include <time.h>
#include "cJSON.h"
#include "dataCollector.h"
#include "awsiot.h"
#include "env.h"
#include "packets.h"
#include "fan.h"
#include <string.h>

extern struct serial_s superFanObj;
extern unsigned char vfAck[24];
extern unsigned char omniAck[15]; 
#if AMBER_AC
extern unsigned char ambAck[15];
unsigned char checkBytes[] = {0x55, 0xAA, 0x03};
#endif
extern void* hoagsMalloc(size_t sz);
extern char* mallocAck;
extern char* mallocvdAck;
extern char* mallocomniAck;
#if VERSADEVICES_SUPERFAN_IOT
extern unsigned char vdAck[15];
unsigned char ackTestvd[] = {0x55, 0xAA, 0x03, 0x07, 0x00};
extern TimerHandle_t timerObj;
extern TimerHandle_t timerObj1;
extern QueueHandle_t ackQ;
extern QueueHandle_t toAckQ;
extern QueueHandle_t actionIdQ;
extern QueueHandle_t toQ;
extern QueueHandle_t cmdQ;
extern void (*lastAction)(void);
unsigned char statusonoff[] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x06 ,0x02 ,0x01 ,0x00 ,0x02 ,0x01 ,0x00, 0x00, 0x00, 0x00};
unsigned char statuson[] =    {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x06 ,0x02 ,0x01 ,0x00 ,0x02 ,0x01 ,0x01, 0x16, 0x00, 0x00};
unsigned char statusmode[] =  {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01, 0x00, 0x00, 0x00, 0x00, 0x00}; 
unsigned char statusfansp[] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x06 ,0x04 ,0x02 ,0x00 ,0x02 ,0x01, 0x00, 0x00, 0x00, 0x00};
unsigned char statusTimer[] = {0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x22, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char lastUpdate = 0;
#endif
int sentacktocloud = 0;
extern unsigned char hdcpAck[26];
extern unsigned char atombergAck[62];
#if HAVELLS_HANDTUNED || HAVELLS_AC
extern unsigned char havellsAck[12];
#endif
#if LIVPURE_CHIMNEY
extern unsigned char lvprAck[26];
#endif
#if VGUARD_NEW_FAN
extern unsigned char vgAck[8];  
#endif

extern BOOL isAckReceived;
//extern char univMacid[13];
//extern BOOL macidSet;

//Global hqtts
struct hoagsMqtt hqttUiAck = {MT_UIACK, ""};
struct hoagsMqtt hqttRegister = {MT_REGISTER, ""};
struct hoagsMqtt hqttPowerUsage = {MT_POWERUSAGE, "PowerUsage:9"};
struct hoagsMqtt hqttFilterChange = {MT_FILTERCHANGE, "FilterChange"};
struct hoagsMqtt hqttAnalytics = {MT_ANALYTICS, ""};
struct hoagsMqtt hqttGasLeak = {MT_GASLEAK, "LEAK"};

char* hqttData = NULL;

cJSON* uiControlInfo	=	NULL;
//cJSON_Hooks memoryHook;

QueueHandle_t pubDataAnalQueueHandle = NULL;
//QueueHandle_t pubUiControlQueueHandle = NULL;
//QueueHandle_t subUiControlQueueHandle = NULL;

BOOL initQueue()
{	
	#if VERSADEVICES_SUPERFAN_IOT
	ackQ = xQueueCreate(10, sizeof(unsigned char*)); //shaik
	cmdQ = xQueueCreate(50, sizeof(void*));
    actionIdQ = xQueueCreate(50, sizeof(short));
    toQ = xQueueCreate(5, sizeof(void*));
	#endif

	pubDataAnalQueueHandle = xQueueCreate(40, sizeof(struct hoagsMqtt*));

	if(pubDataAnalQueueHandle == 0 /*|| subUiControlQueueHandle == 0*/)
		return FALSE;
	
	return TRUE;
}

#if 0
BOOL isMacSet()
{
	for (int i = 0; i < sizeof(univMacid); ++i) 
	{
        if (univMacid[i] != '\0') 
		{
            return TRUE;
        }
    }

	return TRUE;
}


void getMACID()
{
	
	while(!macidSet)
	{
		HOAGS_INFO("Reading macid...\n");
		vTaskDelay(4000);
	}

	HOAGS_INFO("macid fetched=%s\n", univMacid);
	
	#if 0

	uint8_t* macid =  get_ble_id();
	
		
	sprintf(univMacid, "%02x%02x%02x%02x%02x%02x",
												*macid,
												*(macid+1), 
												*(macid+2), 
												*(macid+3),
												*(macid+4),
												*(macid+5));
	
	HOAGS_INFO("macid fetched=%s\n", univMacid);
	#endif

}

#endif
#if 0
char *generate_json_data(int i, int r, int g, int b)
{


	cJSON_Hooks memoryHook;

	memoryHook.malloc_fn = malloc;
	memoryHook.free_fn = free;
	cJSON_InitHooks(&memoryHook);


	cJSON *IOTJSObject = NULL, *colorJSObject = NULL;
	char *iot_json = NULL;

	if ((IOTJSObject = cJSON_CreateObject()) != NULL) {
		cJSON_AddItemToObject(IOTJSObject, "Motion_Sensor", cJSON_CreateNumber(i));
		cJSON_AddItemToObject(IOTJSObject, "Light", colorJSObject = cJSON_CreateObject());

		cJSON_AddItemToObject(colorJSObject, "Red", cJSON_CreateNumber(r));
		cJSON_AddItemToObject(colorJSObject, "Green", cJSON_CreateNumber(g));
		cJSON_AddItemToObject(colorJSObject, "Blue", cJSON_CreateNumber(b));

		iot_json = cJSON_Print(IOTJSObject);
		cJSON_Delete(IOTJSObject);
	}
	return iot_json;

}

char* fetchStaticDetails()
{
	cJSON_Hooks memoryHook;

	memoryHook.malloc_fn = malloc;
	memoryHook.free_fn = free;
	cJSON_InitHooks(&memoryHook);

	cJSON* staticInfo = NULL;
	
	if((staticInfo = cJSON_CreateObject()) == NULL)
	{
		HOAGS_ERR("Error creating staticInfo object\n");
		return FALSE;
	}

	cJSON_AddItemToObject(staticInfo, "static", cJSON_CreateNumber(2));

	char* data = cJSON_Print(staticInfo);

	cJSON_Delete(staticInfo);

	return data;
	//cJSON_AddItemToObject(dataAnalyticInfo, "static", staticInfo);

	char content[12];
	memset(content, 0, sizeof(content));

	getMACID(content);
	cJSON_AddStringToObject(staticInfo, MACID, content);

	HOAGS_INFO("macid=%s\n", content);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_PRODMODEL,content);
	cJSON_AddStringToObject(staticInfo, PRODUCT_MODEL, content);

	HOAGS_INFO("productModel=%s\n", content);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_CUSTNAME,content);
	cJSON_AddStringToObject(staticInfo, CUST_NAME, content);

	HOAGS_INFO("customerName=%s\n", content);

	return TRUE;

}

int fetchDynamicDetails()
{

}
#endif
#if 1
void sendAckToCloud() {

        #if AMBER_AC 
		memcpy(mallocAck, ambAck, sizeof(ambAck));
		#elif VERSADEVICES_SUPERFAN_IOT
		memcpy(mallocvdAck, vdAck, sizeof(vdAck));
		#elif OMNI_AC
		memcpy(mallocomniAck, omniAck, sizeof(omniAck));
		#endif

		struct hoagsMqtt* hmPtr = &hqttUiAck;
		xQueueSend(pubDataAnalQueueHandle, &hmPtr, xQUEUE_TIMEOUT);

		hmPtr = &hqttAnalytics;
		xQueueSend(pubDataAnalQueueHandle, &hmPtr, xQUEUE_TIMEOUT);
}
#endif

#if 0
void getFwVersion(char fwVersion[])
{
	update_manifest_info imgInfo;
    memcpy(&imgInfo, IMG_IMG2_OTA1_ADDR + OTA_IMG_CERTIFICATE, sizeof(update_manifest_info));
	sprintf(fwVersion, "%d.%d", imgInfo.MajorImgVer, imgInfo.MinorImgVer);
}
#endif
// void fwversion_read(char fwVersion[])
// {
// 	HOAGS_MAN_RAW("FW_VERSION=%d.%d\n", imgInfo.MajorImgVer, imgInfo.MinorImgVer);
// 	sprintf(fwVersion, "%d.%d", imgInfo.MajorImgVer, imgInfo.MinorImgVer);
// }

#if 0
void envAlert(const char* key, const char* value)
{
	HOAGS_INFO("%s:%s:%d:key=%s:value:%s\n", __FILE__, __func__, __LINE__, key, value);
}
#endif
#if 1
void createResigsterData()
{
	cJSON_Hooks memoryHook;
	memoryHook.malloc_fn = hoagsMalloc;
	memoryHook.free_fn = free;
	cJSON_InitHooks(&memoryHook);

	cJSON* registerInfo = NULL;
	
	if((registerInfo = cJSON_CreateObject()) == NULL)//hoags/custname/macid/friendlyname
	{
		HOAGS_ERR("Error creating registerInfo object\n");
		return FALSE;
	}

	char* content[16];

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_CUSTNAME,content);
	cJSON_AddStringToObject(registerInfo, REGISTER_CUSTNAME, content);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_PRODTYPE,content);
	cJSON_AddStringToObject(registerInfo, REGISTER_PRODTYPE, content);

	cJSON_AddStringToObject(registerInfo, REGISTER_MACID, umObj.macid);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_USERID,content);
	if(strcmp(content, "0") == 0)
	{
		HOAGS_ERR("No userid set, not registering device...\n");
		return;
	}
	cJSON_AddStringToObject(registerInfo, REGISTER_USERID, content);

	memset(content, 0, sizeof(content));
	getEnvItem(ENV_FRIENDLYNAME,content);
	cJSON_AddStringToObject(registerInfo, REGISTER_FRIENDLYNAME, content);

	hqttData = cJSON_Print(registerInfo);
	cJSON_Delete(registerInfo);

	HOAGS_INFO("Register=%s=%d\n", hqttData, strlen(hqttData));
	
	hqttRegister.data = hqttData;

	struct hoagsMqtt* hmPtr = &hqttRegister;
	xQueueSend(pubDataAnalQueueHandle, &hmPtr, xQUEUE_TIMEOUT);

	return;

}

void createPowerUsageData()
{
	HOAGS_INFO("%s:%d\n", hqttPowerUsage.data, strlen(hqttPowerUsage.data));
	//HOAGS_INFO("hqttPowerUsage=%p hqttPowerUsage.id=%d(%p) hqttPowerUsage.data=%s(%p)(%02x)\n", &hqttPowerUsage, hqttPowerUsage.id, &(hqttPowerUsage.id), hqttPowerUsage.data, hqttPowerUsage.data, *(hqttPowerUsage.data));
	struct hoagsMqtt* hmPtr = &hqttPowerUsage;
	xQueueSend(pubDataAnalQueueHandle, &hmPtr, xQUEUE_TIMEOUT);

}
#if 0
void alertGasLeak()
{
	HOAGS_INFO("%s:%d\n", hqttGasLeak.data, strlen(hqttGasLeak.data));
	struct hoagsMqtt* hmPtr = &hqttGasLeak;
	xQueueSend(pubDataAnalQueueHandle, &hmPtr, xQUEUE_TIMEOUT);	
}
#endif
void createFilterChange()
{
	HOAGS_INFO("%s:%d\n", hqttFilterChange.data, strlen(hqttFilterChange.data));

	struct hoagsMqtt* hmPtr = &hqttFilterChange;
	xQueueSend(pubDataAnalQueueHandle, &hmPtr, xQUEUE_TIMEOUT);

}
#if 0
void updateData(cJSON * defaultAnalyticInfo,char vfAck[], int key)
{
	char temp[8];
	// temp[0] = vfAck[key];
	sprintf(temp, "%02x", vfAck[key]);
	cJSON *jo = cJSON_GetObjectItem(defaultAnalyticInfo,temp);
	
	switch(key)
	{
		case 5:
				if(((int)(cJSON_GetNumberValue(jo))) == 0)
				{ 
					cJSON_AddNumberToObject(defaultAnalyticInfo,temp,1);
				}
				else
				{
					int value = (int) cJSON_GetNumberValue(jo);
					++value;
					cJSON_ReplaceItemInObject(defaultAnalyticInfo, temp, cJSON_CreateNumber(value));
				}
				break;
		case 6:
				if(((int)(cJSON_GetNumberValue(jo))) == 0)
				{ 
					cJSON_AddNumberToObject(defaultAnalyticInfo,temp,1);
				}
				else
				{
					int value = (int) cJSON_GetNumberValue(jo);
					++value;
					cJSON_ReplaceItemInObject(defaultAnalyticInfo, temp, cJSON_CreateNumber(value));
				}
				break;
		case 10:
				if(((int)(cJSON_GetNumberValue(jo))) == 0)
				{ 
					cJSON_AddNumberToObject(defaultAnalyticInfo,temp,1);
				}
				else
				{
					int value = (int) cJSON_GetNumberValue(jo);
					++value;
					cJSON_ReplaceItemInObject(defaultAnalyticInfo, temp, cJSON_CreateNumber(value));
				}
				break;
		default:
					HOAGS_DBG("****************************In default****************\n");
	}
	
}
#endif
#if VERSADEVICES_SUPERFAN_IOT
#if 1

#define SF_PACKET_INDEX_COUNT 6
static ackPktCacheindex[SF_PACKET_INDEX_COUNT] = {0x2, 0x4, 0x21, 0x29, 0x7, 0x22};
static char ackPacketCache[SF_PACKET_INDEX_COUNT][30] = {0};
static time_t ackNextUpdateTime = 0;


char* getAckPacketFromCache (unsigned char type) {
    for (int i = 0; i < sizeof(ackPktCacheindex) / sizeof(int); i++) {
        if (type == ackPktCacheindex[i]) {
            return ackPacketCache[i];
        }
    }
    return NULL;
}
#endif
char* getAckPacketDataString() {
	int length = 10; // Just buffer
	for (int i = 0; i < sizeof(ackPktCacheindex)/ sizeof(int); i++) {
		length += ((ackPacketCache[i][4] << 8) | ackPacketCache[i][5]) + 7;
	}
	length *= 2;
	char *pPacket = hoagsMalloc(length);
	memset(pPacket, 0, length);

	for (int i = 0, k = 0; (i < sizeof(ackPktCacheindex)/ sizeof(int)); i++) {
		/*printf ("Complete cache: %d %02x%02x%02x%02x%02x%02x%02x%02x\n", ackPktCacheindex[i],
		ackPacketCache[i][0],
		ackPacketCache[i][1],
		ackPacketCache[i][2],
		ackPacketCache[i][3],
		ackPacketCache[i][4],
		ackPacketCache[i][5],
		ackPacketCache[i][6],
		ackPacketCache[i][7]);*/
	}
	for (int i = 0, k = 0; (i < sizeof(ackPktCacheindex)/ sizeof(int)); i++) {
		if (ackPacketCache[i][0] == 0) {
			/* No data present in this cache */
			continue;
		}
		int ackLen = ((ackPacketCache[i][4] << 8) | ackPacketCache[i][5]) + 7;
		for (int j = 0; (j < ackLen) && (k < length); j++, k+=2) { 
			char tmp[3];
			sprintf(tmp, "%02x", ackPacketCache[i][j]);
			//printf("Tmp: %s\n", tmp);
			pPacket[k] = tmp[0];
			pPacket[k+1] = tmp[1];
		}
		
	}
	//printf("Ack packet %s\n", pPacket);
	return pPacket;
}
#if 1
int updateAckStatusSF(char* vdAck, unsigned char lastUpdate)
{
	int packetchanged = 0;

	for (int i = 0; i < sizeof(ackPktCacheindex) / sizeof(int); i++) 
	{
		if (vdAck[6] == ackPktCacheindex[i]) 
		{
			int len = ((vdAck[4] << 8) | vdAck[5]) + 7;
			if (memcmp(vdAck, ackPacketCache[i], len) != 0) 
			{
				memcpy(ackPacketCache[i], vdAck, len);
				packetchanged = 1;
			}
			break;
		}
	}

	if (lastUpdate == 1)
	{
		memset(ackPacketCache[2], 0x00, sizeof(ackPacketCache[2]));
	}
	else if (lastUpdate == 2)
	{
		memset(ackPacketCache[1], 0x00, sizeof(ackPacketCache[1]));
	}

	return packetchanged;
}

void clearAppCacheAtIndex(unsigned char type) {
	if(type != 0x22)
	{
		memcpy(ackPacketCache[0], statuson, sizeof(statuson));
	}
	//printf("Clear ack packet of type %02x\n", type);
	for (int i = 0; i < sizeof(ackPktCacheindex) / sizeof(int); i++) {
		// printf("type %02x, ackPktCacheIndex %02x\n", type,ackPktCacheindex[i]);
		if (type == ackPktCacheindex[i]) {
			ackPacketCache[i][0] = 0; 
			// printf("Clearing the packet in ack cache\n");
			break;
		}
	}
}
static time_t timerSetTime;

void setTimerUnderProcess(char* vdAck) {

	timerSetTime = rtc_read();
	}

int isTimerUnderProcess() {
	
	time_t currentTime = rtc_read(); // Timer under process
	if ((ackPacketCache[5][0] != 0) && (difftime(currentTime, timerSetTime) < 5)) {
		printf("Timer is under process\n");
		return 1;
	}
	if (ackPacketCache[5][0] != 0) { // If Timer expires
		printf("Timer expired\n");
		ackPacketCache[5][0] = 0;
		clearAppCacheAtIndex(0x04);
		clearAppCacheAtIndex(0x21);
	}
	printf("Timer not running and clearing\n");
	clearAppCacheAtIndex(0x04); // Timer not running 
	clearAppCacheAtIndex(0x21); 
	clearAppCacheAtIndex(0x02); 
	return 0;
}
#endif
#elif AMBER_AC 
#define AMB_PACKET_INDEX_COUNT 10
static ackPktCacheindex[AMB_PACKET_INDEX_COUNT] = {0x1, 0x2, 0x4, 0x5, 0x19, 0x67, 0x6D, 0x6E, 0x6F};
static char ackPacketCache[AMB_PACKET_INDEX_COUNT][30] = {0};
static time_t ackNextUpdateTime = 0;

 
char* getAckPacketDataString() {
    int length = 10; // Just buffer
    for (int i = 0; i < sizeof(ackPktCacheindex)/ sizeof(int); i++) {
        length += ((ackPacketCache[i][4] << 8) | ackPacketCache[i][5]) + 7;
    }
    length *= 2;
    char *pPacket = hoagsMalloc(length);
    memset(pPacket, 0, length);
    for (int i = 0, k = 0; (i < sizeof(ackPktCacheindex)/ sizeof(int)); i++) {
        /*printf ("Complete cache: %d %02x%02x%02x%02x%02x%02x%02x%02x\n", ackPktCacheindex[i],
        ackPacketCache[i][0],
        ackPacketCache[i][1],
        ackPacketCache[i][2],
        ackPacketCache[i][3],
        ackPacketCache[i][4],
        ackPacketCache[i][5],
        ackPacketCache[i][6],
        ackPacketCache[i][7]);*/
    }
    for (int i = 0, k = 0; (i < sizeof(ackPktCacheindex)/ sizeof(int)); i++) {
        if (ackPacketCache[i][0] == 0) {
            /* No data present in this cache */
            continue;
        }
        int ackLen = ((ackPacketCache[i][4] << 8) | ackPacketCache[i][5]) + 7;
        for (int j = 0; (j < ackLen) && (k < length); j++, k+=2) {
            char tmp[3];
            sprintf(tmp, "%02x", ackPacketCache[i][j]);
            //printf("Tmp: %s\n", tmp);
            pPacket[k] = tmp[0];
            pPacket[k+1] = tmp[1];
        }
       
    }
    return pPacket;
}

#elif OMNI_AC
#define OMNI_PACKET_INDEX_COUNT 10
static ackPktCacheindex[OMNI_PACKET_INDEX_COUNT] = {0x1, 0x2, 0x4, 0x5, 0x6A, 0x67, 0x71, 0x72, 0x73};
static char ackPacketCache[OMNI_PACKET_INDEX_COUNT][30] = {0};
static time_t ackNextUpdateTime = 0;

 
char* getAckPacketDataString() {
    int length = 10; // Just buffer
    for (int i = 0; i < sizeof(ackPktCacheindex)/ sizeof(int); i++) {
        length += ((ackPacketCache[i][4] << 8) | ackPacketCache[i][5]) + 7;
    }
    length *= 2;
    char *pPacket = hoagsMalloc(length);
    memset(pPacket, 0, length);
    for (int i = 0, k = 0; (i < sizeof(ackPktCacheindex)/ sizeof(int)); i++) {
        /*printf ("Complete cache: %d %02x%02x%02x%02x%02x%02x%02x%02x\n", ackPktCacheindex[i],
        ackPacketCache[i][0],
        ackPacketCache[i][1],
        ackPacketCache[i][2],
        ackPacketCache[i][3],
        ackPacketCache[i][4],
        ackPacketCache[i][5],
        ackPacketCache[i][6],
        ackPacketCache[i][7]);*/
    }
    for (int i = 0, k = 0; (i < sizeof(ackPktCacheindex)/ sizeof(int)); i++) {
        if (ackPacketCache[i][0] == 0) {
            /* No data present in this cache */
            continue;
        }
        int ackLen = ((ackPacketCache[i][4] << 8) | ackPacketCache[i][5]) + 7;
        for (int j = 0; (j < ackLen) && (k < length); j++, k+=2) {
            char tmp[3];
            sprintf(tmp, "%02x", ackPacketCache[i][j]);
            //printf("Tmp: %s\n", tmp);
            pPacket[k] = tmp[0];
            pPacket[k+1] = tmp[1];
        }
       
    }
    return pPacket;
}

#endif
#endif
void fetchDeviceDetails()	
{
	//u16_t len = 0x00;

	if(initQueue() == FALSE)
	{
		HOAGS_ERR("Error in initQueue, returning...\n");
		return;	
	}

#if VIRTUALFOREST_AC
	memset(vfAck, 0, sizeof(vfAck));
#elif HAVELLS_AC
	memset(havellsAck, 0, sizeof(havellsAck));
#elif VERSADEVICES_SUPERFAN_IOT
	memset(vdAck, 0, sizeof(vdAck));
#elif VGUARD_NEW_FAN
	memset(vgAck, 0, sizeof(vgAck));
#elif AMBER_AC
	memset(ambAck, 0, sizeof(ambAck));
#elif RR_KABLES
	memset(hdcpAck, 0, sizeof(hdcpAck));
#elif ATOMBERG_FAN
	memset(atombergAck, 0, sizeof(atombergAck));
#elif OMNI_AC
	memset(omniAck, 0, sizeof(omniAck));
#endif
	
	struct hoagsMqtt hqtt = {MT_NONE, ""};

	vTaskDelay(2000);

	createResigsterData();
	//createPowerUsageData();

	unsigned char* ackReceived = NULL;
	int frameHeader = 0;
	int lenn = 0;

	// LOOP_HERE
#if 1
#if VERSADEVICES_SUPERFAN_IOT
int count;
HOAGS_ERR("Inside SF query\n");
send_heartbeat();
// unsigned char sentquery[] = {0x55, 0xAA, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00};
// displayDataUC((unsigned char*)&sentquery, sizeof(sentquery)); 
// serial_clear_rx(&superFanObj);
// uart_send_bytes(&superFanObj,  (char*)&sentquery, sizeof(sentquery));
// HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
count = 2;

while (count) {
	serial_clear_rx(&superFanObj);
	memset(vdAck, 0x00, sizeof(vdAck));
	int len = serial_recv_blocked(&superFanObj, &vdAck, 6, 100000);
	if(memcmp(vdAck, ackTestvd, sizeof(ackTestvd)) != 0 || vdAck[5] > 7)
	{
		HOAGS_ERR("Invalid ack, removed\n");
		serial_clear_rx(&superFanObj);
		continue;
	}
	int len2 = serial_recv_blocked(&superFanObj, &(vdAck[6]), vdAck[5]+1, 600000);

    if (memcmp(statusonoff, vdAck, sizeof(statusonoff) - 4) == 0) {
        memcpy(statusonoff, vdAck, sizeof(vdAck));
		HOAGS_ERR("Received status on/off: %02x\n",statusonoff[11]);
        --count;
		isAckReceived = TRUE;
    }else if (memcmp(statusmode, vdAck, sizeof(statusmode) - 5) == 0) {
        memcpy(statusmode, vdAck, sizeof(vdAck));
		lastUpdate = 2;
		HOAGS_ERR("Received statusmode: %02x\n",statusmode[10]);
        --count;
		isAckReceived = TRUE;
    }else if (memcmp(statusfansp, vdAck, sizeof(statusfansp) - 4) == 0) {
        memcpy(statusfansp, vdAck, sizeof(vdAck));
		lastUpdate = 1;
		HOAGS_ERR("Received statusfansp: %02x\n",statusfansp[11]);
        --count;
		isAckReceived = TRUE;
    }else if (memcmp(statusTimer, vdAck, sizeof(statusTimer) - 8) == 0) {
   		memcpy(statusTimer, vdAck, sizeof(vdAck));
    	lastUpdate = 3; 
    	HOAGS_ERR("Received statustimer: %02x\n", statusTimer[11]); 
    	--count;
   		isAckReceived = TRUE;
	}

	if (updateAckStatusSF(vdAck, lastUpdate) == 1)
	{
		sentacktocloud = 1;
	}
	memset(vdAck, 0x00, sizeof(vdAck));
}

	if (sentacktocloud == 1)
	{
		sendAckToCloud();
	}
#endif

#if VIRTUALFOREST_AC
	unsigned  char sentAck[] = {0x24,0x16,0x03,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x23};
	sentAck[22] = vfChecksum(sentAck+1, 21);
	displayDataUC((unsigned char*)&sentAck, sizeof(sentAck)); 
	uart_send_bytes(&superFanObj,  (char*)&sentAck, sizeof(sentAck));
#endif

	//serial_clear_rx(&superFanObj);

	while(TRUE)
	{

#if VIRTUALFOREST_AC
        int len = serial_recv_blocked(&superFanObj, &vfAck, 24, 600000);
		if((VF0_START_BYTE == vfAck[0]) && (VF23_ENDBYTE == vfAck[23])){
			isAckReceived = TRUE;
		}
		else
		{
			serial_clear_rx(&superFanObj);
			HOAGS_ERR("start byte 0x%0x: and stop byte 0x%0x: are not matching in ack\n",vfAck[0],vfAck[23]);
			continue;
		}

#elif VERSADEVICES_SUPERFAN_IOT
  #if 1
		char header;
		ackReceived = hoagsMalloc(sizeof(vdAck));
		memset(ackReceived, 0x00, sizeof(vdAck));
		memset(vdAck, 0x00, sizeof(vdAck));
		lenn = serial_recv_blocked(&superFanObj, &header, 1, 600000);
		if (lenn != 1) {
			HOAGS_ERR("Error in reading the frame header\n");
			continue;
		}
		frameHeader = ((frameHeader << 8) | (header & 0xFF)) & 0xFFFF;
		if (frameHeader != 0x55AA) continue;
		memset(ackReceived, 0x00, sizeof(vdAck));
		memset(vdAck, 0x00, sizeof(vdAck));
		vdAck[0] = 0x55;
		vdAck[1] = 0xAA;
		lenn = serial_recv_blocked(&superFanObj, &vdAck[2], 4, 600000);
		int length = ((vdAck[4] << 8) | (vdAck[5]));
		if (length > (sizeof(vdAck) - 6)) {
			HOAGS_ERR("Length received =%d\n", length);
			continue;
		}
		lenn = serial_recv_blocked(&superFanObj, &(vdAck[6]), length+1, 600000);

		memcpy(ackReceived, vdAck, sizeof(vdAck));

		if((SF0_START_BYTE == vdAck[0]) && (SF1_BYTE == vdAck[1])){
			isAckReceived = TRUE;
			//for(int i=0;i<sizeof(vdAck);i++){
			//	printf("%02x " ,vdAck[i]);
			//}
			printf("\n");
			time_t currentTime = rtc_read();
			xQueueSend(ackQ, &ackReceived, 0);
			sendAckToApp(0);
			for (int i = 0; i < sizeof(ackPktCacheindex) / sizeof(int); i++) {
				if (vdAck[6] == ackPktCacheindex[i]) {
					int len = ((vdAck[4] << 8) | vdAck[5]) + 7;
						switch (ackPktCacheindex[i]) {
							case 0x02:
							case 0x04:
							case 0x21:
							{
								if (((ackPktCacheindex[i] == 0x04) || (ackPktCacheindex[i] == 0x21)) && (isTimerUnderProcess() == 1)) {
									/* Drop the mode and speed configuration */
									//clearAppCacheAtIndex(0x22);;
									break;
								}
								if ((memcmp(statusonoff, vdAck, sizeof(statusonoff) - 4) != 0) && (memcmp(statusmode, vdAck, sizeof(statusmode) - 5) != 0) &&
									(memcmp(statusfansp, vdAck, sizeof(statusfansp) - 4) != 0)) {
										HOAGS_ERR("Not updating the packet of type %02x\n", ackPktCacheindex[i]);
										break;
								}
								memcpy(ackPacketCache[i], vdAck, len);
								if (ackPktCacheindex[i] == 0x21) {
									clearAppCacheAtIndex(0x04);
								} else if (ackPktCacheindex[i] == 0x04) {
									clearAppCacheAtIndex(0x21);
								} 

								int index_0x2 = -1;
								for (int idx = 0; idx < SF_PACKET_INDEX_COUNT; idx++) {
									//printf("****11****\n");
									if (ackPktCacheindex[idx] == 0x2) {
										index_0x2 = idx;
										break;
									}
									//printf("****12****\n");
								}

								// Check if the 11th byte of 0x2's cache is 0x00, then clear cache for 0x22
								if (index_0x2 != -1 && ackPacketCache[index_0x2][11] == 0x00) {
									//HOAGS_ERR("0x2's 11th byte is 0x00, clearing 0x22 cache\n");
									clearAppCacheAtIndex(0x22);
								}

								time_t currentTime = rtc_read();
								struct tm *nextAckTime = localtime(&currentTime);
								nextAckTime->tm_sec = nextAckTime->tm_sec + 10;
								sendAckToCloud();
							}
							break;
							case 0x22: // Timer
   							{
								memcpy(ackPacketCache[i], vdAck, len);
								setTimerUnderProcess(vdAck);
        						// memcpy(ackPacketCache[i], vdAck, len);
								sendAckToCloud(); 
   							}
   							 break;
							default:
							{
								memcpy(ackPacketCache[i], vdAck, len);
								time_t currentTime = rtc_read();
								if ((ackNextUpdateTime > 0) && (difftime(ackNextUpdateTime, currentTime) < 0)) {
									ackNextUpdateTime = 0;
									sendAckToCloud();
									HOAGS_MAN("Updating ack after 10 seconds of main event %d\n", ackPktCacheindex[i]);
								} else {
									HOAGS_MAN("Not sending ack for this change %d\n", ackPktCacheindex[i]);
								}
							}
						}
						//}
					break;
				}
			}	
		}
		else
		{
			serial_clear_rx(&superFanObj);
			HOAGS_ERR("start byte 0x%0x: and stop byte 0x%0x: are not matching in ack\n",vdAck[0],vdAck[1]);
			continue;
		}
#endif
#elif AMBER_AC 
		char header;		
		memset(ambAck, 0x00, sizeof(ambAck));
		lenn = serial_recv_blocked(&superFanObj, &header, 1, 600000);
		if (lenn != 1) {
			HOAGS_ERR("Error in reading the frame header\n");
			continue;
		}
		frameHeader = ((frameHeader << 8) | (header & 0xFF)) & 0xFFFF;
		if (frameHeader != 0x55AA) continue;
		memset(ambAck, 0x00, sizeof(ambAck));
		ambAck[0] = 0x55;
		ambAck[1] = 0xAA;
		lenn = serial_recv_blocked(&superFanObj, &ambAck[2], 4, 600000);
 
		int length = ((ambAck[4] << 8) | (ambAck[5]));
		if (length > (sizeof(ambAck) - 6)) {
			HOAGS_ERR("Length received =%d\n", length);
			continue;
		}
		lenn = serial_recv_blocked(&superFanObj, &(ambAck[6]), length+1, 600000);
 
		if((AMB0_START_BYTE == ambAck[0]) && (AMB1_BYTE == ambAck[1])){
			isAckReceived = TRUE;
			sendAckToApp(0);

		for (int i = 0; i < sizeof(ackPktCacheindex) / sizeof(int); i++) {
			if (ambAck[6] == ackPktCacheindex[i]) {
				int len = ((ambAck[4] << 8) | ambAck[5]) + 7;
				if (memcmp(ambAck, ackPacketCache[i], len) != 0) {
					memcpy(ackPacketCache[i], ambAck, len);
					switch (ackPktCacheindex[i]) {
						case 0x01: //switchon/off
						case 0x02: //temperature
						case 0x04: //mode
						case 0x05: //fanspeed
						case 0x19: //sleep
						case 0x67: //turbo
						case 0x6D: //displon/off
						case 0x6E: //swingon/off
						case 0x6F: //hroon/off
						{
							time_t currentTime = rtc_read();
							struct tm *nextAckTime = localtime(&currentTime);
							nextAckTime->tm_sec = nextAckTime->tm_sec + 10;
							ackNextUpdateTime = mktime(nextAckTime);
							sendAckToCloud();
						}

						break;

					}
					break;
			}
		}
		}  
		}
		else
		{
			serial_clear_rx(&superFanObj);
			HOAGS_ERR("start byte 0x%0x: and stop byte 0x%0x: are not matching in ack\n",ambAck[0],ambAck[1]);
			continue;
		}
#elif RR_KABLES
       int len = serial_recv_blocked(&superFanObj, &hdcpAck, 26, 600000);
        if((HDCP_START_BYTE == hdcpAck[0]) && (HDCP_BYTE_1 == hdcpAck[1])){
            isAckReceived = TRUE;
        }
		else
		{
			serial_clear_rx(&superFanObj);
			HOAGS_ERR("start byte 0x%0x: and stop byte 0x%0x: are not matching in ack\n",hdcpAck[0],hdcpAck[1]);
			continue;
		}
#elif ATOMBERG_FAN
		//memset(atombergAck,0,sizeof(atombergAck));
        int len = serial_recv_blocked(&superFanObj, &atombergAck, 17, 600000);
		char value1=atombergAck[15];
		char value2=atombergAck[16];
		char legth[10];
		sprintf(legth, "%c%c", value1, value2);;
		int legth2=atoi(legth);
		int len2 = serial_recv_blocked(&superFanObj, &atombergAck[17], legth2+14, 600000);
		for(int i=0;i<len+len2;i++){
			printf("%02x ",atombergAck[i]);
		}
		if((ATBG0_BYTE == atombergAck[0]) && (ATBG1_BYTE == atombergAck[1])){
			isAckReceived = TRUE;
		}
		else
		{
			serial_clear_rx(&superFanObj);
			HOAGS_ERR("start byte 0x%0x: and stop byte 0x%0x: are not matching in ack\n",atombergAck[0],atombergAck[1]);
			continue;
		}

#elif VGUARD_NEW_FAN
		int vg = serial_recv_blocked(&superFanObj, &vgAck, 8 , 600000);
		for (int i = 0; i < vg; ++i)
        {
            printf(" %02X ", vgAck[i]);
        }
		if((VG_STARTBYTE == vgAck[0]) && (VG_MIDBYTE == vgAck[4])){
			isAckReceived = TRUE;
		}
		else
		{
			serial_clear_rx(&superFanObj);
			HOAGS_ERR("start byte 0x%0x: and stop byte 0x%0x: are not matching in ack\n",vgAck[0],vgAck[4]);
			continue;
		}

#elif OMNI_AC
	char header;		
		memset(omniAck, 0x00, sizeof(omniAck));
		lenn = serial_recv_blocked(&superFanObj, &header, 1, 600000);
		if (lenn != 1) {
			HOAGS_ERR("Error in reading the frame header\n");
			continue;
		}
		frameHeader = ((frameHeader << 8) | (header & 0xFF)) & 0xFFFF;
		if (frameHeader != 0x55AA) continue;
		memset(omniAck, 0x00, sizeof(omniAck));
		omniAck[0] = 0x55;
		omniAck[1] = 0xAA;
		lenn = serial_recv_blocked(&superFanObj, &omniAck[2], 4, 600000);
 
		int length = ((omniAck[4] << 8) | (omniAck[5]));
		if (length > (sizeof(omniAck) - 6)) {
			HOAGS_ERR("Length received =%d\n", length);
			continue;
		}
		lenn = serial_recv_blocked(&superFanObj, &(omniAck[6]), length+1, 600000);
 
		if((OMNI0_START_BYTE == omniAck[0]) && (OMNI1_BYTE == omniAck[1])){
			isAckReceived = TRUE;
			sendAckToApp(0);

		for (int i = 0; i < sizeof(ackPktCacheindex) / sizeof(int); i++) {
			if (omniAck[6] == ackPktCacheindex[i]) {
				int len = ((omniAck[4] << 8) | omniAck[5]) + 7;
				if (memcmp(omniAck, ackPacketCache[i], len) != 0) {
					memcpy(ackPacketCache[i], omniAck, len);
					switch (ackPktCacheindex[i]) {
						case 0x01:  //power
						case 0x02:	//temp
						case 0x04:	//mode
						case 0x05:	//fanspeed
						case 0x6A:	//sleep
						case 0x67:	//turbo
						case 0x71:	//lighton/off
						case 0x72:	//swingon/off
						case 0x73:	//hroon/off
						{
							time_t currentTime = rtc_read();
							struct tm *nextAckTime = localtime(&currentTime);
							nextAckTime->tm_sec = nextAckTime->tm_sec + 10;
							ackNextUpdateTime = mktime(nextAckTime);
							sendAckToCloud();
						}

						break;

					}
					break;
			}
		}
		}  
		}
		else
		{
			serial_clear_rx(&superFanObj);
			HOAGS_ERR("start byte 0x%0x: and stop byte 0x%0x: are not matching in ack\n",omniAck[0],omniAck[1]);
			continue;
		}
#else
		vTaskDelay(5000);
		continue;
#endif
		//printf("%s:%d\n", __func__, __LINE__);
		
		#if !defined(VERSADEVICES_SUPERFAN_IOT) && !defined(AMBER_AC) && !defined(OMNI_AC)
		sendAckToApp(0);  //Suvarna: This cannot be moved from here to awsiot.c as BLE should not be dependent on the wifi-connection.(awsiot.c will be consuming the data only if network is connected)

		struct hoagsMqtt* hmPtr = &hqttUiAck;
		xQueueSend(pubDataAnalQueueHandle, &hmPtr, xQUEUE_TIMEOUT);

		hmPtr = &hqttAnalytics;
		xQueueSend(pubDataAnalQueueHandle, &hmPtr, xQUEUE_TIMEOUT);
		#endif

		UBaseType_t qCount = uxQueueMessagesWaiting(pubDataAnalQueueHandle);

		if(qCount == 40)
		{
			xQueueReset(pubDataAnalQueueHandle);
			qCount = uxQueueMessagesWaiting(pubDataAnalQueueHandle);
			HOAGS_ERR("Queue is full, flush it. Data after flushing=%lu\n", qCount);
			createResigsterData();
		}
		else
		{
			HOAGS_INFO("Queue element count=%lu\n", qCount);
		}
	}
	
	vTaskDelete(NULL);
	#endif
	
}

void startDataCollector(void)
{
	xTaskCreate(fetchDeviceDetails,	/* The function that implements the task. */
				"fetchDeviceDetails",			/* Just a text name for the task to aid debugging. */
				512,	/* The stack size is defined in FreeRTOSIPConfig.h. */
				NULL,		/* The task parameter, not used in this case. */
				tskIDLE_PRIORITY + 4,		/* The priority assigned to the task is defined in FreeRTOSConfig.h. */
				NULL);				/* The task handle is not used. */
}
