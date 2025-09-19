#include "purifier.h"

#define OTA_IMGID_BOOT		0
#define OTA_INDEX_1			0
#define OTA_INDEX_2			1

static sControlMessage purifierBle;

uint16_t calculate_checksum(const struct hdcpRd *blePkt, const size_t size) {
    uint16_t checksum = 0;

    for (size_t i = 0; i < size; i++) {
        checksum += blePkt->payload[i];
    }
    checksum += blePkt->seq_num;
    checksum += blePkt->last_seq_num;
    return checksum;
}

void waterControl(const char* payload, const size_t len,int levelIndex)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    printf("action=%d\n", *action);
    struct hdcpRd blePkt ={CONTROL_HEADER,0,0,0,0};
    uint8_t waterOffPayload[] = {0x00, 0x01, 0x00, 0x01,ALL_OPS_DISABLED}; 
    uint8_t normalWaterPayload[] = {0x00, 0x01, 0x00, 0x01,NORMAL_WATER_ON}; 
    uint8_t hotWaterPayload[] = {0x00, 0x01, 0x00, 0x01,HOT_WATER_ON}; 
    uint8_t warmWaterPayload[] = {0x00, 0x01, 0x00, 0x01,WARM_WATER_ON}; 

    memset(&purifierBle,0x00,sizeof(purifierBle));
    switch (*action)
    {
        case WP_WATER_ON:
            purifierBle.msgSource = SOURCE_APP;
            purifierBle.msgId = REMOTE_CONTROL;
            switch(levelIndex) {
                case WP_CMD_NORMAL_CONTROL:
                    printf("Normal water on\n");
                    memcpy(blePkt.payload, normalWaterPayload, sizeof(normalWaterPayload)); 
                    blePkt.len = sizeof(normalWaterPayload) + sizeof(blePkt.checksum) + sizeof(blePkt.seq_num) +
                         sizeof(blePkt.last_seq_num) + sizeof(blePkt.header) + sizeof(blePkt.len);
                    blePkt.checksum = calculate_checksum(&blePkt,sizeof(normalWaterPayload)); 
                    break;
                case WP_CMD_HOT_CONTROL:
                    printf("Hot water on\n");
                    memcpy(blePkt.payload, hotWaterPayload, sizeof(hotWaterPayload)); 
                    blePkt.len = sizeof(hotWaterPayload) + sizeof(blePkt.checksum) + sizeof(blePkt.seq_num) +
                        sizeof(blePkt.last_seq_num) + sizeof(blePkt.header) + sizeof(blePkt.len);
                    blePkt.checksum = calculate_checksum(&blePkt,sizeof(hotWaterPayload));
                    break;
                case WP_CMD_WARM_CONTROL:
                    printf("Warm water on\n");
                    memcpy(blePkt.payload, warmWaterPayload, sizeof(warmWaterPayload)); 
                    blePkt.len = sizeof(warmWaterPayload) + sizeof(blePkt.checksum) + sizeof(blePkt.seq_num) +
                    sizeof(blePkt.last_seq_num) + sizeof(blePkt.header) + sizeof(blePkt.len);
                    blePkt.checksum = calculate_checksum(&blePkt,sizeof(warmWaterPayload));
                    break;

            }
            memcpy(&purifierBle.msgPayload,&blePkt,sizeof(blePkt));
            //display_sControlMessage(purifierBle);
            xQueueSend(getPurifierQueueDataHandle(),&purifierBle,xQUEUE_TIMEOUT);
            break;
            
        case WP_WATER_OFF:
            printf("Water off\n");
            purifierBle.msgSource = SOURCE_APP;
            purifierBle.msgId = REMOTE_CONTROL;
            memcpy(blePkt.payload, waterOffPayload, sizeof(waterOffPayload)); 
            blePkt.len = sizeof(waterOffPayload) + sizeof(blePkt.checksum) + sizeof(blePkt.seq_num) +
            sizeof(blePkt.last_seq_num) + sizeof(blePkt.header) + sizeof(blePkt.len);
            blePkt.checksum = calculate_checksum(&blePkt,sizeof(waterOffPayload));
            memcpy(&purifierBle.msgPayload,&blePkt,sizeof(blePkt));
            //display_sControlMessage(purifierBle);
            xQueueSend(getPurifierQueueDataHandle(),&purifierBle,xQUEUE_TIMEOUT);
            break;
        default:
            HOAGS_ERR("INVALID COMMAND !");
            
    }
    free(action);
}

