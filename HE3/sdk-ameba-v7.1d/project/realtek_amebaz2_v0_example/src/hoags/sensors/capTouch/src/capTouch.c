//#include "ameba_soc.h"
#include "capTouch.h"
#include "PinNames.h"
#include "objects.h"
#include "hoags_config.h"
#include "chimney.h"
#include "queue.h"
#include "timer_api.h"
#include "ameba_captouch.h"

void takeAction(void);
// for long press detection
signed char longPress=-1;
signed char keyNumber = -1;
unsigned char actionTaken = 0;
extern gtimer_t timer_7;
extern signed char deviceMode;


// extern char dthr[4];
// extern char mbias[4];
// extern char etcn1[4];
// extern char etcn2[4];
// extern int dThr;
// extern int mBias;
// extern int etcn;
// extern int etcp;


#if 0
/* NOTE: adjust your parameters here!!! */
CapTouch_CHInitTypeDef CTC_Ch_Config[CT_CHANNEL_NUM] = {
	/*DiffThreshold, MbiasCurrent, ETCNNoiseThr, ETCPNoiseThr, CHEnable*/
	{47,           0x0C,            23,         23,            ENABLE}, /* Channel 0 */
	{50,           0x0C,            22,         22,            ENABLE}, /* Channel 1 */
	{70,           0x0C,            22,         22,            ENABLE}, /* Channel 2 */
	{55,           0x0C,            21,         21,            ENABLE}, /* Channel 3 */
	{65,           0x0C,            21,         21,            ENABLE}, /* Channel 4 */
	{1,           0x0C,            20,         20,            DISABLE}, /* Channel 5 */ //Earlier disabled
	{60,           0x0C,            21,         21,            ENABLE}, /* Channel 6 */ //Earlier enabled
	{1,           0x0C,            20,         20,            DISABLE}, /* Channel 7 */
	{1,           0x0C,            20,         20,            DISABLE}, /* Channel 8: guard */
};
#endif
#if 0			///deciding for new pcb
/* NOTE: adjust your parameters here!!! */

CapTouch_CHInitTypeDef CTC_Ch_Config[CT_CHANNEL_NUM] = {
	/*DiffThreshold, MbiasCurrent, ETCNNoiseThr, ETCPNoiseThr, CHEnable*/
	{76, 		   0x0f,            50,         50,            ENABLE}, /* Channel 0 */
	{72,           0x0f,            60,         60,            ENABLE}, /* Channel 1 */
	{81,           0x0F,            35,         35,            ENABLE}, /* Channel 2 */
	{70,           0x0f,            70,         70,            ENABLE}, /* Channel 3 */
	{81,           0x0f,            30,         30,            ENABLE}, /* Channel 4 */
	{1,           0x0C,            20,         20,            DISABLE}, /* Channel 5 */ //Earlier disabled
	{80,           0x0f,            40,         40,            ENABLE}, /* Channel 6 */ //Earlier enabled
	{1,           0x0C,            20,         20,            DISABLE}, /* Channel 7 */
	{1,           0x0C,            20,         20,            DISABLE}, /* Channel 8: guard */
};


#endif
#if 1		///suvarna sir changes
CapTouch_CHInitTypeDef CTC_Ch_Config[CT_CHANNEL_NUM] = {
	/*DiffThreshold, MbiasCurrent, ETCNNoiseThr, ETCPNoiseThr, CHEnable*/
	{12,           0x0C,            12,         12,            ENABLE}, /* Channel 0 */
	{17,           0x0C,            10,         10,            ENABLE}, /* Channel 1 */
	{20,           0x0C,            15,         15,            ENABLE}, /* Channel 2 */
	{16,           0x0C,            15,         15,            ENABLE}, /* Channel 3 */
	{20,           0x0C,            15,         15,            ENABLE}, /* Channel 4 */
	{26,           0x0C,            20,         20,            DISABLE}, /* Channel 5 */ //Earlier disabled
	{20,           0x0C,            15,         15,            ENABLE}, /* Channel 6 */ //Earlier enabled
	{26,           0x0C,            20,         20,            DISABLE}, /* Channel 7 */
	{26,           0x0C,            20,         20,            DISABLE}, /* Channel 8: guard */
};
#endif

