#include "hoags_config.h"
#include "FreeRTOS.h"
#include "hoags_config.h"
#include "ameba_soc.h"
#include "main.h"
#include "vfs.h"
#include "osdep_service.h"

void getCurrentCPUload()
{
	char buffer[512];
	HOAGS_MAN("[ATSS]: _AT_SYSTEM_CPU_STATS_\n");
	vTaskGetRunTimeStats((char *)buffer);
	HOAGS_MAN("%s\n", buffer);
}

static char cBuffer[512];
#if  HOAGS_CPU_STATS
void GetCPULoad ()
{
	while(1)
	{
       
		HOAGS_MAN("[ATSS]: _AT_SYSTEM_CPU_STATS_\n");
	    vTaskGetRunTimeStats((char *)cBuffer);
		HOAGS_MAN("%s\n", cBuffer);
		vTaskDelay (CPU_STAT_PRINT_FREQ / portTICK_RATE_MS);// for 2 secs of delay
	}
}
void getcpuload()
{
	struct task_struct task;
	if (rtw_create_task(&task, ((const char *)"cpuload_task"), 1024 * 2, tskIDLE_PRIORITY + 2, GetCPULoad, NULL) != pdPASS) {
		ota_printf(_OTA_ERR_, "\n\r[%s] Create update task failed", __FUNCTION__);

	}
}
#endif

void getCPULoad()
{
	HOAGS_MAN("SYSTEM_CPU_STATS\n");
	vTaskGetRunTimeStats((char *)cBuffer);
	char** splitted_string = split_string(cBuffer, "\n");
	for(int i = 0; splitted_string[i] != NULL; ++i)
	{
		HOAGS_MAN("%s\n", splitted_string[i]);
	}
	//HOAGS_MAN("%s\n", cBuffer);
}