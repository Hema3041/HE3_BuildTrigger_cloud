#include "fan.h"
#include "env.h"
#include "hoags_config.h"
#include "packets.h"
#include "htap_config.h"

#include "FreeRTOS.h"
#include "timers.h"
#include "timer_api.h"
//#include "hoags_common.h"

extern uint8_t FanConfigured;
extern uint8_t LightConfigured;
extern uint8_t UARTConfigured;

struct fan fanObj;
struct fan* fanPtr = &fanObj;

#if HOAGS_UART_DUMP
extern struct serial_s dumpUartObj;
#else
extern struct serial_s superFanObj;
#endif
#if LIVPURE_PURIFIER
int currentBaudrate;
#endif
#if VERSADEVICES_SUPERFAN_IOT
extern BOOL SendPollFlag;
extern uint16_t g_conn_handle;
extern unsigned char lastUpdate;
extern uint8_t PayloadValue;
extern unsigned char statusonoff[15];
extern unsigned char statusmode[15]; 
extern unsigned char statusfansp[15];
extern unsigned char statusTimer[15]; 
static char switchon_workaround = 0;
QueueHandle_t cmdQ = NULL;
QueueHandle_t toQ = NULL;
QueueHandle_t actionIdQ;
enum sentReceivedCmdId srciSent = NONE;
enum sentReceivedCmdId srciReceived = NONE;
void* fpp = NULL;
void (*lastAction)(int) = NULL;
int lastId = -1;
TimerHandle_t timerObj, timerObj1;
QueueHandle_t ackQ = NULL;
int id = NONE;
BOOL onState = FALSE;
unsigned char onAck[13] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x06 ,0x02 ,0x01 ,0x00 ,0x02 ,0x01 ,0x01, 0x16};
unsigned char offAck[13] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x06 ,0x02 ,0x01 ,0x00 ,0x02 ,0x01, 0x00, 0x15};
unsigned char lowAck[13] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x06 ,0x04 ,0x02 ,0x00 ,0x02 ,0x01 ,0x21, 0x39};
unsigned char medAck[13] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x06 ,0x04 ,0x02 ,0x00 ,0x02 ,0x01 ,0x42, 0x5A};
unsigned char highAck[13] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x06 ,0x04 ,0x02 ,0x00 ,0x02 ,0x01 ,0x63, 0x7B};
unsigned char breezeAck[12] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x06, 0x38};
unsigned char finetuneAck[12] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x05, 0x37};
unsigned char reverseAck[12] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x04, 0x36};
unsigned char acmixAck[12] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x02, 0x34};
unsigned char ecoAck[12] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x01, 0x33};
unsigned char wellAck[12] = {0x55 ,0xAA ,0x03 ,0x07 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x03, 0x35};
unsigned char timerAck[12] = {0x55, 0xAA, 0x03, 0x07, 0x00, 0x05, 0x22, 0x02, 0x00, 0x01, 0x00, 0x00};
int timerCount = 0;
int cmdSentTick;
BOOL lastAckReceived = TRUE;

void checkIfAck()
{
    if(cmdQ == NULL || actionIdQ == NULL || ackQ == NULL)
        return;
    
    void (*action)(void) = NULL;
    if(xQueuePeek(cmdQ, &action, 0) != pdTRUE)
        return;
    
    short actionId;
    if(xQueuePeek(actionIdQ, &actionId, 0) != pdTRUE)
        return;
    
    if(ackQ ==  NULL)
        return;
    
    BOOL received = FALSE;
    unsigned char* ack;

    if(action && lastAckReceived)
    {
        HOAGS_DBG("\n");
        if(actionId == SWITCHON)
            (*action)();
        else if(actionId == SWITCHOFF)
            (*action)();
        else if(actionId == LOW_SPEED)
            (*action)();
        else if(actionId == MED_SPEED)
            (*action)();
        else if(actionId == HIGH_SPEED)
            (*action)();
        else if(actionId == ACMIX)
            (*action)();
        else if(actionId == WELLNESS)
            (*action)();
        else if(actionId == ECO)
            (*action)();
        else if(actionId == REVERSE)
            (*action)();
        else if(actionId == BREEZE)
            (*action)();
        else if(actionId == FINETUNE)
            (*action)();
         else if(actionId == TIMER)
            (*action)();
        ++timerCount;
        lastAckReceived = FALSE;
        
    }

    // HOAGS_DBG("Checking ack for id=%d\n", actionId);
    while(TRUE)
    {
        if(xQueueReceive(ackQ, &ack, 0) == pdTRUE)
        {
            switch(actionId)
            {
                case SWITCHON:
                    if(memcmp(ack, onAck, 13) == 0)
                    {
                        received = TRUE;
                        memcpy(statusonoff, ack, 15);
                        HOAGS_ERR("Switch-on ack was received=%p\n", ack);

                        vTaskDelay(500);
                        
                        if (lastUpdate == 1 && SendPollFlag == TRUE) {
                            simple_ble_srv_cccd_notify(g_conn_handle, statusfansp, POLLACK_FLAG);
                        }
                        else if (lastUpdate == 2 && SendPollFlag == TRUE) {
                            simple_ble_srv_cccd_notify(g_conn_handle, statusmode, POLLACK_FLAG);
                        }
                        else if (lastUpdate == 3 && SendPollFlag == TRUE) {
                            simple_ble_srv_cccd_notify(g_conn_handle, statusTimer, POLLACK_FLAG);
                        }
                        break;
                    }
                
                case SWITCHOFF:
                    if(memcmp(ack, offAck, 13) == 0)
                    {
                        received = TRUE;
                        memcpy(statusonoff, ack, 15);
                        HOAGS_ERR("Switch-off ack was received=%p\n", ack);
                        break;
                    }
                case LOW_SPEED:
                    if(memcmp(ack, lowAck, 13) == 0)
                    {
                        received = TRUE;
                        lastUpdate = 1;
                        memcpy(statusfansp, ack, 15);
                        statusonoff[11] = 0x01;
                        HOAGS_INFO("statusonoff[11] after: %02x\n", statusonoff[11]);
                        HOAGS_ERR("low ack was received=%p\n", ack);
                        break;
                    }
                
                case MED_SPEED:
                    if(memcmp(ack, medAck, 13) == 0)
                    {
                        received = TRUE;
                        lastUpdate = 1;
                        memcpy(statusfansp, ack, 15);
                        statusonoff[11] = 0x01;
                        HOAGS_INFO("statusonoff[11] after: %02x\n", statusonoff[11]);
                        HOAGS_ERR("med ack was received=%p\n", ack);
                        break;
                    }
                
                case HIGH_SPEED:
                    if(memcmp(ack, highAck, 13) == 0)
                    {
                        received = TRUE;
                        lastUpdate = 1;
                        memcpy(statusfansp, ack, 15);
                        statusonoff[11] = 0x01;
                        HOAGS_INFO("statusonoff[11] after: %02x\n", statusonoff[11]);
                        HOAGS_ERR("high ack was received=%p\n", ack);
                        break;
                    }
                    

                case ACMIX:
                    if(memcmp(ack, acmixAck, 12) == 0)
                    {
                        received = TRUE;
                        lastUpdate = 2;
                        memcpy(statusmode, ack, 15);
                        statusonoff[11] = 0x01;
                        HOAGS_INFO("statusonoff[11] after: %02x\n", statusonoff[11]);
                        HOAGS_ERR("acmix ack was received=%p\n", ack);
                        break;
                    }
                
                case WELLNESS:
                    if(memcmp(ack, wellAck, 12) == 0)
                    {
                        received = TRUE;
                        lastUpdate = 2;
                        memcpy(statusmode, ack, 15);
                        statusonoff[11] = 0x01;
                        HOAGS_INFO("statusonoff[11] after: %02x\n", statusonoff[11]);
                        HOAGS_ERR("wellness ack was received=%p\n", ack);
                        break;
                    }
                
                case ECO:
                    if(memcmp(ack, ecoAck, 12) == 0)
                    {
                        received = TRUE;
                        lastUpdate = 2;
                        memcpy(statusmode, ack, 15);
                        statusonoff[11] = 0x01;
                        HOAGS_INFO("statusonoff[11] after: %02x\n", statusonoff[11]);
                        HOAGS_ERR("eco ack was received=%p\n", ack);
                        break;
                    }

                case REVERSE:
                    if(memcmp(ack, reverseAck, 12) == 0)
                    {
                        received = TRUE;
                        lastUpdate = 2;
                        memcpy(statusmode, ack, 15);
                        statusonoff[11] = 0x01;
                        HOAGS_INFO("statusonoff[11] after: %02x\n", statusonoff[11]);
                        HOAGS_ERR("reverse ack was received=%p\n", ack);
                        break;
                    }

                case BREEZE:
                    if(memcmp(ack, breezeAck, 12) == 0)
                    {
                        received = TRUE;
                        lastUpdate = 2;
                        memcpy(statusmode, ack, 15);
                        HOAGS_ERR("Breeze ack was received=%p\n", ack);
                        break;
                    }
                
                case FINETUNE:
                    if(memcmp(ack, finetuneAck, 12) == 0)
                    {
                        received = TRUE;
                        lastUpdate = 2;
                        memcpy(statusmode, ack, 15);
                        HOAGS_ERR("finetune ack was received=%p\n", ack);
                        break;
                    }

                case TIMER:
                    if(memcmp(ack, timerAck, 10) == 0)
                    {
                        printf("Timer case\n");
                        received = TRUE;
                        lastUpdate = 3;
                        HOAGS_ERR("Timer ack was received=%p\n", ack);
                        break;
                    }
            }   

            free(ack);

        }
        else
            break;
    }

    if(timerCount > 4 || received)
    {
        
        lastAckReceived = TRUE;
        HOAGS_DBG("\n");
        action = NULL;
        timerCount = 0;

        if(xQueueReceive(cmdQ, &action, portMAX_DELAY) != pdTRUE)
            return;
        
        if(xQueueReceive(actionIdQ, &actionId, portMAX_DELAY) != pdTRUE)
            return;

        if (lastUpdate == 1)
        {
            memset(statusmode, 0x00, sizeof(statusmode));
        }
        else if (lastUpdate == 2)
        {
            memset(statusfansp, 0x00, sizeof(statusfansp));
        }
        
        return;
    }

    
    if(!lastAckReceived && xTaskGetTickCount()-cmdSentTick >= 2000)
    {
        HOAGS_DBG("\n");
        if(actionId == SWITCHON)
            (*action)();
        else if(actionId == SWITCHOFF)
            (*action)();
        else if(actionId == LOW_SPEED)
            (*action)();
        else if(actionId == MED_SPEED)
            (*action)();
        else if(actionId == HIGH_SPEED)
            (*action)();
        else if(actionId == ACMIX)
            (*action)();
        else if(actionId == WELLNESS)
            (*action)();
        else if(actionId == ECO)
            (*action)();
        else if(actionId == REVERSE)
            (*action)();
        else if(actionId == BREEZE)
            (*action)();
        else if(actionId == FINETUNE)
            (*action)();
        else if(actionId == TIMER)
            (*action)();
        ++timerCount;
        lastAckReceived = FALSE;
    }
}
#endif