#if 0		///suvarna sir changes
CapTouch_CHInitTypeDef CTC_Ch_Config[CT_CHANNEL_NUM] = {
	/*DiffThreshold, MbiasCurrent, ETCNNoiseThr, ETCPNoiseThr, CHEnable*/
	{100,           0x0C,            20,         20,            ENABLE}, /* Channel 0 */
	{100,           0x0C,            20,         20,            ENABLE}, /* Channel 1 */
	{100,           0x0C,            20,         20,            ENABLE}, /* Channel 2 */
	{100,           0x0C,            20,         20,            ENABLE}, /* Channel 3 */
	{100,           0x0C,            20,         20,            ENABLE}, /* Channel 4 */
	{26,           0x0C,            20,         20,            DISABLE}, /* Channel 5 */ //Earlier disabled
	{100,           0x0C,            20,         20,            ENABLE}, /* Channel 6 */ //Earlier enabled
	{26,           0x0C,            20,         20,            DISABLE}, /* Channel 7 */
	{26,           0x0C,            20,         20,            DISABLE}, /* Channel 8: guard */
};
#endif


u8 CTC_Chan_GRP[] = {
	PB_5,  // K1	Low speed
	PB_4,  // K2	Mid speed
	PB_3,  // K3	High speed
	PB_2,  // K4	Light on
	PB_1,  // K5	Autoclean
	PA_19, // Disabled
	PA_30	//K6	Poweroff/on
};

enum chimneyLightState
{
	CHIMNEY_LIGHT_NONE,
	CHIMNEY_LIGHT_ON,
	CHIMNEY_LIGHT_OFF
};

enum chimneyLightState cls = CHIMNEY_LIGHT_NONE;
// //unsigned char switchLed[6] = {0,0,0,0,0,0};
// u8 Led_Pins[6]={PA_0,PA_1,PA_17,PA_18,PA_21,PA_22};//PA_21 -> PA_28, PA_22 -> PA_29
// gpio_t WakeLed[6];
struct hoagsIrq hiq;
extern QueueHandle_t interruptQueueHandle;

