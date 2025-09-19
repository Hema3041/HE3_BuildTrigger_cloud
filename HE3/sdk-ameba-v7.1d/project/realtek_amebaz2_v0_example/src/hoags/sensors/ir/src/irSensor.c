#include "irSensor.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "hoags_config.h"
#include "timer_api.h"
#include "ameba_soc.h"
#include "device.h"
#include "gpio_api.h"   // mbed
#include "gpio_irq_api.h"   // mbed
#include "diag.h"
#include "us_ticker_api.h"
#include "chimney.h"
#include "queue.h"
#include "atomic.h"



#define GPIO_IRQ_PIN_1        PA_17
#define GPIO_IRQ_PIN_2        PA_18

//for queue and timers.
extern QueueHandle_t interruptQueueHandle;
extern BOOL wwDetected;
extern gtimer_t timer_5;
extern unsigned char autoCleanState;
extern void switchOffChimney();

// for the ir sensor
gpio_t gpio_out;
gpio_irq_t gpio_irq_1;
gpio_irq_t gpio_irq_2;
gpio_irq_t gpio_irq_3;
volatile char irq_rise_1;
volatile char irq_rise_2;
unsigned char irDisable=0;
signed char irCounterLeft=0;
signed char irCounterRight=0;
unsigned char irEnable = 1;
unsigned char leftDetected=0;
unsigned char rightDetected=0;
unsigned char detected=1;
static short int leftDetection=0;
static short int rightDetection=0;

// for autoclean timers and ir off timers
signed char timer_value=4;
signed char autoCleanTimerValue = 10;

#if 0
#define TIMER12 12
#define TIMER13 13
#define TIMER11 11
#define TIMER10 10
#endif
// FOR buzzer initialization

// for timer initialization
struct ir Left;
gtimer_t timer_1;
gtimer_t timer_2;
gtimer_t timer_3;
gtimer_t timer_4;
gtimer_t timer_5;//for ir off timer
gtimer_t timer_6;// for autoclean timer
gtimer_t timer_7;//for long press detection
gpio_t ir_pin;


TimerHandle_t xTimer_1,xTimer_2;
struct hoagsIrq hisObj1;




void initTimer()
{
    HOAGS_INFO("\n");
    gtimer_init(&timer_1,TIMER12);
    gtimer_init(&timer_2,TIMER13);
    gtimer_init(&timer_3,TIMER11);
    gtimer_init(&timer_4,TIMER10);
    gtimer_init(&timer_5,TIMER6);
    gtimer_init(&timer_6,TIMER5);
    gtimer_init(&timer_7,TIMER4);//FOR LONG PRESS
    Left.pwm_ir.pwm_idx=0;
	pwmout_init(&(Left.pwm_ir),PA_31);
}

void irTransmit()
{
    
  gtimer_start_one_shout(&timer_1,2500,(void *)lowPulse,NULL);   
  pwmout_period_us(&(Left.pwm_ir), 26);
  pwmout_pulsewidth_us(&(Left.pwm_ir),9);
   
}

void lowPulse()
{
    
  gtimer_start_one_shout(&timer_2,1000,(void *)irTransmit,NULL);
  pwmout_period_us(&(Left.pwm_ir), 26);
  pwmout_pulsewidth_us(&(Left.pwm_ir),0);
    
}


void finalTaskRight()
{
  printf("%d is the irEnbale value\n",irEnable);
  if(irEnable)  //0:disable  1: enable
  {
    printf("%d irDisable\n",irDisable);
    
    if(irDisable)
    {
      irDisable=0;
      detected=1;
      leftDetected=0;
      rightDetected=0;
      irCounterRight=0;
      irCounterLeft=0;
      return;
    }
    else if(rightDetected==1)
    {
      HOAGS_ERR("Left-->Right movement\n");
      hisObj1.devType = HOAGSIRQ_CHIMNEY;
      hisObj1.action = HOAGSIRQ_CHIMNEY_POWERON_IR;
      xQueueSend(interruptQueueHandle, &hisObj1, xQUEUE_TIMEOUT);
    }
    else
    {
      HOAGS_ERR("Movement timed-out\n");
    }
    detected=1;
    leftDetected=0;
    rightDetected=0;
    irCounterRight=0;
    irCounterLeft=0;
  }
  else
  {
    detected=1;
    leftDetected=0;
    rightDetected=0;
    irCounterLeft=0;
    irCounterRight=0;
  }
  if(irDisable)
  {
      irDisable=0;
      detected=1;
      leftDetected=0;
      rightDetected=0;
      irCounterRight=0;
      irCounterLeft=0;
      
      return;
  }
  
}