#if HAVELLS_HANDTUNED
//Suvarna: Originally done for Havells
void sendWakeword()
{
	//55aa00060005150100010122
	char havellsWwDetected[] = {0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x15, 0x01, 0x00, 0x01, 0x01, 0x22};
    displayData(&havellsWwDetected, sizeof(havellsWwDetected));
    uart_send_bytes(&superFanObj, &havellsWwDetected, sizeof(havellsWwDetected));
}
#endif

void displayDataUC(unsigned char* data, size_t len)
{
    int i = 0;
    while(len--)
    {
        HOAGS_MAN_RAW("%02x", *(data + i));
        i++;
    }
    HOAGS_MAN_RAW("\n");
}

unsigned char vdChecksum(unsigned char* bytes, size_t len)  //ksk
{
    unsigned char sum = 0;
    unsigned char checksum = 0;
    for (int i = 0; i < len; i++) 
    {
        //sum += *(bytes+i);
        sum += bytes[i];

        //printf("sum:0x%02X\n", sum);
    }

    //checksum &= sum;

    checksum = sum & 0xFF;

    //printf("Checksum:0x%02X\n", checksum);

    return checksum;

}

#if HOAGS_UART_DUMP
void initializeDumpUart()
{
    dumpUartObj.uart_idx = 1;
    serial_init(&dumpUartObj, SUPERFAN_TX, SUPERFAN_RX);//TX, RX
	serial_baud(&dumpUartObj, SUPERFAN_BAUDRATE);
	serial_format(&dumpUartObj, 8, 0, 1);

    HOAGS_DBG("%s:%p %d\n", __func__, &dumpUartObj, dumpUartObj.uart_idx);
}
#else
extern gpio_t gpio_pin1;
void initGpioPins(unsigned short pinNo)
{
    gpio_init(&gpio_pin1, pinNo);//HTAP_HDCP1
    gpio_dir(&gpio_pin1, PIN_OUTPUT);    
    gpio_mode(&gpio_pin1, PullDown);
	gpio_write(&gpio_pin1, 0);

    HOAGS_INFO("Initialized GPIO Pin=%d\n", pinNo);

    return;
}
#endif