#if 0
void INIT_LED()
{
	for(int i=0;i<4;i++)
	{
		gpio_init(&WakeLed[i],Led_Pins[i]);
		gpio_dir(&WakeLed[i],PIN_OUTPUT);
		gpio_mode(&WakeLed[i],PullNone);
		gpio_write(&WakeLed[i],0);
	}
}
#endif
void ledAction(u8 key)
{
	memset(&hiq, 0x00, sizeof(struct hoagsIrq));
	switch(key)
	{
		case PB_1:
			HOAGS_ERR("HOAGSIRQ_CHIMNEY_KEY6_PRESSED --> ON/OFF\n");
			//switchLed[5]=!switchLed[5];
			hiq.devType = HOAGSIRQ_CHIMNEY;
			hiq.action = HOAGSIRQ_CHIMNEY_KEY6_PRESSED;
			int ret = xQueueSend(interruptQueueHandle, &hiq, portMAX_DELAY);
			if( ret == pdTRUE)
			{
				HOAGS_INFO("Written successful!\n");
			}
			else
			{
				HOAGS_INFO("Written failed! err=%d\n", ret);
			}
			//gpio_write(&WakeLed[5],switchLed[5]);

			break;

		case PB_2:	
			
			HOAGS_ERR("HOAGSIRQ_CHIMNEY_KEY3_PRESSED --> SPEEDCHIMNEY\n");
			//switchLed[4]=!switchLed[4];
			hiq.devType = HOAGSIRQ_CHIMNEY;
			//hiq.action = HOAGSIRQ_CHIMNEY_KEY5_PRESSED;
			hiq.action = HOAGSIRQ_CHIMNEY_KEY3_PRESSED;
			xQueueSend(interruptQueueHandle, &hiq, xQUEUE_TIMEOUT);
			//gpio_write(&WakeLed[4],switchLed[4]);
			break;

		case PB_3:
			HOAGS_ERR("HOAGSIRQ_CHIMNEY_KEY5_PRESSED --> AUTOCLEAN\n");
			//switchLed[2]=!switchLed[2];
			hiq.devType = HOAGSIRQ_CHIMNEY;
			//hiq.action = HOAGSIRQ_CHIMNEY_KEY3_PRESSED;
			hiq.action = HOAGSIRQ_CHIMNEY_KEY5_PRESSED;
			xQueueSend(interruptQueueHandle, &hiq, xQUEUE_TIMEOUT);
			//gpio_write(&WakeLed[2],switchLed[2]);
			break;

		case PA_30:
			
			HOAGS_ERR("HOAGSIRQ_CHIMNEY_KEY4_PRESSED --> SWITCHONLIGHTCHIMNEY\n");
			//switchLed[3]=!switchLed[3];
			hiq.devType = HOAGSIRQ_CHIMNEY;
			hiq.action = HOAGSIRQ_CHIMNEY_KEY4_PRESSED;
			xQueueSend(interruptQueueHandle, &hiq, xQUEUE_TIMEOUT);
			//gpio_write(&WakeLed[3],switchLed[3]);
			break;

		case PB_5:
			
			HOAGS_ERR("HOAGSIRQ_CHIMNEY_KEY1_PRESSED --> AUTO/MANNUALMODE\n");
			//switchLed[0]=!switchLed[0];
			hiq.devType = HOAGSIRQ_CHIMNEY;
			// if(longPress == 0)
			// {
			// 	hiq.action = HOAGSIRQ_CHIMNEY_MODE;
			// }
			// else
			// {
				//hiq.action = HOAGSIRQ_CHIMNEY_KEY1_PRESSED;
			//}
			if(longPress == 0)
			{
				hiq.action = HOAGSIRQ_CHIMNEY_IR_LOCK;
			}
			else
			{
				hiq.action = HOAGSIRQ_CHIMNEY_KEY1_PRESSED;
			}
			xQueueSend(interruptQueueHandle, &hiq, portMAX_DELAY);
			//gpio_write(&WakeLed[0],switchLed[0]);
			break;

		case PB_4:
			
			
			HOAGS_ERR("HOAGSIRQ_CHIMNEY_KEY2_PRESSED --> MIC MUTE/UNMUTE\n");
			//switchLed[1]=!switchLed[1];
			hiq.devType = HOAGSIRQ_CHIMNEY;
			// if(longPress == 1)
			// {
			// 	hiq.action = HOAGSIRQ_CHIMNEY_IR_LOCK;
			// }
			// else
			// {
				hiq.action = HOAGSIRQ_CHIMNEY_KEY2_PRESSED;
			//}
			xQueueSend(interruptQueueHandle, &hiq, xQUEUE_TIMEOUT);
			//gpio_write(&WakeLed[1],switchLed[1]);
			break;

		default:
			HOAGS_ERR("Invalid key=%d\n", key);
			break;
	}
	
}

u32 CapTouch_irq_handler(void *para)
{
	(void)para;
	u32 IntStatus;
	IntStatus = CapTouch_GetISR(CAPTOUCH_DEV);

	for (u8 i = 0; i < sizeof(CTC_Chan_GRP); i++) {
		if (IntStatus & CT_CHX_PRESS_INT(i)) {
			DBG_8195A("Key %d pressed \n", i);
			if(i == 0  ||  i == 1)
			{
				keyNumber = i;//enable a variable and start the timer.(possibly start a 3 second timer)
				gtimer_start_one_shout(&timer_7,3000000,(void *)takeAction,NULL);
				//timer call back function should disable the variable.
			}
		} else if (IntStatus & CT_CHX_RELEASE_INT(i)) {
			DBG_8195A("Key %d released \n", i);
			// if(i == 0)
			// {
			// 	longPress = -1;//check the variable is still enabled or not .
			// 	gtimer_stop(&timer_7);// if enabled, long press happened else not happened.
			// }
			// switch(i)
			// {
			// 	case 0:	longPress = -1;
			// 			gtimer_stop(&timer_7);
			// 			break;

			// 	case 1: longPress = -1;
			// 			gtimer_stop(&timer_7);
			// 			break;
			// 	default: HOAGS_INFO("NO LONG PRESS\n");
			// }
			if(longPress == -1)
			{
				gtimer_stop(&timer_7);
				ledAction(CTC_Chan_GRP[i]);	
			}
			else
			{
				longPress = -1;
			}
		}
	}


	if (IntStatus & CT_BIT_OVER_P_NOISE_TH_INTR) {

		goto exit;
	}

	if (IntStatus & CT_BIT_GUARD_PRESS_INTR) {
	}

	if (IntStatus & CT_BIT_GUARD_RELEASE_INTR) {
	}

exit:
	CapTouch_INTClearPendingBit(CAPTOUCH_DEV, IntStatus);

	return 0;
}

