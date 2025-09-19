#include "remoteDiag.h"
#include "queue.h"
#include "serial_api.h"
#include "timer_api.h"

extern struct serial_s superFanObj;

static state_machine_t sm;
static QueueHandle_t purifierQueuedataHandle = NULL;
static QueueHandle_t pendingMsgQHandle = NULL;
static SemaphoreHandle_t mutexBleSend = NULL;

bool isBleConnected = false;
bool iswifiConnected = false;

uint32_t RENESES_IMG_START_ADDRESS;

void findRenesesImgAddr() {
    uint32_t receivedAddress = hoags_get_current_img_addr();
    // printf("CURRENT FW ADDRESS:%08x\n",receivedAddress);
    RENESES_IMG_START_ADDRESS = ((receivedAddress + HE3_IMAGE_SIZE));
    // printf("CURRENT RENESES ADDRESS:%08x\n",RENESES_IMG_START_ADDRESS);
}

gtimer_t ledBlinkTimer;
gpio_t ota_led;

bool isFinalAck = 0;
bool isRenesasUpdateBegin = 0;
bool renesasState = 0;

TaskHandle_t remoteDiagTaskHandle = NULL;

void suspendRemoteTask(){
	vTaskSuspend(remoteDiagTaskHandle);
    printf("REMOTE TASK SUSPENDED.\n");
}

void resumeRemoteTask() {
	vTaskResume(remoteDiagTaskHandle);
    printf("REMOTE TASK RESUMED.\n");
}

void display_hdcpRd(struct hdcpRd *pkt) {
    int payLoad_Len = 0;
    printf("Header: 0x%02X\n", pkt->header);
    printf("Length: %u\n", pkt->len);
    printf("Checksum: 0x%08X\n", pkt->checksum);
    printf("Sequence Number: %u\n", pkt->seq_num);
    printf("Last Sequence Number: 0x%08X\n", pkt->last_seq_num);
    printf("Payload:");

    payLoad_Len = (int) pkt->len - (sizeof(pkt->seq_num) + sizeof(pkt->checksum) + sizeof(pkt->last_seq_num) 
                    + sizeof(pkt->header) + sizeof(pkt->len));
    if(payLoad_Len > sizeof(pkt->payload)) {
        printf("[UART] Invalid length received\n");
        return;
    }
    // printf("[UART]Payload Len: %d\n",payLoad_Len);
    for (int i = 0; i < payLoad_Len; i++) {
        printf("0x%02X ", pkt->payload[i]);
    }
    printf("\n\n");
}

void display_sControlMessage(sControlMessage sMsg) {

    printf("msgSource : %d\n",sMsg.msgSource);
    printf("msgId: %d\n",sMsg.msgId);
    printf("Header: 0x%02X\n", sMsg.msgPayload.header);
    printf("Length: %u\n", sMsg.msgPayload.len);
    printf("Checksum: 0x%08X\n", sMsg.msgPayload.checksum);
    printf("Sequence Number: %u\n", sMsg.msgPayload.seq_num);
    printf("Last Sequence Number: 0x%08X\n", sMsg.msgPayload.last_seq_num);
    printf("Payload:");
    int payLoad_Len = (int) (sMsg.msgPayload.len - (sizeof(sMsg.msgPayload.seq_num) + sizeof(sMsg.msgPayload.checksum) +
                             sizeof(sMsg.msgPayload.last_seq_num) + sizeof(sMsg.msgPayload.header) + sizeof(sMsg.msgPayload.len)));
    // printf("[Sm]Payload Len: %d\n",payLoad_Len);
    if(payLoad_Len > sizeof(sMsg.msgPayload.payload)) {
        printf("Invalid length received\n");
        return;
    }
    for (int i = 0; i < payLoad_Len; i++) {
        printf("0x%02X ", sMsg.msgPayload.payload[i]);
    }
    printf("\n\n");
}

void initPurifierQueueDataHandle()
{
    purifierQueuedataHandle = xQueueCreate(5, sizeof(sControlMessage));
    pendingMsgQHandle = xQueueCreate(5, sizeof(sControlMessage));
    if (purifierQueuedataHandle == NULL || pendingMsgQHandle == NULL) {
        HOAGS_ERR("Queue creation failed!\n");
    } else {
        HOAGS_INFO("Queue created successfully: %p\n", (void*)purifierQueuedataHandle);
    }
    memset(&sm, 0, sizeof (sm));
}


