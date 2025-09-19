#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"
#include <example_entry.h>
#include "simple_ble_service.h"
#include "env.h"
#include "fan.h"
#include "app_msg.h"
#include "serial_api.h"
#include "cloudConnect.h"
#include "remoteDiag.h"

// unsigned char ambAck[15];
// unsigned char vfAck[24];
unsigned char vdAck[15];
unsigned char hdcpAck[26];
// unsigned char omniAck[15];
BOOL isEnvInitialized = FALSE;
BOOL isAckReceived = FALSE;
BOOL uartEnable = TRUE;
BOOL SendPollFlag = FALSE;
//struct univMacid umObj = {"aabbccddeeff", 1};
struct univMacid umObj = {{0}, 0};


extern bool renesasState;

#if LIVPURE_PURIFIER
TimerHandle_t uartInactivityTimer;
static BOOL isbaudRateChanged = FALSE;
#endif

#define UART_TX PA_14 // rehan: use for test UART0 TX
#define UART_RX PA_13 // UART0 RX

#define WATCHDOG_TIMEOUT 120000

// struct serial_s uart0Obj;
struct serial_s superFanObj;

extern QueueHandle_t envQ;
extern void console_init(void);
// TaskHandle_t watchDogTaskHandle;

// extern uint32_t sys_update_ota_prepare_addr(void);
// extern void example_mqtt(void);
/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
void runUartReceiveTask(void);
#if 0
void uart_INIT(){ //struct serial_s *sobj
	superFanObj.uart_idx=1;
	serial_init(&superFanObj, PA_14, PA_13);
    serial_baud(&superFanObj, 9600);
    serial_format(&superFanObj, 8, ParityNone, 1);
}
#endif
BOOL uart_send_bytes(struct serial_s *sobj, char *data, size_t len)
{
	if (!uartEnable)
	{
		HOAGS_ERR("huart is disabled\n");
		return FALSE;
	}

	HOAGS_ERR("Transfering to uart\n");

	unsigned int i = 0;
	while (len--)
	{
		serial_putc(sobj, *(data + i));
		++i;
	}
	return TRUE;
}

BOOL uart_receive_bytes(struct serial_s *sobj, size_t len, char *out)
{
	if (!uartEnable)
	{
		HOAGS_ERR("huart is disabled\n");
		return FALSE;
	}

	HOAGS_ERR("huart is enabled\n");

	unsigned int i = 0;
	while (len--)
	{
		out[i] = serial_getc(sobj);
		HOAGS_ERR("Read data=%d %c\n", out[i], out[i]);
		++i;
	}
	return TRUE;
}

char *getMacId()
{
	return umObj.macid;
}

void *hoagsMalloc(size_t sz)
{
	// HOAGS_INFO("Requested=%ld\n", sz);
	if (sz >= xPortGetFreeHeapSize() || sz <= 0)
	{
		HOAGS_ERR("Invalid malloc request=%ld available=%ld\n", sz, xPortGetFreeHeapSize());
		return NULL;
	}

	return malloc(sz);
}

#if 0
//u8 test_data[]={0x49 ,0x20 ,0x61 ,0x6D ,0x20 ,0x74 ,0x65 ,0x73 ,0x74 ,0x69 ,0x6E ,0x67 ,0x20 ,0x75 ,0x61 ,0x72 ,0x74 ,0x20 ,0x73 ,0x65 ,0x6E ,0x64 ,0x20 ,0x62 ,0x79 ,0x74 ,0x65 ,0x20 ,0x5C ,0x6E};