void sendbootpacketToRenesas(void)
{
    printf("Inside Boot Packet Sending\n");
    uint8_t tempPayload[5] = {0};
    struct hdcpRd bootPkt = {0};
    bootPkt.header = 0XDD;

    tempPayload[0] = 0x00;
    tempPayload[1] = 0x07;
    tempPayload[2] = 0x00;
    tempPayload[3] = 0x00;
    tempPayload[4] = 0x00;

    memset(&purifierBle, 0x00, sizeof(purifierBle));
    purifierBle.msgSource = SOURCE_REQUEST;
    purifierBle.msgId = BOOTLOADER;

    memcpy(bootPkt.payload, tempPayload, sizeof(tempPayload));
    bootPkt.len = sizeof(tempPayload) + sizeof(bootPkt.checksum) + sizeof(bootPkt.seq_num) +
                 sizeof(bootPkt.last_seq_num) + sizeof(bootPkt.header) + sizeof(bootPkt.len);

    bootPkt.checksum = calculate_checksum(&bootPkt, sizeof(tempPayload));
    memcpy(&purifierBle.msgPayload, &bootPkt, sizeof(bootPkt));

    //display_sControlMessage(purifierBle);
    xQueueSend(getPurifierQueueDataHandle(), &purifierBle, xQUEUE_TIMEOUT);
}

void sendCommandToMCU(Source src, uint8_t msgId, uint8_t header, uint8_t *payload, size_t payloadSize, const char *logMsg) {
    struct hdcpRd blePkt = {header, 0, 0, 0, 0}; 
    memset(&purifierBle, 0x00, sizeof(purifierBle));

    purifierBle.msgSource = src;
    purifierBle.msgId = msgId;
    
    memcpy(blePkt.payload, payload, payloadSize);
    
    blePkt.len = payloadSize + sizeof(blePkt.checksum) + sizeof(blePkt.seq_num) +
                 sizeof(blePkt.last_seq_num) + sizeof(blePkt.header) + sizeof(blePkt.len);
    
    blePkt.checksum = calculate_checksum(&blePkt, payloadSize);
    
    memcpy(&purifierBle.msgPayload, &blePkt, sizeof(blePkt));

    printf("%s\n", logMsg);
    xQueueSend(getPurifierQueueDataHandle(), &purifierBle, xQUEUE_TIMEOUT);
}

void initiateRemoteDiag(Source src) {
    uint8_t initiateDiagnosticsPayload[] = {0x00, 0x02, 0x00, 0x01, RD_START};
    sendCommandToMCU(src, DIAGNOSTICS_CONTROL, RD_REQ_HEADER, initiateDiagnosticsPayload, 
                   sizeof(initiateDiagnosticsPayload), "Diag_req sent to MCU");
}

void initiateDeviceAnalysis(Source src) {
    uint8_t initiateAnalysisPayload[] = {0x00, 0x04, 0x00, 0x01, START_ANALYSIS};
    sendCommandToMCU(src, DIAGNOSTICS_CONTROL, RD_REQ_HEADER, initiateAnalysisPayload, 
                   sizeof(initiateAnalysisPayload), "Analysis reqeust sent to MCU");
}

void sendResetToReneses(Source src) {
    uint8_t resetPayload[] = {0x00, 0x06, 0x00, 0x01, 0x01};
    sendCommandToMCU(src, REMOTE_CONTROL, CONTROL_HEADER, resetPayload, 
                   sizeof(resetPayload), "Reset cmd sent to MCU");
}

void sendDateTimeToReneses(Source src,int istDateTime[]){
    uint8_t dateTimePayload[] = {0x00, 0x05, 0x00, 0x0F, 0x00,0x01,0x00,0x04,istDateTime[0], istDateTime[1], istDateTime[2], istDateTime[3],
                                    0x00,0x02,0x00,0x03,istDateTime[4], istDateTime[5],istDateTime[6]}; 
    sendCommandToMCU(src, REMOTE_CONTROL, CONTROL_HEADER, dateTimePayload, 
                   sizeof(dateTimePayload), "DateTime sent to MCU");
}

