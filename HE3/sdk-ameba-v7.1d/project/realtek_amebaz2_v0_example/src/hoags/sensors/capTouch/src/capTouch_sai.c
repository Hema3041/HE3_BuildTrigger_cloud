//#include "ameba_soc.h"
#include "capTouch.h"
#include "PinNames.h"
#include "objects.h"
#include "hoags_config.h"

/* NOTE: adjust your parameters here!!! */
CapTouch_CHInitTypeDef CTC_Ch_Config[CT_CHANNEL_NUM] = {
	/*DiffThreshold, MbiasCurrent, ETCNNoiseThr, ETCPNoiseThr, CHEnable*/
	{100,           0x0C,            40,         40,            ENABLE}, /* Channel 0 */
	{100,           0x0C,            40,         40,            ENABLE}, /* Channel 1 */
	{100,           0x0C,            40,         40,            ENABLE}, /* Channel 2 */
	{100,           0x0C,            40,         40,            ENABLE}, /* Channel 3 */
	{100,           0x0C,            40,         40,            ENABLE}, /* Channel 4 */
	{100,           0x0C,            40,         40,            DISABLE}, /* Channel 5 */ //Earlier disabled
	{100,           0x0C,            40,         40,            ENABLE}, /* Channel 6 */ //Earlier enabled
	{100,           0x0C,            40,         40,            DISABLE}, /* Channel 7 */
	{100,           0x0C,            40,         40,            DISABLE}, /* Channel 8: guard */
};


u8 CTC_Chan_GRP[] = {
	PB_5,  // K1
	PB_4,  // K2
	PB_3,  // K3
	PB_2,  // K4
	PB_1,  // K5
	PA_31, // Disabled
	PA_30	//K6
};

//u8 Led_Pins[6]={PA_0,PA_1,PA_17,PA_18,PA_21,PA_22};
gpio_t WakeLed[6];
void INIT_LED()
{
	for(int i=0;i<6;i++)
	{
		gpio_init(&WakeLed[i],Led_Pins[i]);
		gpio_dir(&WakeLed[i],PIN_OUTPUT);
		gpio_mode(&WakeLed[i],PullNone);
		gpio_write(&WakeLed[i],0);
	}

}

// void LED_action(enum chimneyLightState CapLed)
// {
// 	if(CapLed==0||CapLed==1)
// 		gpio_write(&WakeLed,CapLed);
// }

enum chimneyLightState
{
	CHIMNEY_LIGHT_NONE,
	CHIMNEY_LIGHT_ON,
	CHIMNEY_LIGHT_OFF
};

enum chimneyLightState cls = CHIMNEY_LIGHT_NONE;

unsigned char switchLed[6] = {0,0,0,0,0,0};

//~switchLed[key];
void ledAction(u8 key)
{
	switch(key)
	{
		case PB_2:	
			switchLed[0]=!switchLed[0];
			gpio_write(&WakeLed[0],switchLed[0]);
			break;
		case PB_3:
			switchLed[1]=!switchLed[1];
			gpio_write(&WakeLed[1],switchLed[1]);
			break;
		case PB_4:
			switchLed[2]=!switchLed[2];
			gpio_write(&WakeLed[2],switchLed[2]);
			break;
		case PB_5:
			switchLed[3]=!switchLed[3];
			gpio_write(&WakeLed[3],switchLed[3]);
			break;
		case PA_30:
			switchLed[4]=!switchLed[4];
			gpio_write(&WakeLed[4],switchLed[4]);
			break;
		case PB_1:
			switchLed[5]=!switchLed[5];
			gpio_write(&WakeLed[5],switchLed[5]);
			break;
		default:
			HOAGS_ERR("Invalid key=%d\n", key);
			break;
	}
	// switch(cls)
	// {
	// 	case CHIMNEY_LIGHT_NONE:
	// 		cls=CHIMNEY_LIGHT_ON;
	// 		break;
	// 	case CHIMNEY_LIGHT_ON:
	// 		cls=CHIMNEY_LIGHT_NONE;
	// 		break;
		
	// }
	// gpio_write(&WakeLed,cls);
}