void initialize_HDCP_Uart(HTAP_UART_Pins_St Htap_Uart_Conf)
{
    superFanObj.uart_idx = 1;
#if HTAP_MODULE
    serial_init(&superFanObj, RTK_HDCP1, RTK_HDCP0);//TX, RX
    serial_baud(&superFanObj, 9600);
#else
    serial_init(&superFanObj, Htap_Uart_Conf.Tx, Htap_Uart_Conf.Rx);//TX, RX
    serial_baud(&superFanObj, Htap_Uart_Conf.Baudrate_HDCP_u32);
    currentBaudrate = Htap_Uart_Conf.Baudrate_HDCP_u32;
#endif
    HOAGS_MAN("baudrate configured = %d\n",Htap_Uart_Conf.Baudrate_HDCP_u32);

	serial_format(&superFanObj, 8, 0, 1);

    uart_buffered_enable(&superFanObj);

    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void reInitialize_HDCP_Uart(int baudRate)
{
    if (currentBaudrate == baudRate) {
        printf("Baudrate %d already configured. Skipping reinitialization.\n", baudRate);
        return;
    }
    serial_free(&superFanObj);
    superFanObj.uart_idx = 1;

    serial_init(&superFanObj, PA_3, PA_2);//TX, RX
    serial_baud(&superFanObj, baudRate);
    HOAGS_MAN("baudrate configured = %d\n",baudRate);

	serial_format(&superFanObj, 8, 0, 1);

    uart_buffered_enable(&superFanObj);

    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    currentBaudrate = baudRate;
}

void displayData(char* data, size_t len)
{
    int i = 0;
    while(len--)
    {
        HOAGS_MAN_RAW("%02x", *(data + i));
        i++;
    }
    HOAGS_MAN_RAW("\n");
    HOAGS_MAN_RAW("\n");
}

extern gtimer_t timer_7;

void send_heartbeat()
{
    unsigned char sentquery[] = {0x55, 0xAA, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00};
    displayDataUC((unsigned char*)&sentquery, sizeof(sentquery)); 
    serial_clear_rx(&superFanObj);
    uart_send_bytes(&superFanObj,  (char*)&sentquery, sizeof(sentquery));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void sendpowervd()
{
    unsigned char sentvd[] = {0x55, 0xAA, 0x00, 0x06, 0x00, 0x06, 0x31, 0x04, 0x00, 0x02, 0x01, 0x01, 0x44};
	displayDataUC((unsigned char*)&sentvd, sizeof(sentvd)); 
	uart_send_bytes(&superFanObj,  (char*)&sentvd, sizeof(sentvd));
	HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void Initheartbeat()
{
    gtimer_init(&timer_7,TIMER4);
    printf("Timer initialized\n");
}

void vdHeartbeatTask()
{
    gtimer_start_periodical(&timer_7,5000000,(void *)sendpowervd,NULL); 
}

void sendTimeoutvd()
{
  unsigned char vdTimeout[] = {0x55, 0xAA, 0x00, 0x06, 0x00, 0x06, 0x30, 0x03, 0x00, 0x02, 0x01, 0x00, 0x41};
  displayData(&vdTimeout, sizeof(vdTimeout));
  uart_send_bytes(&superFanObj, &vdTimeout, sizeof(vdTimeout));
}

#if VERSADEVICES_SUPERFAN_IOT
void sendWakewordvd()
{
    HOAGS_INFO("\n");
	unsigned char vdWwDetected[] = {0x55, 0xAA, 0x00, 0x06, 0x00, 0x06, 0x30, 0x03, 0x00, 0x02, 0x01, 0x01, 0x42};
    displayData(&vdWwDetected, sizeof(vdWwDetected));
    uart_send_bytes(&superFanObj, &vdWwDetected, sizeof(vdWwDetected));

}
#endif
void superfan_rpm(char val)
{

    char sentvd[] = {0x55,0xAA,0X03,0X06,0X00,0X05,0x29,0x02,0x00,0x01,val,0x00};
    sentvd[11] = vdChecksum(sentvd, 11);
    displayData(&sentvd, sizeof(sentvd));
    uart_send_bytes(&superFanObj, &sentvd, sizeof(sentvd));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void superfan_low_speed()
{
	if(!UARTConfigured) 
		return;
#if UNISEMI
    unisemitest(0x00000022);
#elif HAVELLS        //ksk
    struct hdcp hdcplow ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_SPEED_CONTROL,0,0,0,0},1,0,FAN_CMD_SPEED_LOW_MEDIUM};
    swapStructEndianness(&hdcplow, sizeof(hdcplow));
    displayData(&hdcplow, sizeof(hdcplow));

    uart_send_bytes(&superFanObj, &hdcplow, sizeof(hdcplow));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#elif VERSADEVICES_SUPERFAN_IOT  
    char lowspeed[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x06 ,0x04 ,0x02 ,0x00 ,0x02 ,0x01 ,0x21, 0x35}; 
    //lowspeed[13] = vdChecksum(lowspeed, 12);
    displayData(&lowspeed, sizeof(lowspeed));
    uart_send_bytes(&superFanObj, &lowspeed, sizeof(lowspeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();

#elif POLYCAB_FAN
    struct hdcp hdcpswitchon ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_POWER_CONTROL,0,0,0,0},1,0,FAN_CMD_ON};
    swapStructEndianness(&hdcpswitchon, sizeof(hdcpswitchon));
    displayData(&hdcpswitchon, sizeof(hdcpswitchon));
    uart_send_bytes(&superFanObj, &hdcpswitchon, sizeof(hdcpswitchon));
#elif RR_KABLES
    struct hdcp hdcplow ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_SPEED_CONTROL,0,0,0,0},1,0,FAN_CMD_SPEED_LOW};
    swapStructEndianness(&hdcplow, sizeof(hdcplow));
    displayData(&hdcplow, sizeof(hdcplow));
    uart_send_bytes(&superFanObj, &hdcplow, sizeof(hdcplow));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#elif ATOMBERG_FAN
    char speed1[] = {0x7B, 0x22, 0x73, 0x70, 0x65, 0x65, 0x64, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};              
    displayData(&speed1, sizeof(speed1));
    uart_send_bytes(&superFanObj, &speed1, sizeof(speed1));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#elif VGUARD_FAN
    HOAGS_DBG("Inside VGUARD low-speed\n");
    char lowspeed[] = {0xFF ,0x0F ,0x00 ,0x24 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&lowspeed, sizeof(lowspeed));
    uart_send_bytes(&superFanObj, &lowspeed, sizeof(lowspeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#elif VGUARD_NEW_FAN
    HOAGS_DBG("Inside VGUARD_NEW 1-speed\n");
    char onespeed[] = {0xFF ,0x0B ,0x00 ,0x24 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&onespeed, sizeof(onespeed));
    uart_send_bytes(&superFanObj, &onespeed, sizeof(onespeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#else
    char switchonfan[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x16 ,0x01 ,0x00 ,0x01 ,0x01 ,0x23};
    displayData(&switchonfan, sizeof(switchonfan));
    uart_send_bytes(&superFanObj, &switchonfan, sizeof(switchonfan));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif 
}

void rr_low_med_speed()
{
    if(!UARTConfigured) 
	return;
#if RR_KABLES
    struct hdcp hdcplowmed ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_SPEED_CONTROL,0,0,0,0},1,0,FAN_CMD_SPEED_LOW_MEDIUM};
    swapStructEndianness(&hdcplowmed, sizeof(hdcplowmed));
    displayData(&hdcplowmed, sizeof(hdcplowmed));
    uart_send_bytes(&superFanObj, &hdcplowmed, sizeof(hdcplowmed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#elif ATOMBERG_FAN
    char speed2[] = {0x7B, 0x22, 0x73, 0x70, 0x65, 0x65, 0x64, 0x22, 0x3A, 0x32, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};         
    displayData(&speed2, sizeof(speed2));
    uart_send_bytes(&superFanObj, &speed2, sizeof(speed2));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#elif VGUARD_NEW_FAN
    HOAGS_DBG("Inside VGUARD_NEW 2-speed\n");
    char twospeed[] = {0xFF ,0x1F ,0x00 ,0x24 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&twospeed, sizeof(twospeed));
    uart_send_bytes(&superFanObj, &twospeed, sizeof(twospeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#endif
}

void superfan_medium_speed()
{
	if(!UARTConfigured) 
		return; 
#if UNISEMI
	unisemitest(0x0000000D); 
#elif VERSADEVICES_SUPERFAN_IOT   
    char medium_speed[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x06 ,0x04 ,0x02 ,0x00 ,0x02 ,0x01 ,0x42, 0x56};
    //medium_speed[13] = vdChecksum(medium_speed, 12);
    displayData(&medium_speed, sizeof(medium_speed));
    uart_send_bytes(&superFanObj, &medium_speed, sizeof(medium_speed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();

#elif RR_KABLES
    struct hdcp hdcplow ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_SPEED_CONTROL,0,0,0,0},1,0,FAN_CMD_SPEED_MEDIUM};
    swapStructEndianness(&hdcplow, sizeof(hdcplow));
    displayData(&hdcplow, sizeof(hdcplow));
    uart_send_bytes(&superFanObj, &hdcplow, sizeof(hdcplow));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#elif VGUARD_FAN
    HOAGS_DBG("Inside VGUARD medium-speed\n");
    char midspeed[] = {0xFF ,0x32 ,0x00 ,0x24 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&midspeed, sizeof(midspeed));
    uart_send_bytes(&superFanObj, &midspeed, sizeof(midspeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#elif ATOMBERG_FAN
    char speed3[] = {0x7B, 0x22, 0x73, 0x70, 0x65, 0x65, 0x64, 0x22, 0x3A, 0x33, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};       
    displayData(&speed3, sizeof(speed3));
    uart_send_bytes(&superFanObj, &speed3, sizeof(speed3));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#elif VGUARD_NEW_FAN
    HOAGS_DBG("Inside VGUARD_new 3-speed\n");
    char threespeed[] = {0xFF ,0x35 ,0x00 ,0x24 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&threespeed, sizeof(threespeed));
    uart_send_bytes(&superFanObj, &threespeed, sizeof(threespeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#else
    struct hdcp hdcpmedium ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_SPEED_CONTROL,0,0,0,0},1,0,FAN_CMD_SPEED_MEDIUM_HIGH}; 
    swapStructEndianness(&hdcpmedium, sizeof(hdcpmedium));
    displayData(&hdcpmedium, sizeof(hdcpmedium));
    
    uart_send_bytes(&superFanObj, &hdcpmedium, sizeof(hdcpmedium));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif
}

void rr_med_high_speed()
{
     if(!UARTConfigured) 
	return;
#if RR_KABLES
    struct hdcp hdcpmedhigh ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_SPEED_CONTROL,0,0,0,0},1,0,FAN_CMD_SPEED_MEDIUM_HIGH};
    swapStructEndianness(&hdcpmedhigh, sizeof(hdcpmedhigh));
    displayData(&hdcpmedhigh, sizeof(hdcpmedhigh));
    uart_send_bytes(&superFanObj, &hdcpmedhigh, sizeof(hdcpmedhigh));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#elif ATOMBERG_FAN
    char speed4[] = {0x7B, 0x22, 0x73, 0x70, 0x65, 0x65, 0x64, 0x22, 0x3A, 0x34, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};      
    displayData(&speed4, sizeof(speed4));
    uart_send_bytes(&superFanObj, &speed4, sizeof(speed4));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#elif VGUARD_NEW_FAN
    HOAGS_DBG("Inside VGUARD_new 4-speed\n");
    char fourspeed[] = {0xFF ,0x4A ,0x00 ,0x24 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&fourspeed, sizeof(fourspeed));
    uart_send_bytes(&superFanObj, &fourspeed, sizeof(fourspeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#endif   
}
   
void superfan_high_speed()
{
	if(!UARTConfigured) 
		return;
#if UNISEMI
	unisemitest(0x00000008);
#elif VERSADEVICES_SUPERFAN_IOT   //ksk
    char high_speed[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x06 ,0x04 ,0x02 ,0x00 ,0x02 ,0x01 ,0x63, 0x77};
    //high_speed[13] = vdChecksum(high_speed, 12);
    displayData(&high_speed, sizeof(high_speed));
    uart_send_bytes(&superFanObj, &high_speed, sizeof(high_speed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();

#elif RR_KABLES
    struct hdcp hdcplow ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_SPEED_CONTROL,0,0,0,0},1,0,FAN_CMD_SPEED_HIGH};
    swapStructEndianness(&hdcplow, sizeof(hdcplow));
    displayData(&hdcplow, sizeof(hdcplow));
    uart_send_bytes(&superFanObj, &hdcplow, sizeof(hdcplow));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#elif VGUARD_FAN
    HOAGS_DBG("Inside VGUARD high-speed\n");
    char highspeed[] = {0xFF ,0x63 ,0x00 ,0x24 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&highspeed, sizeof(highspeed));
    uart_send_bytes(&superFanObj, &highspeed, sizeof(highspeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#elif VGUARD_NEW_FAN
    HOAGS_DBG("Inside VGUARD_new 5-speed\n");
    char fivespeed[] = {0xFF ,0x59 ,0x00 ,0x24 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&fivespeed, sizeof(fivespeed));
    uart_send_bytes(&superFanObj, &fivespeed, sizeof(fivespeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#elif ATOMBERG_FAN
    char speed5[] = {0x7B, 0x22, 0x73, 0x70, 0x65, 0x65, 0x64, 0x22, 0x3A, 0x35, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};         
    displayData(&speed5, sizeof(speed5));
    uart_send_bytes(&superFanObj, &speed5, sizeof(speed5));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#else
    struct hdcp hdcphigh ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_SPEED_CONTROL,0,0,0,0},1,0,FAN_CMD_SPEED_HIGH};
    swapStructEndianness(&hdcphigh, sizeof(hdcphigh));
    displayData(&hdcphigh, sizeof(hdcphigh));
    uart_send_bytes(&superFanObj, &hdcphigh, sizeof(hdcphigh));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif
}

#if VERSADEVICES_SUPERFAN_IOT
int superfan_switchon_WA()
{
    if (switchon_workaround == 0)
    {
        if((statusfansp[11] == 0x00) && (statusmode[10] == 0x00))
        {
            HOAGS_ERR("\n");
            fpp = &superfan_medium_speed;
            xQueueSend(cmdQ, &fpp, 0);
            id = MED_SPEED;
            xQueueSend(actionIdQ, &id, 0);
        }
        else if(statusfansp[11] != 0x00)
        {
            switch(statusfansp[11])
            {
                case 0x21:
                fpp = &superfan_low_speed;
                xQueueSend(cmdQ, &fpp, 0);
                id = LOW_SPEED;
                xQueueSend(actionIdQ, &id, 0);
                break;

                case 0x42:
                fpp = &superfan_medium_speed;
                xQueueSend(cmdQ, &fpp, 0);
                id = MED_SPEED;
                xQueueSend(actionIdQ, &id, 0);
                break;

                case 0x63:
                fpp = &superfan_high_speed;
                xQueueSend(cmdQ, &fpp, 0);
                id = HIGH_SPEED;
                xQueueSend(actionIdQ, &id, 0);
                break;

                default:
                fpp = &superfan_medium_speed;
                xQueueSend(cmdQ, &fpp, 0);
                id = MED_SPEED;
                xQueueSend(actionIdQ, &id, 0);
                break;
            }
        }
        else if(statusmode[10] != 0x00)
        {
           switch(statusmode[10]) 
           {
                case 0x01:
                fpp = &superfan_Eco_Mode;
                xQueueSend(cmdQ, &fpp, 0);
                id = ECO;
                xQueueSend(actionIdQ, &id, 0);
                break;

                case 0x02:
                fpp = &superfan_acmix;
                xQueueSend(cmdQ, &fpp, 0);
                id = ACMIX;
                xQueueSend(actionIdQ, &id, 0);
                break;

                case 0x03:
                fpp = &superfan_wellness;
                xQueueSend(cmdQ, &fpp, 0);
                id = WELLNESS;
                xQueueSend(actionIdQ, &id, 0);
                break;

                case 0x04:
                fpp = &superfan_Reverse;
                xQueueSend(cmdQ, &fpp, 0);
                id = REVERSE;
                xQueueSend(actionIdQ, &id, 0);
                break;

                case 0x05:
                fpp = &superfan_Fine_tune_mode;
                xQueueSend(cmdQ, &fpp, 0);
                id = FINETUNE;
                xQueueSend(actionIdQ, &id, 0);
                break;

                case 0x06:
                fpp = &superfan_Breeze_mode;
                xQueueSend(cmdQ, &fpp, 0);
                id = BREEZE;
                xQueueSend(actionIdQ, &id, 0);
                break;

                default:
                fpp = &superfan_medium_speed;
                xQueueSend(cmdQ, &fpp, 0);
                id = MED_SPEED;
                xQueueSend(actionIdQ, &id, 0);
                break;
           }
        }
        switchon_workaround = 1;
        return 1;
    }
    return 0;
}
#endif

void superfan_switchOn()
{
	if(!UARTConfigured) 
		return;
#if VERSADEVICES_SUPERFAN_IOT
    if(superfan_switchon_WA() == 1)
    {
        return;
    }
#endif
#if UNISEMI
	unisemitest(0x00000021);
#elif VERSADEVICES_SUPERFAN_IOT   //ksk
    char switchonfan[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x06 ,0x02 ,0x01 ,0x00 ,0x02 ,0x01 ,0x01, 0x12}; 
    //switchonfan[13] = vdChecksum(switchonfan, 12);
    displayData(&switchonfan, sizeof(switchonfan));
    uart_send_bytes(&superFanObj, &switchonfan, sizeof(switchonfan));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();

#elif RR_KABLES
    struct hdcp hdcpswitchon ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_POWER_CONTROL,0,0,0,0},1,0,FAN_CMD_ON};
    swapStructEndianness(&hdcpswitchon, sizeof(hdcpswitchon));
    displayData(&hdcpswitchon, sizeof(hdcpswitchon));
    uart_send_bytes(&superFanObj, &hdcpswitchon, sizeof(hdcpswitchon));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#elif VGUARD_FAN || VGUARD_NEW_FAN
    HOAGS_DBG("Inside VGUARD switch-on\n");
    char switchOn[] = {0xFF ,0x01 ,0x00 ,0x16 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&switchOn, sizeof(switchOn));
    uart_send_bytes(&superFanObj, &switchOn, sizeof(switchOn));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#elif ATOMBERG_FAN
    char switchonfan[] = {0x7B, 0x22, 0x70, 0x6F, 0x77, 0x65, 0x72, 0x22, 0x3A, 0x74, 0x72, 0x75, 0x65, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};             
    displayData(&switchonfan, sizeof(switchonfan));
    uart_send_bytes(&superFanObj, &switchonfan, sizeof(switchonfan));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#else
    #if !HAVELLS_HANDTUNED //Suvarna: done for havells
    struct hdcp hdcpswitchon ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_POWER_CONTROL,0,0,0,0},1,0,FAN_CMD_ON};
    swapStructEndianness(&hdcpswitchon, sizeof(hdcpswitchon));
    displayData(&hdcpswitchon, sizeof(hdcpswitchon));
    uart_send_bytes(&superFanObj, &hdcpswitchon, sizeof(hdcpswitchon));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    #else
    HOAGS_INFO("Inside havells switchon\n");
    char switchonfan[] = {0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x16, 0x01, 0x00, 0x01, 0x01, 0x23};
    displayData(&switchonfan, sizeof(switchonfan));
    uart_send_bytes(&superFanObj, &switchonfan, sizeof(switchonfan));
    #endif
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif
}

void superfan_switchOff()
{
	if(!UARTConfigured) 
		return;
#if UNISEMI
	unisemitest(0x00000021);
#elif HAVELLS    //ksk
    struct hdcp hdcpswitchoff={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_POWER_CONTROL,0,0,0,0},1,0,FAN_CMD_OFF};
    swapStructEndianness(&hdcpswitchoff, sizeof(hdcpswitchoff));
    displayData(&hdcpswitchoff, sizeof(hdcpswitchoff));

    uart_send_bytes(&superFanObj, &hdcpswitchoff, sizeof(hdcpswitchoff));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#elif VERSADEVICES_SUPERFAN_IOT   //ksk
    char switchofffan[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x06 ,0x02 ,0x01 ,0x00 ,0x02 ,0x01, 0x00 ,0x11};
    //switchofffan[13] = vdChecksum(switchofffan, 12);           
    displayData(&switchofffan, sizeof(switchofffan));
    uart_send_bytes(&superFanObj, &switchofffan, sizeof(switchofffan));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();

#elif ATOMBERG_FAN
    char switchofffan[] = {0x7B, 0x22, 0x70, 0x6F, 0x77, 0x65, 0x72, 0x22, 0x3A, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};           
    displayData(&switchofffan, sizeof(switchofffan));
    uart_send_bytes(&superFanObj, &switchofffan, sizeof(switchofffan));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#elif RR_KABLES
    struct hdcp hdcpswitchon ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_POWER_CONTROL,0,0,0,0},1,0,FAN_CMD_OFF};
    swapStructEndianness(&hdcpswitchon, sizeof(hdcpswitchon));
    displayData(&hdcpswitchon, sizeof(hdcpswitchon));
    uart_send_bytes(&superFanObj, &hdcpswitchon, sizeof(hdcpswitchon));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#elif VGUARD_FAN || VGUARD_NEW_FAN
    HOAGS_DBG("Inside VGUARD switch-off\n");
    char switchOff[] = {0xFF ,0x00 ,0x00 ,0x16 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&switchOff, sizeof(switchOff));
    uart_send_bytes(&superFanObj, &switchOff, sizeof(switchOff));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#else
    #if !HAVELLS_HANDTUNED
    #if POLYCAB_FAN
    HOAGS_INFO("Inside Polycab switch-off\n");
    struct hdcp hdcplow ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_SPEED_CONTROL,0,0,0,0},1,0,FAN_CMD_SPEED_LOW}; 
    swapStructEndianness(&hdcplow, sizeof(hdcplow));
    displayData(&hdcplow, sizeof(hdcplow));
    uart_send_bytes(&superFanObj, &hdcplow, sizeof(hdcplow));
    //HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    #else
    struct hdcp switchofffan ={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_POWER_CONTROL,0,0,0,0},1,0,FAN_CMD_OFF};
    displayData(&switchofffan, sizeof(switchofffan));
    uart_send_bytes(&superFanObj, &switchofffan, sizeof(switchofffan));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    #endif
    #else
    HOAGS_INFO("Inside havells switchoff\n");
    char switchofffan[] = {0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x16, 0x01, 0x00, 0x01, 0x00, 0x22};
    displayData(&switchofffan, sizeof(switchofffan));
    uart_send_bytes(&superFanObj, &switchofffan, sizeof(switchofffan));
    #endif
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif 
}