void sendInletTDSToReneses(Source src, uint8_t statusFlag) {
    char temp[10] = {0};
    getEnvItem(INLET_TDS, temp);

    int tdsValue = atoi(temp);

    memset(temp,0x00,sizeof(temp));

    getEnvItem(OUTLET_TDS, temp);
    int outletTdsValue = atoi(temp);


    char offsetStr[5] = {0};
    getEnvItem(INLET_TDS_OFFSET, offsetStr);
    int offset = atoi(offsetStr);

    uint8_t inletTds[2] = {0};
    inletTds[0] = (tdsValue >> 8) & 0xFF;
    inletTds[1] = tdsValue & 0xFF;

    uint8_t outletTds[2] = {0};
    outletTds[0] = (outletTdsValue >> 8) & 0xFF;
    outletTds[1] = outletTdsValue & 0xFF;

    
    uint8_t tdsPayload[] = {
        0x00, 0x0b, statusFlag,0x00, 0x0d, 0x00, 0x01, 0x00, 0x02,
        inletTds[0],
        inletTds[1],
        0x00, 0x02, 0x00, 0x03,
        outletTds[0],
        outletTds[1],
        0x00
    };

    tdsPayload[17] = (uint8_t)(int8_t)offset;

    sendCommandToMCU(src, REMOTE_CONTROL, CONTROL_HEADER,
                     tdsPayload, sizeof(tdsPayload), "Inlet and Outlet TDS sent to MCU");
}


uint8_t hexToInt(const char *hexStr) {
    uint8_t value = 0;
    while (*hexStr) {
        char c = toupper(*hexStr);  // Ensure uppercase for 'a'-'f'
        value <<= 4;                // Shift left by 4 bits to make space for the next nibble
        if (c >= '0' && c <= '9') {
            value += c - '0';       // Convert '0'-'9' to 0-9
        } else if (c >= 'A' && c <= 'F') {
            value += c - 'A' + 10;  // Convert 'A'-'F' to 10-15
        } else {
            printf("Error: Invalid hexadecimal character '%c'\n", c);
            return 0;
        }
        hexStr++;
    }
    return value;
}

void sendTemperatureToReneses(Source src) {
    char temp[5] = {0};  
    uint8_t tempPayload[15] = {0};
    uint8_t value; 
    int WaterTemperatureTag = 0x01; 
    uint8_t warmTemperature, hotTemperature;

    getEnvItem(WARM_TEMPERATURE, temp);
    warmTemperature = hexToInt(temp);

    memset(temp,0x00,sizeof(temp));

    getEnvItem(HOT_TEMPERATURE, temp);
    hotTemperature = hexToInt(temp);

    struct hdcpRd blePkt = {CONTROL_HEADER, 0, 0, 0, 0};

    tempPayload[0] = 0x00;
    tempPayload[1] = 0x03;
    tempPayload[2] = 0x00;
    tempPayload[3] = 0x0b;
    tempPayload[4] = 0x00;
    tempPayload[5] = WaterTemperatureTag;
    tempPayload[6] = 0x00;
    tempPayload[7] = 0x02;
    tempPayload[8] = warmTemperature;
    tempPayload[9] = hotTemperature;

    memset(temp,0x00,sizeof(temp));

    getEnvItem(CHILDLOCKSTATE, temp);

    value = hexToInt(temp);

    tempPayload[10] = 0x00;
    tempPayload[11] = 0x03;
    tempPayload[12] = 0x00;
    tempPayload[13] = 0x01;
    if(value == 0 || value == 2) tempPayload[14] = 0x00;
    else if(value == 1) tempPayload[14] = 0x01;


    sendCommandToMCU(src, REMOTE_CONTROL, CONTROL_HEADER, tempPayload, 
        sizeof(tempPayload), "Temperature sent to MCU");
}

void sendWaterFlowCustomization(Source src){
    char temp[5] = {0};  
    uint8_t waterCustPayload[10] = {0};
    int WaterCustomizationTag = 0x02; 
    uint8_t glassCust, bottleCust;

    getEnvItem(GLASS_CUST, temp);
    glassCust = hexToInt(temp);

    memset(temp,0x00,sizeof(temp));

    getEnvItem(BOTTLE_CUST, temp);
    bottleCust = hexToInt(temp);

    struct hdcpRd blePkt = {CONTROL_HEADER, 0, 0, 0, 0};

    waterCustPayload[0] = 0x00;
    waterCustPayload[1] = 0x03;
    waterCustPayload[2] = 0x00;
    waterCustPayload[3] = 0x06;
    waterCustPayload[4] = 0x00;
    waterCustPayload[5] = WaterCustomizationTag;
    waterCustPayload[6] = 0x00;
    waterCustPayload[7] = 0x02;
    waterCustPayload[8] = glassCust;
    waterCustPayload[9] = bottleCust;
    
    sendCommandToMCU(src, REMOTE_CONTROL, CONTROL_HEADER, waterCustPayload, 
        sizeof(waterCustPayload), "Water customization sent to MCU");
}

