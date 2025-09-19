#include "cloudConnect.h"

static SemaphoreHandle_t mutexCloudSend = NULL;
static char fwVersion[VERISON_SIZE];

BOOL isRegistrationSent = FALSE;

TaskHandle_t cloudTaskHandle = NULL;

void suspendCloudTask(){
	vTaskSuspend(cloudTaskHandle);
    printf("CLOUD TASK SUSPENDED.\n");
}

void resumeCloudTask() {
	vTaskResume(cloudTaskHandle);
    printf("CLOUD TASK RESUMED.\n");
}

void initMutexCloudSend() {
	mutexCloudSend = xSemaphoreCreateMutex();
	if (mutexCloudSend == NULL) {
		HOAGS_ERR("%s not created successfully\n",__func__);
	}
}

void string_to_hex(char *hex_output,const  char *input) {
    int i = 0;
    while (input[i] != '\0') {
        sprintf(hex_output + (i * 2), "%02x", (unsigned char)input[i]);
        i++;
    }
    hex_output[i * 2] = '\0';
}

void getVersion()
{
    string_to_hex(fwVersion,VERSION_BUILD_STR);
}

void makeRegisterPkt(unsigned char registerPkt[],const int msgType) {
    unsigned char prodModel[MODEL_NO_SIZE] = {0};
    unsigned char totalLen[5] = {0};
    unsigned char macIdLen[4] = {0};
    char modelNo[50] = {0};
    char fwLen[4] = {0};
    int totalLength;
    char devTag[5] = {0};
    char modelLen[4] = {0};
    char macIdtag[5] = {0};
    char versionTag[5] = {0};
    char msgTypeTag[5] = {0};
    unsigned char custNameLen[4] = {0};
    unsigned char prodTypeLen[4] = {0};
    unsigned char userIdLen[4] = {0};
    unsigned char friendlyNameLen[4] = {0};

    unsigned char custName[20] = {0}; 
    unsigned char custNameInHex[20 * 2] = {0};
    unsigned char prodType[20] = {0};
    unsigned char prodTypeInHex[20 * 2] = {0};
    unsigned char userId[50] = {0};
    unsigned char userIdInHex[PACKET_SIZE] = {0};
    unsigned char friendlyname[20] = {0};
    unsigned char friendlynameInHex[20 * 2] = {0};


    memset(registerPkt, 0x00, sizeof(registerPkt));

    sprintf(devTag,"%04d",DEV_TAG);
    sprintf(macIdtag,"%04d",MACID_TAG);
    sprintf(versionTag,"%04d",VERSION_TAG);

    strcpy(registerPkt,"{ \"message\": \"");
    strcat(registerPkt, MARKER);

    sprintf(msgTypeTag,"%04d",msgType);

    strcat(registerPkt, msgTypeTag);

    getEnvItem(ENV_PRODMODEL,prodModel);
    string_to_hex(modelNo,prodModel);

    getEnvItem(ENV_CUSTNAME,custName);
    string_to_hex(custNameInHex,custName);

    getEnvItem(ENV_PRODTYPE,prodType);
    string_to_hex(prodTypeInHex,prodType);

    getEnvItem(ENV_USERID,userId);
    string_to_hex(userIdInHex,userId);

    getEnvItem(ENV_FRIENDLYNAME,friendlyname);
    string_to_hex(friendlynameInHex,friendlyname);

    totalLength = (int) (strlen(macIdtag) + sizeof(macIdLen) + strlen(getMacId()) + strlen(devTag) + 
                            sizeof(modelLen) + strlen(modelNo) +
                           strlen(versionTag) + sizeof(fwLen) + strlen(fwVersion) +
                        strlen(CUST_NAME_TAG) + strlen(PROD_TYPE_TAG) + strlen(USER_ID_TAG) + strlen(FRIENDLY_NAME_TAG) +
                        sizeof(custNameLen) + sizeof(prodTypeLen) + sizeof(userIdLen) + sizeof(friendlyNameLen) + 
                        strlen(custNameInHex) + strlen(prodTypeInHex) + strlen(userIdInHex) + strlen(friendlynameInHex)
                        );
    sprintf(totalLen, "%04x", totalLength / 2);
    strcat(registerPkt, totalLen);

    
    strcat(registerPkt, devTag);
    sprintf(modelLen, "%04x", (int)(strlen(modelNo) / 2));
    strcat(registerPkt, modelLen);
    strcat(registerPkt, modelNo);


    strcat(registerPkt,macIdtag);
    int macIdLenValue = strlen(getMacId()) / 2;
    sprintf(macIdLen, "%04x", macIdLenValue);
    strcat(registerPkt, macIdLen);
    strcat(registerPkt, getMacId());

    strcat(registerPkt, versionTag);
    memset(fwLen,0,sizeof(fwLen));
    sprintf(fwLen,"%04x",(int)strlen(fwVersion) / 2);
    strcat(registerPkt, fwLen);
    strcat(registerPkt, fwVersion);


    strcat(registerPkt, CUST_NAME_TAG);
    sprintf(custNameLen,"%04x",(int)strlen(custNameInHex) / 2);
    strcat(registerPkt, custNameLen);
    strcat(registerPkt, custNameInHex);

    strcat(registerPkt, PROD_TYPE_TAG);
    sprintf(prodTypeLen,"%04x",(int)strlen(prodTypeInHex) / 2);
    strcat(registerPkt, prodTypeLen);
    strcat(registerPkt, prodTypeInHex);

    strcat(registerPkt, USER_ID_TAG);
    sprintf(userIdLen,"%04x",(int)strlen(userIdInHex) / 2);
    strcat(registerPkt, userIdLen);
    strcat(registerPkt, userIdInHex);
	
    strcat(registerPkt, FRIENDLY_NAME_TAG);
    sprintf(friendlyNameLen,"%04x",(int)strlen(friendlynameInHex) / 2);
    strcat(registerPkt, friendlyNameLen);
    strcat(registerPkt, friendlynameInHex);

    strcat(registerPkt,"\" } ");
}

