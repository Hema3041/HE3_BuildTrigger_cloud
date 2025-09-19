#include <sys.h>
#include <device_lock.h>
#include "ota_8710c.h"
#include "lwip/netdb.h"
#include "wdt_api.h"
#include "sys_api.h"
#include "osdep_service.h"
#include "hal_misc.h"
#include "hal_wdt.h"

#include "stddef.h"
#include "packets.h"
#include "hoags_config.h"
#include "remoteDiag.h"
#include "version.h"
// #include "LED.h"
extern QueueHandle_t envQ;
extern hwifi scannedSSIDs;
bool isOtaHappening = false;

bool getOtaStatus() {
    return isOtaHappening;
}

#define CHUNK_SIZE 512 // don't change this size

//1
#if 0
#include "ota_h3.h"
#include "flash_api.h"
#include "hci_platform.h"
#endif
//1
#include "packets.h"

#include "env.h"
#include "fan.h"
//#include "light.h"
//#include "mic.h"
#include "ac.h"
//#include "aircooler.h"
//#include "models.h"
//#include "mapConfig.h"
#include "circularbuffer.h"
//#include "chimney.h"
//2
#include "atcmd_wifi.h"
#include "wifi_conf.h"
#include "lwip_netconf.h"
#include "sys_api.h"
#include "simple_ble_service.h"
//3
#include "scheduler.h"
//#include "rtk_bt_le_gap.h"
#include "wifi_structures.h"
//shaik:export functions
extern int write_to_flash(unsigned int address, int len, unsigned char buff);
extern void read_from_flash(unsigned int address, int len, unsigned char buff);
extern unsigned int sys_update_ota_prepare_addr(void);
//extern int Erase_OTA_Region(unsigned int Address);

extern int update_ota_erase_upg_region(uint32_t img_len, uint32_t NewFWLen, uint32_t NewFWAddr);

#define BUFFER_SIZE 4096

//extern rtk_bt_le_auth_key_cfm_ind_t key_cfm_param = {0};
struct ble_passkey bleObj;

static flash_t flash;
static flash_t flash_OTA;
static struct meta_data* mp = NULL;
struct all_dev_info* all_info = NULL;

/*rehan : begin*/

extern struct fan* fanPtr;
extern struct led* ledPtr;
extern gpio_t gpio_led_red_demo;
extern gpio_t gpio_led_green_demo;
extern gpio_t gpio_led_blue_demo;
extern TaskHandle_t micRecordTaskHandle;
extern TaskHandle_t sensoryTaskHandle;
extern BOOL SendPollFlag;
extern uint8_t conn_ID, service_ID;


extern QueueHandle_t interruptQueueHandle;
#if LIVPURE_CHIMNEY
extern unsigned char irDisable;
extern void switchOffChimney();
extern void sendAckPackets();
extern unsigned short int smoke1Threshold;
extern unsigned short int smoke2Threshold;
extern unsigned char LEd;
extern unsigned char displayByte;
extern unsigned char inductionByte;
extern unsigned short int writeByte;
extern i2c_t i2cObj;
#endif

#if LIVPURE_PURIFIER
extern BOOL isRegistrationSent;
extern bool isBleConnected;
#endif


#if VERSADEVICES_SUPERFAN_IOT
char *fanSpeedAck = NULL;
char *fanModeAck = NULL;
char *fanTimerAck = NULL;
uint8_t PayloadValue;
extern int timerCount;
extern QueueHandle_t cmdQ;
extern QueueHandle_t toQ;
extern QueueHandle_t actionIdQ;
extern void* fpp;
extern int id;
extern void superfan_Breeze_mode();
extern void superfan_switchOn();
extern void superfan_switchOff();
extern void superfan_medium_speed();
extern void superfan_low_speed();
extern void superfan_high_speed();
extern void superfan_acmix();
extern void superfan_wellness();
extern void superfan_Eco_Mode();
extern void superfan_Reverse();
extern void superfan_Fine_tune_mode();
extern void superfan_Timer();
extern void rr_Timer();
extern unsigned char statusonoff[15];
extern unsigned char statusmode[15]; 
extern unsigned char statusfansp[15];
extern unsigned char lastUpdate;
#endif

extern char univMacid[13];
extern struct univMacid umObj;

uint16_t g_conn_handle;
extern rtw_wifi_setting_t *current_ssid;
extern BOOL SCAN_FROM_APP;
extern int hoagsWifiStatus;
extern unsigned char vfAck[24];
extern unsigned char ambAck[15];
extern unsigned char havellsAck[12];
extern unsigned char atombergAck[62];
extern unsigned char vdAck[15];
extern unsigned char hdcpAck[26];
extern unsigned char vgAck[8];
extern unsigned char omniAck[15];
extern rtw_scan_param_t scan_param = {0};

extern char (*result_ssid)[33];
extern p_wlan_autoreconnect_hdl_t p_wlan_autoreconnect_hdl;
extern void wifi_autoreconnect_hdl(rtw_security_t security_type,
                            char *ssid, int ssid_len,
                            char *password, int password_len,
                            int key_id);

#if HOAGS_OTA
static int flash;
extern void* decompress(void* ptrBuf,  int i_InSize, int i_OutSize);
#endif

#define DIAG_PRINT_STR_SIZE 50
#define DIAG_CIRC_BUFFER_SIZE 50

typedef enum {
    BLE_STATE_IDLE,
    BLE_STATE_OTA,
    BLE_STATE_MODEL_RECV_BEGIN,
    BLE_STATE_MODEL_FILE_DOWNLOADING,
    BLE_STATE_OTA_FILE_DOWNLOADING,
    BLE_STATE_LFS_FILE_DOWNLOADING,
    BLE_STATE_OTA_BOOT_FILE_DOWNLOADING  //shaik: for bootloader 2//
} ble_state_e;

typedef struct {
    BOOL isInit;
    ble_state_e state;
    struct file_info_t *pHead;
    struct file_info_t *pCurFile;
    char rebootWaiting;
    QueueHandle_t taskDeadInformQueue;
    circular_buffer diagBuffer;
    BOOL diagStart;
    uint16_t diagBleHandle;
    volatile BOOL micMute;
} ble_state_machine_t;

static ble_state_machine_t ble_state_machine;

void ble_state_machine_init () {
    ble_state_machine.isInit = TRUE;
    ble_state_machine.state = BLE_STATE_IDLE;
    ble_state_machine.pHead = ble_state_machine.pCurFile = NULL;
    ble_state_machine.rebootWaiting = 0;
    ble_state_machine.taskDeadInformQueue = xQueueCreate( 2, sizeof(TaskHandle_t *));
    cb_init(&ble_state_machine.diagBuffer, DIAG_CIRC_BUFFER_SIZE, DIAG_PRINT_STR_SIZE);
    ble_state_machine.diagBleHandle = 0;
    ble_state_machine.diagStart = FALSE;
}

BOOL isDuplicateSSID(struct wifiConnect* wObj)
{
    HOAGS_INFO("new=%s\n", wObj->ssid);
    if(current_ssid)
    {
        HOAGS_INFO("current=%s\n", current_ssid->ssid);
        if(!memcmp(current_ssid->ssid, wObj->ssid, strlen(wObj->ssid)))
        {
            HOAGS_INFO("current=%s new=%s\n", current_ssid->ssid, wObj->ssid);
            return TRUE;
        }
    }
    HOAGS_INFO("\n");
    return FALSE;
}

void wifiAction()
{
    HOAGS_INFO("\n");
    HOAGS_MAN_RAW("wifi_config_func\n");
    char gap = 0;
    struct wifiConnect wifiObj;
    char strrr[32];
    for (int level = 1, levelIndex = 0; level <= mp->cp->total_level; ++level)
    {
        HOAGS_INFO("\n");
        if (level == 1)
        {
            HOAGS_INFO("\n");
            switch (mp->cp->level[levelIndex])
            {
                HOAGS_INFO("\n");
                case WIFI_CMD_MODE_SCANLIST:
                    //a=0;
                    //memset(result_ssid, 0, sizeof(result_ssid));
                    memset(&scannedSSIDs, 0, sizeof(scannedSSIDs));
                    HOAGS_MAN_RAW("scanning.......\n");
                    SCAN_FROM_APP = TRUE;
                    #if LIVPURE_PURIFIER
                        breathe_LED();
                    #endif
                    printf("At %s,%d\n",__func__,__LINE__);
                    fATWS(NULL);       
                    printf("At %s,%d\n",__func__,__LINE__);
                    HOAGS_INFO("\n");
                    vTaskDelay(pdMS_TO_TICKS(5000));
                    HOAGS_INFO("Taskname=%s\n", pcTaskGetName(NULL));
                    simple_ble_srv_cccd_notify(g_conn_handle, "", SSID_LIST);
                    break;
                
                case WIFI_CMD_MODE_CONNECT: 
                    HOAGS_INFO("\n");
                    HOAGS_INFO("new=%s isCurrent=%s payload=%s\n", wifiObj.ssid, current_ssid, mp->cp->payload);
                    HOAGS_INFO("new=%d isCurrent=%d payload=%d\n", (wifiObj.ssid == NULL), (current_ssid == NULL), (mp->cp->payload == NULL));
                    memcpy(&wifiObj, mp->cp->payload, mp->cp->len); 
                    HOAGS_INFO("new=%d isCurrent=%d payload=%d\n", (wifiObj.ssid == NULL), (current_ssid == NULL), (mp->cp->payload == NULL));
                    if(isDuplicateSSID(&wifiObj))
                    {
                        HOAGS_INFO("This is a duplicate connection\n");
                        //memset(strrr, 0, sizeof(strrr));
                        //sprintf(strrr, "duplicate:%d", CONNECTION_DUPLICATE);
                        simple_ble_srv_cccd_notify(g_conn_handle, "", CONNECTION_STATUS);
                        break;
                    }
                    else
                    {
                        HOAGS_INFO("This is not a duplicate connection!\n");
                    }

                    
                    fATW0(wifiObj.ssid);
                    vTaskDelay(pdMS_TO_TICKS(500));
                    #if LIVPURE_PURIFIER
                        breathe_LED(); 
                    #endif           
                    fATW1(wifiObj.password);
                    breathe_LED();           //password   
                    vTaskDelay(pdMS_TO_TICKS(500));   
                    fATWC(NULL);            //connected
                    printf("hoagsWifiStatus:%d\n",hoagsWifiStatus);
                    if (hoagsWifiStatus != RTW_SUCCESS)
                    {
                        printf("Inside auto\n");
                        p_wlan_autoreconnect_hdl = NULL;
                        printf("after auto\n"); 
                    }
                    else
                    {
                        p_wlan_autoreconnect_hdl = wifi_autoreconnect_hdl;
                        printf("auto enable\n");
                    }

                    #if 1
                    if (hoagsWifiStatus != RTW_SUCCESS) 
                    {
                        if (hoagsWifiStatus == RTW_INVALID_KEY) 
                        {
                            HOAGS_ERR("\n\rERROR:Invalid Key\n");

                            memset(strrr, 0, sizeof(strrr));
                            sprintf(strrr, "failedconnection:%d", CONNECTION_FAILED);
                            simple_ble_srv_cccd_notify(g_conn_handle, strrr, CONNECTION_STATUS);
                        }
                        
                        HOAGS_ERR("\n\rERROR: Device not connected\n");
                        memset(strrr, 0, sizeof(strrr));
                        sprintf(strrr, "failedconnection:%d", CONNECTION_FAILED);

                        simple_ble_srv_cccd_notify(g_conn_handle, strrr, CONNECTION_STATUS);
                    
                        
                    }
                    #endif
                    if (hoagsWifiStatus == RTW_SUCCESS)
                    {
                        memset(strrr, 0, sizeof(strrr));
                        sprintf(strrr, "sucess:%d", CONNECTION_SUCESS);
                        //wifi_ble_conn();

                        simple_ble_srv_cccd_notify(g_conn_handle, strrr, CONNECTION_STATUS);
                    }

                    printf("\n\r");
                    

                    break;

                case WIFI_CMD_MODE_DISCONNECT:     
                    //wifi_ble_disconn();       
                    break;
            }
        }
    }
}

