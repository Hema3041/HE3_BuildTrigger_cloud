#ifndef __HOAGS_LIGHT_CONTROLS_H__
#define __HOAGS_LIGHT_CONTROLS_H__

#include "pwmout_api.h"

//for ble
enum LIGHT_CMD {
	LIGHT_CMD_POWER_CONTROL,
	LIGHT_CMD_INCREASE_BRIGHTNESS,
	LIGHT_CMD_DECREASE_BRIGHTNESS,
	LIGHT_CMD_MODE_CONTROL
};

enum LIGHT_CMD_POWER {
	LIGHT_CMD_ON,
	LIGHT_CMD_OFF
};

enum LIGHT_CMD_MODE {
	LIGHT_CMD_MODE_NORMAL,
	LIGHT_CMD_MODE_CLUB,
	LIGHT_CMD_MODE_ROMANTIC
};

//for voice-controls
enum led_brightness_level
{
    LED_OFF = 0,
    LED_LOW = 10,
	LED_LOW_MID = 12,
	LED_MID = 20,
	LED_MID_HIGH = 30,
	LED_HIGH = 50
};


struct led
{
    pwmout_t pwm_led;
    enum led_brightness_level brightness;
    int period;
    int pin;
};

void init_led(struct led* l, int period, int pin, int channel);
void set_led_period(struct led* l, int period);
void set_led_brightness(struct led* l, enum led_brightness_level level);
void step_up_led_brightness(struct led* l);
void step_down_led_brightness(struct led* l);
void gpio_test_task (void * parm);
#endif //__HOAGS_LIGHT_CONTROLS_H__