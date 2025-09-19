#include "flashWritePurifier.h"
#include "flash_api.h"

#define OTA_IMGID_BOOT		0
#define OTA_INDEX_1			0
#define OTA_INDEX_2			1

//0xFAFF 20250202 0001 0003 0005 FFFF
static flash_data_info flashDataInfo[TOTAL_DAYS_COUNT];
static totalWcStruct totalWater;
static int istDateTimeStored[7] = {0};
static int recordCount = 0;

static bool isTempSent = FALSE;
static bool isWaterCustSent = FALSE;

uint16_t waterConsumption = 0;
uint32_t receivedDate = 0;
static flash_t flash_wc;


void setIsWaterCustSent(bool custStatus){
    isWaterCustSent = custStatus;
}

bool getIsWaterCustSent() {
    return isWaterCustSent;
}

void resetIsTemp(){
    isTempSent = FALSE;
}

int* getIstDateTimeStored(void) {
    return istDateTimeStored;
}

uint16_t getTotalWaterConsumption() {
    return totalWater.currentValue;
}

uint16_t getCurrentValue(int sectorNo){
    return flashDataInfo[sectorNo].currentValue;
}

uint32_t getDate(int sectorNo) {
    return flashDataInfo[sectorNo].date;
}

eHoagsError flash_init_sector(char sector, uint32_t date, uint16_t value) {
    flashDataInfo[sector].pCurrentAddress = flashDataInfo[sector].pStartAddress;
    flashDataInfo[sector].currentValue = 0;
    HOAGS_ERR("flashDataInfo[%d].pCurrentAddress:%p\n",sector,flashDataInfo[sector].pCurrentAddress);
	uint16_t error = flashEraseSector(flashDataInfo[sector].pCurrentAddress);
    if (error == 0) {
        flashWriteRenesesData(flashDataInfo[sector].pCurrentAddress, 0xFAFF, sizeof(uint16_t));
        flashDataInfo[sector].pCurrentAddress += 1;
        flashWriteRenesesData(flashDataInfo[sector].pCurrentAddress, (date >> 16), sizeof(uint16_t));
        flashDataInfo[sector].pCurrentAddress += 1;
        flashWriteRenesesData(flashDataInfo[sector].pCurrentAddress, (date & 0xFFFF), sizeof(uint16_t));
        flashDataInfo[sector].pCurrentAddress += 1;
        flashWriteRenesesData(flashDataInfo[sector].pCurrentAddress, value, sizeof(uint16_t));
        flashDataInfo[sector].pCurrentAddress += 1;
        flashDataInfo[sector].isFree = FALSE;
    } else {
        flashDataInfo[sector].unusable = TRUE;
        return HOAGS_FAILURE;
    }

    return HOAGS_SUCCESS;
}

int flash_allocate_new_sector (uint32_t date) {
    int sectorToPrefer = -1;
    uint32_t minDate = date;
    for (int i = 0; i < TOTAL_DAYS_COUNT; i++) {
        if (flashDataInfo[i].unusable != TRUE) {
            if (flashDataInfo[i].isFree == TRUE) {
                /* Free sector found so use this sector */
                sectorToPrefer = i;
                break;
            } else {
                if (flashDataInfo[i].date < minDate) {
                    minDate = flashDataInfo[i].date;
                    sectorToPrefer = i;
                }
            }
        }
    }
    if (sectorToPrefer == -1) {
        /* This scenario should not happen at all but if it happened, try using sector 0 */
        printf("*****************************END of the WATER CONSUMPTION REGION **************************\n");
        sectorToPrefer = 0;
    }
    return sectorToPrefer;
}

char flash_allocate_init_sector(uint32_t date, uint16_t value) {
    for (int try = 0;  try < TOTAL_DAYS_COUNT; try++) {
        int s = flash_allocate_new_sector(date);
        if (flash_init_sector(s, date, value) == HOAGS_SUCCESS) {
            //flash_erase_sector(flashDataInfo[try].pStartAddress, FLASH_PARTITION_SIZE);
            flashDataInfo[s].date = date;
			// flashEraseSector(flashDataInfo[try].pStartAddress);
            return s;
        }
    }
    return TOTAL_DAYS_COUNT;
}


