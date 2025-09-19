#include "light.h"
#include "hoags_config.h"
#include "htap_config.h"

extern FanConfigured;
extern LightConfigured;
extern UARTConfigured;
extern LedConfRed;
extern LedConfGreen;
extern LedConfBlue;

extern struct  Light_Pins_St;
BOOL gpioTestResult = TRUE;

#if HOAGS_GPIO_LED_DEMO
gpio_t gpio_led_red_demo;
gpio_t gpio_led_green_demo;
gpio_t gpio_led_blue_demo;
#endif

#if HOAGS_GPIO_LED
gpio_t gpio_led_red;
extern gpio_t gpio_pin1;
gpio_t gpio_pin2;

gpio_t gpio_led_green;
gpio_t gpio_led_blue;
#endif
// int result;
// int result1;
// int GPIO_pins1[]={GPIO_PIN0};
// int GPIO_pins2[]={GPIO_PIN1};
// int PINS_SZ = sizeof(GPIO_pins1)/sizeof(GPIO_pins1[0]);

extern int8_t WW_Led_Pin;
#if HOAGS_GPIO_LED
gpio_t gpio_led_WW;
#endif
// void InitWakeWord_LED(int8_t WW_Led_Pin)
// {
//     gpio_init(&gpio_led_WW, WW_Led_Pin);
//     gpio_dir(&gpio_led_WW, PIN_OUTPUT);    // Direction: Output
//     gpio_mode(&gpio_led_WW, PullNone);

//     gpio_write(&gpio_led_WW, 0);
// }

#if 0 //HOAGS_GPIO_LED
void initialize_gpio_pin(int pin1,int pin2)
{
    
    gpio_init(&gpio_pin1,pin1);
    gpio_dir(&gpio_pin1, PIN_OUTPUT);    
    gpio_mode(&gpio_pin1, PullNone);

    gpio_init(&gpio_pin2, pin2);
    gpio_dir(&gpio_pin2, PIN_INPUT);    
    gpio_mode(&gpio_pin2, PullNone);

    gpio_pin_status_read(gpio_pin1,gpio_pin2);
  
}
void gpio_pin_status_read(gpio_t output,gpio_t input)
{   
        gpio_write(&output,0);
        result1 = gpio_read(&input);
        printf(" %d->(%d) SENDING TO %d (%d)\n",output,0,input,result1);

        if(result1!=0)
            gpioTestResult = FALSE;

        gpio_write(&output,1);
        result1 = gpio_read(&input);
        printf(" %d->(%d) SENDING TO %d (%d)\n",output,1,input,result1);

        if(result1!=1)
            gpioTestResult = FALSE;

        // DelayMs(250);
        // gpio_write(&gpio_led_red, 1);
        // result = gpio_read(&gpio_led_green);
        // printf("result =%d\n",result);
        // DelayMs(1000);
}
void gpio_checking(){
    for (int i=0;i<PINS_SZ;i++){
        initialize_gpio_pin(GPIO_pins1[i],GPIO_pins2[i]);
        initialize_gpio_pin(GPIO_pins2[i],GPIO_pins1[i]);
    }

    if(gpioTestResult)
        HOAGS_MAN_RAW("\n\nGPIO_PASS\n\n");
    else
        HOAGS_MAN_RAW("\n\nGPIO_FAILED\n\n");
}
void initializeEVBLed()
{
    gpio_init(&gpio_led_red, GPIO_LED_RED);
    gpio_dir(&gpio_led_red, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_led_red, PullNone);

    gpio_init(&gpio_led_green, GPIO_LED_GREEN);
    gpio_dir(&gpio_led_green, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_led_green, PullNone);

    gpio_init(&gpio_led_blue, GPIO_LED_BLUE);
    gpio_dir(&gpio_led_blue, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_led_blue, PullNone);

    gpio_write(&gpio_led_red, 0);
    gpio_write(&gpio_led_green, 0);
    gpio_write(&gpio_led_blue, 0);
}

void glowLEDGreen()
{
        gpio_write(&gpio_led_red, 0);
        gpio_write(&gpio_led_green, 1);
        gpio_write(&gpio_led_blue, 0);
}

void glowLEDRed()
{   
        HOAGS_DBG(":%p:%p:%p\n", &gpio_led_red, &gpio_led_green, &gpio_led_blue);
        gpio_write(&gpio_led_red, 1);
        gpio_write(&gpio_led_green, 0);
        gpio_write(&gpio_led_blue, 0);
}

void glowLEDBlue()
{
        gpio_write(&gpio_led_red, 0);
        gpio_write(&gpio_led_green, 0);
        gpio_write(&gpio_led_blue, 1);
}

void glowLEDWhite()
{ 
        gpio_write(&gpio_led_red, 0);
        gpio_write(&gpio_led_green, 0);
        gpio_write(&gpio_led_blue, 0);
}

void glowLEDNoColor()
{     
        gpio_write(&gpio_led_red, 0);
        gpio_write(&gpio_led_green, 0);
        gpio_write(&gpio_led_blue, 0);
}
#endif

/*gpio testing begin */
gpio_t pin_1;
gpio_t pin_2;
BOOL bist_gpioTestResult = FALSE;
// int result;
int bist_result1;