void makeDataPacket(unsigned char packet[], const int msgType, const char *msgData) {
    unsigned char prodModel[MODEL_NO_SIZE] = {0};
    unsigned char totalLen[2] = {0};
    unsigned char macIdLen[4] = {0};
    unsigned char dataLen[4] = {0};
    char modelNo[MODEL_NO_SIZE] = {0};
    char fwLen[4] = {0};
    int totalLength;
    char devTag[5] = {0};
    char modelLen[4] = {0};
    char macIdtag[5] = {0};
    char versionTag[5] = {0};
    char msgTypeTag[5] = {0};
    char rdDataTag[5] = {0};

    memset(packet, 0x00, sizeof(packet));

    sprintf(devTag,"%04d",DEV_TAG);
    sprintf(macIdtag,"%04d",MACID_TAG);
    sprintf(versionTag,"%04d",VERSION_TAG);
    sprintf(rdDataTag,"%04d",msgType);
    
    strcpy(packet,"{ \"message\": \"");

    strcat(packet, MARKER);
    sprintf(msgTypeTag,"%04d",RD_RES_TAG);
    strcat(packet, msgTypeTag);
    getEnvItem(ENV_PRODMODEL,prodModel);
    string_to_hex(modelNo,prodModel);

    totalLength = (int) (strlen(macIdtag) + sizeof(macIdLen) + strlen(getMacId()) + strlen(devTag) + sizeof(modelLen) +
                                strlen(modelNo) + strlen(rdDataTag) + strlen(msgData) + sizeof(dataLen)+
                                strlen(versionTag) + sizeof(fwLen) + strlen(fwVersion));
    sprintf(totalLen, "%04x", totalLength / 2);
    strcat(packet, totalLen);

    strcat(packet, devTag);
    sprintf(modelLen, "%04x", (int)(strlen(modelNo) / 2));
    strcat(packet, modelLen);
    strcat(packet, modelNo);

    int macIdLenValue = strlen(getMacId()) / 2;
    sprintf(macIdLen, "%04x", macIdLenValue);
    strcat(packet, macIdtag);
    strcat(packet, macIdLen);
    strcat(packet, getMacId());

    strcat(packet, versionTag);
    sprintf(fwLen,"%04x",(int)strlen(fwVersion) / 2);
    strcat(packet, fwLen);
    strcat(packet, fwVersion);

    strcat(packet, rdDataTag);
    sprintf(dataLen,"%04x",(int)(strlen(msgData) / 2));
    strcat(packet, dataLen);
    strcat(packet, msgData);

    strcat(packet,"\" } ");

    printf("Cloud packet(%ld):%s.\n",strlen(packet),packet);
}


BOOL checkInternet()
{
    //add Internet connectivity code here
    if(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS) {
            return FALSE;
	}
    else 
        return TRUE;
}


void NetworkInitHoags(Network *n)
{
    HOAGS_ERR("\n");
	n->my_socket = -1;
	n->mqttread = FreeRTOS_read;
	n->mqttwrite = FreeRTOS_write;
	n->disconnect = FreeRTOS_disconnect;

#if (MQTT_OVER_SSL)
	n->use_ssl = 1;
	n->ssl = NULL;
	n->conf = NULL;
	n->rootCA = IOT_ROOT_CA;
	n->clientCA = IOT_CLIENT_CA;
	n->private_key = IOT_PRIVATE_KEY;
	n->ciphersuites = NULL;
#endif
}