void superfan_acmix()
{
	if(!UARTConfigured) 
		return;
#if VERSADEVICES_SUPERFAN_IOT   //ksk
    char acmix[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x02, 0x30};
    //acmix[12] = vdChecksum(acmix, 11);           
    displayData(&acmix, sizeof(acmix));
    uart_send_bytes(&superFanObj, &acmix, sizeof(acmix));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();

#else
    struct hdcp hdcpacmix={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_MODE_CONTROL,0,0,0,0},1,0,FAN_CMD_MODE_ACMIX};
    swapStructEndianness(&hdcpacmix, sizeof(hdcpacmix));
    displayData(&hdcpacmix, sizeof(hdcpacmix));
    
    uart_send_bytes(&superFanObj, &hdcpacmix, sizeof(hdcpacmix));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif
}

void superfan_acfan()    //ksk
{
	if(!UARTConfigured) 
		return;
#if VERSADEVICES_SUPERFAN_IOT   //ksk
    char acfan[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x07, 0x35};
    //acfan[12] = vdChecksum(acfan, 11);            
    displayData(&acfan, sizeof(acfan));
    uart_send_bytes(&superFanObj, &acfan, sizeof(acfan));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();
#endif
}

void superfan_wellness()
{
	if(!UARTConfigured) 
		return;
#if VERSADEVICES_SUPERFAN_IOT   //ksk
    char wellness[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x03, 0x31};
    //wellness[12] = vdChecksum(wellness, 11);
    printf("Inside wellness\n");              
    displayData(&wellness, sizeof(wellness));
    uart_send_bytes(&superFanObj, &wellness, sizeof(wellness));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();

#else
    struct hdcp hdcpwellness={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_MODE_CONTROL,0,0,0,0},1,0,FAN_CMD_MODE_ACMIX};// payload to be checked later
    swapStructEndianness(&hdcpwellness, sizeof(hdcpwellness));  
    displayData(&hdcpwellness, sizeof(hdcpwellness));
    
    uart_send_bytes(&superFanObj, &hdcpwellness, sizeof(hdcpwellness));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif
}