void initDummy()
{
	int counter = 0;
	char tmp[64];
	// vTaskDelay(5000);
	while(TRUE)
	{
		// HOAGS_INFO("Sending data to app\n");
		// memset(tmp, 0x00, strlen(tmp));
		// sprintf(tmp, "Diag:%d:This is BLE Notification", counter);
		// simp_ble_service_send_v3_notify(0,1, tmp, strlen(tmp));
		// vTaskDelay(1000);
		// ++counter;
  		
		
		if(uart_receive_bytes(&uart0Obj, sizeof(test_data), test_data) == TRUE){
			for(int i=0;i<sizeof(test_data);i++){
				printf("%02x ",test_data[i]);
			}
			printf("\n");
		
		}

	}
	
	vTaskDelete(NULL);
}

 void dummyTask(void)
{
	if(xTaskCreate(initDummy, ((const char*)"initDummy"), 1024, NULL, tskIDLE_PRIORITY + 4, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(dummyTask) failed", __FUNCTION__);
}

#endif

// for watch dog timer
u32 watchdog_timer_expiry(void *id)
{
	printf("Watchdog Expire.......\n");
	watchdog_stop();
	return 0;
}
void watch_dog_task(void *params)
{
	watchdog_init(WATCHDOG_TIMEOUT);
	#if RUN_CALLBACK_IF_WATCHDOG_BARKS
    watchdog_irq_init(&watchdog_timer_expiry, 0); 
	#else
    	// system would restart when watchdog barks
	#endif

	watchdog_start();
	//vTaskDelay(100);
	while(1)
	{
      watchdog_refresh();
	  vTaskDelay(500);
	}

}  

void wdg_task()
{
	if (pdTRUE != xTaskCreate((TaskFunction_t)watch_dog_task, "watchdog_task", (256), (void *)NULL, tskIDLE_PRIORITY+4	, NULL)) {
		printf("Create watchdog_task Err!!\r\n");
	}
}

void rebootRenesas(void)
{
	printf("Rebooting Renesas\n");
	gpio_t gpio_reset;
	gpio_init(&gpio_reset, PA_19);
	gpio_dir(&gpio_reset, PIN_OUTPUT);    
    gpio_mode(&gpio_reset, PullNone);
	gpio_write(&gpio_reset, 1);
	vTaskDelay(pdMS_TO_TICKS(2));
	gpio_write(&gpio_reset, 0);
	gpio_deinit(&gpio_reset);
}

BOOL isBIST = FALSE;

int main(void)
{

	//BOOL isFileSystemUp = FALSE;
	/* Initialize log uart and at command service */
	console_init();

	
	uint8_t uartFlag = 0xFF;	//uartlogenable=0xff uartlogdisable=0x00
	//uint8_t BistFlag = 0xFF;	//bistmode=0xff in appmode=0x01
	#if 0
	BOOL isSecured = isBoardSecured();
	if(isSecured)
	{
		printf("Board is secured\n");
		isBIST = FALSE;
	}
	else
	{
		printf("Board is non-secured\n");
		isBIST = TRUE;
	}
	#endif 
	#if 0
	efuse_logical_read(0x011, 1, &BistFlag);
	if(BistFlag == 0xFF)
	{
		printf("\n********In BIST Mode********\n");
	}
	else
	{
		printf("\n********In Application Mode********\n");
		isBIST=FALSE;
	}
	#endif
	MAC_Id_Read();

	printf("FIRMWARE VERSION:%s\n",VERSION_BUILD_STR);
	printf("RENESES VERSION:%s\n",RENESAS_VERSION_NUMBER);
	
	#if LOG_UART_DISABLE
	efuse_logical_read(0x010, 1, &uartFlag);
	if(uartFlag == 0xFF)
	{
		printf("UART-LOG and JTAG is enabled\n");
	}
	else
	{
		printf("UART-LOG and JTAG is disabled\n");
		sys_log_uart_off();
		sys_jtag_off();
		//Disable uart here
		//Disable jtag here
	}
	#endif
	
	if(isBIST == FALSE)
	{
		HTAP_Init();
	}	

	
	
	// uart_INIT(&superFanObj);
	

	/* pre-processor of application example */
	pre_example_entry();

	sys_update_ota_prepare_addr();
	
	/* wlan intialization */
	wlan_network();

	initEnv();
	// sys_update_ota_prepare_addr();
	// example_entry();
	#if 0
	if (hoagsInitFATFS())
	{
		isFileSystemUp = TRUE;
	}
	else
	{
		HOAGS_ERR("Error initializing Filesystem\n");
		while (TRUE)
		{
		}
	}
	#endif 

	//envTask();
	// startAWSIOT();
	// example_mqtt();
	// startDataCollector();

	if(isBIST == FALSE)
	{

	#if LIVPURE_PURIFIER
		startUartReceiveTask();
		startRemoteDiagTask();
		startMqttTask();
	#endif
	}

#if WATCHDOG_ENABLE
    wdg_task();
#endif

	vTaskStartScheduler();
	/* Should NEVER reach here */
	return 0;
}
#if LIVPURE_PURIFIER

#define CHECKSUM_SIZE sizeof(uint16_t)
#define SEQ_NUM_SIZE sizeof(uint16_t)
#define LAST_SEQ_NUM_SIZE sizeof(uint16_t)
TaskHandle_t runUartTaskHandle = NULL;
void suspendUartTask(){
	vTaskSuspend(runUartTaskHandle);
    printf("UART TASK SUSPENDED.\n");
}

void resumeUartTask() {
	vTaskResume(runUartTaskHandle);
    printf("UART TASK RESUMED.\n");
}

void setIsBaudRateChanged(){
	isbaudRateChanged = TRUE;
}

void uartInactivityCallback(TimerHandle_t xTimer)
{
	static uint32_t currentBaudRate = HE3_NEW_BAUDRATE;
	if(!isbaudRateChanged){
		uint32_t oppositeBaudRate = (currentBaudRate == HE3_NEW_BAUDRATE) ? HE3_OLD_BAUDRATE : HE3_NEW_BAUDRATE;
		reInitialize_HDCP_Uart(oppositeBaudRate);
		currentBaudRate = oppositeBaudRate;
		setIsBaudRateChanged();
		return;
	}
    rebootRenesas();
	resetIsTemp();
	isbaudRateChanged = FALSE;
}

void resetUartTimer(){
	if (uartInactivityTimer != NULL) {
		xTimerStop(uartInactivityTimer, 0);
		xTimerStart(uartInactivityTimer, 0);
	}
}
TimerHandle_t getUartInactivityHandle() {
	return uartInactivityTimer;
}

void runUartReceiveTask(void)
{
	struct hdcpRd hdcpPkt;
	uint8_t header_buffer[sizeof(uint8_t) + sizeof(uint16_t)];
	static uint8_t renesasNackCount  = 0;
	int headerlen = 0;
	static uint8_t renesasWaitforUpgrade = 0;
	uartInactivityTimer = xTimerCreate("uartInactivityTimer",
                                   pdMS_TO_TICKS(1000 * 16),
                                   pdTRUE,
                                   NULL,
                                   uartInactivityCallback);
	if (uartInactivityTimer != NULL) {
		xTimerStart(uartInactivityTimer, 0);
	}
	while (TRUE)
	{
		memset(&hdcpPkt, 0x00, sizeof(hdcpPkt));
		int headerlen = serial_recv_buffered(&superFanObj, header_buffer, 1, 1000000000);
		printf("Data Received:%d\n",header_buffer[0]);
		if((headerlen == 1))
		{
			if(isRenesasUpdateinProgress() && (header_buffer[0] == RENESAS_UPGRADE_ACK))
			{
				resetUartTimer();
				setIsBaudRateChanged();
				sControlMessage mcuAck;
				mcuAck.msgSource = SOURCE_RENESASUPDATE;
				mcuAck.msgId = MCU_UPDATE;
				xQueueSend(getPurifierQueueDataHandle(), &mcuAck, xQUEUE_TIMEOUT);
			}
			else if(header_buffer[0] == RENESAS_UPGRADE_NACK)
			{
				resetUartTimer();
				setIsBaudRateChanged();
				renesasWaitforUpgrade++;
				if(renesasWaitforUpgrade >= RENESES_UART_OTA_START_COUNT)
				{
					renesasFiwareUpdate();
					renesasWaitforUpgrade = 0;
				}
			}
			else
			{
				renesasWaitforUpgrade = 0;
			}
		}
		else
			continue;
		if ((header_buffer[0] != CTRL_ACK_HEADER) && (header_buffer[0] != RD_RES_HEADER))
		{
			continue;
		}
		int initialLen = serial_recv_buffered(&superFanObj, &header_buffer[1], sizeof(header_buffer)-1, 1000); // 1000000000

		if ((initialLen+1) == sizeof(header_buffer))
		{

			uint16_t actualLen = (*(uint16_t *)&header_buffer[1]) - sizeof(header_buffer);
			uint8_t *full_packet;
			if(actualLen > (sizeof(hdcpPkt) - sizeof(header_buffer))) continue;
			full_packet = (uint8_t *)hoagsMalloc(actualLen);
			HOAGS_ERR("Malloc Request len:%d\n", actualLen);
			int totalLen = serial_recv_buffered(&superFanObj, (char *)full_packet, actualLen, 1000);
			if (totalLen == actualLen)
			{
				hdcpPkt.header = header_buffer[0];
				hdcpPkt.len = *(uint16_t *)&header_buffer[1];
				hdcpPkt.checksum = *(uint16_t *)&full_packet[0];
				hdcpPkt.seq_num = *(uint16_t *)&full_packet[CHECKSUM_SIZE];
				hdcpPkt.last_seq_num = *(uint16_t *)&full_packet[CHECKSUM_SIZE + SEQ_NUM_SIZE];
				uint16_t payload_length = hdcpPkt.len - (sizeof(hdcpPkt.checksum) + sizeof(hdcpPkt.seq_num) + sizeof(hdcpPkt.last_seq_num));
				memcpy(hdcpPkt.payload, &full_packet[CHECKSUM_SIZE + SEQ_NUM_SIZE + LAST_SEQ_NUM_SIZE], payload_length);
				display_hdcpRd(&hdcpPkt);
				if ((hdcpPkt.header == CTRL_ACK_HEADER || hdcpPkt.header == RD_RES_HEADER) && (hdcpPkt.len < sizeof(hdcpPkt)))
				{
					resetUartTimer();
					setIsBaudRateChanged();
					if (hdcpPkt.payload[0] == 0x00 && hdcpPkt.payload[1] == 0x05 && (hdcpPkt.len > 28))
					{
						if (validateChecksum(&hdcpPkt))
						{
							periodicDataExtract(&hdcpPkt.payload,(hdcpPkt.len - (sizeof(hdcpPkt) - sizeof(hdcpPkt.payload))));
							renesasState = TRUE;
							resetUartCount();
							//printf("checksum success\n");
						}
						else
							printf("Invalid periodic packet\n");
					}
					else if((getIsWaterCustSent() == FALSE) && (hdcpPkt.payload[0] == 0x00 && hdcpPkt.payload[1] == 0x03 &&
							hdcpPkt.payload[4] == 0x00 && hdcpPkt.payload[5] == 0x02)){
						if(validateChecksum(&hdcpPkt)){
							extractWaterCustomizationData(&hdcpPkt.payload,(hdcpPkt.len - (sizeof(hdcpPkt) - sizeof(hdcpPkt.payload))));
						}
						else printf("Received invalid water customization packet\n");
					}
					else {	
						sControlMessage mcuPkt;
						memset(&mcuPkt, 0x00, sizeof(mcuPkt));
						mcuPkt.msgSource = SOURCE_MCU;
						mcuPkt.msgId = MCU_MSG;
						memcpy(&mcuPkt.msgPayload, &hdcpPkt, sizeof(hdcpPkt));
						xQueueSend(getPurifierQueueDataHandle(), &mcuPkt, xQUEUE_TIMEOUT);
					}
				}
				else
				{
					HOAGS_ERR("Invalid header received,Packet is dropped\n");
				}
			}
			else
			{
				HOAGS_ERR("Invalid total length received,Packet is dropped\n");
			}
			free(full_packet);
		}
		else
			HOAGS_ERR("Invalid Initial length received,Packet is dropped\n");
	}
}

void startUartReceiveTask()
{
	HOAGS_INFO("\n");
	if (pdTRUE != xTaskCreate(runUartReceiveTask, "runUartReceiveTask", 1024 + 256, NULL, tskIDLE_PRIORITY + 4, &runUartTaskHandle)) {
		HOAGS_ERR("Failed to create %s\n", __func__);
	}
}
#endif