void finalTaskLeft()
{
  printf("%d is the irEnbale value\n",irEnable);
  if(irEnable)  // 0: disable   1: enable
  {
    printf("%d irDisable\n",irDisable);
    if(irDisable)
    {
      irDisable=0;
      detected=1;
      leftDetected=0;
      rightDetected=0;
      irCounterLeft=0;
      irCounterRight=0;
      // gpio_irq_enable(&gpio_irq_2);
      // gpio_irq_enable(&gpio_irq_1);
      return;
    }
    else if(leftDetected)
    {
      HOAGS_ERR("Right-->Left movement\n");
      hisObj1.devType = HOAGSIRQ_CHIMNEY;
      hisObj1.action = HOAGSIRQ_CHIMNEY_POWEROFF_IR;
      xQueueSend(interruptQueueHandle, &hisObj1, xQUEUE_TIMEOUT);
    }
    else
    {
      HOAGS_INFO("Movement timed-out\n");
    }
    detected=1;
    leftDetected=0;
    rightDetected=0;
    irCounterLeft=0;
    irCounterRight=0;
  }
  else
  {
    detected=1;
    leftDetected=0;
    rightDetected=0;
    irCounterLeft=0;
    irCounterRight=0;
  }
  if(irDisable)
  {
      irDisable=0;
      detected=1;
      leftDetected=0;
      rightDetected=0;
      irCounterRight=0;
      irCounterLeft=0;
      return;
  }
  
}


void gpio_irq_handler_1(uint32_t id)
{
    
        leftDetected=1;
        if(detected)
        {
          detected=0;
          gpio_irq_disable(&gpio_irq_2);
          DelayMs(100);
          gpio_irq_enable(&gpio_irq_2);
          gtimer_start_one_shout(&timer_3,400000,(void *)finalTaskRight,NULL);
        }
    
}


void gpio_irq_handler_2(uint32_t id)
{
  
    
        rightDetected=1;
        if(detected)
        {
          detected=0;
          gpio_irq_disable(&gpio_irq_1);
          DelayMs(100);
          gpio_irq_enable(&gpio_irq_1);
          gtimer_start_one_shout(&timer_4,400000,(void*)finalTaskLeft,NULL);
        }
        
    
    
}


void mbed_gpio_pulse_measure(void)
{
    // Initialize Push Button pin as interrupt source
    gpio_irq_init(&gpio_irq_1, GPIO_IRQ_PIN_1, gpio_irq_handler_1, (uint32_t)(&gpio_irq_1));
    gpio_irq_init(&gpio_irq_2, GPIO_IRQ_PIN_2, gpio_irq_handler_2, (uint32_t)(&gpio_irq_2));
    gpio_irq_set(&gpio_irq_1, IRQ_FALL, 1); 
    gpio_irq_set(&gpio_irq_2, IRQ_FALL, 1); // Falling Edge Trigger
    irq_rise_1 = 1;
    irq_rise_2=1;
    gpio_irq_pull_ctrl(&gpio_irq_1, PullNone);
    gpio_irq_pull_ctrl(&gpio_irq_2, PullNone);
    gpio_irq_enable(&gpio_irq_1);
    gpio_irq_enable(&gpio_irq_2);
	
}


//ir Sensor timer callback
void timerFunc()
{
  timer_value--;
  HOAGS_ERR("%d is the timer value\n",timer_value);
  if(timer_value==-1)
  {
    HOAGS_ERR("chimney off\n");
    switchOffChimney();
    irDisable=1;   //its affecting ir so that it is disabled.
    gtimer_stop(&timer_5);
    timer_value=4;
  }
}

// autoclean timer callback
void runAtLow()
{
  
    autoCleanTimerValue--;
    printf("%d is the autoclean timer value\n",autoCleanTimerValue);
    if(autoCleanTimerValue < 2 && autoCleanTimerValue >=0)
    {
      HOAGS_ERR("*******AutoClean Low Speed Running*******\n");
      lowSpeedChimney();
      irDisable = 1;
    }
    if(autoCleanTimerValue == -1)
    {
      autoCleanTimerValue = 10;
      
      switchOffChimney();
      irDisable = 1;
      gtimer_stop(&timer_6);
      HOAGS_ERR("AutoClean done --------Chimney Off\n");
    }
    
  
  
}