void superfan_Eco_Mode()
{
	if(!UARTConfigured) 
		return;
#if VERSADEVICES_SUPERFAN_IOT   //ksk
    char ecomode[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x01, 0x2F};
    //ecomode[12] = vdChecksum(ecomode, 11);            
    displayData(&ecomode, sizeof(ecomode));
    uart_send_bytes(&superFanObj, &ecomode, sizeof(ecomode));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();

#else
    struct hdcp hdcpecomode={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_MODE_CONTROL,0,0,0,0},1,0,FAN_CMD_MODE_ECO};
    swapStructEndianness(&hdcpecomode, sizeof(hdcpecomode));  
    displayData(&hdcpecomode, sizeof(hdcpecomode));
    
    uart_send_bytes(&superFanObj, &hdcpecomode, sizeof(hdcpecomode));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif
}

void superfan_Reverse()
{
	if(!UARTConfigured) 
		return;
#if VERSADEVICES_SUPERFAN_IOT   //ksk
    char Reverse[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x04, 0x32};
    //Reverse[12] = vdChecksum(Reverse, 11);              
    displayData(&Reverse, sizeof(Reverse));
    uart_send_bytes(&superFanObj, &Reverse, sizeof(Reverse));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();

#elif VGUARD_NEW_FAN
    HOAGS_DBG("Inside VGUARD reverse_on\n");
    char reverse_on[] = {0xFF ,0x01 ,0x00 ,0x1E ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&reverse_on, sizeof(reverse_on));
    uart_send_bytes(&superFanObj, &reverse_on, sizeof(reverse_on));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#else
    struct hdcp hdcpreverse={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_MODE_CONTROL,0,0,0,0},1,0,FAN_CMD_MODE_REVERSE};
    swapStructEndianness(&hdcpreverse, sizeof(hdcpreverse));
    displayData(&hdcpreverse, sizeof(hdcpreverse));
    
    uart_send_bytes(&superFanObj, &hdcpreverse, sizeof(hdcpreverse));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif
}