int sendRegistrationPacket() {
	if(checkInternet()) {
		unsigned char registerPacket[PACKET_SIZE * 4];
		makeRegisterPkt(registerPacket,REG_TAG);
        printf("Registration packet:%s\n",registerPacket);
		return sendDataToCloud(registerPacket);
	}
	else{
		return -1;
	}
}

int sendDataToCloud(char data[]) {
    if(!checkInternet()) {
        HOAGS_ERR("Wifi not connected yet!\n");
        return -1;
    }
    if (xSemaphoreTake(mutexCloudSend, portMAX_DELAY) == pdTRUE) {


        MQTTClient client;
        Network network;
        char clientId[32];
        int rc = 0, count = 0;
        MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
        unsigned char readbuf[100];
        unsigned char sendbuf[PACKET_SIZE * 7];
        

        memset(readbuf, 0x00, sizeof(readbuf));
        memset(sendbuf, 0x00, sizeof(sendbuf));

        NetworkInitHoags(&network);
        MQTTClientInit(&client, &network, 8000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

        HOAGS_INFO("Connect Network \"%s\"\n", IOT_ENDPOINT);
        

        while ((rc = NetworkConnect(&network, (char *)IOT_ENDPOINT, IOT_PORT_NUMBER)) != 0) {
            HOAGS_DBG("Return code from network connect is %d\n", rc);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        
        
        HOAGS_INFO("\"%s\" Connected\n", IOT_ENDPOINT);

        memset(clientId, 0, sizeof(clientId));
        strcat(clientId, CLIENT_ID);

        strcat(clientId, getMacId());
        connectData.MQTTVersion = HOAGS_MQTT_VERSION;
        connectData.clientID.cstring = clientId;


        HOAGS_INFO("Device Clientid=%s\n", connectData.clientID.cstring);

        HOAGS_INFO("Start MQTT connection\n");

        
        while ((rc = MQTTConnect(&client, &connectData)) != 0) {
            HOAGS_DBG("Return code from MQTT connect is %d\n", rc);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        HOAGS_INFO("MQTT Connected\n");
        
        MQTTMessage message;
        message.qos = QOS1;
        message.retained = 0;
        message.payload = data;
        message.payloadlen = strlen(data);
        HOAGS_INFO("Publishing to %s,Datalen(%ld):%s\n", LOTIER_TOPIC,strlen(message.payload),message.payload);
        if ((rc = MQTTPublish(&client, LOTIER_TOPIC, &message)) != 0) 
        {
            HOAGS_ERR("Return code from MQTT publish is %d\n", rc);
        }
        MQTTDisconnect(&client);
        xSemaphoreGive(mutexCloudSend);
        FreeRTOS_disconnect(&network);
        return rc;
    }
}

static QueueHandle_t mqttQueueHandle = NULL;

void initMqttQueue()
{
    mqttQueueHandle = xQueueCreate(5, sizeof(unsigned char *));
    if (mqttQueueHandle == NULL)
        HOAGS_ERR("Error initializing %s!\n", __func__);
}

QueueHandle_t getMqttQueueHandle() {
    return mqttQueueHandle;
}

void runMqttTask() {
    TickType_t timeout = ((60 * 1000) * TIME_SET_FOR_REGISTRATION_CHECK);
    initMqttQueue();
    initMutexCloudSend();
    unsigned char *cloudDataPtr = NULL;
    char userIdStored[50] = {0};
    getEnvItem(ENV_USERID,userIdStored);
    while(TRUE) {
        if(xQueueReceive(mqttQueueHandle,&cloudDataPtr,timeout) == pdFALSE){
            if((strnlen(userIdStored, sizeof(userIdStored)) > 0) && (isRegistrationSent == FALSE)) {

                if(sendRegistrationPacket() != -1)
                {
                    isRegistrationSent = TRUE;
                }
                continue;
            }
        }
        else{
            if(cloudDataPtr != NULL) {
                if(sendDataToCloud(cloudDataPtr) == 0){
                    printf("MQTT send success\n");
                }
                else {
                    printf("MQTT send failed\n");
                }
                free(cloudDataPtr);
                cloudDataPtr == NULL;
            }
        }
    }
}



void startMqttTask() {
    HOAGS_ERR("\n");
	if(pdTRUE != xTaskCreate(runMqttTask,"runMqttTask",1024 * 2,NULL,tskIDLE_PRIORITY + 4,&cloudTaskHandle)){
		printf("Failed to create %s\n",__func__);
	}
}