void restoringEnvs() {
    char serialNoStored[20] = {0};

    getEnvItem(ENV_SERIALNO, serialNoStored);

    Erased_Env_part();
    initEnv();

    if (strlen(serialNoStored) != 0) {
        if (setEnvItem(ENV_SERIALNO, serialNoStored)) printf("serialNo restored.\n");
    }
}

void factoryReset(void){
    if (wifi_clear_all_ssid() == 0)
        printf("\nAll SSIDs cleared successfully.\n");
    restoringEnvs();
    sys_reset();
}

void sendAckToApp(int source)
{
    if(!SendPollFlag)
    {
        return;
    }
    #if VIRTUALFOREST_AC
    simple_ble_srv_cccd_notify(g_conn_handle, vfAck, POLLACK_FLAG);
    #elif VERSADEVICES_SUPERFAN_IOT
   if(source == 1)
    {
        fanSpeedAck = getAckPacketFromCache(0x04);
        fanModeAck = getAckPacketFromCache(0x21);
        fanTimerAck = getAckPacketFromCache(0x22);
 
        simple_ble_srv_cccd_notify(g_conn_handle, statusonoff, POLLACK_FLAG);
        if (statusonoff[11] != 0x00)
        {
            if (fanSpeedAck[0] != 0) {
                simple_ble_srv_cccd_notify(g_conn_handle, fanSpeedAck, POLLACK_FLAG);
            }
            else if (fanModeAck != 0) {
                simple_ble_srv_cccd_notify(g_conn_handle, fanModeAck, POLLACK_FLAG);
            }
            if (fanTimerAck != 0) { 
                simple_ble_srv_cccd_notify(g_conn_handle, fanTimerAck, POLLACK_FLAG);
            }
        }
        else
        {
            HOAGS_ERR("Power is in off state\n");
        }
    }
    else
    {
        simple_ble_srv_cccd_notify(g_conn_handle, vdAck, POLLACK_FLAG);
    }
    #elif VGUARD_FAN
    simple_ble_srv_cccd_notify(g_conn_handle, vdAck, POLLACK_FLAG);
    #elif RR_KABLES
    simple_ble_srv_cccd_notify(g_conn_handle, hdcpAck, POLLACK_FLAG);
    #elif AMBER_AC 
    simple_ble_srv_cccd_notify(g_conn_handle, ambAck, POLLACK_FLAG);
    #elif HAVELLS_AC
    simple_ble_srv_cccd_notify(g_conn_handle, havellsAck, POLLACK_FLAG);
    #elif ATOMBERG_FAN
    simple_ble_srv_cccd_notify(g_conn_handle, atombergAck, POLLACK_FLAG);
    #elif LIVPURE_CHIMNEY
    sendAckPackets();
    #elif VGUARD_NEW_FAN
    simple_ble_srv_cccd_notify(g_conn_handle, vgAck, POLLACK_FLAG);
    #elif OMNI_AC
    if(source == 1)
    {
        simple_ble_srv_cccd_notify(g_conn_handle, omniAck, POLLACK_FLAG);
        vTaskDelay(3000);
        SendHeartBeat_Amb();
    }
    else
    {
        simple_ble_srv_cccd_notify(g_conn_handle, omniAck, POLLACK_FLAG);
    }
    #endif
}

void ble_diag(const char * format, ...) {
    if (ble_state_machine.isInit != TRUE){
        HOAGS_INFO("BLE State machine not initialized\n");
        return;
    } 

    va_list args;
    va_start(args, format);
    if (ble_state_machine.diagStart == FALSE) {
        char * buffer = cb_get_buffer_rotate(&ble_state_machine.diagBuffer);
        vsnprintf(buffer, DIAG_PRINT_STR_SIZE, format, args);
        cb_push_back(&ble_state_machine.diagBuffer, buffer);
    } else {
        char buffer[DIAG_PRINT_STR_SIZE] = {0};
        vsnprintf(buffer, DIAG_PRINT_STR_SIZE, format, args);
        simple_ble_srv_cccd_notify(ble_state_machine.diagBleHandle, buffer, DIAG_FLAG);
    }
    
    va_end(args);
}

void app_task_dead(TaskHandle_t taskHandle) {
    HOAGS_ERR("app dead task handle %p\n", &taskHandle);
    xQueueSend(ble_state_machine.taskDeadInformQueue, &taskHandle, portMAX_DELAY);
}


struct file_info_t * add_new_file_struct (uint16_t action, const char *newFileName, int tot_size, int chunk_len, uint32_t params, uint32_t cksum) {
    HOAGS_INFO("File create %d %s %d %d\n", action, newFileName, tot_size, chunk_len);
    struct file_info_t *new_file = hoagsMalloc(sizeof(struct file_info_t));
    new_file->pNext = NULL;
    new_file->action = action;
    new_file->filename = newFileName;
    new_file->params = params;
    new_file->fileBuffer = (uint8_t*)hoagsMalloc(tot_size);
	new_file->fbPos = new_file->fileBuffer;
    new_file->total_size = tot_size;
    new_file->prev_seq_no = 0;
    new_file->pDecompressBuf = NULL;
    new_file->end_seq = ceil(((double)(tot_size))/((double)(chunk_len)));
    new_file->checksum = cksum;
    new_file->append = 0;
    if (ble_state_machine.pHead == NULL) {
        ble_state_machine.pHead = new_file;
    } else {
        struct file_info_t *file = ble_state_machine.pHead;
        while (file != NULL) {
            //HOAGS_ERR("File %s in cache\n", file->filename);
            if (file->pNext == NULL) {
                file->pNext = new_file;
                break;
            }
            file = file->pNext;
        }
    }
    ble_state_machine.pCurFile = new_file;
    return new_file;
}

error_code_e free_all_files () {
    struct file_info_t *pFile = ble_state_machine.pHead;
    while (pFile != NULL) {
        struct file_info_t * pFileToFree = pFile;
        pFile = pFile->pNext;
        free(pFileToFree->fileBuffer);
        free(pFileToFree);
    }
    ble_state_machine.pHead = ble_state_machine.pCurFile = NULL;
}

error_code_e free_all_resources () {
    HOAGS_ERR("Freeing up file transfer resources\n");
    ble_state_machine.state = BLE_STATE_IDLE;
    return free_all_files();
}

uint32_t swapEndianness32(uint32_t value) {
    return ((value >> 24) & 0xFF) |       // Move byte 0 to byte 3
           ((value >> 8) & 0xFF00) |     // Move byte 1 to byte 2
           ((value << 8) & 0xFF0000) |   // Move byte 2 to byte 1
           ((value << 24) & 0xFF000000); // Move byte 3 to byte 0
}

uint16_t swapEndianness16(uint16_t value) {
    return (value >> 8) | (value << 8);
}

void swapStructEndianness(struct hdcp * hdcptr, size_t len)
{
    #if !BAJAJFAN
    hdcptr->action      = swapEndianness16(hdcptr->action);
    #endif
    hdcptr->len         = swapEndianness16(hdcptr->len);
    hdcptr->seq_num     = swapEndianness16(hdcptr->seq_num);
    hdcptr->total_size  = swapEndianness32(hdcptr->total_size);
    hdcptr->checksum    = swapEndianness32(hdcptr->checksum);
    hdcptr->params      = swapEndianness32(hdcptr->params);

}

void rebootIfRequired(const int herr)
{
    if(herr!=ALL_FINE)
    {
        sys_reset();
    }

    //Reboot if all ota files are transferred
    if((mp->cp->action == OTA_BIN) && (mp->end_seq == mp->cp->seq_num))
    {
        sys_reset();
    }    
}

void unpack(uint8_t* buffer)
{
	memset(mp->cp, 0, sizeof(struct hdcp));
    memcpy(mp->cp, buffer, sizeof(struct hdcp));
   
	mp->cp->action = __ntohs(mp->cp->action);
	mp->cp->len = __ntohs(mp->cp->len);
	mp->cp->seq_num = __ntohs(mp->cp->seq_num);
	mp->cp->checksum = __ntohl(mp->cp->checksum);
	mp->cp->total_size = __ntohl(mp->cp->total_size);
    mp->cp->params = __ntohl(mp->cp->params);
}