void initMutexBleSend() {
	mutexBleSend = xSemaphoreCreateMutex();
	if (mutexBleSend == NULL) {
		HOAGS_ERR("%s not created successfully\n",__func__);
	}
}

SemaphoreHandle_t getMutexBleSend(void) {
    return mutexBleSend;
}

QueueHandle_t getPurifierQueueDataHandle() {
    return purifierQueuedataHandle;
}

void payloadToString(uint8_t payload[],char strData[],int payloadLen){

    for (size_t i = 0; i < payloadLen; i++) {
        sprintf(&strData[i * 2], "%02X", payload[i]);
    }
    strData[payloadLen * 2] = '\0';
}

int renesasUpdateInit(void)
{
    sendbootpacketToRenesas();
}

void bleWifi_ledOn(void)
{
    led_always_on();
}

void bleWifi_ledOff(void)
{
    if(isBleConnected == false && iswifiConnected == false)
    {
        led_always_off();
    }
}

void ledBlink(void)
{
    static BOOL isBlink = FALSE;
    isBlink = (!isBlink);
    if(isBlink)
    {
        gpio_write(&ota_led, 1);
    }
    else
    {
        gpio_write(&ota_led, 0);
    }
}

void renesasFiwareUpdate(void)
{
    pwmout_free(&htapledPtr->pwm_htap_led);
	gpio_init(&ota_led, PA_20);
	gpio_dir(&ota_led, PIN_OUTPUT);    
    gpio_mode(&ota_led, PullNone);
    gtimer_init(&ledBlinkTimer,TIMER5);
    sControlMessage mcuFirmwarePck;
    mcuFirmwarePck.msgSource = SOURCE_REQUEST;
    mcuFirmwarePck.msgId = MCU_UPDATE;
    xQueueSend(getPurifierQueueDataHandle(), &mcuFirmwarePck, xQUEUE_TIMEOUT);
    gtimer_start_periodical(&ledBlinkTimer,200000,(void *)ledBlink,NULL);
}

bool isRenesasUpdateinProgress(void)
{
    return (sm.current_state == SM_MCU_IFC_RENESAS_UPDATE_WAIT);
}


BOOL validateChecksum(struct hdcpRd* receivedPkt) {
    uint16_t checkSumCalculated = 0;
    if (receivedPkt == NULL || receivedPkt->len < sizeof(receivedPkt->seq_num) + sizeof(receivedPkt->last_seq_num) + sizeof(receivedPkt->checksum)) {
        return FALSE;
    }
    int payloadLen = (int) (receivedPkt->len - (sizeof(receivedPkt->seq_num) + sizeof(receivedPkt->last_seq_num) 
                            + sizeof(receivedPkt->checksum) + sizeof(receivedPkt->header) + sizeof(receivedPkt->len)));
    for (size_t i = 0; i < payloadLen; i++) {
        checkSumCalculated += receivedPkt->payload[i];
    }
    checkSumCalculated += receivedPkt->seq_num;
    checkSumCalculated += receivedPkt->last_seq_num;
    printf("Checksum received: %u,Checksum Calculted: %u\n",receivedPkt->checksum,checkSumCalculated);
    if(receivedPkt->checksum == checkSumCalculated) return TRUE;
    else return FALSE;
}

void makeARQOrReqNext(uint8_t header,struct hdcpRd *ARQpkt,int expected_seq, uint16_t last_seq_num) {
    if(ARQpkt == NULL) return;
    ARQpkt->header = header;
    ARQpkt->len = sizeof(ARQpkt->checksum) + sizeof(ARQpkt->last_seq_num) + sizeof(ARQpkt->seq_num)+
                    sizeof(ARQpkt->header) + sizeof(ARQpkt->checksum);
    ARQpkt->seq_num = expected_seq;
    ARQpkt->last_seq_num = last_seq_num;
    ARQpkt->checksum = expected_seq + last_seq_num;
    memset(ARQpkt->payload,0x00,sizeof(ARQpkt->payload));
}

void sendDataToApp(char data[],int flag) {
    if(isBleConnected == TRUE){
        simple_ble_srv_cccd_notify(getBleConnHandle(), data , flag);
    }
}