void reverse_off()
{
    if(!UARTConfigured) 
		return;
    #if VGUARD_NEW_FAN
    HOAGS_DBG("Inside VGUARD reverse_off\n");
    char reverse_off[] = {0xFF ,0x0 ,0x00 ,0x1E ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&reverse_off, sizeof(reverse_off));
    uart_send_bytes(&superFanObj, &reverse_off, sizeof(reverse_off));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    #endif
}
void superfan_Breeze_mode()
{
	if(!UARTConfigured) 
		return;
#if VERSADEVICES_SUPERFAN_IOT   //ksk 
    char breeze_mode[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x06, 0x34};
    //breeze_mode[12] = vdChecksum(breeze_mode, 11);               
    displayData(&breeze_mode, sizeof(breeze_mode));
    uart_send_bytes(&superFanObj, &breeze_mode, sizeof(breeze_mode));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();

#elif RR_KABLES
    struct hdcp hdcpbreeze = {0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_MODE_CONTROL,0,0,0,0},1,0,FAN_CMD_MODE_BREEZE};
    swapStructEndianness(&hdcpbreeze, sizeof(hdcpbreeze));
    displayData(&hdcpbreeze, sizeof(hdcpbreeze)); 
    uart_send_bytes(&superFanObj, &hdcpbreeze, sizeof(hdcpbreeze));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#elif VGUARD_NEW_FAN
    HOAGS_DBG("Inside VGUARD_new breeze\n");
    char breeze[] = {0xFF ,0x02 ,0x00 ,0x18 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&breeze, sizeof(breeze));
    uart_send_bytes(&superFanObj, &breeze, sizeof(breeze));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#else
    struct hdcp hdcpbreeze = {0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_MODE_CONTROL,0,0,0,0},1,0,FAN_CMD_MODE_BREEZE};
    swapStructEndianness(&hdcpbreeze, sizeof(hdcpbreeze));
    displayData(&hdcpbreeze, sizeof(hdcpbreeze));
    
    uart_send_bytes(&superFanObj, &hdcpbreeze, sizeof(hdcpbreeze));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif 
}

void rr_mob_mode()
{
    if(!UARTConfigured) 
		return;
#if RR_KABLES
    struct hdcp hdcpmob = {0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_MODE_CONTROL,0,0,0,0},1,0,FAN_CMD_MODE_MOB};
    swapStructEndianness(&hdcpmob, sizeof(hdcpmob));
    displayData(&hdcpmob, sizeof(hdcpmob)); 
    uart_send_bytes(&superFanObj, &hdcpmob, sizeof(hdcpmob));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx); 
#endif  
}