void pack()
{
	printf("\n");
}

void print()
{
    if(mp->filename)
        printf("filename:%s", mp->filename);

	printf("header:%d\n", mp->cp->header);
	printf("action:%d\n", mp->cp->action);
	printf("len:%d\n", mp->cp->len);
	printf("seq_num:%d\n", mp->cp->seq_num); 
	printf("checksum:%d\n",  mp->cp->checksum);
    printf("total_level:%d\n",  mp->cp->total_level);
     for(int i = 0; i < 5; ++i)
         printf("level[%d]:%d ", i, mp->cp->level[i]);
	printf("\ntotal_size:%d\n", mp->cp->total_size);
    printf("\nparams:%d\n", mp->cp->params);
	printf("payload:%02x %02x %02x %02x %02x...%02x %02x %02x %02x %02x\n", 
    mp->cp->payload[0], mp->cp->payload[1], mp->cp->payload[2], mp->cp->payload[3], mp->cp->payload[4],
    mp->cp->payload[mp->cp->len-1], mp->cp->payload[mp->cp->len-2], mp->cp->payload[mp->cp->len-3], mp->cp->payload[mp->cp->len-4], mp->cp->payload[mp->cp->len-5]);
	
}

void ble_password()
{   
    #if 1
    HOAGS_MAN_RAW("BLE password func\n");
    char strrr[20];

    bleObj.app_input_passkey[0] = mp->cp->payload[0];
    bleObj.app_input_passkey[1] = mp->cp->payload[1];
    bleObj.app_input_passkey[2] = mp->cp->payload[2];
    bleObj.app_input_passkey[3] = mp->cp->payload[3];

    for (int level = 1, levelIndex = 0; level <= mp->cp->total_level; ++level)
    {
        if (level == 1)
        {
            HOAGS_INFO("mp->cp->level[levelIndex] ->%d\n",mp->cp->level[levelIndex]);
            switch (mp->cp->level[levelIndex])
            {
                case FIRST_CONNECTION:
                
                if (bleObj.app_input_passkey != NULL)
                {

                    if (memcmp(bleObj.app_input_passkey, "0000", 4) == 0)  //1N
                    {
                        HOAGS_ERR("Initial_input_passkey:%s\n", bleObj.app_input_passkey);
                        //Need to send sucess msg to app - INITIAL_BLE_SUCESS
                        memset(strrr, 0, sizeof(strrr));
                        sprintf(strrr, "initialpasskeysuccess:%d", INITIAL_BLE_SUCCESS);
                        simple_ble_srv_cccd_notify(g_conn_handle, strrr, BLE_PASSKEY_STATUS);
                    } 
                    else 
                    {
                        HOAGS_ERR("First connection, incorrect initial passkey\n");
                        // Need to send fail msg to app - INITIAL_BLE_FAILED
                        memset(strrr, 0, sizeof(strrr));
                        sprintf(strrr, "initialpasskeyfail:%d", INITIAL_BLE_FAILED);
                        simple_ble_srv_cccd_notify(g_conn_handle, strrr, BLE_PASSKEY_STATUS);
                    }                    
                }
                else
                {
                    HOAGS_ERR("[APP] Passkey failed\r\n");
                    HOAGS_ERR("empty_passkey_app:%s\n", bleObj.app_input_passkey);
                    sprintf(strrr, "invalid:%d", PASSWORD_INVALID);
                    simple_ble_srv_cccd_notify(g_conn_handle, strrr, BLE_PASSKEY_STATUS);
                }

                break; 

                case SET_NEW_PASSWORD:

                    if (bleObj.app_input_passkey != NULL)
                    {
                        memcpy(bleObj.stored_passkey, bleObj.app_input_passkey, 4);          //2N               //bleObj.app_input_passkey need to come from app
                        bleObj.stored_passkey[4] = '\0';
                        HOAGS_ERR("app_passkey:%s\n", bleObj.app_input_passkey);

                        if (memcmp(bleObj.stored_passkey, bleObj.app_input_passkey, 4) == 0) //3N //2A
                        {
                            HOAGS_ERR("[APP] Passkey is correct\r\n");
                            HOAGS_INFO("key_stored_passkey:%s\n", bleObj.stored_passkey);

                            setEnvItem(ENV_BLEPASSWORD, bleObj.stored_passkey);
                            // need to send sucess message to app
                            memset(strrr, 0, sizeof(strrr));
                            sprintf(strrr, "passwordsuccess:%d\n", PASSWORD_SUCCESS);
                            simple_ble_srv_cccd_notify(g_conn_handle, strrr, BLE_PASSKEY_STATUS);
                            #if LIVPURE_PURIFIER
                            isBleConnected = true;
                            bleWifi_ledOn();
                            #endif
                        }
                        else
                        {
                        HOAGS_ERR("[APP] Passkey is incorrect\r\n");
                        // need to send error message to app
                        memset(strrr, 0, sizeof(strrr));
                        sprintf(strrr, "passwordfailed:%d", PASSWORD_FAILED);
                        simple_ble_srv_cccd_notify(g_conn_handle, strrr, BLE_PASSKEY_STATUS);

                        }
                    }
                    else
                    {
                        HOAGS_ERR("[APP] Passkey failed\r\n");
                        HOAGS_ERR("empty_passkey_app:%s\n", bleObj.app_input_passkey);
                        sprintf(strrr, "invalid:%d", PASSWORD_INVALID);
                        simple_ble_srv_cccd_notify(g_conn_handle, strrr, BLE_PASSKEY_STATUS);
                    }
                    
                break;

                case NOT_FIRST_CONNECTION:

                    if (bleObj.app_input_passkey != NULL)
                    {
                        if(getEnvItem(ENV_BLEPASSWORD, bleObj.stored_passkey) == TRUE)
                        {
                            HOAGS_INFO("bleObj.stored_passkey ->%s\n" ,bleObj.stored_passkey);
                            HOAGS_INFO("bleObj.app_input_passkey ->%s\n" ,bleObj.app_input_passkey);
                                
                            if (memcmp(bleObj.stored_passkey, bleObj.app_input_passkey, 4) == 0)  //1A // cust need to input pass key and check with stored passkey/ here need to compare the input from customer with stored passkey
                            {
                                HOAGS_ERR("[APP] Passkeys matches\r\n");
                                // Passkey matches need to send to app
                                memset(strrr, 0, sizeof(strrr));
                                sprintf(strrr, "passkeymatches:%d", PASSKEY_MATCHES);
                                simple_ble_srv_cccd_notify(g_conn_handle, strrr, BLE_PASSKEY_STATUS);

                                memset(strrr, 0, sizeof(strrr));
                                sprintf(strrr, "passwordsuccess:%d", PASSWORD_SUCCESS);
                                simple_ble_srv_cccd_notify(g_conn_handle, strrr, BLE_PASSKEY_STATUS);
                                #if LIVPURE_PURIFIER
                                isBleConnected = true;
                                bleWifi_ledOn();
                                #endif

                                SendPollFlag = TRUE;
                            } 
                            else 
                            {
                                HOAGS_ERR("[APP] Passkeys do not match.\r\n");
                                // Passkey doesn't matches re enter the correct password send to app
                                memset(strrr, 0, sizeof(strrr));
                                sprintf(strrr, "passkeynotmatches:%d", PASSKEY_NOT_MATCHES);
                                simple_ble_srv_cccd_notify(g_conn_handle, strrr, BLE_PASSKEY_STATUS);
                            }
                        }
                        else {
                            HOAGS_ERR("ENV_BLEPASSWORD getting Failed \r\n");
                        }
                    }
                    else
                    {
                        HOAGS_ERR("[APP] Passkey failed\r\n");
                        HOAGS_ERR("empty_passkey_app:%s\n", bleObj.app_input_passkey);
                        sprintf(strrr, "invalid:%d", PASSWORD_INVALID);
                        simple_ble_srv_cccd_notify(g_conn_handle, strrr, BLE_PASSKEY_STATUS);
                    }

                break;
                
            }

        }    
    }
    #endif
}



void resetMetaData()
{
    printf("start\n");
    if(mp->cp)
    {
        printf("Freeing mp.cp.action=%d\n", mp->cp->action);
	    free(mp->cp);
	    mp->cp = NULL;
    }

    if(mp->fileBuffer)
    {
        free(mp->fileBuffer);
        mp->fileBuffer = NULL;
        printf("Freeing mp.fileBuffer\n");
    }

    if(mp->filename)
    {
        printf("Freeing mp.filename=%s\n", mp->filename);
        free(mp->filename);
        mp->filename = NULL;
    }
    
    if(mp->fbPos)
    {
        free(mp->fbPos);
        mp->fbPos = NULL;
        printf("Freeing mp.fbPos\n");
    }

    mp->prev_seq_no = 0;
	mp->end_seq = 0;
	mp->append = 0;
	mp->resetFlag = 1;

	printf("end\n");
}

void initMetaData()
{
    if(mp)
        return;
    
   // printf("initMetaData()__start\n");    
    mp = (struct meta_data*)hoagsMalloc(sizeof(struct meta_data));

    mp->cp = NULL;
    mp->fileBuffer = NULL;
    mp->prev_seq_no = 0;
    mp->end_seq = 0;
    mp->filename = NULL;
    mp->append = 0;
    mp->resetFlag = 1;
    mp->fbPos = NULL;
   // printf("initMetaData()__end\n");    
}

void printMetaData()
{
    if(!all_info)
        return;

    HOAGS_DBG("dev1.dev:%d\n", all_info->dev1.dev);
    HOAGS_DBG("dev1.intensity:%d\n", all_info->dev1.intensity);
    HOAGS_DBG("dev1.color:%d\n", all_info->dev1.color);

    HOAGS_DBG("dev2.dev:%d\n", all_info->dev2.dev);
    HOAGS_DBG("dev2.intensity:%d\n", all_info->dev2.intensity);
    HOAGS_DBG("dev2.color:%d\n", all_info->dev2.color);

}