void setTemperature(const char* payload, const size_t len) {
    if (len == 0) {
        HOAGS_ERR("Payload length is zero\n");
        return;
    }
    uint8_t* action = hoagsMalloc(len);
    if (action == NULL) {
        HOAGS_ERR("Memory allocation failed\n");
        return;
    }
    memcpy(action, payload, len);
    char tempValue[3] = {0};
    snprintf(tempValue, sizeof(tempValue), "%02X", action[0]);
    printf("action=%d\n", *action);
    int temperature = (*action);
    if((temperature) >= WARM_WATER_MIN_RANGE && (temperature) <= WARM_WATER_MAX_RANGE){
        setEnvItem(WARM_TEMPERATURE, tempValue);
    }
    else if((temperature) >= HOT_WATER_MIN_RANGE && (temperature) <= HOT_WATER_MAX_RANGE){
        setEnvItem(HOT_TEMPERATURE, tempValue);
    }
    free(action);
    sendTemperatureToReneses(SOURCE_APP);
}

void filterReset(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    if (payload == NULL || len == 0) {
        HOAGS_ERR("Invalid payload in %s\n", __func__);
        return;
    }
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    printf("action=%d\n", *action);
    uint8_t filterResetCmd[5] = {0x00, 0x08, 0x00, 0x01,WP_NO_RESET};  
    switch (*action)
    {
        case WP_OVERALL_FILTER_RESET:
        case WP_SEDIMENTARY_FILTER_RESET:
        case WP_RO_FILTER_RESET:
        case WP_ALKALINE_FILTER:
        case WP_MINERAL_FILTER:
        case WP_COPPER_FILTER:
            filterResetCmd[4] = *action;
            break;
        default:
            HOAGS_ERR("INVALID COMMAND FOR %s\n!",__func__);
            
    }
    free(action);
    sendCommandToMCU(SOURCE_APP, REMOTE_CONTROL, CONTROL_HEADER, filterResetCmd, 
        sizeof(filterResetCmd), "filterReset sent to MCU");
}

void sendWaterconusmptionEraseCmdToReneses(Source src) {
    eraseWaterConsumptionRegion(); //this erase water consumption storage in HE3
    uint8_t resetPayload[] = {0x00, 0x32, 0x00, 0x01, 0x01};
    sendCommandToMCU(src, REMOTE_CONTROL, CONTROL_HEADER, resetPayload, 
                   sizeof(resetPayload), "sendWaterconusmptionEraseCmdToReneses sent to MCU");
}

#if FILTER_SETTING
void filterSetting(uint8_t externalTag, const char* payload, const size_t len, uint8_t internalTag)
{

    if (payload == NULL || len == 0) {
        HOAGS_ERR("Invalid payload in %s\n", __func__);
        return;
    }

    uint8_t* action = hoagsMalloc(len);
    if (action == NULL) {
        HOAGS_ERR("Memory allocation failed in %s\n", __func__);
        return;
    }

    memcpy(action, payload, len);

    switch (internalTag)
    {
        case WP_CARBON:
        case WP_SEDIMENTARY:
        case WP_RO:
        case WP_ALKALINE:
        case WP_MINERAL:
        case WP_COPPER:
        {
            uint8_t filtersettingCmd[] = {0x00, externalTag, 0x00, 0x06, 0x00, internalTag, 0x00, 0x02, action[1], action[0]};
            sendCommandToMCU(SOURCE_APP, REMOTE_CONTROL, CONTROL_HEADER, filtersettingCmd, 
                     sizeof(filtersettingCmd), "filter Setting sent to MCU");
            break;
        }
        default:
            HOAGS_ERR("INVALID COMMAND FOR %s\n!", __func__);
            free(action);
            return;
    }

    free(action);
}
#endif