void rr_boost_mode()
{
    if(!UARTConfigured) 
		return;
#if RR_KABLES
    struct hdcp hdcpboost = {0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_MODE_CONTROL,0,0,0,0},1,0,FAN_CMD_MODE_BOOST};
    swapStructEndianness(&hdcpboost, sizeof(hdcpboost));
    displayData(&hdcpboost, sizeof(hdcpboost)); 
    uart_send_bytes(&superFanObj, &hdcpboost, sizeof(hdcpboost));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#elif ATOMBERG_FAN
    char boost[] = {0x7B, 0x22, 0x73, 0x70, 0x65, 0x65, 0x64, 0x22, 0x3A, 0x36, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};           
    displayData(&boost, sizeof(boost));
    uart_send_bytes(&superFanObj, &boost, sizeof(boost));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx); 

#elif VGUARD_NEW_FAN
    HOAGS_DBG("Inside VGUARD six-speed\n");
    char sixspeed[] = {0xFF ,0x63 ,0x00 ,0x24 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&sixspeed, sizeof(sixspeed));
    uart_send_bytes(&superFanObj, &sixspeed, sizeof(sixspeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif
}

void rr_sleep_mode()
{
    if(!UARTConfigured) 
		return;
#if RR_KABLES
    struct hdcp hdcpsleep = {0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_MODE_CONTROL,0,0,0,0},1,0,FAN_CMD_MODE_SLEEP};
    swapStructEndianness(&hdcpsleep, sizeof(hdcpsleep));
    displayData(&hdcpsleep, sizeof(hdcpsleep)); 
    uart_send_bytes(&superFanObj, &hdcpsleep, sizeof(hdcpsleep));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx); 

    #elif VGUARD_NEW_FAN
    HOAGS_DBG("Inside VGUARD_new sleep_mode\n");
    char sleep[] = {0xFF ,0x03 ,0x00 ,0x18 ,0x0C ,0x00 ,0xFF ,0xFF};
    displayData(&sleep, sizeof(sleep));
    uart_send_bytes(&superFanObj, &sleep, sizeof(sleep));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif  
}
void sleep_mode_on()
{
    #if ATOMBERG_FAN
    char sleep_on[] = {0x7B, 0x22, 0x73, 0x6C, 0x65, 0x65, 0x70, 0x22, 0x3A, 0x74, 0x72, 0x75, 0x65, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};           
    displayData(&sleep_on, sizeof(sleep_on));
    uart_send_bytes(&superFanObj, &sleep_on, sizeof(sleep_on));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    #endif
}
void sleep_mode_off()
{
    #if ATOMBERG_FAN
    char sleep_off[] = {0x7B, 0x22, 0x73, 0x6C, 0x65, 0x65, 0x70, 0x22, 0x3A, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};          
    displayData(&sleep_off, sizeof(sleep_off));
    uart_send_bytes(&superFanObj, &sleep_off, sizeof(sleep_off));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    #endif
}
void led_on()
{
    #if ATOMBERG_FAN
    char led_on[] = {0x7B, 0x22, 0x6C, 0x65, 0x64, 0x22, 0x3A, 0x74, 0x72, 0x75, 0x65, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};            
    displayData(&led_on, sizeof(led_on));
    uart_send_bytes(&superFanObj, &led_on, sizeof(led_on));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

    #elif VGUARD_NEW_FAN
    HOAGS_DBG("inisde vguard_led_on\n");
    char ledon[] = {0xFF,0x01,0x00,0x26,0x0C,0x00,0xFF,0xFF};
    displayData(&ledon,sizeof(ledon));
    uart_send_bytes(&superFanObj, &ledon, sizeof(ledon));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    #endif
}
void led_off()
{
    #if ATOMBERG_FAN
    char led_off[] = {0x7B, 0x22, 0x6C, 0x65, 0x64, 0x22, 0x3A, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};             
    displayData(&led_off, sizeof(led_off));
    uart_send_bytes(&superFanObj, &led_off, sizeof(led_off));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

    #elif VGUARD_NEW_FAN
    HOAGS_DBG("inisde vguard_led_off\n");
    char ledoff[] = {0xFF,0x00,0x00,0x26,0x0C,0x00,0xFF,0xFF};
    displayData(&ledoff,sizeof(ledoff));
    uart_send_bytes(&superFanObj, &ledoff, sizeof(ledoff));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    #endif
}
void superfan_Fine_tune_mode()
{
	if(!UARTConfigured) 
		return;
#if VERSADEVICES_SUPERFAN_IOT   //ksk 
    char Fine_tune[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x21 ,0x02 ,0x00 ,0x01 ,0x05, 0x33};
    //Fine_tune[12] = vdChecksum(Fine_tune, 11); 
    displayData(&Fine_tune, sizeof(Fine_tune));
    uart_send_bytes(&superFanObj, &Fine_tune, sizeof(Fine_tune));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();

#else
    struct hdcp hdcpfinetune={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_SPEED_CONTROL,0,0,0,0},1,0,FAN_CMD_MODE_FINETUNE};
    swapStructEndianness(&hdcpfinetune, sizeof(hdcpfinetune));
    displayData(&hdcpfinetune, sizeof(hdcpfinetune));
    uart_send_bytes(&superFanObj, &hdcpfinetune, sizeof(hdcpfinetune));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#endif
}

void superfan_normalmode()
{
    if(!UARTConfigured) 
		return;
    #if VERSADEVICES_SUPERFAN_IOT
    char normal_mode[] = {0x55, 0xAA, 0x00, 0x06, 0x04, 0x21, 0x02, 0x00, 0x00, 0x2C};
    //normal_mode[10] = vdChecksum(normal_mode, 9);
    displayData(&normal_mode, sizeof(normal_mode));
    uart_send_bytes(&superFanObj, &normal_mode, sizeof(normal_mode));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

    #elif VGUARD_NEW_FAN
    HOAGS_DBG("inside vguard_normal\n");
    char normalmode[] = {0xFF,0x01,0x00,0x18,0x0C,0x00,0xFF,0xFF};
    displayData(&normalmode,sizeof(normalmode));
    uart_send_bytes(&superFanObj, &normalmode, sizeof(normalmode));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    #endif
}

void superfan_Timer()
{
	if(!UARTConfigured) 
		return;

    #if VERSADEVICES_SUPERFAN_IOT
    const int value1 = PayloadValue;
    char timer1[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x22 ,0x02 ,0x00 ,0x01 ,value1, 0x00};
    timer1[11] = vdChecksum(timer1, 11); 
    displayData(&timer1, sizeof(timer1));
    uart_send_bytes(&superFanObj, &timer1, sizeof(timer1));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();

    struct hdcp hdcptimer={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_TIMER_CONTROL,0,0,0,0},1,0,value1};  
    swapStructEndianness(&hdcptimer, sizeof(hdcptimer));
    displayData(&hdcptimer, sizeof(hdcptimer));
    uart_send_bytes(&superFanObj, &hdcptimer, sizeof(hdcptimer));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
   #endif
}