void init()
{
    if(mp->cp)
        return;
   // printf("init()___start\n");
	mp->cp = hoagsMalloc(sizeof(struct hdcp));
	//printf("init()___end cp=%p\n", mp->cp);
}
#if 0
int fillFileBuffer()
{
    if ((mp->cp->seq_num - ble_state_machine.pCurFile->prev_seq_no)!=1)
    { //when packets are missed
        blink_LED();
        HOAGS_ERR("Packet missed, seq_num=%d prev_seq_num=%d\n",
                    mp->cp->seq_num, ble_state_machine.pCurFile->prev_seq_no);

        return PACKET_MISSED;
    }

    ble_state_machine.pCurFile->prev_seq_no = mp->cp->seq_num;
    //HOAGS_ERR("Fill file buffer %d\n", mp->cp->len);
    //HOAGS_INFO("\n");
    #if 0
    printf("**************orig******************\n");
    uint8_t* a = mp->cp->payload;
    for(int i = 0; i < mp->cp->len; ++i)
    {
        if (0 == i%16)
            printf("\n\r");
        printf("%02x ", *(a+i));
    }
    printf("********************************\n");
    #endif
	memcpy(ble_state_machine.pCurFile->fbPos, mp->cp->payload, mp->cp->len);
	ble_state_machine.pCurFile->fbPos += mp->cp->len;
    return ALL_FINE;
}
#endif
void deserialize(uint8_t* val)
{
    //HOAGS_INFO("start\n");

    init();
    unpack(val);
   // print();
    //HOAGS_INFO("end\n");
}
#if 0
void printSha1sum(unsigned char* s, size_t len)
{
    for(int i = 0; i<len; ++i)
        HOAGS_MAN_RAW("%02x", s[i]);
    HOAGS_MAN_RAW("\n");
}
#endif


/*rehan : end*/

//extern void ota_update(struct file_info_t* file);



void printDevState(struct hdcpr* hdcprObj)
{
	HOAGS_MAN_RAW("hdcpr->majorVersion=%d\n", hdcprObj->majorVersion);
	HOAGS_MAN_RAW("hdcpr->minorVersion=%d\n", hdcprObj->minorVersion);
	HOAGS_MAN_RAW("hdcpr->custName=%s\n", hdcprObj->custName);
	HOAGS_MAN_RAW("hdcpr->prodModel=%s\n", hdcprObj->prodModel);
	HOAGS_MAN_RAW("hdcpr->prodType=%s\n", hdcprObj->prodType);
	HOAGS_MAN_RAW("hdcpr->friendlyName=%s\n", hdcprObj->friendlyName);
	HOAGS_MAN_RAW("hdcpr->micStatus=%d\n", hdcprObj->micStatus);
	HOAGS_MAN_RAW("hdcpr->powerControl=%d\n", hdcprObj->powerControl);
	HOAGS_MAN_RAW("hdcpr->modeControl=%d\n", hdcprObj->modeControl);
	HOAGS_MAN_RAW("hdcpr->speedControl=%d\n", hdcprObj->speedControl);
	HOAGS_MAN_RAW("hdcpr->tempControl=%d\n", hdcprObj->tempControl);
    HOAGS_MAN_RAW("hdcpr->lfsSize=%d\n", hdcprObj->lfsSize);
    HOAGS_MAN_RAW("hdcpr->ssid=%s\n", hdcprObj->ssid);
    HOAGS_MAN_RAW("hdcpr->capability=%d\n", hdcprObj->capability);
    HOAGS_MAN_RAW("hdcpr->mac_id=%s\n", hdcprObj->mac_id);
    HOAGS_MAN_RAW("hdcpr->blepasskey=%s\n", hdcprObj->stored_passkey);  
    HOAGS_MAN_RAW("hdcpr->ledControl=%d\n", hdcprObj->ledControl);
    HOAGS_MAN_RAW("hdcpr->buzControl=%d\n", hdcprObj->buzControl);
    HOAGS_MAN_RAW("hdcpr->revControl=%d\n", hdcprObj->revControl);
    HOAGS_MAN_RAW("hdcpr->serialNo=%s\n", hdcprObj->serialNo);
}

/*rehan : hdcpr need to check simple_ble_service.c*/

void getDevState(struct hdcpr* hdcprObj)
{
    breathe_LED();
    vTaskDelay(1000);
    HOAGS_INFO("Current Tead : %s \n",pcTaskGetName(NULL));
    memset(hdcprObj, 0x00, sizeof(struct hdcpr));
    //struct ble_passkey bleObject;
    
    hdcprObj->majorVersion = VERSION_MAJOR;
    hdcprObj->minorVersion = VERSION_MINOR;
    memset(hdcprObj->custName, 0x00, sizeof(hdcprObj->custName));
    getEnvItem(ENV_CUSTNAME, hdcprObj->custName);

    memset(hdcprObj->prodModel, 0x00, sizeof(hdcprObj->prodModel));
    getEnvItem(ENV_PRODMODEL, hdcprObj->prodModel);

    memset(hdcprObj->prodType, 0x00, sizeof(hdcprObj->prodType));
    getEnvItem(ENV_PRODTYPE, hdcprObj->prodType);
    
    // memset(hdcprObj->friendlyName, 0x00, sizeof(hdcprObj->friendlyName));
    // getEnvItem(ENV_FRIENDLYNAME, hdcprObj->friendlyName);
    
    memset(hdcprObj->micStatus, 0x00, sizeof(hdcprObj->micStatus));
    hdcprObj->micStatus = 0;//Suvarna: Invalid here as no VFS

    char powerCtrl[2];
    memset(powerCtrl,0x00,sizeof(powerCtrl));
    memset(hdcprObj->powerControl, 0x00, sizeof(hdcprObj->powerControl));
    getEnvItem(ENV_POWERCONTROL, powerCtrl);
    hdcprObj->powerControl = atoi(powerCtrl);
    
    char modeCtrl[8];
    memset(modeCtrl,0x00,sizeof(modeCtrl));
    memset(hdcprObj->modeControl, 0x00, sizeof(hdcprObj->modeControl));
    getEnvItem(ENV_MODECONTROL, modeCtrl);
    hdcprObj->modeControl = atoi(modeCtrl);
    
    char speedCtrl[8];
    memset(speedCtrl,0x00,sizeof(speedCtrl));
    memset(hdcprObj->speedControl, 0x00, sizeof(hdcprObj->speedControl));
    getEnvItem(ENV_SPEEDCONTROL, speedCtrl);
    hdcprObj->speedControl = atoi(speedCtrl);
    
    // char tempCtrl[8];
    // memset(tempCtrl,0x00,sizeof(tempCtrl));
    // memset(hdcprObj->tempControl, 0x00, sizeof(hdcprObj->tempControl));
    // getEnvItem(ENV_TEMPCONTROL, tempCtrl);
    // hdcprObj->tempControl = atoi(tempCtrl);

    char temp[5] = {0};  
    uint8_t warmTemperature, hotTemperature;

    getEnvItem(WARM_TEMPERATURE, temp);
    warmTemperature = hexToInt(temp);

    memset(temp,0x00,sizeof(temp));

    getEnvItem(HOT_TEMPERATURE, temp);
    hotTemperature = hexToInt(temp);

    hdcprObj->tempControl = (warmTemperature << 8) | hotTemperature;

    

    memset(hdcprObj->friendlyName, 0x00, sizeof(hdcprObj->friendlyName));
    getEnvItem(ENV_FRIENDLYNAME, hdcprObj->friendlyName);   

    memset(hdcprObj->airCoolerModeValue, 0x00, sizeof(hdcprObj->airCoolerModeValue));
    hdcprObj->airCoolerModeValue = 0; //Invalid here as env Not contain 

    memset(hdcprObj->lfsSize, 0x00, sizeof(hdcprObj->lfsSize));
    hdcprObj->lfsSize = 0;//Suvarna: Invalid here as no VFS
    
    if(current_ssid == 0)
    {
        memset(hdcprObj->ssid, 0, sizeof(hdcprObj->ssid));
        memcpy(hdcprObj->ssid, "<>", sizeof("<>"));
        //HOAGS_MAN_RAW("NULL value\n");                                  
    }
    else
    {
        memcpy(hdcprObj->ssid, current_ssid->ssid, sizeof(hdcprObj->ssid));
    }
    
    memset(hdcprObj->capability, 0x00, sizeof(hdcprObj->capability));
    hdcprObj->capability = FW_CAP_LEVEL;

    memset(hdcprObj->mac_id, 0,sizeof(hdcprObj->mac_id));
    memcpy(hdcprObj->mac_id,umObj.macid,sizeof(hdcprObj->mac_id));

    memset(bleObj.stored_passkey, '\0', 4);
    memset(hdcprObj->stored_passkey, '\0', 4);
    getEnvItem(ENV_BLEPASSWORD, hdcprObj->stored_passkey);
    //HOAGS_INFO("After get env hdcprObj->stored_passkey : %s \n",hdcprObj->stored_passkey);
    //HOAGS_INFO("After get env bleObj.stored_passkey : %s \n",bleObj.stored_passkey);
    memcpy(bleObj.stored_passkey, hdcprObj->stored_passkey, 4);
    
    //HOAGS_INFO("After get env hdcprObj->stored_passkey : %s \n",hdcprObj->stored_passkey);
    //HOAGS_INFO("After get env bleObj.stored_passkey : %s \n",bleObj.stored_passkey);
    
    
    memset(hdcprObj->ledControl, 0x00, sizeof(hdcprObj->ledControl));
    hdcprObj->ledControl = 0; //Invalid here as env Not contain

    memset(hdcprObj->buzControl, 0x00, sizeof(hdcprObj->buzControl));
    hdcprObj->buzControl = 0; //Invalid here as env Not contain

    memset(hdcprObj->revControl, 0x00, sizeof(hdcprObj->revControl));
    hdcprObj->revControl = 0; //Invalid here as env Not contain
    
    memset(hdcprObj->serialNo, 0x00, sizeof(hdcprObj->serialNo));
    getEnvItem(ENV_SERIALNO, hdcprObj->serialNo);

    printf("App_Read_HDCPR_SuccessFully....\n");
}

struct all_dev_info* initDevInfo()
{
    HOAGS_INFO("\n");
    if(all_info)
        return all_info;
    
    HOAGS_INFO("\n");
    all_info = (struct all_dev_info*) hoagsMalloc(sizeof(struct all_dev_info));

