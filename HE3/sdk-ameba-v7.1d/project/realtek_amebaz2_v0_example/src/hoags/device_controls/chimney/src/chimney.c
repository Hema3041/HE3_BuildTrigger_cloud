#include "chimney.h"
#include "env.h"
#include "hoags_config.h"
#include "packets.h"
#include "timer_api.h"
#include "gpio_api.h"
#include "pwmout_api.h"
#include "irSensor.h"
#include "awsiot.h"

extern uint8_t FanConfigured;
extern uint8_t LightConfigured;
extern uint8_t UARTConfigured;

//for bcd to seven segment

extern void displayZero();
extern void displayOne();
extern void displayTwo();
extern void displayThree();

#if HOAGS_UART_DUMP
extern struct serial_s dumpUartObj;
#else
extern struct serial_s superFanObj;
#endif
//for leds , seven segments, autoclean, ir.
extern unsigned char LEd;
extern unsigned char Seg;
extern unsigned short int Send;
extern unsigned char irEnable;
extern signed char timer_value;
extern signed char autoCleanTimerValue;
extern unsigned char irDisable;
// for the timers
extern gtimer_t timer_5;
extern gtimer_t timer_6;
extern void switchOffChimney();
extern void timerFunc();
extern void runAtLow();
extern void alertGasLeak();
// describing the status of the chimney.
unsigned char chimneyState = 0; //0,1,2,3,4
unsigned char lightState = 0;
unsigned char autoCleanState = 0;
unsigned char indication = 0x00;
unsigned char SmokeState=0;
unsigned char buzzerStatus = 0;
gpio_t gpio_smoke;
// modes of operation
unsigned char deviceMode = 1; // default mode: auto mode.
// temp task
unsigned char ext_temp_readBuf[2] = {'\0'};
int temperature_check = 0;
int32_t prev_Gas_State;
int32_t cur_Gas_State;
int prev_Temp_State = 0;
int cur_Temp_State = 0;
//for buzzer
pwmout_t buzzerPwm;
// unsigned char buzz_count=0;
// unsigned char buzzOverflow=0;
unsigned short int testBytes = 0x00ff;
gpio_t gpio_test;
//sgpio_t gpio_buzz;//for buzzer
// for smoke task
extern unsigned short int smoke1Threshold ;
extern unsigned short int smoke2Threshold;
//For ACK to cloud
unsigned char lvprAck[26];
//unsigned char *lvprChimneyAck;

//for newly updated code
extern unsigned char displayByte;
extern unsigned char inductionByte;
extern unsigned short int writeByte;

extern uint16_t g_conn_handle;





QueueHandle_t interruptQueueHandle = NULL;
i2c_t i2cObj;






BOOL initInterruptQueue()
{
    interruptQueueHandle = xQueueCreate(MAX_INTERRUPT_COUNT, sizeof(struct hoagsIrq));

	if(interruptQueueHandle == 0)
		return FALSE;
	
	return TRUE;
}

void initI2C()
{
	HOAGS_INFO("Slave addr=0x%x\n", MBED_I2C_SLAVE_ADDR0);
	
	_memset(&i2cObj, 0x00, sizeof(i2c_t));
	i2cObj.i2c_idx = 0;
	i2c_init(&i2cObj,PA_29,PA_28);
	i2c_frequency(&i2cObj,MBED_I2C_BUS_CLK);
    HOAGS_INFO("I2C initialized\n");

}


void timerTask()
{
   
    while((!ble_download_in_progress()))
    {

        
        if(timer_value < 4 && timer_value >= 0)
        {
            //HOAGS_INFO("Timer Detection: %d\n",timer_value);
            
            switch(timer_value)
            {
                case 0: displayZero();
                        vTaskDelay(500);
                        if(timer_value < 4)
                        displayNone();
                        break;
                case 1: displayOne();
                        vTaskDelay(500);
                        if(timer_value < 4)
                        displayNone();
                        break;
                case 2: displayTwo();
                        vTaskDelay(500);
                        if(timer_value < 4)
                        displayNone();
                        break;
                case 3: displayThree();
                        vTaskDelay(500);
                        if(timer_value < 4)
                        displayNone();
                        break;
                case -1: displayZero();
                         vTaskDelay(500);
                         if(timer_value < 4)
                         displayNone();
                         break;   
                default:HOAGS_INFO("invalid timer segment\n");
            }
            
        }
        if(autoCleanTimerValue < 10 && autoCleanTimerValue >= 0)
        {
            //HOAGS_INFO("Auto Clean Timer Detection: %d\n",autoCleanTimerValue);
            
            switch(autoCleanTimerValue)
            {
                case 0: displayZero();
                        vTaskDelay(500);
                        if(autoCleanTimerValue < 10)
                        displayNone();
                        break;
                case 1: displayOne();
                        vTaskDelay(500);
                        if(autoCleanTimerValue < 10)
                        displayNone();
                        break;
                case 2: displayTwo();
                        vTaskDelay(500);
                        if(autoCleanTimerValue < 10)
                        displayNone();
                        break;
                case 3: displayThree();
                        vTaskDelay(500);
                        if(autoCleanTimerValue < 10)
                        displayNone();
                        break;
                case 4: displayFour();
                        vTaskDelay(500);
                        if(autoCleanTimerValue < 10)
                        displayNone();
                        break;
                case 5: displayFive();
                        vTaskDelay(500);
                        if(autoCleanTimerValue < 10)
                        displayNone();
                        break;
                case 6: displaySix();
                        vTaskDelay(500);
                        if(autoCleanTimerValue < 10)
                        displayNone();
                        break;
                case 7: displaySeven();
                        vTaskDelay(500);
                        if(autoCleanTimerValue < 10)
                        displayNone();
                        break;
                case 8: displayEight();
                        vTaskDelay(500);
                        if(autoCleanTimerValue < 10)
                        displayNone();
                        break;
                case 9: displayNine();
                        vTaskDelay(500);
                        if(autoCleanTimerValue < 10)
                        displayNone();
                        break;       
                case -1: displayZero();
                         vTaskDelay(500);
                         if(autoCleanTimerValue < 10)
                         displayNone();
                         break;   
                default:HOAGS_INFO("invalid autoClean timer segment\n");
            }
            
        }
        vTaskDelay(750);
    }
    HOAGS_MAN("timer Task exit\n");
    app_task_dead(interruptQueueHandle);
    vTaskDelete(NULL);
    return;
}
void smokeDetectorTask()
{
    struct hoagsIrq hisObj;
 


    PAD_PullCtrl(AD_5, GPIO_PuPd_NOPULL);
    vTaskDelay(30000);
    while((!ble_download_in_progress()))
    {
        printf("Entered smoke detected current Threshold: %d,  %d\n",smoke1Threshold,smoke2Threshold);
        mbed_adc_vol_demo(&hisObj);
        vTaskDelay(10000);
    }
    switchOffChimney();
    irDisable = 1;
    HOAGS_MAN("Smoke Task exit\n");
    app_task_dead(interruptQueueHandle);
    vTaskDelete(NULL);
    return;
}