eHoagsError flash_write_inc_data() {
    int sector = -1;

    for (int i = (TOTAL_DAYS_COUNT - 1); i >= 0; i--) {
        if (flashDataInfo[i].date == receivedDate) {
            sector = i;
            break;
        }
    }
    if (sector == -1) {
        printf("********** NEW DAY ***************\n");
        sector = flash_allocate_init_sector(receivedDate, 0);
        if (sector >= 0) {
            recordCount++;
        } else {
            printf("Error: Failed to allocate new sector.\n");
            return HOAGS_FAILURE;
        }
    }

    if (sector < TOTAL_DAYS_COUNT && sector >= 0) {
        printf("Before adding: %d\n", flashDataInfo[sector].currentValue);
        flashDataInfo[sector].currentValue += waterConsumption;
        printf("After adding: %d\n", flashDataInfo[sector].currentValue);

        if ((flashDataInfo[sector].pCurrentAddress + 2) >= (flashDataInfo[sector].pEndAddress)) {
            printf("Sector is full. Creating a new sector for the same date.\n");

            uint16_t oldValue = flashDataInfo[sector].currentValue;

            int newSector = flash_allocate_init_sector(receivedDate, oldValue);

            if (newSector < 0) {
                printf("Error: Failed to allocate new sector after full sector.\n");
                return HOAGS_FAILURE;
            }

            // Optionally erase or mark old sector as unusable
            printf("ERASING SECTOR %d\n",sector);
            flashEraseSector(flashDataInfo[sector].pStartAddress);
            flashDataInfo[sector].pCurrentAddress = flashDataInfo[sector].pStartAddress;
            flashDataInfo[sector].unusable = FALSE;
            flashDataInfo[sector].isFree = TRUE;
            flashDataInfo[sector].date = 0;
            flashDataInfo[sector].currentValue = 0;
            sector = newSector;
            flashDataInfo[sector].currentValue = oldValue;
        }
        printf("Data written at %p: %d\n", flashDataInfo[sector].pCurrentAddress, flashDataInfo[sector].currentValue);
        flashWriteRenesesData(flashDataInfo[sector].pCurrentAddress, flashDataInfo[sector].currentValue, sizeof(uint16_t));
        flashDataInfo[sector].pCurrentAddress += 1;
        storeTotalWaterConsumption(waterConsumption);

        waterConsumption = 0;

        return HOAGS_SUCCESS;
    }

    return HOAGS_FAILURE;
}