    all_info->dev1.dev = FAN;
    all_info->dev1.intensity = POW_ON;
    all_info->dev1.color = NO_COLOR;

    all_info->dev2.dev = LIGHT;
    all_info->dev2.intensity = POW_ON;
    all_info->dev2.color = NO_COLOR;
    HOAGS_INFO("\n");

    return all_info;

}

// void erase_temp_Adder(void)
// {
// 	unsigned int Adres = sys_update_ota_prepare_addr();
// 	Erase_OTA_Region(Adres);
// 	return;
// }

unsigned int ota_Addres;
int total_image_size;
void initBuffer()
{
    if (!mp->resetFlag)
        return;

    printf("start\n");
    ota_Addres = sys_update_ota_prepare_addr();
    printf("OTA_Adress:0x%08x\n", ota_Addres);

    mp->end_seq = ceil(((double)(mp->cp->total_size)) / ((double)(mp->cp->len)));
    mp->bufferFillSize = 0; 
    mp->resetFlag = 0;
    mp->flashAddress = ota_Addres;
    total_image_size = update_ota_erase_upg_region(mp->cp->total_size, total_image_size, ota_Addres); 

}



/*rehan : begin for hdcpr status*/

//check in simple_ble_service.c

/* rehan : end for hdcpr status*/
#if 0
void fillBuffer()
{
    int result;
    if ((mp->cp->seq_num - mp->prev_seq_no)!=1)
    { //when packets are missed
        printf("Packet missed, seq_num=%d prev_seq_num=%d\n", mp->cp->seq_num, mp->prev_seq_no);
        sys_reset();
    }

    mp->prev_seq_no = mp->cp->seq_num;
            
    result = flash_write_locked((uint32_t)mp->fbPos, mp->cp->len, mp->cp->payload);
    if (result)
    {
        // DBG_DIRECT("Write_Done:%02x %02x %02x %02x %02x...%02x %02x %02x %02x %02x\n", mp->cp->payload[0], mp->cp->payload[1], mp->cp->payload[2], mp->cp->payload[3], mp->cp->payload[4], mp->cp->payload[mp->cp->len - 1], mp->cp->payload[mp->cp->len - 2], mp->cp->payload[mp->cp->len - 3], mp->cp->payload[mp->cp->len - 4], mp->cp->payload[mp->cp->len - 5]);
        // for(int i=0;i<128;i++) DBG_DIRECT("flash_adr:%02x",*(mp->fbPos+i));
        mp->fbPos += mp->cp->len;
    }
    //printf("\n");
    
	// memcpy(mp->fbPos, mp->cp->payload, mp->cp->len);
//	mp->fbPos += mp->cp->len;
    
}
#endif

#if 1

extern int update_ota_signature(unsigned char *sig_backup, uint32_t NewFWAddr);
unsigned char sigBack[32];

void fillBuffer(void)
{
    if ((mp->cp->seq_num - mp->prev_seq_no) != 1)
    { // Handle missed packets
        Erase_OTA_Region(ota_Addres);
        printf("Packet missed, seq_num=%d prev_seq_num=%d\n", mp->cp->seq_num, mp->prev_seq_no);
        sys_reset();
    }
    mp->prev_seq_no = mp->cp->seq_num;
    if (mp->cp->seq_num == 1)
    {
        memset(sigBack, '\0', sizeof(sigBack));
        memcpy(sigBack, mp->cp->payload, 32);
        memset(mp->cp->payload, 0xFF, 32);
    }
    device_mutex_lock(RT_DEV_LOCK_FLASH);
    if (flash_burst_write(&flash_OTA, mp->flashAddress, mp->cp->len, mp->cp->payload) < 0)
    {
        printf("Flash write failed\n");
        device_mutex_unlock(RT_DEV_LOCK_FLASH);
        return;
    }
    device_mutex_unlock(RT_DEV_LOCK_FLASH);
    mp->flashAddress += mp->cp->len;
    
}


void flashWriteRenesesData(u32 address, uint16_t data, uint32_t size){
    device_mutex_lock(RT_DEV_LOCK_FLASH);
    if(flash_burst_write(&flash, address, size, &data) < 0)
    {
        printf("Flash write failed\n");
        device_mutex_unlock(RT_DEV_LOCK_FLASH);
        return;
    }
    device_mutex_unlock(RT_DEV_LOCK_FLASH);
}

int flashReadRenesesData(u32 address,uint32_t size,uint16_t *data){
    device_mutex_lock(RT_DEV_LOCK_FLASH);
    flash_burst_read(&flash,address,size,data);
    device_mutex_unlock(RT_DEV_LOCK_FLASH);
    return 0;
}

int flashEraseSector(u32 address){
    device_mutex_lock(RT_DEV_LOCK_FLASH);
    flash_erase_sector(&flash,address);
    device_mutex_unlock(RT_DEV_LOCK_FLASH);
    return 0;
}


int ReadOtaData(uint32_t address, uint32_t size, uint8_t *data) {
    device_mutex_lock(RT_DEV_LOCK_FLASH);
    flash_burst_read(&flash, address, size, data);
    device_mutex_unlock(RT_DEV_LOCK_FLASH);
    return 0;
}



static inline uint32_t read_be32_inline(const uint8_t *p) {
    return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) |
           ((uint32_t)p[2] << 8) | (uint32_t)p[3];
}

int verify_flash_image() {
    uint32_t checksum = 0;
    uint8_t buffer[CHUNK_SIZE];

    printf("DEBUG: Total image size = %zu bytes.\n", total_image_size);

    if (total_image_size < 8) {
        printf("ERROR: Image size too small.\n");
        return -1;
    }

     // Step 3: Read offset value (4 bytes before the checksum)
    uint8_t offset_bytes[4];
    if (ReadOtaData(ota_Addres + total_image_size - 8, 4, offset_bytes) != 0) {
        printf("ERROR: Failed to read model offset\n");
        return -1;
    }
    uint32_t model_offset = read_be32_inline(offset_bytes);
    printf("DEBUG: model_offset %08x\n",model_offset);

    // Step 4: Read model number from TLV block
    uint8_t tag_len_buf[8];
    if (ReadOtaData(ota_Addres + model_offset, 8, tag_len_buf) != 0) {
        printf("ERROR: Failed to read TLV header at offset %u\n", model_offset);
        return -1;
    }

    uint32_t tag = read_be32_inline(&tag_len_buf[0]);
    uint32_t model_len = read_be32_inline(&tag_len_buf[4]);

    if (model_len != strlen(PRODUCT_MODEL_NUMBER)) {
        printf("ERROR: Model number length mismatch. Expected %d, found %u\n", strlen(PRODUCT_MODEL_NUMBER), model_len);
        return -1;
    }

    char flash_model[20 + 1] = {0};
    if (ReadOtaData(ota_Addres + model_offset + 8, strlen(PRODUCT_MODEL_NUMBER), (uint8_t *)flash_model) != 0) {
        printf("ERROR: Failed to read model number from flash\n");
        return -1;
    }

    printf("DEBUG: Model in flash  = [%s]\n", flash_model);
    printf("DEBUG: Expected model  = [%s]\n", PRODUCT_MODEL_NUMBER);

    if (memcmp(flash_model, PRODUCT_MODEL_NUMBER, strlen(PRODUCT_MODEL_NUMBER)) != 0) {
        printf("ERROR: Model number mismatch!\n");
        return -1;
    }

    printf("DEBUG: Model number matched.\n");
    
    // Step 1: Compute checksum excluding the last 4 bytes (checksum field)
    size_t checksum_limit = total_image_size - 4;
    int aligned_size = (checksum_limit / 4) * 4;

    for (int offset = 0; offset < aligned_size; offset += CHUNK_SIZE) {
        int chunk_len = ((aligned_size - offset) > CHUNK_SIZE) ? CHUNK_SIZE : (aligned_size - offset);

        if (ReadOtaData(ota_Addres + offset, chunk_len, buffer) != 0) {
            printf("ERROR: Flash read failed at offset %d\n", offset);
            return -1;
        }

        if (offset == 0) {
            printf("DEBUG: First chunk data (first 16 bytes):\n");
            for (int j = 0; j < 16 && j < chunk_len; j++) {
                printf("%02X ", buffer[j]);
            }
            printf("\n");
        }

        for (int i = 0; i < chunk_len; i += 4) //WORD_SIZE 4
        {
            uint32_t word = read_be32_inline(&buffer[i]);
            checksum = (checksum + word) & 0xFFFFFFFF;
        }

        memset(buffer, 0x00, sizeof(buffer));
    }

    // Step 2: Read and verify final checksum (last 4 bytes)
    uint8_t checksum_bytes[4];
    if (ReadOtaData(ota_Addres + total_image_size - 4, 4, checksum_bytes) != 0) {
        printf("ERROR: Failed to read checksum from flash\n");
        return -1;
    }
    uint32_t expected_checksum = read_be32_inline(checksum_bytes);

    checksum = (checksum + expected_checksum) & 0xFFFFFFFF;
    printf("Checksum including stored value: 0x%08X\n", checksum);

    if (checksum != 0) {
        printf("ERROR: Checksum mismatch! Expected total sum to be 0\n");
        return -1;
    }

    printf("DEBUG: Checksum is valid !\n");
    printf("INFO: OTA image checksum and model number verified successfully.\n");
    return 0;
}




