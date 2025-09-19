#if 0
#include <stdlib.h>
#include <sys.h>
#include <device_lock.h>
#include "ota_8710c.h"
#include "ota_h3.h"
#include "lwip/netdb.h"
#include "wdt_api.h"
#include "sys_api.h"
#include "osdep_service.h"
#include "hal_misc.h"
#include "hal_wdt.h"
#include "packets.h"
#include "ota_8710c.h"
#include "simple_ble_service.h"


extern uint32_t sys_update_ota_get_curr_fw_idx(void);
//extern uint32_t sys_update_ota_prepare_addr(void);
//extern void sys_disable_fast_boot (void);

sys_thread_t TaskOTA1 = NULL;
#define STACK_SIZE		1024
#define TASK_PRIORITY	tskIDLE_PRIORITY + 1
static flash_t flash_ota;

int Verify_CheckSum_BLE(uint32_t Addr, u32 Len, uint32_t checksum)
{
	uint32_t flash_checksum = 0;
	u8 *FlashPtr =  (u8 *)Addr;
    u32 len_CkSum = Len;
    for(int i=0; i<len_CkSum; i++)
    {
        flash_checksum += FlashPtr[i];
    }

	if (flash_checksum != checksum) 
    {
       // blink_LED();
		printf("Checksum failed Calculated : 0x%08x Expected : 0x%08x\n",flash_checksum, checksum);
		return 0;
	} 
    else 
    {
		printf("Checksum success Calculated : 0x%08x Expected : 0x%08x\n",flash_checksum, checksum);
		return 1;
        	
    }
}

/*************************end************************************************************/

void ota_update(struct meta_data* file)
{
    OTA_ImgHdr_St OTA_Header;
   // memcpy(&OTA_Header, file->fileBuffer, sizeof(OTA_ImgHdr_St));
    unsigned char sig_backup[32]={0};
    unsigned char *buff = file->fileBuffer;
    uint32_t fw_len = OTA_Header.ImgLen;
	int len=0;
	//if(sizeof(file->fileBuffer)==10240)

    uint32_t address = 0;
	uint32_t NewFWLen = 0, NewFWAddr = 0;
	int ret = -1 ;
	uint32_t curr_fw_idx = 0;

while(TRUE)
{
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	if(flash_stream_write(&flash_ota, address+len, 10240, file->fileBuffer)<0)
		{
				printf("\n\r[%s] Write stream failed", __FUNCTION__);
				device_mutex_unlock(RT_DEV_LOCK_FLASH);
				goto update_ota_exit;
		}
		len +=len + 10240;
        device_mutex_unlock(RT_DEV_LOCK_FLASH);
		if(len == file->cp->total_size)
		break;
}













printf("start bytes\n");
 for(int i=0;i<60;i++)
 {
	printf("%02x ",*(buff+i));
 }

	curr_fw_idx = sys_update_ota_get_curr_fw_idx();
    printf("\n\r[%s] Current firmware index is %d\r\n", __FUNCTION__, curr_fw_idx);
    
    printf("...........OTA_Start............\n");
 if(Verify_CheckSum_BLE((file->fileBuffer+sizeof(OTA_ImgHdr_St)), OTA_Header.ImgLen, OTA_Header.Checksum))
 {

   printf("taking signatutre backup 32byts\n");
   memcpy(sig_backup,buff,32);
   printf(".....Done....\n");
   memset(buff,0xff,32);
   printf("sig 32bytes 0xff done\n");
  // NewFWAddr = update_ota_prepare_addr();
   if(address == -1)
   {
		goto update_ota_exit;
   }
   printf("Erase start\n");

  NewFWLen = update_ota_erase_upg_region(fw_len, NewFWLen, NewFWAddr);
  if(NewFWLen == -1)
  {

		goto update_ota_exit;
  }
   printf("Erase done\n");
 if(NewFWAddr != ~0x0)
 {
		address = NewFWAddr;
		printf("....writing start....\n");
		device_mutex_lock(RT_DEV_LOCK_FLASH);

	    if(flash_stream_write(&flash_ota, address, NewFWLen, buff)<0)
		{
				printf("\n\r[%s] Write stream failed", __FUNCTION__);
				device_mutex_unlock(RT_DEV_LOCK_FLASH);
				goto update_ota_exit;
		}

		device_mutex_unlock(RT_DEV_LOCK_FLASH);
		printf("........write done..........\n");

 }   
        printf("Updating signature to end of ota writing..\n");
        ret = update_ota_signature(sig_backup, NewFWAddr);
		if(ret == -1)
		{
			printf("\r\n[%s] Update signature fail\r\n", __FUNCTION__);
			goto update_ota_exit;
		}
		printf("ota signature updated successfully\n");
 }
 else{
	printf("..............checksum FAIL................\n");
	sys_reset();
 }

update_ota_exit:
	if(buff)
		update_free(buff);	
	TaskOTA1 = NULL;
	printf("\n\r[%s] Update task exit", __FUNCTION__);	
	if(!ret)
	{
		printf("\n\r[%s] Ready to reboot", __FUNCTION__);	
		osDelay(100);
		ota_platform_reset();
	}
	vTaskDelete(NULL);	
	return;
}
#endif
