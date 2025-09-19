
#include "device.h"
#include "analogin_api.h"
#include <sys_api.h>
#include "hoags_config.h"
#include "i2c_api.h"
#include "chimney.h"
#include "math.h"
#include "gpio_api.h"
//***********for mq2 smoke sensor*******//
// #define SMOKE1_THRESHOLD	340	
// #define SMOKE2_THRESHOLD	420

//***********for mq135 smoke sensor*******//
// #define SMOKE1_THRESHOLD	260	
// #define SMOKE2_THRESHOLD	300

#if defined (__ICCARM__)
analogin_t   adc5;
#else
volatile analogin_t   adc5;
#endif

uint16_t adcdat5=0;
int32_t  v_mv5;
unsigned short int currentSmokeLevel=0;
unsigned short int prevSmokeLevel=0;
unsigned char LED=0xFF;
unsigned short int smoke1Threshold = 245;
unsigned short int smoke2Threshold = 265;

// for the queue and smoke sensor
extern i2c_t i2cObj;
extern QueueHandle_t interruptQueueHandle;
extern gpio_t gpio_smoke;


void mbed_adc_vol_demo(struct hoagsIrq* hisObj)
{
	prevSmokeLevel = currentSmokeLevel;
	analogin_init(&adc5, AD_5);
	adcdat5 = analogin_read_u16(&adc5);	
	v_mv5 = analogin_voltage_norm(adcdat5);
	currentSmokeLevel = v_mv5;

	HOAGS_ERR("AD5:0x%x => %dmV\n", adcdat5, v_mv5);
	

	// if(currentSmokeLevel - prevSmokeLevel >= 50 )
	// 	return;

	if(v_mv5<smoke1Threshold)
	{
		hisObj->devType = HOAGSIRQ_CHIMNEY;
		hisObj->action = HOAGSIRQ_CHIMNEY_NO_SMOKE_DETECTED;
		xQueueSend(interruptQueueHandle, hisObj, xQUEUE_TIMEOUT);
	}
	else if((v_mv5>smoke1Threshold) && (v_mv5<smoke2Threshold))
	{
		hisObj->devType = HOAGSIRQ_CHIMNEY;
		hisObj->action = HOAGSIRQ_CHIMNEY_SMOKE_DETECTED1;
		xQueueSend(interruptQueueHandle, hisObj, xQUEUE_TIMEOUT);
	}
	else if(v_mv5>smoke2Threshold )
	{
		hisObj->devType = HOAGSIRQ_CHIMNEY;
		hisObj->action = HOAGSIRQ_CHIMNEY_SMOKE_DETECTED2;
		xQueueSend(interruptQueueHandle, hisObj, xQUEUE_TIMEOUT);	
	}
	
}

int32_t lpg_Read()
{
	analogin_init(&adc5, AD_5);
	adcdat5 = analogin_read_u16(&adc5);
		
	v_mv5 = analogin_voltage_norm(adcdat5);

	HOAGS_ERR("LPG:0x%x => %dmV\n", adcdat5, v_mv5);
	return v_mv5;
}
