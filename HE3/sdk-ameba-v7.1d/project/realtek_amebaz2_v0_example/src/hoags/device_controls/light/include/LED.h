#ifndef LED_H
#define LED_H
#include "pwmout_api.h"
#include "hoags_config.h"
#include "packets.h"
#include "fan.h"

extern struct htap_led* htapledPtr;

extern struct serial_s superFanObj;
enum htap_led_blink_speed
{
    HTAP_LED_OFF = 0,
	HTAP_LED_LOW = 10,		//For Bajaj Fan:60
	HTAP_LED_LOW_MID = 12,
	HTAP_LED_MID = 20,		//For Bajaj Fan:70
	HTAP_LED_MID_HIGH = 30,
	HTAP_LED_HIGH = 50		//For Bajaj Fan:100
};

struct htap_led
{
    pwmout_t pwm_htap_led;
    enum htap_led_blink_speed speed;
    int period;
    int pin;
};

void breathe_LED();
void initialize_Htap_LED(uint32_t Led_Ctrl_Pin);
#endif