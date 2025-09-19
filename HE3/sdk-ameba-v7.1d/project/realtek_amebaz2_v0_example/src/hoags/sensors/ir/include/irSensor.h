#ifndef __IR_SENSOR_H__
#define __IR_SENSOR_H__

#include "pwmout_api.h"

#define TMR_12 12
#define TMR_13 13

struct ir
{
    pwmout_t pwm_ir;
    int period;
    int pin;
};


void initTimer();
void irTransmit();
void lowPulse();
//void livpure_pwmout_pulsewidth_us(pwmout_t *obj, float us);

#endif //__IR_SENSOR_H__