void rr_Timer()
{
	if(!UARTConfigured) 
		return;
#if RR_KABLES
    struct hdcp hdcprrtimer={0xFF,FAN_CTRL,1,1,0,2,{FAN_CMD_TIMER_CONTROL,0,0,0,0},1,0,value};
    swapStructEndianness(&hdcprrtimer, sizeof(hdcprrtimer));
    displayData(&hdcprrtimer, sizeof(hdcprrtimer));
    uart_send_bytes(&superFanObj, &hdcprrtimer, sizeof(hdcprrtimer));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
#elif ATOMBERG_FAN
    char ch = value + '0';  // Convert integer to character
    int value2= (int) ch;  // Get the ASCII value of the character
    char led_off[] = {0x7B, 0x22, 0x74, 0x69, 0x6D, 0x65, 0x72, 0x22, 0x3A, value2, 0x2C, 0x22, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x61, 0x72, 0x74, 0x22, 0x7D};         
    displayData(&led_off, sizeof(led_off));
    uart_send_bytes(&superFanObj, &led_off, sizeof(led_off));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#elif VERSADEVICES_SUPERFAN_IOT
    const int value = PayloadValue;
    char timer[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x22 ,0x02 ,0x00 ,0x01 ,value, 0x00};
    timer[11] = vdChecksum(timer, 11); 
    displayData(&timer, sizeof(timer));
    uart_send_bytes(&superFanObj, &timer, sizeof(timer));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    cmdSentTick = xTaskGetTickCount();
#endif
}

#if 1

void vguard_timer(const int value1, int value2){
    if(!UARTConfigured) 
		return;
    HOAGS_DBG("inside vguard_timern\n");
    char timer_mode[] = {0xFF, value1, value2, 0x3E, 0x0C, 0x00, 0xFF, 0xFF};
    displayData(&timer_mode,sizeof(timer_mode));
    uart_send_bytes(&superFanObj, &timer_mode, sizeof(timer_mode));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);  
}

void buzzermuteon(){
    if(!UARTConfigured) 
		return;
    HOAGS_DBG("inisde vguard_buzzer on\n");
    char buzon[] = {0xFF,0x00,0x00,0x20,0x0C,0x00,0xFF,0xFF};
    displayData(&buzon,sizeof(buzon));
    uart_send_bytes(&superFanObj, &buzon, sizeof(buzon));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    }

void buzzermuteoff(){
    if(!UARTConfigured) 
		return;
    HOAGS_DBG("inisde vguard_buzzer off\n");
    char buzoff[] = {0xFF,0x01,0x00,0x20,0x0C,0x00,0xFF,0xFF};
    displayData(&buzoff,sizeof(buzoff));
    uart_send_bytes(&superFanObj, &buzoff, sizeof(buzoff));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void speedregulator(const int value1){
    if(!UARTConfigured) 
		return;
    HOAGS_DBG("inside vguard_speedregulator\n");
    char regspeed[] = {0XFF, value1, 0x00, 0x24, 0x0C, 0x00, 0xFF, 0xFF};
    displayData(&regspeed,sizeof(regspeed));
    uart_send_bytes(&superFanObj, &regspeed, sizeof(regspeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void breezeregulator(const int value1){
    if(!UARTConfigured) 
		return;
    HOAGS_DBG("inisde vguard_breezeregulator\n");
    char breezereg[] = {0xFF, value1, 0x00, 0x30, 0x0C, 0x00, 0xFF, 0xFF};
    displayData(&breezereg,sizeof(breezereg));
    uart_send_bytes(&superFanObj, &breezereg, sizeof(breezereg));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}
#endif

void initializeFan(uint32_t Fan_Ctrl_Pin)
{
    init_fan(fanPtr, PWM_PERIOD_FAN, Fan_Ctrl_Pin, PWM_CHANNEL_FAN);
}

void init_fan(struct fan* f, int period, int pin, int channel)
{
    HOAGS_DBG("period=%d pin=%d\n", period, pin);
    f->pwm_fan.pwm_idx = channel;
    pwmout_init(&(f->pwm_fan), pin);
    pwmout_period_us(&(f->pwm_fan), period);
}

void set_fan_speed(struct fan* f, enum fan_speed_level level)
{
#if !UNISEMI
    HOAGS_DBG("level=%d\n", level);
    pwmout_pulsewidth_us(&(f->pwm_fan), level);
    f->speed = level;
#endif
}

void step_up_fan_speed(struct fan* f)
{
    #if HAVELLS_HANDTUNED
    char currentSpeed[4];
    memset(currentSpeed, 0x00, sizeof(currentSpeed));
    getEnvItem(ENV_MODEVALUE, currentSpeed);
    int sp = atoi(currentSpeed);
    ++sp;
    if(sp == 6)
        sp = 5;
    unsigned char incSpeedPacket[] = {0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x17, 0x04, 0x00, 0x01, sp, sp+0x26};
    HOAGS_INFO("Inside havells increase speed=%d\n", sp);
    displayData(&incSpeedPacket, sizeof(incSpeedPacket));
    uart_send_bytes(&superFanObj, &incSpeedPacket, sizeof(incSpeedPacket));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    
    #else //Suvarna: for havells
    switch(f->speed)
    {
        case FAN_LOW:
            pwmout_pulsewidth_us(&(f->pwm_fan), FAN_LOW_MID);
            HOAGS_DBG("new_level=%d prev_level=%d", FAN_LOW_MID, f->speed);
            f->speed = FAN_LOW_MID;
            break;

        case FAN_LOW_MID:
            pwmout_pulsewidth_us(&(f->pwm_fan), FAN_MID);
            HOAGS_DBG("new_level=%d prev_level=%d\n", FAN_MID, f->speed);
            f->speed = FAN_MID;
            break;

        case FAN_MID:
            pwmout_pulsewidth_us(&(f->pwm_fan), FAN_MID_HIGH);
            HOAGS_DBG("new_level=%d prev_level=%d\n", FAN_MID_HIGH, f->speed);
            f->speed = FAN_MID_HIGH;
            break;

        case FAN_MID_HIGH:
            pwmout_pulsewidth_us(&(f->pwm_fan), FAN_HIGH);
            HOAGS_DBG("new_level=%d prev_level=%d\n", FAN_HIGH, f->speed);
            f->speed = FAN_HIGH;
            break;
    }
    #endif
}

void step_down_fan_speed(struct fan* f)
{
    #if HAVELLS_HANDTUNED
    char currentSpeed[4];
    memset(currentSpeed, 0x00, sizeof(currentSpeed));
    getEnvItem(ENV_MODEVALUE, currentSpeed);
    int sp = atoi(currentSpeed);
    --sp;
    if(sp == 0)
        sp = 1;
    unsigned char decSpeedPacket[] = {0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x17, 0x04, 0x00, 0x01, sp, sp+0x26};
    HOAGS_INFO("Inside havells decrease speed=%d\n", sp);
    displayData(&decSpeedPacket, sizeof(decSpeedPacket));
    uart_send_bytes(&superFanObj, &decSpeedPacket, sizeof(decSpeedPacket));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
    #else //Suvarna: for havells
    switch(f->speed)
    {
        case FAN_HIGH:
            pwmout_pulsewidth_us(&(f->pwm_fan), FAN_MID_HIGH);
            f->speed = FAN_MID_HIGH;
            break;

        case FAN_MID_HIGH:
            pwmout_pulsewidth_us(&(f->pwm_fan), FAN_MID);
            f->speed = FAN_MID;
            break;

        case FAN_MID:
            pwmout_pulsewidth_us(&(f->pwm_fan), FAN_LOW_MID);
            f->speed = FAN_LOW_MID;
            break;

        case FAN_LOW_MID:
            pwmout_pulsewidth_us(&(f->pwm_fan), FAN_LOW);
            f->speed = FAN_LOW;
            break;
    }
    #endif
}