void bist_initialize_gpio_pin(int pin1,int pin2)
{
    
    gpio_init(&pin_1,pin1);
    gpio_dir(&pin_1, PIN_OUTPUT);    
    gpio_mode(&pin_1, PullNone);

    gpio_init(&pin_2, pin2);
    gpio_dir(&pin_2, PIN_INPUT);    
    gpio_mode(&pin_2, PullNone);

    bist_gpio_pin_status_read(pin_1,pin_2);
  
}
void bist_deinitialize_gpio_pin()
{
    gpio_deinit(&pin_1);
    gpio_deinit(&pin_2);
    
}
void bist_gpio_pin_status_read(gpio_t output,gpio_t input)
{   
        gpio_write(&output,0);
        bist_result1 = gpio_read(&input);
        // printf(" %d->(%d) SENDING TO %d (%d)\n",output,0,input,result1);

        if(bist_result1!=0)
            bist_gpioTestResult = FALSE;
		else
			bist_gpioTestResult = TRUE;
        gpio_write(&output,1);
        bist_result1 = gpio_read(&input);
        // printf(" %d->(%d) SENDING TO %d (%d)\n",output,1,input,result1);

        if(bist_result1!=1)
            bist_gpioTestResult = FALSE;
		else
			bist_gpioTestResult = TRUE;
		

        // DelayMs(250);
        // gpio_write(&gpio_led_red, 1);
        // result = gpio_read(&gpio_led_green);
        // printf("result =%d\n",result);
        // DelayMs(1000);
}

void bist_gpio_checking(PinName pin1,PinName pin2 ){
    bist_initialize_gpio_pin(pin1,pin2);
	if(bist_gpioTestResult)
        HOAGS_MAN_RAW("\n\nGPIO_PASS %d, %d\n\n",pin1,pin2);
    else
        HOAGS_MAN_RAW("\n\nGPIO_FAILED %d, %d\n\n",pin1,pin2);
	
	bist_deinitialize_gpio_pin();
    vTaskDelay(1000);
	bist_initialize_gpio_pin(pin2,pin1);
    
	if(bist_gpioTestResult)
        HOAGS_MAN_RAW("\n\nGPIO_PASS %d, %d\n\n",pin2,pin1);
    else
        HOAGS_MAN_RAW("\n\nGPIO_FAILED %d, %d\n\n",pin1,pin2);
	bist_deinitialize_gpio_pin();
	 
}


void bist_gpio_test (void){
	HOAGS_DBG ("Befor checking \n");
	bist_gpio_checking(PA_2,PA_3);
	bist_gpio_checking(PA_19,PA_20);
	HOAGS_DBG ("After checking \n");
	
	// vTaskDelete(NULL);

}
/*gpio end*/


void initializeLight(Light_Pins_St Htap_Light_Red,Light_Pins_St Htap_Light_Green, Light_Pins_St Htap_Light_Blue)
{
    #if HOAGS_GPIO_LED_DEMO

    gpio_init(&gpio_led_red_demo, PB_2);
    gpio_dir(&gpio_led_red_demo, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_led_red_demo, PullNone);
    gpio_write(&gpio_led_red_demo, 0);

    gpio_init(&gpio_led_green_demo, PA_30);
    gpio_dir(&gpio_led_green_demo, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_led_green_demo, PullNone);
    gpio_write(&gpio_led_green_demo, 0);

    gpio_init(&gpio_led_blue_demo, PA_31);
    gpio_dir(&gpio_led_blue_demo, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_led_blue_demo, PullNone);
    gpio_write(&gpio_led_blue_demo, 0);
    #endif
}
void init_led(struct led* l, int period, int pin, int channel)
{
    HOAGS_DBG("period=%d pin=%d\n", period, pin);
    l->pwm_led.pwm_idx = channel;
    pwmout_init(&(l->pwm_led), pin);
    pwmout_period_us(&(l->pwm_led), period);
}

void set_led_period(struct led* l, int period)
{
    HOAGS_DBG("period=%d\n", period);
    pwmout_period_us(&(l->pwm_led), period);
}
void set_led_brightness(struct led* l, enum led_brightness_level level)
{
    HOAGS_DBG("level=%d\n", level);
    pwmout_pulsewidth_us(&(l->pwm_led), level);
    l->brightness = level;
}

void step_up_led_brightness(struct led* l)
{
    switch (l->brightness)
    {
        case LED_LOW:
            pwmout_pulsewidth_us(&(l->pwm_led), LED_LOW_MID);
            HOAGS_DBG("new_level=%d prev_level=%d\n", LED_LOW_MID, l->brightness);
            l->brightness = LED_LOW_MID;
            break;
        
        case LED_LOW_MID:
            pwmout_pulsewidth_us(&(l->pwm_led), LED_MID);
            HOAGS_DBG("new_level=%d prev_level=%d\n", LED_MID, l->brightness);
            l->brightness = LED_MID;
            break;
        
        case LED_MID:
            pwmout_pulsewidth_us(&(l->pwm_led), LED_MID_HIGH);
            HOAGS_DBG("new_level=%d prev_level=%d\n", LED_MID_HIGH, l->brightness);
            l->brightness = LED_MID_HIGH;
            break;
        
        case LED_MID_HIGH:
            pwmout_pulsewidth_us(&(l->pwm_led), LED_HIGH);
            HOAGS_DBG("new_level=%d prev_level=%d\n", LED_HIGH, l->brightness);
            l->brightness = LED_HIGH;
            break;
    }
}

void step_down_led_brightness(struct led* l)
{
    switch(l->brightness)
    {
        case LED_HIGH:
            pwmout_pulsewidth_us(&(l->pwm_led), LED_MID_HIGH);
            l->brightness = LED_MID_HIGH;
            break;

        case LED_MID_HIGH:
            pwmout_pulsewidth_us(&(l->pwm_led), LED_MID);
            l->brightness = LED_MID;
            break;

        case LED_MID:
            pwmout_pulsewidth_us(&(l->pwm_led), LED_LOW_MID);
            l->brightness = LED_LOW_MID;
            break;

        case LED_LOW_MID:
            pwmout_pulsewidth_us(&(l->pwm_led), LED_LOW);
            l->brightness = LED_LOW;
            break;
    }
}