void smokeDetected(unsigned char level)
{
    
    if(deviceMode)//0 :for mannual mode  1: for auto mode 
    {
        if(level==0)
        {        
            HOAGS_ERR("%d , %d \n",chimneyState,SmokeState);
            printf("no smoke detected\n");
            if(SmokeState==1|| SmokeState==2)
            {
                switchOffChimney();
                SmokeState=0;
            }
            else
            {
                printf("**** No Action taken from SMOKE sensor ****\n");
            }
        }
        else if(level == 1)
        {
            HOAGS_ERR("Smoke detected! - LOW \n");
            HOAGS_ERR("%d , %d \n",chimneyState,SmokeState);

            if(SmokeState != 1)
            {
           
                if(chimneyState != 2) // not equals to low speed
                {
                    if(chimneyState == 0)
                    {
                        switchOnChimney();
                        //lowSpeedLight();
                        lowSpeedChimney();
                    }
                    else
                    {
                        //lowSpeedLight();
                        lowSpeedChimney();
                    }
                    SmokeState=1;
                }
                else
                {
                    printf("**** Already in Low Speed No Action taken from SMOKE sensor ****\n");
                }
            
            }
            else
            {
                HOAGS_ERR("Smoke detected! --> already ON \n");
            }
        }
        else if(level == 2)
        {
            HOAGS_ERR("Smoke detected-high!\n");
            HOAGS_ERR("%d , %d \n",chimneyState,SmokeState);
            if(SmokeState != 2) 
            {
                if(chimneyState==0)
                {
                    switchOnChimney();
                    highSpeedChimney();
                    //highSpeedLight();
                    SmokeState=2;
                }
                else if(chimneyState < 4)
                {
                    //highSpeedLight();
                    highSpeedChimney();
                    SmokeState=2;
                }
                else
                {
                    printf("**** No Action taken from SMOKE sensor ****\n");
                }
            }
            else
            {
                printf("****Already on high speed No Action taken from SMOKE sensor ****\n");
            }
        }
    }
}

int read_temperature()
{
    //printf("INto read temp\n");
    ext_temp_readBuf[0] = 0xff;
    ext_temp_readBuf[1] = 0xff;
    i2c_read(&i2cObj,TEMP_SENSOR_I2C_ADDRESS, ext_temp_readBuf, 2,0);
    //printf("After REad\n");
    // printf("****ext_temp_readBuf = %d***\n",ext_temp_readBuf[0]);
    // printf("****ext_temp_readBuf = %d***\n",ext_temp_readBuf[1]);
    vTaskDelay(250);
    // short int raw_value = (ext_temp_readBuf[0] << 8) | ext_temp_readBuf[1];
    // printf("***********Debug 5************************\n");
    // printf("raw_value %x\r\n",raw_value);
   
    // temperature_check = (int)(raw_value >> 4) * 0.0625f;
    temperature_check = (int) ext_temp_readBuf[0];
    return temperature_check;
    //printf("***********Temperature :%d************************\n",temperature_check);
}

void tempTask()
{
    initI2C();
    //vTaskDelay(15000);
    //vTaskDelay(15000);
    while((!ble_download_in_progress()))
    {
        //printf("In tempTAsk\n");
        
        prev_Gas_State=cur_Gas_State;
        cur_Gas_State = lpg_Read();
       // printf("LPG Read done\n");
       HOAGS_ERR("LPG READ DONE\n");
        prev_Temp_State = cur_Temp_State;
        cur_Temp_State = read_temperature();
        HOAGS_ERR("temp READ DONE\n");
        HOAGS_ERR("Temperature: %d deg  LPG GAS: %d\n",temperature_check,cur_Gas_State);
        if(prev_Gas_State - cur_Gas_State >=100)
            continue;
        if((cur_Gas_State >= 500) && (prev_Gas_State >= 500))
        {
            HOAGS_ERR("FACTOR 1 : LPG DETECTED\n");
            if((cur_Temp_State - prev_Temp_State) > 5)
            {
                HOAGS_ERR("FACTOR 2 : TEMP DETECTED\n");
            }
            else if((cur_Temp_State - prev_Temp_State) < 5)
            {
                HOAGS_ERR("FACTOR 2 : TEMP DETECTION FAILED\n");
                
            }
        }
        //printf("Calling start buzzer\n");
        startBuzzer();
        //vTaskDelay(5000);
        vTaskDelay(7000);
    } 
    HOAGS_MAN("Temp Task exit\n");
    app_task_dead(interruptQueueHandle);
    vTaskDelete(NULL);
    return;   
}