void flash_inc_init() {
    unsigned int address = (unsigned int*) WC_FLASH_START_ADDRESS;
    for (int i = 0; i < TOTAL_DAYS_COUNT; i++) {
        flashDataInfo[i].pCurrentAddress = flashDataInfo[i].pStartAddress = address + (FLASH_PARTITION_SIZE * i);
        unsigned int tempStartAddr = flashDataInfo[i].pStartAddress;
        flashDataInfo[i].pEndAddress = (tempStartAddr + FLASH_PARTITION_SIZE);
        flashDataInfo[i].unusable = FALSE;

        uint16_t marker;
        flashReadRenesesData(flashDataInfo[i].pCurrentAddress,sizeof(uint16_t),&marker);
        //printf("%d. StartAddress:%p,End address:%p\n",i,flashDataInfo[i].pStartAddress,flashDataInfo[i].pEndAddress);
        if (marker == 0xFAFF) {
            /* Data present in this sector */
            flashDataInfo[i].pCurrentAddress += 1;
            /* Extract the date which will be in first 4 bytes */
            uint16_t dateMsb;
            flashReadRenesesData(flashDataInfo[i].pCurrentAddress,sizeof(uint16_t),&dateMsb);

            flashDataInfo[i].pCurrentAddress += 1;

            uint16_t dataLsb;
            flashReadRenesesData(flashDataInfo[i].pCurrentAddress,sizeof(uint16_t),&dataLsb);

            flashDataInfo[i].date = (dateMsb << 16) | dataLsb;
            flashDataInfo[i].pCurrentAddress += 1;
            while (1) {
                uint16_t lastData;
                flashReadRenesesData((flashDataInfo[i].pCurrentAddress + 1),sizeof(uint16_t),&lastData);
                //printf("LastData:%04x\n\n",lastData);
                if ((flashDataInfo[i].pCurrentAddress + 1) >= flashDataInfo[i].pEndAddress) {
                    /* This sector is filled with data. This should not happen at all so erase sector for recovery */
                    flashDataInfo[i].isFree = TRUE;
                    flashDataInfo[i].pCurrentAddress = flashDataInfo[i].pStartAddress;
                    flashDataInfo[i].currentValue = 0;
                    HOAGS_ERR("ERASE is happeing for sector:%d\n",i);
					flashEraseSector(flashDataInfo[i].pStartAddress);
                    break;
                } else if (lastData == 0xFFFF) {
                    /* No data beyond this address so we have th latest value here */
                    uint16_t currentData;
                    flashReadRenesesData(flashDataInfo[i].pCurrentAddress,sizeof(uint16_t),&currentData);
                    flashDataInfo[i].currentValue = currentData;
                    printf("Date:%d,Current Value:%d\n",flashDataInfo[i].date,flashDataInfo[i].currentValue);
                    break;
                }
                flashDataInfo[i].pCurrentAddress++;
            }
        } else {
            flashDataInfo[i].isFree = TRUE;
        }
    }

    //Sorting the data
    for(int i = 0; i < TOTAL_DAYS_COUNT - 1; i++){
        for(int j = 0; j < TOTAL_DAYS_COUNT - i - 1; j++){
            if(flashDataInfo[j].date > flashDataInfo[j + 1].date)
            {
                flash_data_info temp = flashDataInfo[j + 1];
                flashDataInfo[j + 1] = flashDataInfo[j];
                flashDataInfo[j] = temp;
            }
        }
    }
}

void handleWaterConsumptionData(uint32_t receivedTime) {
    static uint32_t lastStoredTime = 0;
    static uint32_t lastReceivedDate = 0;

    int hour = receivedTime / 10000;
    int minute = (receivedTime / 100) % 100;
    uint32_t totalMinutes = hour * 60 + minute;

    if (lastStoredTime == 0) {
        lastStoredTime = totalMinutes;
    }
    if((waterConsumption != 0) &&
        ((waterConsumption >= LITRE_WISE_STORING) || (receivedDate != lastReceivedDate) || (totalMinutes - lastStoredTime) >= RESET_TIME_INTERVEL)) {
        printf("*************send reset to reneses********************");
        sendResetToReneses(SOURCE_REQUEST);
        lastStoredTime = totalMinutes;
    }
    lastReceivedDate = receivedDate;
}

void sendLivePeriodicDataToCloud(uint16_t cloudWc, int index,uint16_t alarmValue, uint8_t filterLife) {
    cloudWc += flashDataInfo[index].currentValue;
    static uint32_t lastSentData;
    printf("********************Total water Consumption(%d):%d****************\n",receivedDate,cloudWc);
    if(((cloudWc - lastSentData) >= WATER_CONSUMPTION_CLOUD_SEND_INTERVEL) || (lastSentData > cloudWc)) {
        char periodicDataPkt[PACKET_SIZE * 5];
        unsigned char *liveWaterConsumedCloudDataPkt = hoagsMalloc(PACKET_SIZE * 6);
        if (!liveWaterConsumedCloudDataPkt) {
            printf("Memory allocation failed for liveWaterConsumedCloudDataPkt\n");
            return;
        }
        memset(liveWaterConsumedCloudDataPkt,0x00,sizeof(liveWaterConsumedCloudDataPkt));
        memset(periodicDataPkt,0x00,sizeof(periodicDataPkt));

        makeCloudPeriodicPacket(periodicDataPkt,cloudWc,alarmValue,filterLife);

        makeDataPacket(liveWaterConsumedCloudDataPkt,RD_RSP_TAG,periodicDataPkt);

        if (xQueueSend(getMqttQueueHandle(), &liveWaterConsumedCloudDataPkt, pdMS_TO_TICKS(200)) != pdPASS) {
            printf("Queue send failed, freeing memory \n");
            free(liveWaterConsumedCloudDataPkt);
        }
        lastSentData = cloudWc;
    }
}