#endif
void HoagsOTA(void)
{
    if (mp->end_seq != mp->cp->seq_num)
    {
        return;
    }

    printf("\nmp->cp->seq_num_LAST:%d\n", mp->cp->seq_num);
    printf("\n...OTA File Download Completed...\n");

    update_ota_signature(sigBack, ota_Addres);

    char strrr[100];
    memset(strrr, 0, sizeof(strrr));

    if (verify_flash_image() != 0) {
        snprintf(strrr, sizeof(strrr), "ota:%d", OTA_FAILED);
        simple_ble_srv_cccd_notify(g_conn_handle, strrr, STATUS_FLAG);
        printf("OTA image verification failed\n");
        Erase_OTA_Region(ota_Addres);
        if(isOtaHappening){
            resumeUartTask();
            resumeRemoteTask();
            resumeCloudTask();
            if(getUartInactivityHandle() != NULL) xTimerStart(getUartInactivityHandle(), 0);
            isOtaHappening = false;
        }
        return;
    }
    
    snprintf(strrr, sizeof(strrr), "ota:%d", OTA_WRITING);
    simple_ble_srv_cccd_notify(g_conn_handle, strrr, STATUS_FLAG);
    vTaskDelay(100);


    memset(strrr, 0, sizeof(strrr));
    snprintf(strrr, sizeof(strrr), "ota:%d", OTA_SUCCESS);
    simple_ble_srv_cccd_notify(g_conn_handle, strrr, STATUS_FLAG);
    vTaskDelay(100);
    memset(strrr, 0, sizeof(strrr));
    snprintf(strrr, sizeof(strrr), "ota:%d", OTA_REBOOT);
    simple_ble_srv_cccd_notify(g_conn_handle, strrr, STATUS_FLAG);

    osDelay(1000);
    sys_reset();
    
}


// void ble_device_disconnected () {
//     printf("BLE Disconnected\n");
//   // ble_state_machine.diagStart = FALSE;
//}

/*

if(ble_state_machine.pCurFile->end_seq == mp->cp->seq_num)
{
        
                    printf("File download %s complete\n", ble_state_machine.pCurFile->filename);

                  if (ble_state_machine.state == BLE_STATE_OTA_FILE_DOWNLOADING) 
                   {
                        dumpBufferOTA(ble_state_machine.pCurFile);

                        // memset(strrr, 0, sizeof(strrr));
                        // sprintf(strrr, "ota:%d", OTA_REBOOT);

                     //   simple_ble_srv_cccd_notify(g_conn_handle, strrr , STATUS_FLAG);

                        vTaskDelay(500);

                        sys_reset();
                        
                        free_all_resources();
                   }
 }
 */


/*rehan : begin device control */

/*fan control begin*/
//#if ENABLE_FAN
#if 1
void fanPowerControl(const char* payload, const size_t len)
{
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_DBG("action=%d\n", *action);
    switch (*action)
    {
        case FAN_CMD_ON:
            set_fan_speed(fanPtr, FAN_LOW);
            #if HOAGS_UART_DUMP
            ;
            #elif VERSADEVICES_SUPERFAN_IOT
            // fpp = &superfan_switchOn;
            // xQueueSend(cmdQ, &fpp, 0);
            // id = SWITCHON;
            // xQueueSend(actionIdQ, &id, 0);
            // #else
            superfan_switchOn(); //for superfan demo   //ksk
            #endif
            break;
        
        case FAN_CMD_OFF:
            set_fan_speed(fanPtr, FAN_OFF);
            #if HOAGS_UART_DUMP
            ;
            #elif VERSADEVICES_SUPERFAN_IOT
            // fpp = &superfan_switchOff;
            // xQueueSend(cmdQ, &fpp, 0);
            // id = SWITCHOFF;
            // xQueueSend(actionIdQ, &id, 0);
            // #else
            superfan_switchOff(); //for superfan demo
            #endif
            break;
    }

#if VGUARD_NEW_FAN
    char power[8];
    sprintf(power, "%d", *action + 1);
    setEnvItem(ENV_POWERCONTROL, power);
#else
    char power[8];
    sprintf(power, "%d", *action);
    setEnvItem(ENV_POWERCONTROL, power);
#endif

    free (action);
}

void fanIncreaseSpeed()
{
    HOAGS_INFO("\n");
}

void fanDecreaseSpeed()
{
    HOAGS_INFO("\n");
}

//TODO: Move this to fan.c
void fanModeControl(const char* payload, const size_t len)
{
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_INFO("action=%d\n",*action);
    switch (*action)
    {
	#if 1 //TODO: Suvarna >> Add more changes here when commands are freezed
        case FAN_CMD_MODE_NORMAL:
            set_fan_speed(fanPtr, FAN_MID);
            #if VERSADEVICES_SUPERFAN_IOT
            superfan_normalmode();
            #else
            superfan_normalmode();
            #endif
            break;
	#endif
        case FAN_CMD_MODE_BREEZE:
            set_fan_speed(fanPtr, FAN_HIGH);
            #if HOAGS_UART_DUMP
            ;
            #elif VERSADEVICES_SUPERFAN_IOT
            // fpp = &superfan_Breeze_mode;
            // xQueueSend(cmdQ, &fpp, 0);
            // id = BREEZE;
            // xQueueSend(actionIdQ, &id, 0);
            // #else
            superfan_Breeze_mode(); //for superfan demo
            #endif            
            break;

        case FAN_CMD_MODE_ECO:
            #if VERSADEVICES_SUPERFAN_IOT
            // fpp = &superfan_Eco_Mode;
            // xQueueSend(cmdQ, &fpp, 0);
            // id = ECO;
            // xQueueSend(actionIdQ, &id, 0);
            superfan_Eco_Mode();
            #endif                              
        break;

        case FAN_CMD_MODE_ACMIX:
            #if VERSADEVICES_SUPERFAN_IOT
            // fpp = &superfan_acmix;
            // xQueueSend(cmdQ, &fpp, 0);
            // id = ACMIX;
            // xQueueSend(actionIdQ, &id, 0); 
            superfan_acmix();
            #endif    
        break;

        case FAN_CMD_ACFAN:
            superfan_acfan();
        break;

        case FAN_CMD_MODE_WELLNESS:
            superfan_wellness();
            #if VERSADEVICES_SUPERFAN_IOT
            // fpp = &superfan_wellness;
            // xQueueSend(cmdQ, &fpp, 0);
            // id = WELLNESS;
            // xQueueSend(actionIdQ, &id, 0); 
            #endif 
        break;

        case FAN_CMD_MODE_REVERSE:
            superfan_Reverse();
            #if VERSADEVICES_SUPERFAN_IOT
            // fpp = &superfan_Reverse;
            // xQueueSend(cmdQ, &fpp, 0);
            // id = REVERSE;
            // xQueueSend(actionIdQ, &id, 0);
            #endif
        break;

        case FAN_CMD_MODE_FINETUNE:
            superfan_Fine_tune_mode();
            #if VERSADEVICES_SUPERFAN_IOT
            // fpp = &superfan_Fine_tune_mode;
            // xQueueSend(cmdQ, &fpp, 0);
            // id = FINETUNE;
            // xQueueSend(actionIdQ, &id, 0);
            #endif
        break;

        case FAN_CMD_MODE_MOB:
            rr_mob_mode();
        break;

        case FAN_CMD_MODE_BOOST:
            rr_boost_mode();
        break;

        case FAN_CMD_MODE_SLEEP:
            rr_sleep_mode();
        break;
        case FAN_CMD_MODE_SLEEP_ON:
            sleep_mode_on();
        break;
        case FAN_CMD_MODE_SLEEP_OFF:
            sleep_mode_off();
        break;
        case FAN_CMD_MODE_LED_ON:
            led_on();
        break;
        case FAN_CMD_MODE_LED_OFF:
            led_off();
        break;
        default:
            return;
    }

    #if VGUARD_NEW_FAN
    setEnvItem(ENV_SPEEDCONTROL, "0");
    char mode[8];
    sprintf(mode, "%d", *action + 1);
    setEnvItem(ENV_MODECONTROL, mode);        
    #endif
    free(action);
}

void fanTimerControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_DBG("action=%d\n", *action);

    printf("Payload[0]_int_1 = %d\n", payload[0]);
    #if RR_KABLES
        rr_Timer(payload[0]);

    #elif VERSADEVICES_SUPERFAN_IOT
    PayloadValue = payload[0];
    fpp = &superfan_Timer;
    xQueueSend(cmdQ, &fpp, 0);
    id = TIMER;
    xQueueSend(actionIdQ, &id, 0);

    #elif VGUARD_NEW_FAN
        HOAGS_INFO("Payload[0]_int_1 = %d\n, Payload[0]_int_2 = %d\n", payload[0], payload[1]);
        vguard_timer(payload[0], payload[1]);
    #endif
free(action);
}

void fanvguardled(const char* payload, const size_t len)
{
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_INFO("action=%d\n",*action);
    switch (*action)
    {
        case FAN_CMD_MODE_VGUARD_LED_ON:
            led_on();
        break;
        case FAN_CMD_MODE_VGUARD_LED_OFF:
            led_off();
        break;
    }

    char led[8];
    sprintf(led, "%d", *action + 1);
    setEnvItem(ENV_LEDCONTROL, led);        
    free(action);
}
void fanvguardbuzzer(const char* payload, const size_t len)
{
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_INFO("action=%d\n",*action);
    switch (*action)
    {
        case FAN_CMD_MODE_VGUARD_BUZZER_ON:
            buzzermuteon();
        break;
        case FAN_CMD_MODE_VGUARD_BUZZER_OFF:
            buzzermuteoff();
        break;
    }

    char buzzer[8];
    sprintf(buzzer, "%d", *action + 1);
    setEnvItem(ENV_BUZZER, buzzer);        
    free(action);
}
void fanvguardreverse(const char* payload, const size_t len)
{
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_INFO("action=%d\n",*action);
    switch (*action)
    {
        case FAN_CMD_MODE_VGUARD_REVERSE_ON:
            superfan_Reverse();
        break;
        case FAN_CMD_MODE_VGUARD_REVERSE_OFF:
            reverse_off();
        break;
    }

    char reverse[8];
    sprintf(reverse, "%d", *action + 1);
    setEnvItem(ENV_REVERSE, reverse);        
    free(action);
}
void fanregulatorControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_DBG("action=%d\n", *action);

   
    HOAGS_INFO("Payload[0] = %d\n", payload[0]);

    speedregulator(payload[0]);
    
free(action);
}

void fanbreezeControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_DBG("action=%d\n", *action);

   
    HOAGS_INFO("Payload[0] = %d\n", payload[0]);

    breezeregulator(payload[0]);
    
free(action);
}


void Rpmfan(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_DBG("action=%d\n", *action);

    printf("Payload[0]_int_rpm = %d\n", payload[0]);

    superfan_rpm(payload[0]);

free(action);
}

void fandownTimerControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_DBG("action=%d\n", *action);

    printf("Payload[0]_down = %d\n", payload[0]);

    #if VERSADEVICES_SUPERFAN_IOT
    PayloadValue = payload[0];
    fpp = &rr_Timer;
    xQueueSend(cmdQ, &fpp, 0);
    id = TIMER;
    xQueueSend(actionIdQ, &id, 0);

    #else
    rr_Timer(payload[0]);

    #endif

    #if 0
    char mode[8];
    sprintf(mode, "%d", *action);
    setEnvItem(ENV_MODECONTROL, mode);       
    #endif
    free(action);
}


void fanSpeedControl(const char* payload, const size_t len)
{
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_INFO("action=%d\n",*action);
    switch (*action)
    {
        case FAN_CMD_SPEED_LOW:
            set_fan_speed(fanPtr, FAN_LOW);
            #if HOAGS_UART_DUMP
            ;
            #elif VERSADEVICES_SUPERFAN_IOT
            // fpp = &superfan_low_speed;
            // xQueueSend(cmdQ, &fpp, 0);
            // id = LOW_SPEED;
            // xQueueSend(actionIdQ, &id, 0);
            // #else
            superfan_low_speed(); //for superfan demo
            #endif
            break;
        case FAN_CMD_SPEED_LOW_MEDIUM:
            rr_low_med_speed();
        break;
        case FAN_CMD_SPEED_MEDIUM:
            set_fan_speed(fanPtr, FAN_MID);
            #if HOAGS_UART_DUMP
            ;
            #elif VERSADEVICES_SUPERFAN_IOT
            // fpp = &superfan_medium_speed;
            // xQueueSend(cmdQ, &fpp, 0);
            // id = MED_SPEED;
            // xQueueSend(actionIdQ, &id, 0);
            // #else
            superfan_medium_speed(); //for superfan demo
            #endif
            break;
        case FAN_CMD_SPEED_MEDIUM_HIGH:
            rr_med_high_speed();
        break;
        case FAN_CMD_SPEED_HIGH:
            set_fan_speed(fanPtr, FAN_HIGH);
            #if HOAGS_UART_DUMP
            ;
            #elif VERSADEVICES_SUPERFAN_IOT
            // fpp = &superfan_high_speed;
            // xQueueSend(cmdQ, &fpp, 0);
            // id = HIGH_SPEED;
            // xQueueSend(actionIdQ, &id, 0);
            // #else
            superfan_high_speed(); //for superfan demo
            #endif
            break;
        
    }
#if VGUARD_NEW_FAN
    setEnvItem(ENV_MODECONTROL, "0");
    char speed[8];
    sprintf(speed, "%d", *action + 1);
    setEnvItem(ENV_SPEEDCONTROL, speed);
#else	
    char speed[8];
    sprintf(speed, "%d", *action);
    setEnvItem(ENV_SPEEDCONTROL, speed); 
#endif  

    free(action);
}

void controlFan()       //fan control main 
{

    //print();
    
    for(int level = 2, levelIndex = 0; level <= mp->cp->total_level; ++level)
    {
        if(level == 2)//for now only 2 levels, if third level comes add more if/else
        {
            switch(mp->cp->level[levelIndex])
            {
                case FAN_CMD_POWER_CONTROL:
                    fanPowerControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case FAN_CMD_INCREASE_SPEED:
                    step_up_fan_speed(fanPtr);
                    return;
                case FAN_CMD_DECREASE_SPEED:
                    step_down_fan_speed(fanPtr);
                    return;
                case FAN_CMD_MODE_CONTROL:
                    fanModeControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case FAN_CMD_TIMER_CONTROL:
                    fanTimerControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case FAN_CMD_SPEED_CONTROL:
                    fanSpeedControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case FAN_CMD_TIMER_SPEED:
                    fandownTimerControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case FAN_CMD_RPM_CONTROL:
                    Rpmfan(mp->cp->payload, mp->cp->total_size);
                    return;
                case FAN_CMD_SPEED_REG_CONTROL:
                    fanregulatorControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case FAN_CMD_BREEZE_CONTROL:
                    fanbreezeControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case FAN_CMD_LED_CONTROL:
                    fanvguardled(mp->cp->payload, mp->cp->total_size);
                    return;
                case FAN_CMD_BUZZER_CONTROL:
                    fanvguardbuzzer(mp->cp->payload, mp->cp->total_size);
                    return;
                case FAN_CMD_REVERSE_CONTROL:
                    fanvguardreverse(mp->cp->payload, mp->cp->total_size);
                    return;

            }
        }    
    }
}
#endif

#if LIVPURE_PURIFIER
void controlPurifier()
{
    for(int level = 2, levelIndex = 0; level <= mp->cp->total_level; ++level)
    {
        if(level == 2)//for now only 2 levels, if third level comes add more if/else
        {
            switch(mp->cp->level[levelIndex])
            {
                //printf("CASE NO:%d\n",mp->cp->level[levelIndex]);
                case WP_CMD_POWER_CONTROL:
                    //if power control is there add it here
                    break;
                case WP_CMD_NORMAL_CONTROL:
                case WP_CMD_HOT_CONTROL:
                case WP_CMD_WARM_CONTROL:
                    waterControl(mp->cp->payload, mp->cp->total_size,mp->cp->level[levelIndex]);
                    break;
                case WP_CMD_REMOTE_DIAG:
                    initiateRemoteDiag(SOURCE_APP);
                    break;
                case WP_CMD_SET_TEMPERATURE:
                    setTemperature(mp->cp->payload, mp->cp->total_size);
                    break;
                case WP_CMD_DEVICE_ANALYSIS:
                    initiateDeviceAnalysis(SOURCE_APP);
                    break;
                case WP_CMD_PERIODIC_DATA:
                    sendPeriodcDataToApp();
                    break;
                case WP_CMD_DATETIME_SET:
                    {
                        int  istDateTimeFromApp[7] = {0};
                        char *dataPtr = hoagsMalloc(mp->cp->total_size);
                        memcpy(dataPtr, mp->cp->payload, mp->cp->total_size);  
                        for(int i = 0; i < mp->cp->total_size; i++) {
                            istDateTimeFromApp[i] = (int *)dataPtr[i]; 
                        }
                        free(dataPtr);
                        int *timePtr = getIstDateTimeStored();
                        for (int i = 0; i < 7; i++) {
                            timePtr[i] = istDateTimeFromApp[i];
                        }
                        sendDateTimeToReneses(SOURCE_APP,istDateTimeFromApp);
                    }
                    break;
                case WP_CMD_FILTER_RESET:
                    filterReset(mp->cp->payload, mp->cp->total_size);
                    break;
                #if FILTER_SETTING
                case WP_CMD_FILTER_SETTING_VIA_TIME:
                    filterSetting(0x09, mp->cp->payload, mp->cp->total_size,mp->cp->level[1]);
                    break;
                case WP_CMD_FILTER_SETTING_VIA_WATER: 
                    filterSetting(0x0a,mp->cp->payload, mp->cp->total_size,mp->cp->level[1]);
                    break;
                #endif
                case WP_CMD_INLET_TDS_SETTING:
                    {
                            if (mp->cp->total_size < 2) {
                                printf("Invalid payload size\n");
                                break;
                            }

                            uint8_t *inletDataPtr = (uint8_t *)hoagsMalloc(mp->cp->total_size);
                            if (!inletDataPtr) {
                                printf("Memory allocation failed\n");
                                break;
                            }

                            memcpy(inletDataPtr, mp->cp->payload, mp->cp->total_size);

                            // Little-endian: low byte first
                            int inletTdsValue = (inletDataPtr[1] << 8) | inletDataPtr[0];

                            free(inletDataPtr);

                            if (inletTdsValue < 100 || inletTdsValue > 2000) {
                                printf("Invalid TDS value: %d\n", inletTdsValue);
                                break;
                            }

                            // Convert to string and store in env
                            char tdsStr[10];
                            sprintf(tdsStr, "%d", inletTdsValue);
                            setEnvItem(INLET_TDS, tdsStr);

                            sendInletTDSToReneses(SOURCE_APP,0x01);
                    }
                    break;
                case WP_CMD_RESET_WATER_CONSUMPTION: 
                    sendWaterconusmptionEraseCmdToReneses(SOURCE_APP);
                    break;
                default:
                    HOAGS_INFO("Default triggerd from app \n");
            }
        }    
    }
}
#endif

/*fan control end*/

/*AC control begin*/

//#if ENABLE_AC
#if 0
void acPowerControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_DBG("action=%d\n", *action);
    switch (*action)
    {
    case AC_CMD_ON:
        switchOnAC();
        break;

    case AC_CMD_OFF:
        switchOffAC();
        break;
    }

    char power[8];
    sprintf(power, "%d", *action);
    setEnvItem(ENV_POWERCONTROL, power);   

    free(action);
}

void acSpeedControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_DBG("action=%d\n", *action);
    switch (*action)
    {
    case AC_CMD_SPEED_LOW:
        lowSpeedAC();
        break;
    
    case AC_CMD_SPEED_MID:
        midSpeedAC();
        break;

    case AC_CMD_SPEED_HIGH:
        highSpeedAC();
        break;
    }

    char speed[8];
    sprintf(speed, "%d", *action);
    setEnvItem(ENV_SPEEDCONTROL, speed);   

    free(action);
}

void acTempControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_DBG("action=%d\n", *action);
    incTempAC(payload[0]);
    //decTempAC(payload[0]);
    char temp[8];
    sprintf(temp, "%d", *action);
    setEnvItem(ENV_TEMPCONTROL, temp);   

    free(action);
}

void acModeControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    HOAGS_DBG("action=%d\n", *action);
    switch (*action)
    {
    case AC_CMD_MODE_DRY:
        dryModeAC();
        break;

    case AC_CMD_MODE_COOL:
        coolModeAC();
        break;
    
    case AC_CMD_MODE_AUTO:
        autoModeAC();
        break;
    
    case AC_CMD_MODE_FAN:
        fanModeAC();
        break;
    
    case AC_CMD_MODE_HOT:
        hotModeAC();
        break;

    case AC_CMD_MODE_WIND:
        windModeAC();
        break;

    }

    #if 0
    char mode[8];
    sprintf(mode, "%d", *action);
    setEnvItem(ENV_MODECONTROL, mode);   
    #endif
    free(action);
}