void makePeriodicPacket(unsigned char packet[],uint32_t date,uint32_t alarmValue,uint8_t filterLife,uint8_t sedimentaryLife,uint8_t ROfilterLife,
    uint8_t alkalineFilter,uint8_t mineralFilter,uint8_t copperFilter,uint16_t waterConsumption) {
    int totalLength = 0;
    unsigned char totalLen[5] = {0};
    unsigned char dateLen[5] = {0};
    unsigned char dateStr[15] = {0};
    unsigned char dateInHex[20] = {0};

    unsigned char wcStr[20] = {0};
    unsigned char wcLen[5] = {0}; //water consumption

    unsigned char alarmValueStr[5] = {0};
    unsigned char alarmValueLen[5] = {0};

    unsigned char filterLifeStr[20] = {0};
    unsigned char filterLifeLen[5] = {0};

    memset(packet,0x00,sizeof(packet));

    strcpy(packet,PERIODIC_DATA_TAG);

    sprintf(dateStr,"%d",date);
    sprintf(dateLen,"%04x",(int)strlen(dateStr) / 2);

    sprintf(wcStr, "%04x",waterConsumption); 
    sprintf(wcLen,"%04x",(int)strlen(wcStr) / 2);

    sprintf(alarmValueStr,"%04d",alarmValue);
    sprintf(alarmValueLen,"%04x",(int)strlen(alarmValueStr) / 2);

    sprintf(filterLifeStr,"%02x%02x%02x%02x%02x%02x",filterLife,sedimentaryLife,ROfilterLife,
        alkalineFilter,mineralFilter,copperFilter);
    sprintf(filterLifeLen,"%04x",(int)strlen(filterLifeStr) / 2);

    totalLength = (int) (strlen(DATETAG) + strlen(WCTAG) + strlen(ALARM_TAG)+
    strlen(wcStr) + strlen(dateStr) + strlen(alarmValueStr)
    + strlen(dateLen) + strlen(wcLen) + strlen(alarmValueLen)
    + strlen(FILTER_CLEAN) + strlen(filterLifeLen) + strlen(filterLifeStr));
    sprintf(totalLen, "%04x",(int)(totalLength) / 2);

    strcat(packet, totalLen);

    strcat(packet,DATETAG);
    strcat(packet,dateLen);
    strcat(packet,dateStr);

    strcat(packet,WCTAG);
    strcat(packet,wcLen);
    strcat(packet,wcStr);

    strcat(packet,ALARM_TAG);
    strcat(packet,alarmValueLen);
    strcat(packet,alarmValueStr);

    strcat(packet,FILTER_CLEAN);
    strcat(packet,filterLifeLen);
    strcat(packet,filterLifeStr);
}


// void sendPeriodcDataToApp() {
//     unsigned char periodicPkt[PACKET_SIZE];
//     for(int sector = 0; sector < TOTAL_DAYS_COUNT; sector++){
//         //printf("Index:%d,Date:%d\t Value:%d\n",sector,getDate(sector),getCurrentValue(sector));
//         if(getDate(sector) > 0){
//             makePeriodicPacket(periodicPkt,getDate(sector),0,0,0,0,0,0,0,getCurrentValue(sector));
//             sendDataToApp(periodicPkt,POLLACK_FLAG);
//             vTaskDelay(pdMS_TO_TICKS(100));
//         }
//     }
// }


void sendPeriodcDataToApp(void) {
    unsigned char periodicPkt[PACKET_SIZE];
    int offset = 0;
    int dayCounter = 0;

    periodicPkt[offset++] = START_BYTE;

    for (int sector = 0; sector < TOTAL_DAYS_COUNT; sector++) {
        uint32_t date = getDate(sector);
        uint16_t value = getCurrentValue(sector);

        if (date > 0) {
            char buffer[32];
            int written = snprintf(buffer, sizeof(buffer), "%08u,%u;", date, value);

            memcpy(&periodicPkt[offset], buffer, written);
            offset += written;
            dayCounter++;

            // If 5 days collected, close packet and send
            if (dayCounter == 5) {
                periodicPkt[offset++] = STOP_BYTE;
                sendDataToApp(periodicPkt, POLLACK_FLAG);

                vTaskDelay(pdMS_TO_TICKS(50)); // small gap

                // Reset for next packet
                memset(periodicPkt, 0, sizeof(periodicPkt));
                offset = 0;
                periodicPkt[offset++] = START_BYTE;
                dayCounter = 0;
            }
        }
    }

    // If leftover days < 5, send them too
    if (dayCounter > 0) {
        periodicPkt[offset++] = STOP_BYTE;
        sendDataToApp(periodicPkt, POLLACK_FLAG);
    }
}