void sendLivePeriodicDataToApp(int index, uint32_t receivedDate, uint16_t alarmValue, uint8_t filterLife,
                                  uint8_t sedimentaryLife, uint8_t ROfilterLife,
                                  uint8_t alkalineFilter, uint8_t mineralFilter, uint8_t copperFilter,
                                  uint16_t AppWc) {
    unsigned char liveWcAppPkt[PACKET_SIZE] = {0};

    if (index < TOTAL_DAYS_COUNT) {
        makePeriodicPacket(liveWcAppPkt, receivedDate, alarmValue, filterLife, sedimentaryLife,
                           ROfilterLife, alkalineFilter, mineralFilter, copperFilter,
                           flashDataInfo[index].currentValue + AppWc);
    } else {
        makePeriodicPacket(liveWcAppPkt, receivedDate, alarmValue, filterLife, sedimentaryLife,
                           ROfilterLife, alkalineFilter, mineralFilter, copperFilter,
                           AppWc);
    }

    sendDataToApp(liveWcAppPkt, POLLACK_FLAG); // live water consumption data sent to app
}


void periodicDataExtract(uint8_t *payload, int payloadLen) {
    uint8_t *payloadPtr = payload;
    uint16_t year = 0;
    uint8_t month = 0,day = 0;
    char *ptr;
    char buffer[10] = {0};
    uint32_t receivedTime = 0;
    uint16_t alarmValue = 0;
    uint8_t filterLife = 0;
    uint8_t sedimentaryLife = 0;
    uint8_t ROfilterLife = 0;
    uint8_t alkalineFilter = 0;
    uint8_t mineralFilter = 0;
    uint8_t copperFilter = 0;
    static uint8_t prevChildlockStatus = 0;
    receivedDate = 0;

    year = payload[8] << 8;
    year = year | payload[9];
    month = payload[10];
    day = payload[11];
    sprintf(buffer,"%d%02d%02d",year,month,day);
    ptr = buffer;
    for(int i = 0; i < strlen(buffer); i++){
        receivedDate = (receivedDate * 10) + (*ptr - 48);
        ptr = ptr + 1;
    }
    printf("Date:%d\n",receivedDate);
    memset(buffer,0x00,sizeof(buffer));
    
    sprintf(buffer,"%02d%02d%02d",payload[16],payload[17],payload[18]);
    ptr = buffer;
    for(int i = 0; i < strlen(buffer); i++){
        receivedTime = (receivedTime * 10) + (*ptr - 48);
        ptr = ptr + 1;
    }
    printf("Time:%d\n",receivedTime);
    waterConsumption = payload[23];
    waterConsumption = waterConsumption | (payload[24] << 8);
    printf("Water Consumption:%d\n",waterConsumption);

    alarmValue = payload[29];
    alarmValue = alarmValue | (payload[30] << 8);
    printf("Alarm value:%d\n",alarmValue);

    if(year > 2023){ //hardcoded for now
        memset(istDateTimeStored, 0, 7 * sizeof(int));
        istDateTimeStored[0] = payload[8];
        istDateTimeStored[1] = payload[9];
        istDateTimeStored[2] = payload[10];
        istDateTimeStored[3] = payload[11];
        istDateTimeStored[4] = payload[16];
        istDateTimeStored[5] = payload[17];
        istDateTimeStored[6] = payload[18];
    }
    else{
        if(memcmp(istDateTimeStored, (int[7]){0}, sizeof(istDateTimeStored)) != 0){
            sendDateTimeToReneses(SOURCE_REQUEST,istDateTimeStored);
        }
    }
    if(!isTempSent){
        sendTemperatureToReneses(SOURCE_REQUEST);
        sendWaterFlowCustomization(SOURCE_REQUEST);
        sendInletTDSToReneses(SOURCE_REQUEST,0x00);
        isTempSent = TRUE;
        setIsWaterCustSent(TRUE);
    }

    if((prevChildlockStatus != (alarmValue>>4)&1))
    {
        uint8_t childlockState[2] = {0};
        childlockState[0] = (((alarmValue >> 4) & 1) ? 1 : 2) + 0x30;
        setEnvItem(CHILDLOCKSTATE,childlockState);
        prevChildlockStatus = ((alarmValue>>4)&1);
    }

    filterLife = payload[35];
    sedimentaryLife = payload[36];
    ROfilterLife = payload[37];
    alkalineFilter = payload[38];
    mineralFilter = payload[39];
    copperFilter = payload[40];
    printf("Carbon life:%d\t",filterLife);
    printf("Sedimentary life:%d\t",sedimentaryLife);
    printf("ROfilterLife :%d\n",ROfilterLife);
    printf("alkalineFilter:%d\t",alkalineFilter);
    printf("mineralFilter:%d\t",mineralFilter);
    printf("copperFilter :%d\n",copperFilter);
    
    handleWaterConsumptionData(receivedTime);
    int index;
    for(index = 0; index < TOTAL_DAYS_COUNT; index++) {
        if(receivedDate == flashDataInfo[index].date){
            break;
        }
    }

    sendLivePeriodicDataToApp(index, receivedDate, alarmValue, filterLife, sedimentaryLife,
                             ROfilterLife, alkalineFilter, mineralFilter, copperFilter,
                             waterConsumption);
    
    if(checkInternet() == TRUE) {
        sendLivePeriodicDataToCloud(waterConsumption,index,alarmValue,filterLife); //live water consumption data to cloud
    }
}