// acSwingControl
void acSwingControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    printf("action=%d\n", *action);
    switch (*action)
    {
        case AC_SWING_VON:
            swingVerticalOn();
            printf("swingv-o");
            break;
        case AC_SWING_VOFF:
            swingVerticalOff();
            printf("swingv-off");
            break;
        case AC_SWING_HON:
            swingHorizontalOn();
            break;
        case AC_SWING_HOFF:
            swingHorizontalOff();
            break;
        default:
            HOAGS_ERR("INVALID COMMAND !");
    }

    #if 0
    char mode[8];
    sprintf(mode, "%d", *action);
    setEnvItem(ENV_MODECONTROL, mode);   
    #endif
    free(action);
}

//acTurboControl
void acTurboControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    printf("action=%d\n", *action);
    switch (*action)
    {
        case AC_TURBO_ON:
            turboOn();
            break;
        case AC_TURBO_OFF:
            turboOff();
            break;
        default:
            HOAGS_ERR("INVALID COMMAND !");
            
    }

    #if 0
    char mode[8];
    sprintf(mode, "%d", *action);
    setEnvItem(ENV_MODECONTROL, mode);   
    #endif
    free(action);
}

//acSleepControl
void acSleepControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    printf("action=%d\n", *action);
    switch (*action)
    {
        case AC_SLEEP_ON:
            sleepOn();
            break;
        case AC_SLEEP_OFF:
            sleepOff();
            break;
        default:
            HOAGS_ERR("INVALID COMMAND !");
    }

    #if 0
    char mode[8];
    sprintf(mode, "%d", *action);
    setEnvItem(ENV_MODECONTROL, mode);   
    #endif
    free(action);
}

//acTimerControl
void acTimerControl(const uint8_t payload[], const u8_t level[])
{
    HOAGS_INFO("\n");
    switch (level[1])
    {
        case AC_TIMER_ON: 
            setTimer(payload[0], payload[1]);
            break;
        default:
            HOAGS_ERR("INVALID COMMAND !");
    }
}

//acCondaControl
void acCondaControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    printf("action=%d\n", *action);
    switch (*action)
    {
        case AC_CONDA_ON:
            condaOn();
            break;
        case AC_CONDA_OFF:
            condaOff();
            break;
        default:
            HOAGS_ERR("INVALID COMMAND !");
    }

    #if 0
    char mode[8];
    sprintf(mode, "%d", *action);
    setEnvItem(ENV_MODECONTROL, mode);   
    #endif

    free(action);
}

//acEcoControl
void acEcoControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    printf("action=%d\n", *action);
    switch (*action)
    {
        case AC_ECO_ON:
            echoOn();
            break;
        case AC_ECO_OFF:
            echoOff();
            break;
        default:
            HOAGS_ERR("INVALID COMMAND !");
    }

    #if 0
    char mode[8];
    sprintf(mode, "%d", *action);
    setEnvItem(ENV_MODECONTROL, mode);   
    #endif
    free(action);
}

//acDisplayControl
void acDisplayControl(const char* payload, const size_t len)
{
    HOAGS_INFO("\n");
    uint8_t* action = hoagsMalloc(len);
    memcpy(action, payload, len);
    printf("action=%d\n", *action);
    switch (*action)
    {
        case AC_DISPLAY_ON:
            displayOn();
            break;
        case AC_DISPLAY_OFF:
            displayOff();
            break;
        default:
            HOAGS_ERR("INVALID COMMAND !");
    }

    #if 0
    char mode[8];
    sprintf(mode, "%d", *action);
    setEnvItem(ENV_MODECONTROL, mode);   
    #endif
    free(action);
}

void controlAC()        //ac control main
{
    for(int level = 2, levelIndex = 0; level <= mp->cp->total_level; ++level)
    {
        if(level == 2)//for now only 2 levels, if third level comes add more if/else
        {
            switch(mp->cp->level[levelIndex])
            {
                case AC_CMD_POWER_CONTROL:
                    acPowerControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case AC_CMD_SPEED_CONTROL:
                    acSpeedControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case AC_CMD_TEMP_CONTROL:
                    acTempControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case AC_CMD_MODE_CONTROL:
                    acModeControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case AC_CMD_SWING_CONTROL:
                    acSwingControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case AC_CMD_TURBO_CONTROL:
                    acTurboControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case AC_CMD_SLEEP_CONTROL:
                    acSleepControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case AC_CMD_TIMER_CONTROL://level[0] = 7 for timer control ////level[1] = 0 = timer on/ 1 = timer off
                    if((mp->cp->level[levelIndex+1]) == 0)
                    {
                        acTimerControl(mp->cp->payload, mp->cp->level);
                    }
                    else
                    {
                        HOAGS_ERR("**********In side packets.c file*****\n");
                        cancelAllTimer();
                    }
                    return;
                case AC_CMD_CONDA_CONTROL:
                    acCondaControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case AC_CMD_ECO_CONTROL:
                    acEcoControl(mp->cp->payload, mp->cp->total_size);
                    return;
                case AC_CMD_DISPLAY_CONTROL:
                    acDisplayControl(mp->cp->payload, mp->cp->total_size);
                    return;
            }
        }    
    }
}
#endif

/*AC control end*/

/*rehan : end device control */

  #if 1     
void action(void)
{
    // char continueLoop = 0;
    // do {
    //     continueLoop = 0;
    //     switch (ble_state_machine.state) {
                //printf("action: %d\n",mp->cp->action);
                switch (mp->cp->action)
                {

                    case OTA_BIN: 
                     if(!isOtaHappening){
                        suspendUartTask();
                        suspendRemoteTask();
                        suspendCloudTask();
                        if(getUartInactivityHandle() != NULL) xTimerStop(getUartInactivityHandle(), 0);
                        isOtaHappening = true;
                     }
                     initBuffer();
                     fillBuffer();
                     HoagsOTA();
                    break;

                    case DEV_NAME:
                    {
                        char *devName = (char *)hoagsMalloc(mp->cp->len + 1);
                        if (devName == NULL) {
                            printf("Memory allocation failed.\n");
                            return;
                        }

                        memcpy(devName, mp->cp->payload, mp->cp->len);
                        devName[mp->cp->len] = '\0';

                        printf("Device Name set to =%s\n", devName);
                        printf("STORED DEV LENGTH:%d\n", strlen(devName));

                        if (strlen(devName) != 0) {
                            if (setEnvItem(ENV_FRIENDLYNAME, devName))
                            {
                                printf("Friendly name setting done succcesfully\n");
                                sys_reset();
                            }
                            else
                                printf("Friendly name setting Failed\n");
                        }
                        free(devName);
                    }
                    break;
                    case FACTORY_RESET:
                        factoryReset();
                    break;
                    case MACID_SET:
                    {
                        unsigned char macid[13];
                        memset(macid, 0x00, sizeof(macid));
                        memcpy(macid, mp->cp->payload, 12);
                        printf("MACID RECEIVED FROM APP:%s\n",macid);
                        uint16_t address = hextstrTOshort("190");  

                        u16 length = strlen((char*)macid) / 2;

                        u8* data = hoagsMalloc(length * 2);
                        memset(data, 0x00, length * 2);

                        for (int i = 0; i < length; ++i) {
                            data[i] = _2char2hex(macid[i*2], macid[i*2+1]);
                        }

                        int ret = hoagsEFUSEWrite(address, length, data);
                        free(data);

                        char fn[16];
                        memset(fn, 0x00, sizeof(fn));
                        getEnvItem(ENV_FRIENDLYNAME, fn);
                        memcpy(&(fn[6]), macid, 4);
                        setEnvItem(ENV_FRIENDLYNAME, fn);

                        MAC_Id_Read();
                    }
                    break;
                    #if ENABLE_FAN 
                    case FAN_CTRL:
                        controlFan();
                        break;
                    #endif
                    #if LIVPURE_PURIFIER
                    case PURIFIER_CTRL:
                        controlPurifier();
                        break;
                    #endif
                #if 0    
                    #if ENABLE_LIGHT
                    case LIGHT_CTRL:
                        controlLight();
                        break;
                    #endif

                    #if 1
                    case AC_CTRL:
                        controlAC();
                        break;
                    #endif
                #endif
                    case BLE_PASSWORD:
                        ble_password();
                        break;
                    case WIFI_CONFIG:
                        HOAGS_INFO("\n");
                        wifiAction();
                        break;

                    case DEV_USERID:
                        {
                            char *userId = (char *)hoagsMalloc(mp->cp->len + 1);
                            if (userId == NULL) {
                                printf("Memory allocation failed.\n");
                                return;
                            }

                            memcpy(userId, mp->cp->payload, mp->cp->len);
                            userId[mp->cp->len] = '\0';

                            printf("UserID set to =%s\n", userId);
                            printf("STORED USER LENGTH:%d\n", strlen(userId));

                            if (strlen(userId) != 0) {
                                if (setEnvItem(ENV_USERID, userId))
                                    printf("User Id is stored.\n");
                                else
                                    printf("User id storing failed.\n");
                                isRegistrationSent = FALSE;
                            }

                            free(userId);
                        }
                        break;
                    case DEV_SERIAL_NO:
                        {
                            char *serialNo = (char *)hoagsMalloc(mp->cp->len + 1);
                            if (serialNo == NULL) {
                                printf("Memory allocation failed.\n");
                                return;
                            }

                            memcpy(serialNo, mp->cp->payload, mp->cp->len);
                            serialNo[mp->cp->len] = '\0';

                            printf("serialNo set to =%s\n", serialNo);
                            printf("STORED SERIAL LENGTH:%d\n", strlen(serialNo));

                            if (strlen(serialNo) != 0) {
                                if (setEnvItem(ENV_SERIALNO, serialNo))
                                    printf("serialNo is stored.\n");
                                else
                                    printf("serialNo storing failed.\n");
                            }
                            free(serialNo);
                        }
                        break;
                    default:
                        break;

                }
    //     }
    // }while (continueLoop==1);
}

#endif



