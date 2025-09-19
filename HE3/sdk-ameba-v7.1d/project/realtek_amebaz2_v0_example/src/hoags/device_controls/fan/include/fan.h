#ifndef __HOAGS_FAN_CONTROLS_H__
#define __HOAGS_FAN_CONTROLS_H__

#include "pwmout_api.h"
#include "objects.h"
//for ble controls
enum FAN_CMD {
	FAN_CMD_POWER_CONTROL, //total level = 2, level[0] = fan_power_control, payload[0] = fan_cmd_on
	FAN_CMD_INCREASE_SPEED,//total level = 2, level[0] = fan_inc_speed, no need to check payload here
	FAN_CMD_DECREASE_SPEED,
	FAN_CMD_MODE_CONTROL,
	FAN_CMD_TIMER_CONTROL,
	FAN_CMD_SPEED_CONTROL,
	FAN_CMD_TIMER_SPEED,
	FAN_CMD_RPM_CONTROL,
	FAN_CMD_SPEED_REG_CONTROL,
	FAN_CMD_BREEZE_CONTROL,
	FAN_CMD_LED_CONTROL,
	FAN_CMD_BUZZER_CONTROL,
	FAN_CMD_REVERSE_CONTROL
};

enum FAN_CMD_POWER {
	FAN_CMD_ON,
	FAN_CMD_OFF
};
#if RR_KABLES
enum FAN_CMD_MODE {
	FAN_CMD_MODE_ACMIX = 0,
	FAN_CMD_MODE_WELLNESS,
	FAN_CMD_MODE_ECO,
	FAN_CMD_MODE_REVERSE,
	FAN_CMD_MODE_BREEZE,
	FAN_CMD_MODE_FINETUNE,
	FAN_CMD_ACFAN,
	FAN_CMD_MODE_MOB,
	FAN_CMD_MODE_BOOST,
	FAN_CMD_MODE_SLEEP = 9,
	FAN_CMD_MODE_SLEEP_ON,
	FAN_CMD_MODE_SLEEP_OFF,
	FAN_CMD_MODE_LED_ON,
	FAN_CMD_MODE_LED_OFF,
	FAN_CMD_MODE_NORMAL	//Suvarna: This is not used in RR_KABLES. Need to inform RR_Kable MCU guy to make changes. Note: Remove macro when done               
};
#else
enum FAN_CMD_MODE {
	FAN_CMD_MODE_ACMIX = 0,
	FAN_CMD_MODE_WELLNESS,
	FAN_CMD_MODE_ECO,
	FAN_CMD_MODE_REVERSE,
	FAN_CMD_MODE_BREEZE,
	FAN_CMD_MODE_FINETUNE,
	FAN_CMD_ACFAN,
	FAN_CMD_MODE_NORMAL,
	FAN_CMD_MODE_SLEEP = 9,
	FAN_CMD_MODE_MOB,
	FAN_CMD_MODE_BOOST,
	FAN_CMD_MODE_SLEEP_ON,
	FAN_CMD_MODE_SLEEP_OFF,
	FAN_CMD_MODE_LED_ON,
	FAN_CMD_MODE_LED_OFF           
};
#endif
enum FAN_CMD_TIMER {
	FAN_CMD_TIMER_NONE,
	FAN_CMD_TIMER_ONE,
	FAN_CMD_TIMER_TWO,
	FAN_CMD_TIMER_THREE,
	FAN_CMD_TIMER_FOUR,
	FAN_CMD_TIMER_FIVE,
	FAN_CMD_TIMER_SIX
};

enum FAN_CMD_SPEED {
	FAN_CMD_SPEED_LOW,  
	FAN_CMD_SPEED_LOW_MEDIUM,  
	FAN_CMD_SPEED_MEDIUM, 
	FAN_CMD_SPEED_MEDIUM_HIGH, 
	FAN_CMD_SPEED_HIGH
};


enum FAN_CMD_LED {
	FAN_CMD_MODE_VGUARD_LED_ON,  
	FAN_CMD_MODE_VGUARD_LED_OFF
};
enum FAN_CMD_BUZZER {
	FAN_CMD_MODE_VGUARD_BUZZER_ON,  
	FAN_CMD_MODE_VGUARD_BUZZER_OFF
};
enum FAN_CMD_REVERSE {
	FAN_CMD_MODE_VGUARD_REVERSE_ON,  
	FAN_CMD_MODE_VGUARD_REVERSE_OFF
};


//for voice controls
enum fan_speed_level
{
    FAN_OFF = 0,
	FAN_LOW = 10,		//For Bajaj Fan:60
	FAN_LOW_MID = 12,
	FAN_MID = 20,		//For Bajaj Fan:70
	FAN_MID_HIGH = 30,
	FAN_HIGH = 50		//For Bajaj Fan:100
};

enum sentReceivedCmdId
{
    NONE,
    WAKEWORD,
    SWITCHON,
    SWITCHOFF,
	LOW_SPEED,
	MED_SPEED,
	HIGH_SPEED,
	ACMIX,
	WELLNESS,
	ECO,
	REVERSE,
	BREEZE,
	FINETUNE,
	TIMER
};

struct fan
{
    pwmout_t pwm_fan;
    enum fan_speed_level speed;
    int period;
    int pin;
};

#if VERSADEVICES_SUPERFAN_IOT

#define SF0_START_BYTE  0x55  //ksk
#define SF1_BYTE  0xAA  //ksk

#endif

#if RR_KABLES

#define HDCP_START_BYTE 0xFF
#define HDCP_BYTE_1 0x00

#endif

#if ATOMBERG_FAN
#define ATBG0_BYTE 0x41
#define ATBG1_BYTE 0x43
#endif

#if VGUARD_NEW_FAN
#define VG_STARTBYTE 0XFF
#define VG_MIDBYTE 0X0C
#endif

void controlFan();
void init_fan(struct fan* f, int period, int pin, int channel);
void set_fan_speed(struct fan* f, enum fan_speed_level level);
void step_up_fan_speed(struct fan* f);
void step_down_fan_speed(struct fan* f);
void reInitialize_HDCP_Uart(int baudRate);

void initializeSuperfan();
void superfan_low_speed();
void superfan_high_speed();
void superfan_switchOn();
void superfan_switchOff();
void superfan_reverseMode();
void send_heartbeat();
void superfan_Breeze_mode();
void superfan_Eco_Mode();
void superfan_acmix();
void superfan_wellness();
void superfan_Reverse();
void superfan_Fine_tune_mode();

struct serial_s superFanObj;

#endif //__HOAGS_FAN_CONTROLS_H__