void extractWaterCustomizationData(uint8_t *payload, int payloadLen) {
    char temp[5] = {0};
    int currentVal;
    getEnvItem(GLASS_CUST, temp);
    currentVal = hexToInt(temp);

    if (strlen(temp) == 0 || currentVal != payload[8]) {
        snprintf(temp, sizeof(temp), "%02X", payload[8]);
        setEnvItem(GLASS_CUST, temp);
    }

    memset(temp, 0x00, sizeof(temp));
    getEnvItem(BOTTLE_CUST, temp);
    currentVal = hexToInt(temp);

    if (strlen(temp) == 0 || currentVal != payload[9]) {
        snprintf(temp, sizeof(temp), "%02X", payload[9]);
        setEnvItem(BOTTLE_CUST, temp);
    }
}

void storeTdsOffset(uint8_t *payload) {
    int8_t offset = (int8_t)payload[17];

    char storedOffsetStr[5] = {0};
    getEnvItem(INLET_TDS_OFFSET, storedOffsetStr);
    int storedOffset = atoi(storedOffsetStr);

    if (offset != storedOffset) {
        char offsetStr[5] = {0};
        snprintf(offsetStr, sizeof(offsetStr), "%d", offset);

        if (setEnvItem(INLET_TDS_OFFSET, offsetStr)) {
            printf("Stored TDS offset: %d\n", offset);
        } else {
            printf("Failed to store TDS offset: %d\n", offset);
        }
    }

    uint16_t outletTds = ((uint16_t)payload[15] << 8) | payload[16];

    char storedOutletTdsStr[6] = {0};
    getEnvItem(OUTLET_TDS, storedOutletTdsStr);
    int storedOutletTds = atoi(storedOutletTdsStr);

    if (outletTds != storedOutletTds) {
        char outletTdsStr[6] = {0};
        snprintf(outletTdsStr, sizeof(outletTdsStr), "%d", outletTds);

        if (setEnvItem(OUTLET_TDS, outletTdsStr)) {
            printf("Stored Outlet TDS: %d\n", outletTds);
        } else {
            printf("Failed to store Outlet TDS: %d\n", outletTds);
        }
    }
}



void printStoredData() {
    for(int i = 0; i < TOTAL_DAYS_COUNT; i++){
        if(flashDataInfo[i].date > 0){
            printf("At index:%d, Date=%u, Water Consumption=%u\r\n", i,flashDataInfo[i].date, flashDataInfo[i].currentValue);
        }
    }
    printf("TOTAL WATER CONSUMED:%d\n",totalWater.currentValue);
}

void clear_flash_data_info(void) {
    for (int i = 0; i < TOTAL_DAYS_COUNT; i++) {
        flashDataInfo[i].isFree = 0;
        flashDataInfo[i].unusable = 0;
        flashDataInfo[i].pStartAddress = NULL;
        flashDataInfo[i].pEndAddress = NULL;
        flashDataInfo[i].pCurrentAddress = NULL;
        flashDataInfo[i].date = 0;
        flashDataInfo[i].currentValue = 0;
    }
}