void startBuzzer()
{
    unsigned char lvprChimneyAckGasLeak[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
	if(((cur_Temp_State - prev_Temp_State) < 5)   &&    (cur_Gas_State > 550 ) &&  (deviceMode))
    {
        buzzerStatus = 1;
        HOAGS_ERR("BUZZER ON\n");
        //gpio_write(&gpio_buzz, 1);
        inductionByte = inductionByte | (1<<4);
        writeByte = displayByte;
        writeByte = (displayByte<<8) | inductionByte;
        i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
        alertGasLeak();
        simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckGasLeak, NOTIFICATION);
        //lpgDetection = 1;
        //vTaskDelay(5000);
    }
    else
    {
        HOAGS_ERR("BUZZER OFF\n");
        //gpio_write(&gpio_buzz, 0);
        inductionByte = inductionByte &(~ (1<<4));
        writeByte = displayByte;
        writeByte = (displayByte<<8) | inductionByte;
        i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
        buzzerStatus = 0;
    }
}
// void gasLeakage()
// {
//     if(leakage_detected==2)
//     {
//         //buzzer will start to detect only after confirming 2 consecutive values which is more than 400.
//         startBuzzer();
//         leakage_detected = 0;
//     }
//     else
//     {
//         leakage_detected++;
//     }
// }
void sendToCloud()
{
    unsigned char lvprChimneyAckAuto[]={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char lvprChimneyAckMannual[]={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
    unsigned char lvprChimneyAckLightOn[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char lvprChimneyAckLightOff[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
    unsigned char lvprChimneyAckAutocleanOn[]  ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char lvprChimneyAckAutocleanOff[]={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
    unsigned char lvprChimneyAckPowerOff[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
    unsigned char lvprChimneyAckPowerOn[]  ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char lvprChimneyAckLowSpeed[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char lvprChimneyAckMidSpeed[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
    unsigned char lvprChimneyAckHighSpeed[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02};
    if(deviceMode)
    {
        memcpy(lvprAck,lvprChimneyAckAuto,sizeof(lvprChimneyAckAuto));
        sendAckToCloud();

    }
    else
    {
        memcpy(lvprAck,lvprChimneyAckMannual,sizeof(lvprChimneyAckMannual));
        sendAckToCloud();
    }
    if(lightState)
    {
        
        memcpy(lvprAck,lvprChimneyAckLightOn,sizeof(lvprChimneyAckLightOn));
        sendAckToCloud();
    }
    else
    {
        memcpy(lvprAck,lvprChimneyAckLightOff,sizeof(lvprChimneyAckLightOff));
        sendAckToCloud(); 
    }
    if(autoCleanState)
    {
        memcpy(lvprAck,lvprChimneyAckAutocleanOn,sizeof(lvprChimneyAckAutocleanOn));
        sendAckToCloud();
    }
    else
    {
        memcpy(lvprAck,lvprChimneyAckAutocleanOff,sizeof(lvprChimneyAckAutocleanOff));
        sendAckToCloud();
    }
    if(chimneyState == 0)
    {
        memcpy(lvprAck,lvprChimneyAckPowerOff,sizeof(lvprChimneyAckPowerOff));
        sendAckToCloud();
    }
    else if(chimneyState == 1|| chimneyState == 2)
    {
        memcpy(lvprAck,lvprChimneyAckPowerOn,sizeof(lvprChimneyAckPowerOn));
        sendAckToCloud();
        memcpy(lvprAck,lvprChimneyAckLowSpeed,sizeof(lvprChimneyAckLowSpeed));
        sendAckToCloud();
    }
    else if(chimneyState == 3)
    {
         
        
        memcpy(lvprAck,lvprChimneyAckPowerOn,sizeof(lvprChimneyAckPowerOn));
        sendAckToCloud();
        memcpy(lvprAck,lvprChimneyAckMidSpeed,sizeof(lvprChimneyAckMidSpeed));
        sendAckToCloud();
    }
    else if(chimneyState == 4)
    {
        memcpy(lvprAck,lvprChimneyAckPowerOn,sizeof(lvprChimneyAckPowerOn));
        sendAckToCloud();
        memcpy(lvprAck,lvprChimneyAckHighSpeed,sizeof(lvprChimneyAckHighSpeed));
        sendAckToCloud();
    }
}
void sendAckPackets()
{
    unsigned char lvprChimneyAckAuto[]={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char lvprChimneyAckMannual[]={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
    unsigned char lvprChimneyAckLightOn[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char lvprChimneyAckLightOff[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
    unsigned char lvprChimneyAckAutocleanOn[]  ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char lvprChimneyAckAutocleanOff[]={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
    unsigned char lvprChimneyAckPowerOff[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
    unsigned char lvprChimneyAckPowerOn[]  ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char lvprChimneyAckLowSpeed[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char lvprChimneyAckMidSpeed[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
    unsigned char lvprChimneyAckHighSpeed[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02};
    unsigned char lvprChimneyAckMicMute[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
    unsigned char lvprChimneyAckMicUnmute[] ={0xFF, 0x00, 0x71, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    if(deviceMode)
    {
        
        simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckAuto, POLLACK_FLAG);

    }
    else
    {
        
        simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckMannual, POLLACK_FLAG);
        
    }
    if(lightState)
    {
        
        simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckLightOn, POLLACK_FLAG);
        
    }
    else
    {
        
        simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckLightOff, POLLACK_FLAG);
        
    }
    if(autoCleanState)
    {
        
        simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckAutocleanOn, POLLACK_FLAG);
        
    }
    else
    {
       
        simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckAutocleanOff, POLLACK_FLAG);
        
    }
    // if(buzzerStatus)
    // {
    //     simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckGasLeak, POLLACK_FLAG);
    // }
    if(chimneyState == 0)
    {
        
        simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckPowerOff, POLLACK_FLAG);
        
    }
    else if(chimneyState == 1|| chimneyState == 2)
    {
        if(autoCleanState)
        {   
            simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckPowerOn, POLLACK_FLAG);
        }
        else
        {
            simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckPowerOn, POLLACK_FLAG);
            simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckLowSpeed, POLLACK_FLAG);
        }
        
    }
    else if(chimneyState == 3)
    {
         
        
        simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckPowerOn, POLLACK_FLAG);
        
        
        simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckMidSpeed, POLLACK_FLAG);
        
    }
    else if(chimneyState == 4)
    {
         
        
        simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckPowerOn, POLLACK_FLAG);
       
        
        simple_ble_srv_cccd_notify(g_conn_handle, lvprChimneyAckHighSpeed, POLLACK_FLAG);
        
    }

    // if (((wifi_get_join_status() == RTW_JOINSTATUS_SUCCESS) && (*(u32 *)LwIP_GetIP(0) != IP_ADDR_INVALID))) 
    // {
    //     sendToCloud();
    //     //vTaskDelay(2000);
    // }
    return;
}

void resetSevenSegment()
{
//     LEd=0x00;  
//     i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &LEd, 1, 1, I2C_TIMEOUT);
//    // displayZero();
//     LEd = 0xff;
//     i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &LEd, 1, 1, I2C_TIMEOUT);
//     LEd = 0xfe;
//     i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &LEd, 1, 1, I2C_TIMEOUT);
    deviceMode = 1;
    lightState = 0;
    // displayByte = 0xff;
    // inductionByte = 0xff;
    // writeByte = displayByte;
    // writeByte = (displayByte<<8)|(inductionByte);
    // i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
    //DelayMs(200);
    displayByte = 0xFF;
    inductionByte = 0x0f;
    writeByte = displayByte;
    writeByte = (displayByte<<8)|(inductionByte);
    i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
    DelayMs(100);
    displayByte = 0x7e;
    inductionByte = 0x0f;
    writeByte = displayByte;
    writeByte = (displayByte<<8)|(inductionByte);
    i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
}

void interruptTask()
{
    initI2C();
    //initGpioPins(PA_21);
    initGpioBcd();
    resetSevenSegment();
    DelayMs(1200);
	mbed_gpio_pulse_measure();
    initCapTouchPins();


    if(initInterruptQueue() == FALSE)
    {
        HOAGS_ERR("Error initializing queue for interrupts!!!\n");
        return;
    }

    struct hoagsIrq hiObj;
    
    while((!ble_download_in_progress()))//Suvarna: receive action here
    {
        
        HOAGS_ERR("Trying to read queue!\n");
        memset(&hiObj, 0x00, sizeof(struct hoagsIrq));
        if(xQueueReceive(interruptQueueHandle, &hiObj, portMAX_DELAY) == pdTRUE)
        {	
            HOAGS_INFO("Received, devtype=%d action=%d\n", hiObj.devType, hiObj.action);
            
        }
        else
        {
            HOAGS_INFO("Queue is empty!\n");
            vTaskDelay(200);
            continue;
        }

        if((hiObj.action != HOAGSIRQ_CHIMNEY_POWEROFF_IR) && (hiObj.action != HOAGSIRQ_CHIMNEY_NO_SMOKE_DETECTED) && (hiObj.action != HOAGSIRQ_CHIMNEY_KEY4_PRESSED) && (hiObj.action != HOAGSIRQ_CHIMNEY_LIGHTON) && (hiObj.action != HOAGSIRQ_CHIMNEY_LIGHTOFF) && (hiObj.action != HOAGSIRQ_CHIMNEY_KEY1_PRESSED) && (hiObj.action != HOAGSIRQ_CHIMNEY_KEY2_PRESSED) && (hiObj.action != HOAGSIRQ_CHIMNEY_IR_LOCK) && (hiObj.action != HOAGSIRQ_CHIMNEY_MODE_AUTO) && (hiObj.action != HOAGSIRQ_CHIMNEY_MODE_MANNUAL) && (hiObj.action != HOAGSIRQ_CHIMNEY_SMOKE_DETECTED1) && (hiObj.action != HOAGSIRQ_CHIMNEY_SMOKE_DETECTED2))
        {
            HOAGS_ERR("STOPPING IR TIMER \n");
            timer_value = 4;
            //printf("Stopping ir off timer\n");
            gtimer_stop(&timer_5);
            DelayMs(10);
            
        }
        if(hiObj.action != HOAGSIRQ_CHIMNEY_KEY5_PRESSED && (hiObj.action != HOAGSIRQ_CHIMNEY_NO_SMOKE_DETECTED) && (hiObj.action != HOAGSIRQ_CHIMNEY_KEY4_PRESSED) && (hiObj.action != HOAGSIRQ_CHIMNEY_LIGHTON) && (hiObj.action != HOAGSIRQ_CHIMNEY_LIGHTOFF) && (hiObj.action != HOAGSIRQ_CHIMNEY_KEY1_PRESSED) && (hiObj.action != HOAGSIRQ_CHIMNEY_KEY2_PRESSED)&& (hiObj.action != HOAGSIRQ_CHIMNEY_IR_LOCK) && (hiObj.action != HOAGSIRQ_CHIMNEY_MODE_MANNUAL) && (hiObj.action != HOAGSIRQ_CHIMNEY_MODE_AUTO) && (hiObj.action != HOAGSIRQ_CHIMNEY_SMOKE_DETECTED1) && (hiObj.action != HOAGSIRQ_CHIMNEY_SMOKE_DETECTED2))
        {
            HOAGS_ERR("STOPPING AUTOCLEAN TIMER\n");
            gtimer_stop(&timer_6);
           //HOAGS_INFO("Stopping autoclean timer\n");
            autoCleanState = 0;
            autoCleanTimerValue = 10;
        }

    //    if(deviceMode)
    //     {
    //         // if in auto mode and if any changes came through touch and localvoice or ble, it turns into mannual mode
    //         if(hiObj.action != HOAGSIRQ_CHIMNEY_NO_SMOKE_DETECTED && hiObj.action != HOAGSIRQ_CHIMNEY_SMOKE_DETECTED2 && hiObj.action != HOAGSIRQ_CHIMNEY_SMOKE_DETECTED1 && hiObj.action != HOAGSIRQ_CHIMNEY_KEY1_PRESSED)
    //         {
    //             deviceMode = 0;
    //             SmokeState = 0;
    //             // LEd = LEd | 0x01;
    //             // i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &LEd, 1, 1, I2C_TIMEOUT);

    //         }
    //     }

        //Suvarna: For now consider this is only for Chimney
        switch(hiObj.action)
        {
            case HOAGSIRQ_CHIMNEY_POWERON:
                switchOnChimney();
                //deviceMode = 1;
                break;
            
            case HOAGSIRQ_CHIMNEY_POWEROFF:
                switchOffChimney();
                //deviceMode = 0;
                break;
            
            case HOAGSIRQ_CHIMNEY_POWERON_IR:
                if(chimneyState == 0)
                    switchOnChimney();
                else if(chimneyState == 4 )
                {
                    // if(lightState)
                    //     switchOnLightChimney();
                    lowSpeedChimney();
                }                
                else if(chimneyState == 2 || chimneyState == 1 )
                {
                    // if(lightState)
                    //     switchOnLightChimney();
                    
                    midSpeedChimney();
                }
                else if(chimneyState == 3)
                {
                    // if(lightState)
                    //     switchOnLightChimney();
                    highSpeedChimney();
                }
                break;

            case HOAGSIRQ_CHIMNEY_POWEROFF_IR:
                if(timer_value == 4)
                {
                    if(chimneyState > 0)
                    {
                        timer_value--;
                        gtimer_start_periodical(&timer_5,1000000*60,(void *)timerFunc,NULL);
                        printf("Timer Started\n");
                    }
                }
                else
                {
                    timer_value=4;
                    gtimer_stop(&timer_5);
                    switchOffChimney();
                }
                break;
            
            case HOAGSIRQ_CHIMNEY_POWERON_LV:
                switchOnChimney();
                //deviceMode = 1;
                break;

            case HOAGSIRQ_CHIMNEY_POWEROFF_LV:
                switchOffChimney();
                //deviceMode = 0;
                break;

            case HOAGSIRQ_CHIMNEY_LIGHTON:// just turn on light dont consider speed its running
                    lightState = 1;
                    switchOnLightChimney();
                    // switch(chimneyState)
                    // {
                    //     case 0:switchOnLightChimney();
                    //             break;
                    //     case 1: if(autoCleanState)
                    //             {
                    //                 switchOnLightChimney();
                    //             }
                    //             else
                    //             {
                    //                 switchOnChimney();
                    //                 HOAGS_ERR("LIGHT Off IN THE SWITCHON CHIMNEY\n");
                    //             }
                    //             break;
                    //     case 2: lowSpeedLight();
                    //             break;
                    //     case 3: midSpeedLight();
                    //             break;
                    //     case 4: highSpeedLight();
                    //             break;
                    //     default: HOAGS_INFO("Unable to find the State\n");
                    // }
                    
                break;

            case HOAGSIRQ_CHIMNEY_LIGHTOFF://just turn off the light dont consider the speed
                lightState = 0;
                switchOffLightChimney();
                // switch(chimneyState)
                //     {
                //         case 0:switchOffChimney();
                //                 break;
                //         case 1: if(autoCleanState)
                //                 {
                //                     switchOffChimney();
                //                     autoClean();
                //                 }
                //                 else
                //                 {
                //                     HOAGS_ERR("LIGHT ON IN THE SWITCHON CHIMNEY\n");
                //                     lowSpeedChimney();
                //                 }
                //                 break;
                //         case 2: lowSpeedChimney();
                //                 break;
                //         case 3: midSpeedChimney();
                //                 break;
                //         case 4: highSpeedChimney();
                //                 break;
                //         default: HOAGS_INFO("Unable to find the State\n");
                //     }
                
                break;

            case HOAGSIRQ_CHIMNEY_FAN_LOW:
                    lowSpeedChimney();
                break;

            case HOAGSIRQ_CHIMNEY_FAN_MEDIUM:
                    midSpeedChimney();
                break;

            case HOAGSIRQ_CHIMNEY_FAN_HIGH:
                    highSpeedChimney();
                break;
            
            case HOAGSIRQ_CHIMNEY_TIMER_4MINS:
                break;

            case HOAGSIRQ_CHIMNEY_TIMER_10MINS:
                break;

            case HOAGSIRQ_CHIMNEY_AUTOCLEAN:
                if(autoCleanState == 0)
                {
                    autoClean();
                    autoCleanState = 1;
                    if(autoCleanTimerValue == 10)
                    {
                        autoCleanTimerValue--;
                    }
                    gtimer_start_periodical(&timer_6,1000000*60,(void *)runAtLow,NULL);
                    HOAGS_INFO("AutoClean timer Start\n");
                }
                else
                {
                    switchOffChimney();
                    autoCleanState = 0;
                    irDisable = 1;
                    autoCleanTimerValue = 10;
                    gtimer_stop(&timer_6);
                }
                break;
                
            
            case HOAGSIRQ_CHIMNEY_KEY1_PRESSED:
                // if(lightState)
                //     lowSpeedLight();
                // else
                //     lowSpeedChimney();
                // break;
                if(deviceMode)
                {
                    deviceMode = 0;
                    HOAGS_ERR("MANNUAL MODE ON\n");
                    
                    // LEd = LEd | 0x01;
                    displayByte = displayByte | 0x01;
                    inductionByte = inductionByte | (1<<4);
                    writeByte = displayByte;
                    writeByte = (displayByte << 8) | inductionByte;
                    i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
                    inductionByte = inductionByte & (~(1<<4));
                    writeByte = displayByte;
                     writeByte = (displayByte<<8) | inductionByte;
                    DelayMs(180);
                    i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
                    // gpio_write(&gpio_buzz,1);  
                    // DelayMs(200);
                    // gpio_write(&gpio_buzz,0);
                }
                else
                {
                    deviceMode = 1;
                    HOAGS_ERR("AUTO MODE ON\n");
                    displayByte = displayByte & (~(1<<0));
                    inductionByte = inductionByte | (1<<4);
                    writeByte = displayByte;
                    writeByte = (displayByte << 8) | inductionByte;
                    i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
                    inductionByte = inductionByte & (~(1<<4));
                    writeByte = displayByte;
                    writeByte = (displayByte<<8) | inductionByte;
                    DelayMs(180);
                    i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT); 
                    
                    // LEd = LEd & 0xfe;
                    // i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &LEd, 1, 1, I2C_TIMEOUT);
                    // gpio_write(&gpio_buzz,1);  
                    // DelayMs(200);
                    // gpio_write(&gpio_buzz,0);
                }
                break;

            case HOAGSIRQ_CHIMNEY_KEY2_PRESSED:
                {
                    unsigned char micStatusLivpure[2];
                    memset(micStatusLivpure,'\0',sizeof(micStatusLivpure));
                    getEnvItem(ENV_MICMUTE,micStatusLivpure);
                    printf("%s is the mic Mute status of livpure\n",micStatusLivpure);
                    if(micStatusLivpure[0] == '1')
                    {
                        
                        HOAGS_ERR("MIC UNMUTE\n");
                        // LEd = LEd | 0x04;
                        controlMicLivpure(0);
                        // irDisable = 1;
                        // vTaskDelay(100);
                        // irDisable = 0;
                        displayByte = displayByte |(1<<1);
                        inductionByte = inductionByte | (1<<4);
                        writeByte = displayByte;
                        writeByte = (displayByte << 8) | inductionByte;
                        i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
                        inductionByte = inductionByte & (~(1<<4));
                        writeByte = displayByte;
                        writeByte = (displayByte<<8) | inductionByte;
                        DelayMs(180);
                        i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
                        
                        
                    }
                    else
                    {
                        
                        HOAGS_ERR("MIC MUTE\n");
                        controlMicLivpure(1);
                        // irDisable = 1;
                        // vTaskDelay(100);
                        // irDisable = 0;
                        displayByte = displayByte & (~(1<<1));
                        inductionByte = inductionByte | (1<<4);
                        writeByte = displayByte;
                        writeByte = (displayByte << 8) | inductionByte;
                        i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
                        inductionByte = inductionByte & (~(1<<4));
                        writeByte = displayByte;
                        writeByte = (displayByte<<8) | inductionByte;
                        DelayMs(180);
                        i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
                        
                    }
                    // gpio_write(&gpio_buzz,1);  
                    // DelayMs(200);
                    // gpio_write(&gpio_buzz,0);
                    
                
                }

                
                break;

            case HOAGSIRQ_CHIMNEY_KEY3_PRESSED:
                // if(lightState)
                //     highSpeedLight();
                // else
                //     highSpeedChimney();
                // break;
                if(chimneyState == 0  || chimneyState == 4)
                {
                    lowSpeedChimney();
                }
                else if(chimneyState == 2 || chimneyState == 1)
                {
                    midSpeedChimney();
                }
                else if(chimneyState == 3)
                {
                    highSpeedChimney();
                }
                
                // if(lightState)
                // {
                //     if(chimneyState == 0 || chimneyState == 1 || chimneyState == 4)
                //     {
                //         lowSpeedLight();
                //     }
                //     else if(chimneyState == 2)
                //     {
                //         midSpeedLight();
                //     }
                //     else if(chimneyState == 3)
                //     {
                //         highSpeedLight();
                //     }
                // }
                // else
                // {
                //     if(chimneyState == 0 || chimneyState == 1 || chimneyState == 4)
                //     {
                //         lowSpeedChimney();
                //     }
                //     else if(chimneyState == 2)
                //     {
                //         midSpeedChimney();
                //     }
                //     else if(chimneyState == 3)
                //     {
                //         highSpeedChimney();
                //     }
                // }
                break;

            case HOAGSIRQ_CHIMNEY_KEY4_PRESSED:// just according to the light state turn on or off the light
                if(lightState == 0)
                {
                    switchOnLightChimney();
                    // switch(chimneyState)
                    // {
                    //     case 0:switchOnLightChimney();
                    //             break;
                    //     case 1: if(autoCleanState)
                    //             {
                    //                 switchOnLightChimney();
                    //             }
                    //             else
                    //             {
                    //                 switchOnChimney();
                    //                 HOAGS_ERR("LIGHT Off IN THE SWITCHON CHIMNEY\n");
                    //             }
                    //             break;
                    //     case 2: lowSpeedLight();
                    //             break;
                    //     case 3: midSpeedLight();
                    //             break;
                    //     case 4: highSpeedLight();
                    //             break;
                    //     default: HOAGS_INFO("Unable to find the State\n");
                   
                    lightState = 1;
                }
                else
                {
                    switchOffLightChimney();
                    // switch(chimneyState)
                    // {
                    //     case 0:switchOffChimney();
                    //             break;
                    //     case 1: if(autoCleanState)
                    //             {
                    //                 switchOffChimney();
                    //                 autoClean();
                    //             }
                    //             else
                    //             {
                    //                 HOAGS_ERR("LIGHT ON IN THE SWITCHON CHIMNEY\n");
                    //                 lowSpeedChimney();
                    //             }
                    //             break;
                    //     case 2: lowSpeedChimney();
                    //             break;
                    //     case 3: midSpeedChimney();
                    //             break;
                    //     case 4: highSpeedChimney();
                    //             break;
                    //     default: HOAGS_INFO("Unable to find the State\n");
                    // }
                    lightState = 0;
                }
                
                break;

            case HOAGSIRQ_CHIMNEY_KEY5_PRESSED:// just turn on relay 4 and autoclean led with power on
                if(autoCleanState == 0)
                {
                    autoClean();
                    autoCleanState = 1;
                    if(autoCleanTimerValue == 10)
                    {
                        autoCleanTimerValue--;
                    }
                    gtimer_start_periodical(&timer_6,1000000*60,(void *)runAtLow,NULL);
                    HOAGS_INFO("AutoClean timer Start\n");
                }
                else
                {
                    switchOffChimney();
                    autoCleanState = 0;
                    irDisable = 1;
                    autoCleanTimerValue = 10;
                    gtimer_stop(&timer_6);
                }
                break;

            case HOAGSIRQ_CHIMNEY_KEY6_PRESSED:
                HOAGS_ERR("Entered Chimney state = %d\n",chimneyState);
                if(chimneyState == 0)
                    switchOnChimney();
                else if(chimneyState >= 1)
                {
                    switchOffChimney();
                }
                break;
            
            case HOAGSIRQ_CHIMNEY_SMOKE_DETECTED1:
                smokeDetected(1);
                break;
            
            case HOAGSIRQ_CHIMNEY_SMOKE_DETECTED2:
                smokeDetected(2);
                break;

            case HOAGSIRQ_CHIMNEY_NO_SMOKE_DETECTED:
                smokeDetected(0);
                break;

            case HOAGSIRQ_CHIMNEY_MODE_AUTO:
                //deviceMode = !deviceMode;
                deviceMode = 1;
                // LEd = LEd & 0xfe;
                // i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &LEd, 1, 1, I2C_TIMEOUT);
                // gpio_write(&gpio_buzz,1);  
                // DelayMs(200);
                // gpio_write(&gpio_buzz,0);
                HOAGS_ERR("AUTO MODE ON\n");
                displayByte = displayByte & (~(1<<0));
                inductionByte = inductionByte | (1<<4);
                writeByte = displayByte;
                writeByte = (displayByte << 8) | inductionByte;
                i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
                inductionByte = inductionByte & (~(1<<4));
                writeByte = displayByte;
                writeByte = (displayByte<<8) | inductionByte;
                DelayMs(180);
                i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT); 
                if(deviceMode)
                {
                    HOAGS_ERR("*********AUTO MODE********\n");
                }
                // else
                // {
                //     HOAGS_ERR("*********MANNUAL MODE*******\n");
                // }
                break;

            case HOAGSIRQ_CHIMNEY_MODE_MANNUAL:
                //deviceMode = !deviceMode;
                deviceMode = 0;
                HOAGS_ERR("MANNUAL MODE ON\n");
                
                // LEd = LEd | 0x01;
                displayByte = displayByte | 0x01;
                inductionByte = inductionByte | (1<<4);
                writeByte = displayByte;
                writeByte = (displayByte << 8) | inductionByte;
                i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
                inductionByte = inductionByte & (~(1<<4));
                writeByte = displayByte;
                        writeByte = (displayByte<<8) | inductionByte;
                DelayMs(180);
                i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
                if(deviceMode)
                {
                    HOAGS_ERR("*********AUTO MODE********\n");
                }
                else
                {
                    HOAGS_ERR("*********MANNUAL MODE*******\n");
                }
                break;
            
            case HOAGSIRQ_CHIMNEY_IR_LOCK:
                irEnable = !irEnable;
                // i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &indication, 1, 1, I2C_TIMEOUT);
                // gpio_write(&gpio_buzz,1);
                // DelayMs(350);
                // LEd = LEd&0xff;
                // i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &LEd, 1, 1, I2C_TIMEOUT);
                // gpio_write(&gpio_buzz,0);
                indication = displayByte & (1<<6);
                inductionByte = inductionByte | (1<<4);
                writeByte = indication;
                writeByte = (indication << 8) | inductionByte;
                i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
                inductionByte = inductionByte & (~(1<<4));
                writeByte = displayByte;
                        writeByte = (displayByte<<8) | inductionByte;
                DelayMs(250);
                i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
                if(irEnable)
                {
                    HOAGS_INFO("*********UNLOCK MODE********\n");
                }
                else
                {
                    HOAGS_INFO("*********LOCK MODE*******\n");
                }
            default:
                HOAGS_ERR("Unknown action=%d\n", hiObj.action);
                break;

        }
        sendAckPackets();
        //sendToCloud();
        irDisable = 1;
        vTaskDelay(100);
        irDisable = 0;
    }
    switchOffChimney();
    irDisable = 1;
    displayByte = 0x7e;
    inductionByte = 0x0f;
    writeByte = displayByte;
    writeByte = (displayByte<<8)|(inductionByte);
    i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
    HOAGS_MAN("Interrupt Task exit\n");
    app_task_dead(interruptQueueHandle);
    vTaskDelete(NULL);
    return;

}

void chimney_PowerOn(){
    char switchon[]={0x02, 0x2E, 0xE0, 0x00, 0x12, 0x7B, 0x22, 0x50, 0x6F, 0x77, 0x65, 0x72, 0x43, 0x6E, 0x74, 0x72, 0x6C, 0x22, 0x3A, 0x22, 0x31, 0x22, 0x7D, 0x4C, 0xAA, 0x01, 0x0B, 0xB8, 0x00, 0x2A, 0x1A, 0x1E};
    displayDataUC((char*)&switchon, sizeof(switchon));
    uart_send_bytes(&superFanObj, (char*)&switchon, sizeof(switchon));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);              
}

void chimney_PowerOff(){
    char switchoff[]={0x02, 0x2E, 0xE0, 0x00, 0x12, 0x7B, 0x22, 0x50, 0x6F, 0x77, 0x65, 0x72, 0x43, 0x6E, 0x74, 0x72, 0x6C, 0x22, 0x3A, 0x22, 0x30, 0x22, 0x7D, 0x1D, 0x6A, 0x01, 0x0B, 0xB8, 0x00, 0x2A, 0x1A, 0x1E};
    displayDataUC((char*)&switchoff, sizeof(switchoff));
    uart_send_bytes(&superFanObj, (char*)&switchoff, sizeof(switchoff));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void chimney_low_speed_fan(){
    char lowspeed[]={0x02, 0x2E, 0xE0, 0x00, 0x16, 0x7B, 0x22, 0x46, 0x61, 0x6E, 0x54, 0x72, 0x67, 0x74, 0x53, 0x70, 0x65, 0x65, 0x64, 0x22, 0x3A, 0x22, 0x31, 0x30, 0x30, 0x22, 0x7D, 0x55, 0xCB, 0x01, 0x0B, 0xB8, 0x00, 0x2E, 0x1B, 0xDD};
    displayDataUC((char*)&lowspeed, sizeof(lowspeed));
    uart_send_bytes(&superFanObj, (char*)&lowspeed, sizeof(lowspeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void chimney_medium_speed_fan(){
    char mediumspeed[]={0x02, 0x2E, 0xE0, 0x00, 0x16, 0x7B, 0x22, 0x46, 0x61, 0x6E, 0x54, 0x72, 0x67, 0x74, 0x53, 0x70, 0x65, 0x65, 0x64, 0x22, 0x3A, 0x22, 0x32, 0x35, 0x30, 0x22, 0x7D, 0x11, 0x07, 0x01, 0x0B, 0xB8, 0x00, 0x2E, 0x1B, 0xDD};
    displayDataUC((char*)&mediumspeed, sizeof(mediumspeed));
    uart_send_bytes(&superFanObj, (char*)&mediumspeed, sizeof(mediumspeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void chimney_high_speed_fan(){
    char highspeed[]={0x02, 0x2E, 0xE0, 0x00, 0x16, 0x7B, 0x22, 0x46, 0x61, 0x6E, 0x54, 0x72, 0x67, 0x74, 0x53, 0x70, 0x65, 0x65, 0x64, 0x22, 0x3A, 0x22, 0x34, 0x30, 0x30, 0x22, 0x7D, 0x99, 0xCB, 0x01, 0x0B, 0xB8, 0x00, 0x2E, 0x1B, 0xDD};
    displayDataUC((char*)&highspeed, sizeof(highspeed));
    uart_send_bytes(&superFanObj, (char*)&highspeed, sizeof(highspeed));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void chimney_turbo_speed_fan(){
    char turbo[]={0x02, 0x2E, 0xE0, 0x00, 0x16, 0x7B, 0x22, 0x46, 0x61, 0x6E, 0x54, 0x72, 0x67, 0x74, 0x53, 0x70, 0x65, 0x65, 0x64, 0x22, 0x3A, 0x22, 0x35, 0x30, 0x30, 0x22, 0x7D, 0xA4, 0x0B, 0x01, 0x0B, 0xB8, 0x00, 0x2E, 0x1B, 0xDD};
    displayDataUC((char*)&turbo, sizeof(turbo));
    uart_send_bytes(&superFanObj, (char*)&turbo, sizeof(turbo));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void chimney_led_on(){
    char led_on[]={0x02, 0x2E, 0xE0, 0x00, 0x10, 0x7B, 0x22, 0x4C, 0x65, 0x64, 0x43, 0x6E, 0x74, 0x72, 0x6C, 0x22, 0x3A, 0x22, 0x31, 0x22, 0x7D, 0x05, 0x88, 0x01, 0x0B, 0xB8, 0x00, 0x28, 0x9B, 0xDF};
    displayDataUC((char*)&led_on, sizeof(led_on));
    uart_send_bytes(&superFanObj, (char*)&led_on, sizeof(led_on));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void chimney_led_off(){
    char led_off[]={0x02, 0x2E, 0xE0, 0x00, 0x10, 0x7B, 0x22, 0x4C, 0x65, 0x64, 0x43, 0x6E, 0x74, 0x72, 0x6C, 0x22, 0x3A, 0x22, 0x30, 0x22, 0x7D, 0x54, 0x48, 0x01, 0x0B, 0xB8, 0x00, 0x28, 0x9B, 0xDF};
    displayDataUC((char*)&led_off, sizeof(led_off));
    uart_send_bytes(&superFanObj, (char*)&led_off, sizeof(led_off));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void chimney_autoclean_on(){
    char autoclean_on[]={0x02, 0x2E, 0xE0, 0x00, 0x0E, 0x7B, 0x22, 0x41, 0x75, 0x74, 0x6F, 0x43, 0x6C, 0x22, 0x3A, 0x22, 0x31, 0x22, 0x7D, 0xA8, 0x79, 0x01, 0x0B, 0xB8, 0x00, 0x23, 0xDA, 0x18};
    displayDataUC((char*)&autoclean_on, sizeof(autoclean_on));
    uart_send_bytes(&superFanObj, (char*)&autoclean_on, sizeof(autoclean_on));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void chimney_autoclean_off(){
    char autoclean_off[]={0x02, 0x2E, 0xE0, 0x00, 0x0E, 0x7B, 0x22, 0x41, 0x75, 0x74, 0x6F, 0x43, 0x6C, 0x22, 0x3A, 0x22, 0x30, 0x22, 0x7D, 0xF9, 0xB9, 0x01, 0x0B, 0xB8, 0x00, 0x23, 0xDA, 0x18};
    displayDataUC((char*)&autoclean_off, sizeof(autoclean_off));
    uart_send_bytes(&superFanObj, (char*)&autoclean_off, sizeof(autoclean_off));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void read_status(){
    char readStatus[]={0x01, 0x07, 0xD0, 0x00, 0x06, 0x99, 0x4F};
    displayDataUC((char*)&readStatus, sizeof(readStatus));
    uart_send_bytes(&superFanObj, (char*)&readStatus, sizeof(readStatus));
    HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}