u32 CapTouch_irq_handler(void *para)
{
	printf("handler called\n");
	(void)para;
	u32 IntStatus;
	IntStatus = CapTouch_GetISR(CAPTOUCH_DEV);

	for (u8 i = 0; i < sizeof(CTC_Chan_GRP); i++) {
		printf("IntStatus=%d CT_CHX=%d status=%d\n", IntStatus, CT_CHX_PRESS_INT(i), IntStatus & CT_CHX_PRESS_INT(i));
		if (IntStatus & CT_CHX_PRESS_INT(i)) {
			DBG_8195A("Key %d pressed \n", i);
		} else if (IntStatus & CT_CHX_RELEASE_INT(i)) {
			DBG_8195A("Key %d released \n", i);
			ledAction(CTC_Chan_GRP[i]);
		}
	}
	#if 0
	if (IntStatus & CT_BIT_AFIFO_OVERFLOW_INTR) {
		DBG_8195A("CT_BIT_AFIFO_OVERFLOW_INTR \n");
	}
	#endif

	if (IntStatus & CT_BIT_OVER_P_NOISE_TH_INTR) {
		//DBG_8195A("CT_BIT_OVER_P_NOISE_TH_INTR \n");
		//CapTouch_Cmd(CAPTOUCH_DEV, DISABLE);
		//CapTouch_Cmd(CAPTOUCH_DEV, ENABLE);

		goto exit;
	}

	if (IntStatus & CT_BIT_GUARD_PRESS_INTR) {
		//DBG_8195A("Guard sensor pressed \n");
	}

	if (IntStatus & CT_BIT_GUARD_RELEASE_INTR) {
		//DBG_8195A("Guard sensor released \n");
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
			DBG_8195A("ch:%d, sample_data:%d\r\n", i, CapTouch_GetChAveData(CAPTOUCH_DEV, i));
			DelayMs(500);
		}
	}
}

void capTouchInit(void)
{
	//Initializing gpio output pin
	INIT_LED();


	CapTouch_InitTypeDef CapTouch_InitStruct;

	RCC_PeriphClockCmd(APBPeriph_CTC, APBPeriph_CTC_CLOCK, ENABLE);
	RCC_PeriphClockCmd(APBPeriph_ADC, APBPeriph_ADC_CLOCK, ENABLE);

	for (u8 i = 0; i < sizeof(CTC_Chan_GRP); i++) {
		if (ENABLE == CTC_Ch_Config[i].CT_CHEnable) {
			printf("%d is the pin\n",i);
			if (PB_1 == CTC_Chan_GRP[i]) {
				Pinmux_Swdoff();
			}
			
			PAD_PullCtrl(CTC_Chan_GRP[i], GPIO_PuPd_NOPULL);
			PAD_InputCtrl(CTC_Chan_GRP[i], ENABLE);
			Pinmux_Config(CTC_Chan_GRP[i], PINMUX_FUNCTION_AUXIN);
		}
	}

	CapTouch_StructInit(&CapTouch_InitStruct);

	_memcpy((void *)CapTouch_InitStruct.CT_Channel, (void *)CTC_Ch_Config, CT_CHANNEL_NUM * sizeof(CapTouch_CHInitTypeDef));

	CapTouch_Init(CAPTOUCH_DEV, &CapTouch_InitStruct);
	CapTouch_Cmd(CAPTOUCH_DEV, ENABLE);
	CapTouch_INTConfig(CAPTOUCH_DEV, CT_ALL_INT_EN, ENABLE);
	
	InterruptRegister((IRQ_FUN) CapTouch_irq_handler, CTOUCH_IRQ, (u32)NULL, 7);
	printf("After settin priority to 7\n");
	InterruptEn(CTOUCH_IRQ, 7);

	DBG_8195A("CapTouch init done \r\n");

	#if 0
	while (1) {
		/* call function ctc_period_debug() to check captouch channel sample data */
		 ctc_period_debug();
	}
	#endif
}