void eraseWaterConsumptionRegion(){
    int write_sector = 0;
	int erased = 0;
	unsigned int adress = WC_FLASH_START_ADDRESS;
	printf("Erasing Water consumption storage area partition\n");
	printf("%s : Erase Start Address:%08x\n",__FUNCTION__ ,adress);
	while (erased < 0xF000) //60kb
	{
		unsigned int current_address = adress + (write_sector * 4096);

		device_mutex_lock(RT_DEV_LOCK_FLASH);
		flash_erase_sector(&flash_wc, current_address);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);
		write_sector++;
		erased += 4096;
	}
    clear_flash_data_info();
	printf("Water consumption storage area erased\n");
    eraseTotalWaterConsumptionRegion();
    flash_inc_init();
}

void eraseTotalWaterConsumptionRegion(){
    int write_sector = 0;
	int erased = 0;
	unsigned int adress = SECTOR1_BASE_ADDR;
	printf("%s : Erase Start Address:%08x\n",__FUNCTION__ ,adress);
	while (erased < 0x2000) //8kb
	{
		unsigned int current_address = adress + (write_sector * 4096);

		device_mutex_lock(RT_DEV_LOCK_FLASH);
		flash_erase_sector(&flash_wc, current_address);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);
		write_sector++;
		erased += 4096;
	}
    totalWc_init();
}


void makeCloudPeriodicPacket(unsigned char packet[],uint16_t cloudWc, uint16_t alarmValue, uint8_t filterLife) {
    unsigned char valueLen[5] = {0};
    unsigned char dateStr[20] = {0};
    unsigned char wcStr[10] = {0};
    unsigned char dateInHex[20] = {0};
    unsigned char wcInHex[10] = {0};
    unsigned char dataBuffer[PACKET_SIZE * 4] = {0};
    unsigned char alarmValueStr[5] = {0};
    unsigned char alarmValueLen[5] = {0};
    unsigned char alarmValueInHex[10] = {0};
    unsigned char filterLifeStr[5] = {0};
    unsigned char filterLifeLen[5] = {0};
    unsigned char filterLifeInHex[10] = {0};

    bool isTodayDataIncluded = FALSE;

    memset(packet, 0x00, sizeof(packet));
    strcpy(packet, PERIODIC_DATA_TAG);
    for(int i = 0; i < TOTAL_DAYS_COUNT; i++){
        if(flashDataInfo[i].date > 0){
            sprintf(dateStr, "%d", flashDataInfo[i].date);
            if(receivedDate == flashDataInfo[i].date){
                isTodayDataIncluded = TRUE;
                sprintf(wcStr, "%02d", cloudWc);
            }
            else sprintf(wcStr, "%02d", flashDataInfo[i].currentValue);

            string_to_hex(dateInHex, dateStr);
            string_to_hex(wcInHex, wcStr);

            strcat(dataBuffer, dateInHex);
            strcat(dataBuffer, "3A"); //":"
            strcat(dataBuffer, wcInHex);

            strcat(dataBuffer, "2C"); //","
        }
    }
    if(!isTodayDataIncluded){
        sprintf(dateStr, "%d", receivedDate);
        sprintf(wcStr, "%02d", cloudWc); 
        string_to_hex(dateInHex, dateStr);
        string_to_hex(wcInHex, wcStr);
        strcat(dataBuffer, dateInHex);
        strcat(dataBuffer, "3A");
        strcat(dataBuffer, wcInHex);
        strcat(dataBuffer, "2C");
    }
    //printf("Cloud data buffer :%s\n",dataBuffer);
    sprintf(alarmValueStr, "%02d", alarmValue);
    string_to_hex(alarmValueInHex, alarmValueStr);
    sprintf(alarmValueLen, "%04x", (int)strlen(alarmValueInHex) / 2);

    sprintf(filterLifeStr, "%02d", filterLife);
    string_to_hex(filterLifeInHex, filterLifeStr);
    sprintf(filterLifeLen, "%04x", (int)strlen(filterLifeInHex) / 2);

    sprintf(valueLen, "%04x", (int)strlen(dataBuffer) / 2);
    strcat(packet, valueLen);
    strcat(packet, dataBuffer);  
    strcat(packet, ALARM_TAG);
    strcat(packet, alarmValueLen);
    strcat(packet, alarmValueInHex);
    strcat(packet, FILTER_CLEAN);
    strcat(packet, filterLifeLen);
    strcat(packet, filterLifeInHex);
}