void ctc_period_debug(void)
{
	u8 i;

	for (i = 0; i < CT_CHANNEL_NUM; i++) {
		if (ENABLE == CTC_Ch_Config[i].CT_CHEnable) {
			//DBG_8195A("ch:%d, sample_data:%d\r\n", i, CapTouch_GetChAveData(CAPTOUCH_DEV, i));
			DelayMs(50);
		}
	}
}


void initCapTouchPins(void)
{

	CapTouch_InitTypeDef CapTouch_InitStruct;
	printf("initializing captouch\n");
	RCC_PeriphClockCmd(APBPeriph_CTC, APBPeriph_CTC_CLOCK, ENABLE);
	RCC_PeriphClockCmd(APBPeriph_ADC, APBPeriph_ADC_CLOCK, ENABLE);

	for (u8 i = 0; i < sizeof(CTC_Chan_GRP); i++) {
		if (ENABLE == CTC_Ch_Config[i].CT_CHEnable) {
			if (PB_1 == CTC_Chan_GRP[i]) {
				Pinmux_Swdoff();
			}
			
			PAD_PullCtrl(CTC_Chan_GRP[i], GPIO_PuPd_NOPULL);
			PAD_InputCtrl(CTC_Chan_GRP[i], ENABLE);
			Pinmux_Config(CTC_Chan_GRP[i], PINMUX_FUNCTION_AUXIN);
		}
//  CTC_Ch_Config[i].CT_DiffThrehold = dThr;//ENV VARIABLE
//  CTC_Ch_Config[i].CT_MbiasCurrent = mBias;
//  CTC_Ch_Config[i].CT_ETCNNoiseThr = etcn;
//  CTC_Ch_Config[i].CT_ETCPNoiseThr = etcp;

//HOAGS_ERR("Touch %d, is assigned with Thr : %d, Bias : %d, Etcn : %d, Etcp : %d\n",i,CTC_Ch_Config[i].CT_DiffThrehold, CTC_Ch_Config[i].CT_MbiasCurrent, CTC_Ch_Config[i].CT_ETCNNoiseThr, CTC_Ch_Config[i].CT_ETCPNoiseThr);

	}

//CapTouch_CHInitTypeDef CTC_Ch_Config[9];


	CapTouch_StructInit(&CapTouch_InitStruct);

	_memcpy((void *)CapTouch_InitStruct.CT_Channel, (void *)CTC_Ch_Config, CT_CHANNEL_NUM * sizeof(CapTouch_CHInitTypeDef));

	CapTouch_Init(CAPTOUCH_DEV, &CapTouch_InitStruct);
	CapTouch_Cmd(CAPTOUCH_DEV, ENABLE);
	CapTouch_INTConfig(CAPTOUCH_DEV, CT_ALL_INT_EN, ENABLE);
	
	InterruptRegister((IRQ_FUN) CapTouch_irq_handler, CTOUCH_IRQ, (u32)NULL, 7);
	InterruptEn(CTOUCH_IRQ, 7);

}

void takeAction(void)
{
	longPress = keyNumber;
	switch(longPress)
	{
		case 0:	ledAction(CTC_Chan_GRP[0]);
				//HOAGS_INFO("*********ENTERED MANNUAL MODE*********\n");
				break;
		
		case 1: ledAction(CTC_Chan_GRP[1]);
				//HOAGS_INFO("********IR LOCK*******\n");
				break;
		default: HOAGS_INFO("**********No long Press*********\n");
	}
}