static BOOL getTime(int istDateTime[])
{
	int hour = 5;
    int minutes = 30;
	struct tm tm_now = hoags_sntp_gen_system_time(hour,minutes);
    printf("IST Time:\n");
	printf("%d-%d-%d %d:%d:%d\n",
		   tm_now.tm_year, tm_now.tm_mon, tm_now.tm_mday, tm_now.tm_hour, tm_now.tm_min, tm_now.tm_sec);
    if(tm_now.tm_year > 2000) {
        uint16_t date = tm_now.tm_year;
        unsigned char *temp = (unsigned char *) &date;
        unsigned char *temp1 = (unsigned char *) &date;
        istDateTime[0] = (*++temp);
        istDateTime[1] = (*temp1);
        istDateTime[2] = tm_now.tm_mon;
        istDateTime[3] = tm_now.tm_mday;
        istDateTime[4] = tm_now.tm_hour;
        istDateTime[5] = tm_now.tm_min;
        istDateTime[6] = tm_now.tm_sec; 
        return TRUE;
    }
    else return FALSE;
}

void setDefaultTemperatures() {
    uint8_t warmTemperature = 0, hotTemperature = 0;
    char temp[10] = {0};

    getEnvItem(WARM_TEMPERATURE, temp);
    warmTemperature = hexToInt(temp);

    memset(temp, 0x00, sizeof(temp));
    getEnvItem(HOT_TEMPERATURE, temp);
    hotTemperature = hexToInt(temp);
    
    memset(temp, 0x00, sizeof(temp));
    if (hotTemperature == 0) {
        snprintf(temp, sizeof(temp), "%02X", 60);
        setEnvItem(HOT_TEMPERATURE, temp);
    }
    memset(temp, 0x00, sizeof(temp));
    if (warmTemperature == 0) {
        snprintf(temp, sizeof(temp), "%02X", 45);
        setEnvItem(WARM_TEMPERATURE, temp);
    }
}

void setDefaultWaterCustomization() {
    uint8_t glassCust = 0, bottleCust = 0;
    char temp[10] = {0};

    getEnvItem(GLASS_CUST, temp);
    glassCust = hexToInt(temp);

    memset(temp, 0x00, sizeof(temp));
    getEnvItem(BOTTLE_CUST, temp);
    bottleCust = hexToInt(temp);
    
    memset(temp, 0x00, sizeof(temp));
    if (bottleCust == 0) {
        snprintf(temp, sizeof(temp), "%02X", DEFAULT_BOTTLE_WATER_CUST);
        setEnvItem(BOTTLE_CUST, temp);
    }
    memset(temp, 0x00, sizeof(temp));
    if (glassCust == 0) {
        snprintf(temp, sizeof(temp), "%02X", DEFAULT_GLASS_WATER_CUST);
        setEnvItem(GLASS_CUST, temp);
    }
}