uint16_t read_sector_marker(uint32_t baseAddr) {
    uint16_t marker = 0xFFFF;
    flashReadRenesesData(baseAddr,sizeof(uint16_t),&marker);
    return marker;
}

void write_sector_marker(uint32_t baseAddr, uint16_t marker) {
    flashWriteRenesesData(baseAddr, marker, sizeof(uint16_t));
}

void storeTotalWaterConsumption(uint16_t newValue) {
    totalWater.currentValue += newValue;
    if ((totalWater.pCurrentAddress + 1) >= (totalWater.pEndAddress)) {
        uint32_t currentBase = (uint32_t)totalWater.pStartAddress - sizeof(uint16_t);
        uint32_t newBase = (currentBase == SECTOR1_BASE_ADDR) ? SECTOR2_BASE_ADDR : SECTOR1_BASE_ADDR;

        flashEraseSector(newBase);
        write_sector_marker(newBase, SECTOR_MARKER_USED);

        totalWater.pStartAddress = (uint16_t *)(newBase + sizeof(uint16_t));
        totalWater.pEndAddress = (uint16_t *)(newBase + FLASH_PARTITION_SIZE);
        totalWater.pCurrentAddress = totalWater.pStartAddress;

        printf("************ NEW SECTOR: %08x **************\n", newBase);
        printf("Writing current total to NEW sector at %p: %d\n", totalWater.pCurrentAddress, totalWater.currentValue);
        flashWriteRenesesData(totalWater.pCurrentAddress, totalWater.currentValue, sizeof(uint16_t));
        totalWater.pCurrentAddress++;

        flashEraseSector(currentBase);
        write_sector_marker(currentBase, SECTOR_MARKER_FREE);
        return;
    }

    printf("TOTAL WC written at %p: %d\n", totalWater.pCurrentAddress, totalWater.currentValue);
    flashWriteRenesesData(totalWater.pCurrentAddress, totalWater.currentValue, sizeof(uint16_t));
    totalWater.pCurrentAddress++;
}


void totalWc_init() {
    uint16_t marker1 = read_sector_marker(SECTOR1_BASE_ADDR);
    uint16_t marker2 = read_sector_marker(SECTOR2_BASE_ADDR);

    uint32_t baseAddr = 0;

    if (marker1 != SECTOR_MARKER_USED && marker2 != SECTOR_MARKER_USED) {
        flashEraseSector(SECTOR1_BASE_ADDR);
        write_sector_marker(SECTOR1_BASE_ADDR, SECTOR_MARKER_USED);
        baseAddr = SECTOR1_BASE_ADDR;
    } else if (marker1 == SECTOR_MARKER_USED) {
        baseAddr = SECTOR1_BASE_ADDR;
    } else {
        baseAddr = SECTOR2_BASE_ADDR;
    }
    printf("BASE ADDR %p\n", baseAddr);
    totalWater.pStartAddress = (uint16_t *)(baseAddr + sizeof(uint16_t));
    totalWater.pEndAddress = (uint16_t *)(baseAddr + FLASH_PARTITION_SIZE);
    totalWater.pCurrentAddress = totalWater.pStartAddress;
    totalWater.currentValue = 0;
    uint16_t lastValue = 0;
    for (uint16_t *p = totalWater.pStartAddress; p < totalWater.pEndAddress; p++) {
        uint16_t val;
        flashReadRenesesData(p,sizeof(uint16_t),&val);
        //printf("\nAddress:%p,LastData: %04x",p,val);
        if (val == 0xFFFF) {
            break;
        }
        lastValue = val;
        totalWater.pCurrentAddress = p + 1;
    }

    totalWater.currentValue = lastValue;
    printf("TOTAL WATER CONSUMED:%d\n",totalWater.currentValue);
}