void runRemoteDiagTask() 
{
    findRenesesImgAddr();
    bool isDateTimeUpdated = FALSE;
    sControlMessage message;
    initPurifierQueueDataHandle();
    initMutexBleSend();
    setDefaultTemperatures();
    setDefaultWaterCustomization();
    char appDataString[PACKET_SIZE] = {0};
    char ackBuffer[2] = {0};
    uint8_t finalPack = 0x04;
    uint8_t Nackpck = 0;
    int istDateTime[7] = {0};
    uint8_t failurePkt[5] = {0x00,0x00,0x00,0x00,0x00};
    uint8_t versionNumber[11]={0,0,0,0,0,0,0,0,0,0,0};
    struct hdcpRd ARQpkt;
    flash_inc_init();
    totalWc_init();
    getVersion();
    sendTemperatureToReneses(SOURCE_REQUEST);
    while (TRUE) {
        TickType_t timeout = pdMS_TO_TICKS(200);
        if (sm.current_state == SM_MCU_IFC_IDLE) {
            if((versionNumber[0] == 0 && versionNumber[1] == 0 && versionNumber[2] == 0 && versionNumber[3] == 0) && (renesasState == TRUE))
            {
                printf("Inside Version Request\n");
                initiateRemoteDiag(SOURCE_REQUEST);
            }
            else if(isDateTimeUpdated == FALSE) {
                timeout = 2000;
            }
            else timeout = -1; /* If the state is idle, wait infinite for message else wait for 200 ms */
        }

        if(checkInternet())
        {
            iswifiConnected = true;
            bleWifi_ledOn();
        }
        else
        {
            iswifiConnected = false;
            bleWifi_ledOff();
        }
        
        // Add delay or event trigger simulation here
        if((sm.current_state == SM_MCU_IFC_IDLE) && xQueueReceive(pendingMsgQHandle, &message, 0) == pdTRUE) {
        }
        else if ((xQueueReceive(purifierQueuedataHandle, &message, timeout) != pdTRUE)) {
            //display_sControlMessage(message);
            printf("RENESES VERSION:%s\n",versionNumber);
            printf("timeout print\n");
            message.msgSource = SOURCE_TIMER;
            message.msgId = TIMER_EXPIRED;
        } 
        else if (sm.current_state != SM_MCU_IFC_IDLE) {
            // printf("Inside Pending Queue\n");
            if (message.msgSource != SOURCE_MCU && message.msgSource != SOURCE_RENESASUPDATE) {
                /* Some command is in processing so if any message received other than from MCU, store it in pending queue for processing it later */
                if(sm.current_state != SM_MCU_IFC_RENESAS_UPDATE_WAIT)
                    xQueueSend(pendingMsgQHandle,&message, 0);
                continue;
            }
        }
        // printf("Queue Receive Done\n");
        switch (sm.current_state)
        {
            case SM_MCU_IFC_IDLE:
            // printf("Inside SM_MCU_IFC_IDLE\n");
                switch (message.msgSource) {
                    case SOURCE_APP:
                    case SOURCE_REQUEST:
                        if (message.msgId == REMOTE_CONTROL) {
                            /* Send the payload in the message to MCU for dispensing water */
                            uart_send_bytes(&superFanObj,(char*)&message.msgPayload, message.msgPayload.len);
                            sm.current_state = SM_MCU_IFC_CONTROL_REPLY_WAIT;
                        } else if (message.msgId == DIAGNOSTICS_CONTROL) {
                            /* Send the payload in the message to MCU for starting diagnostics */
                            uart_send_bytes(&superFanObj,(char*)&message.msgPayload, message.msgPayload.len);
                            sm.current_state = SM_MCU_IFC_DIAG_START_WAIT;
                        }
                        else if(message.msgId == MCU_UPDATE)
                        {
                            printf("Inside MCU_UPDATE\n");
                            sm.diag_command_index = 0;
                            ble_app_deinit();
                            uint32_t address = RENESES_IMG_START_ADDRESS + (sm.diag_command_index * COLUMN_SIZE);
                            uint16_t temp_buffer[COLUMN_SIZE / 2];
                            flashReadRenesesData(address, COLUMN_SIZE, temp_buffer);
                            //printf("START ADDRESS:0x%08x",address);
                            for (int i = 0; i < COLUMN_SIZE / 2; i++) {
                                xmodem_data[0][2 * i]     = (uint8_t)(temp_buffer[i] & 0xFF);
                                xmodem_data[0][2 * i + 1] = (uint8_t)((temp_buffer[i] >> 8) & 0xFF);
                            }
                            // printf("PACKET SENT\n");
                            // for(int i = 0; i < COLUMN_SIZE; i++){
                            //     printf("0x%02x\t",xmodem_data[0][i]);
                            // }
                            // printf("\n");
                            uart_send_bytes(&superFanObj, xmodem_data[sm.diag_command_index], COLUMN_SIZE);
                            sm.current_state = SM_MCU_IFC_RENESAS_UPDATE_WAIT;
                        }
                        else if(message.msgId == BOOTLOADER)
                        {
                            uart_send_bytes(&superFanObj,(char*)&message.msgPayload, message.msgPayload.len);
                            sm.current_state = SM_MCU_IFC_RENESAS_BOOT_ACK_WAIT;
                        }
                        sm.lastMessage = message;
                        sm.retry_count = 0;
                        sm.expected_seq = 0;
                        break;
                    case SOURCE_TIMER:
                        sntp_init();
                        if(getTime(istDateTime)) {
                            isDateTimeUpdated = TRUE;
                            sendDateTimeToReneses(SOURCE_REQUEST,istDateTime);
                        }
                        break;
                    default:
                        HOAGS_INFO("Board is in idle state, so packet is dropped\n");
                }
                break;

            case SM_MCU_IFC_CONTROL_REPLY_WAIT:
            // printf("Inside SM_MCU_IFC_CONTROL_REPLY_WAIT\n");
                switch (message.msgSource) {
                    case SOURCE_MCU:
                        if (message.msgPayload.seq_num == 0 && message.msgPayload.header == CTRL_ACK_HEADER && (validateChecksum(&message.msgPayload))) {
                            /* Forward the message to appropriate source */
                            if(message.msgPayload.payload[0] == 0x00 && message.msgPayload.payload[1] == 0x06 && 
                                message.msgPayload.payload[2] == 0x00 && message.msgPayload.payload[3] == 0x01 &&
                                message.msgPayload.payload[4] == 0x01)
                            {
                                flash_write_inc_data();
                            }
                            else if(message.msgPayload.payload[0] == 0x00 && message.msgPayload.payload[1] == 0x0b &&
                                    message.msgPayload.payload[5] == 0x00 && message.msgPayload.payload[6] == 0x01){
                                storeTdsOffset(message.msgPayload.payload);
                            }
                            else if(message.msgPayload.payload[0] == 0x00 && message.msgPayload.payload[1] == 0x03 &&
							            message.msgPayload.payload[4] == 0x00 && message.msgPayload.payload[5] == 0x02){
                                setIsWaterCustSent(FALSE);
                            }
                            memset(appDataString,0x00,sizeof(appDataString));
                            if(sm.lastMessage.msgSource == SOURCE_APP) {
                                int payloadLen = (int) (message.msgPayload.len - (sizeof(message.msgPayload.seq_num) + sizeof(message.msgPayload.checksum) +
                                                    sizeof(message.msgPayload.last_seq_num) + sizeof(message.msgPayload.header) + sizeof(message.msgPayload.len)));
                                payloadToString(&message.msgPayload.payload,appDataString,payloadLen);
                                sendDataToApp(appDataString,POLLACK_FLAG);
                            }
                            sm.current_state = SM_MCU_IFC_IDLE;
                        } else {
                            if (sm.retry_count++ >= MAX_RETRY_LIMIT) {
                                /* Send control failed message to source in sm.lastMessage.msgSource */
                                if(sm.lastMessage.msgSource == SOURCE_APP){
                                    memset(appDataString,0x00,sizeof(appDataString));
                                    payloadToString(failurePkt,appDataString,sizeof(failurePkt));
                                    sendDataToApp(appDataString,POLLACK_FLAG);
                                }
                                sm.current_state = SM_MCU_IFC_IDLE;
                                setIsWaterCustSent(FALSE);
                            }
                            else {
                                /* Retransmit Control message sm.lastMessage */
                                display_sControlMessage(sm.lastMessage);
                                uart_send_bytes(&superFanObj,(char*)&sm.lastMessage.msgPayload, sm.lastMessage.msgPayload.len);
                            }
                        }
                    
                        break;
                    case SOURCE_TIMER:
                        if (message.msgId == TIMER_EXPIRED) {
                        if (sm.retry_count++ >= MAX_RETRY_LIMIT) {
                            /* Send diag(control) failed message to source in sm.lastMessage.msgSource */
                            if(sm.lastMessage.msgSource == SOURCE_APP){
                                memset(appDataString,0x00,sizeof(appDataString));
                                payloadToString(failurePkt,appDataString,sizeof(failurePkt));
                                sendDataToApp(appDataString,POLLACK_FLAG);
                            }
                            sm.current_state = SM_MCU_IFC_IDLE;
                        } else {
                            /* Send message to MCU with expected sequence number in it for retransmission */
                            printf("At SM_MCU_IFC_CONTROL_REPLY_WAIT,SOURCE_TIMER,TIMER_EXPIRED\n");
                            display_sControlMessage(sm.lastMessage);
                            uart_send_bytes(&superFanObj,(char*)&sm.lastMessage.msgPayload, sm.lastMessage.msgPayload.len);
                        }
                        break;
                    }
                    default:
                        /* Already a control message is under process reply with error to appropriate source */
                        HOAGS_INFO("Already a control message is under process reply with error to appropriate source\n");
                }
                break;

            case SM_MCU_IFC_DIAG_START_WAIT:
            // printf("Inside SM_MCU_IFC_DIAG_START_WAIT\n");
                switch (message.msgSource)
                {
                    case SOURCE_MCU:
                        /* Received message from MCU. check if it is diag reply with sequence 0 */
                        if(message.msgPayload.seq_num == 0 && message.msgPayload.header == RD_RES_HEADER && (validateChecksum(&message.msgPayload))) {
                            /* Send the message to appropriate source */
                            // send request for next seq number
                            //set expected seq number to 1
                            if(message.msgPayload.payload[0] == 0x00 && message.msgPayload.payload[1] == 0x02 && 
                                message.msgPayload.payload[4] == 0x00 && message.msgPayload.payload[5] == 0x05)
                            {
                                memset(versionNumber,0x00,sizeof(versionNumber));
                                memcpy(versionNumber, &message.msgPayload.payload[8], message.msgPayload.payload[7]);
                                versionNumber[message.msgPayload.payload[7]] = '\0';
                                if(strncmp(versionNumber,RENESAS_VERSION_NUMBER,strlen(RENESAS_VERSION_NUMBER)) != 0)
                                {
                                    printf("New Version is available Update Renesas\n");
                                    sendbootpacketToRenesas(); 
                                }
                            }
                            memset(appDataString,0x00,sizeof(appDataString));
                            int payloadLen = (int) (message.msgPayload.len - (sizeof(message.msgPayload.seq_num) + sizeof(message.msgPayload.checksum) +
                                                    sizeof(message.msgPayload.last_seq_num) + sizeof(message.msgPayload.header) + sizeof(message.msgPayload.len)));
                            if(sm.lastMessage.msgSource == SOURCE_APP){
                                payloadToString(message.msgPayload.payload,appDataString,payloadLen);
                                sendDataToApp(appDataString,POLLACK_FLAG);
                            }

                            sm.expected_seq = 1;

                            memset(&ARQpkt,0x00,sizeof(ARQpkt));
                            makeARQOrReqNext(RD_REQ_HEADER,&ARQpkt,sm.expected_seq,message.msgPayload.last_seq_num);
                            printf("Request for next packet\n");
                            display_hdcpRd(&ARQpkt);
                            uart_send_bytes(&superFanObj,(char*)&ARQpkt, ARQpkt.len);

                            sm.current_state = SM_MCU_IFC_DIAG_RESP_WAIT;
                        }
                        else {
                            /* Retransmit DIAG initialization message sm.lastMessage */
                            printf("Valid data not received ,Retransmit DIAG ini sm.lastMessage\n");
                            display_sControlMessage(sm.lastMessage);
                            uart_send_bytes(&superFanObj,(char*)&sm.lastMessage.msgPayload, sm.lastMessage.msgPayload.len);
                        }
                        break;
                    case SOURCE_TIMER:
                        if (message.msgId == TIMER_EXPIRED) {
                            if (sm.retry_count++ >= MAX_RETRY_LIMIT) {
                                /* Send diag failed message to source in sm.lastMessage.msgSource */
                                if(sm.lastMessage.msgSource == SOURCE_APP){
                                    memset(appDataString,0x00,sizeof(appDataString));
                                    payloadToString(failurePkt,appDataString,sizeof(failurePkt));
                                    sendDataToApp(appDataString,POLLACK_FLAG);
                                }
                                sm.current_state = SM_MCU_IFC_IDLE;
                            } else {
                                /* Retransmit DIAG initialization message sm.lastMessage */
                                printf("Retransmit DIAG ini sm.lastMessage,SOURCE_TIMER\n");
                                display_sControlMessage(sm.lastMessage);
                                uart_send_bytes(&superFanObj,(char*)&sm.lastMessage.msgPayload, sm.lastMessage.msgPayload.len);
                            }
                        }
                        
                        break;
                    default:
                        break;
                    }
                break;
            case SM_MCU_IFC_DIAG_RESP_WAIT:
            // printf("Inside SM_MCU_IFC_DIAG_RESP_WAIT\n");
                switch (message.msgSource) {
                    case SOURCE_MCU:
                        if ((message.msgPayload.seq_num == sm.expected_seq) && message.msgPayload.header == RD_RES_HEADER && (validateChecksum(&message.msgPayload))/* Also check the header */) {
                            sm.expected_seq++;
                            int payloadLen = (int) (message.msgPayload.len - (sizeof(message.msgPayload.seq_num) + sizeof(message.msgPayload.checksum) +
                                                    sizeof(message.msgPayload.last_seq_num) + sizeof(message.msgPayload.header) + sizeof(message.msgPayload.len)));
                            if(message.msgPayload.payload[0] == 0x00 && message.msgPayload.payload[1] == 0x04 && 
                                message.msgPayload.payload[4] == 0x00 && message.msgPayload.payload[5] == 0x07)
                            {
                                message.msgPayload.payload[8] = (getTotalWaterConsumption() >> 8) & 0xFF; 
                                message.msgPayload.payload[9] = getTotalWaterConsumption() & 0xFF; 
                            }
                            if (sm.expected_seq == message.msgPayload.last_seq_num) {
                                /* Diag report complete */
                                /* Forward the message to appropriate source */
                                memset(appDataString,0x00,sizeof(appDataString));
                                if(sm.lastMessage.msgSource == SOURCE_APP){
                                    payloadToString(message.msgPayload.payload,appDataString,payloadLen);
                                    sendDataToApp(appDataString,POLLACK_FLAG);
                                }
                                    sm.current_state = SM_MCU_IFC_IDLE;
                                }
                            else {
                                /* Send message to MCU with expected sequence number in it for transmitting next seq number */
                                memset(appDataString,0x00,sizeof(appDataString));
                                if(sm.lastMessage.msgSource == SOURCE_APP){
                                    payloadToString(&message.msgPayload.payload,appDataString,payloadLen);
                                    sendDataToApp(appDataString,POLLACK_FLAG);
                                }
                                
                                memset(&ARQpkt,0x00,sizeof(ARQpkt));
                                makeARQOrReqNext(RD_REQ_HEADER,&ARQpkt,sm.expected_seq,message.msgPayload.last_seq_num);
                                display_hdcpRd(&ARQpkt);
                                uart_send_bytes(&superFanObj,(char*)&ARQpkt, ARQpkt.len);
                                sm.retry_count = 0; // reset retry count to 0 (for testing)
                            }
                        } else if (sm.retry_count++ >= MAX_RETRY_LIMIT) {
                            /* Send diag failed message to source in sm.lastMessage.msgSource */
                            if(sm.lastMessage.msgSource == SOURCE_APP){
                                memset(appDataString,0x00,sizeof(appDataString));
                                payloadToString(failurePkt,appDataString,sizeof(failurePkt));
                                sendDataToApp(appDataString,POLLACK_FLAG);
                            }
                            sm.current_state = SM_MCU_IFC_IDLE;
                        } else {
                            /* Send message to MCU with expected sequence number in it for retransmission */
                            printf("Invalid data,retransmit the expected sequence number\n");
                            memset(&ARQpkt,0x00,sizeof(ARQpkt));
                            makeARQOrReqNext(RD_REQ_HEADER,&ARQpkt,sm.expected_seq,message.msgPayload.last_seq_num);
                            uart_send_bytes(&superFanObj,(char*)&ARQpkt, ARQpkt.len);
                        }
                        break;

                    case SOURCE_TIMER:
                        if (message.msgId == TIMER_EXPIRED) {
                            if (sm.retry_count++ >= MAX_RETRY_LIMIT) {
                                /* Send diag failed message to source in sm.lastMessage.msgSource */
                                if(sm.lastMessage.msgSource == SOURCE_APP) {
                                    memset(appDataString,0x00,sizeof(appDataString));
                                    payloadToString(failurePkt,appDataString,sizeof(failurePkt));
                                    sendDataToApp(appDataString,POLLACK_FLAG);
                                }
                                sm.current_state = SM_MCU_IFC_IDLE;
                            } else {
                                /* Send message to MCU with expected sequence number in it for retransmission */
                                printf("Data not received,retransmission\n");
                                memset(&ARQpkt,0x00,sizeof(ARQpkt));
                                makeARQOrReqNext(RD_REQ_HEADER,&ARQpkt,sm.expected_seq,message.msgPayload.last_seq_num);
                                display_hdcpRd(&ARQpkt);
                                uart_send_bytes(&superFanObj,(char*)&ARQpkt, ARQpkt.len);
                            }
                        }
                        break;
                    
                    default:
                        /* Diagnostics under process reply with error to appropriate source */
                        HOAGS_ERR("Diagnostics under process reply with error to appropriate source\n");
                        if(sm.lastMessage.msgSource == SOURCE_APP){
                            memset(appDataString,0x00,sizeof(appDataString));
                            payloadToString(failurePkt,appDataString,sizeof(failurePkt));
                            sendDataToApp(appDataString,POLLACK_FLAG);
                        }
                }
                break;
            case SM_MCU_IFC_RENESAS_BOOT_ACK_WAIT:
                switch (message.msgSource)
                {
                    case SOURCE_MCU:
                    if (message.msgPayload.seq_num == 0 && message.msgPayload.header == CTRL_ACK_HEADER && (validateChecksum(&message.msgPayload))) 
                    {
                        printf("Renesas ACK Received\n");
                        renesasState = FALSE;
                        sm.current_state = SM_MCU_IFC_IDLE;
                        vTaskDelay(pdMS_TO_TICKS(10000));
                        rebootRenesas();
                        resetUartTimer();
                    }
                    case SOURCE_TIMER:
                    if (message.msgId == TIMER_EXPIRED)
                    {
                        if (sm.retry_count++ >= MAX_RETRY_LIMIT)
                        {
                            /* Send diag failed message to source in sm.lastMessage.msgSource */
                            sm.current_state = SM_MCU_IFC_IDLE;
                            printf("Retry Limit Completed Changing State to IDLE\n");
                        }
                        else
                        {
                            /* Send message to MCU with expected sequence number in it for retransmission */
                            display_sControlMessage(sm.lastMessage);
                            uart_send_bytes(&superFanObj,(char*)&sm.lastMessage.msgPayload, sm.lastMessage.msgPayload.len);
                            printf("ACK Missing Retry the packet\n");
                        }
                    }
                    default:
                        break;
                }
                break;
            case SM_MCU_IFC_RENESAS_UPDATE_WAIT:
            // printf("Inside SM_MCU_IFC_RENESAS_UPDATE_WAIT\n");
                switch (message.msgSource)
                {
                case SOURCE_RENESASUPDATE:
                    sm.retry_count = 0;
                    sm.diag_command_index++;
                    if (sm.diag_command_index < (TOTAL_ROW_SIZE))
                    {
                        //printf("Sending packet to MCU(%d).\n",sm.diag_command_index);
                        uint32_t address = RENESES_IMG_START_ADDRESS + (sm.diag_command_index * COLUMN_SIZE);
                        uint16_t temp_buffer[COLUMN_SIZE / 2];
                        flashReadRenesesData(address, COLUMN_SIZE, temp_buffer);
                        memset(xmodem_data,0x00,sizeof(xmodem_data));
                        for (int i = 0; i < COLUMN_SIZE / 2; i++) {
                            xmodem_data[0][2 * i]     = (uint8_t)(temp_buffer[i] & 0xFF);
                            xmodem_data[0][2 * i + 1] = (uint8_t)((temp_buffer[i] >> 8) & 0xFF);
                        }
                        
                        uart_send_bytes(&superFanObj, xmodem_data[0], COLUMN_SIZE);
                    }
                    else if(sm.diag_command_index == (TOTAL_ROW_SIZE))
                    {
                        isFinalAck = TRUE;
                        uart_send_bytes(&superFanObj, &finalPack, sizeof(finalPack));
                        printf("Final Pack\n");
                    }
                    else
                    {
                        gtimer_stop(&ledBlinkTimer);
                        gtimer_deinit(&ledBlinkTimer);
                        gpio_write(&ota_led, 0);
                        isFinalAck = FALSE;
                        isRenesasUpdateBegin = FALSE;
                        sm.current_state = SM_MCU_IFC_IDLE;
                        gpio_deinit(&ota_led);
                        initialize_Htap_LED(PA_20);
                        ble_app_init();
                        printf("Renesas Update Success\n");
                        memset(versionNumber,0x00,sizeof(versionNumber));
                        reInitialize_HDCP_Uart(HE3_NEW_BAUDRATE);
                        resetIsTemp();
                    }
                    break;

                case SOURCE_TIMER:
                    if (message.msgId == TIMER_EXPIRED)
                    {
                        if (sm.retry_count++ >= MAX_RETRY_LIMIT)
                        {
                            /* Send diag failed message to source in sm.lastMessage.msgSource */
                            gtimer_stop(&ledBlinkTimer);
                            gtimer_deinit(&ledBlinkTimer);
                            gpio_write(&ota_led, 0);
                            isFinalAck = FALSE;
                            isRenesasUpdateBegin = FALSE;
                            sm.current_state = SM_MCU_IFC_IDLE;
                            rebootRenesas();
                            gpio_deinit(&ota_led);
                            initialize_Htap_LED(PA_20);
                            ble_app_init();
                            printf("Retry Limit Completed Changing State to IDLE\n");
                        }
                        else
                        {
                            /* Send message to MCU with expected sequence number in it for retransmission */
                            uart_send_bytes(&superFanObj, xmodem_data[sm.diag_command_index], COLUMN_SIZE);
                            printf("ACK Missing Retry the packet OTA\n");
                        }
                    }
                    default:
                        break;
                }
                break;
            default:
                HOAGS_INFO("Invalid state. Resetting to IDLE.\n");
                sm.current_state = SM_MCU_IFC_IDLE;
                break;
        }        
    }
}

void startRemoteDiagTask() {
	HOAGS_INFO("\n");
	if(pdTRUE != xTaskCreate(runRemoteDiagTask, ((const char *)"runRemoteDiagTask"), 1024, NULL, tskIDLE_PRIORITY + 4, &remoteDiagTaskHandle)) {
		HOAGS_ERR("Failed to create %s\n",__func__);
	}
}


/* In UART task receiving message from MCU, create a message sControlMessage and fill the source as MCU and message id as MCU_MSG and payload in msgPayload */
