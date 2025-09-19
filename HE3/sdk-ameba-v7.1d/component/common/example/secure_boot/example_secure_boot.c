#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "hal_efuse.h"
#include "efuse_api.h"
#include "osdep_service.h"
#include "device_lock.h"
#include "efuse_logical_api.h"
/*
=========================================================================
 SS Key : the super secure private key used for encryption in secure boot
 S Key : the secure encrypted hash key used for hash in secure boot
=========================================================================
*/
#define PRIV_KEY_LEN 32		// The SS key and S key length is 32 bytes

//these two keys are the same default keys used in SDK
const uint8_t susec_key[PRIV_KEY_LEN] = {
    0x9A, 0x2C, 0x4E, 0x2B, 0x7D, 0x0A, 0x18, 0xCB,
    0x47, 0xD2, 0x61, 0x31, 0x9D, 0xD8, 0x20, 0xDB,
    0x41, 0xFF, 0x7E, 0x7B, 0x44, 0xB1, 0x65, 0xE8,
    0xF5, 0x9D, 0xF9, 0x81, 0xAE, 0x67, 0x13, 0xCB
};
const uint8_t sec_key[PRIV_KEY_LEN] = {
    0x18, 0xA8, 0xEE, 0x9F, 0x9C, 0xAF, 0x59, 0x14,
    0xF6, 0xAB, 0x6E, 0x2F, 0x5F, 0x45, 0xAD, 0x03,
    0x7A, 0x42, 0x4B, 0x8F, 0x58, 0x1B, 0xD0, 0xA3,
    0x5A, 0x1A, 0x25, 0x10, 0xD9, 0x9B, 0xD2, 0x00
};

BOOL isBoardSecured()
{
    unsigned char read_buf[PRIV_KEY_LEN] = {0};
    memset(read_buf, 0x00, sizeof(read_buf));

    unsigned char forComparision[PRIV_KEY_LEN] = {0};
    memset(forComparision, 0xFF, sizeof(forComparision));

    device_mutex_lock(RT_DEV_LOCK_EFUSE);
    int ret = hal_susec_key_get(read_buf);
    device_mutex_unlock(RT_DEV_LOCK_EFUSE);
    // dbg_printf("%s:%d:ret=%d\n", __func__, __LINE__, ret);
    // for(int i=0; i<PRIV_KEY_LEN; i+=8){
    //         dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
    //                 i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
    //     }
    // dbg_printf("%s:%d:ret=%d\n", __func__, __LINE__, ret);
    return memcmp(read_buf, forComparision, sizeof(read_buf));

}

void hoags_efuse_secure(int flag, unsigned char *data)
{
    int ret;
    unsigned char i, write_buf[PRIV_KEY_LEN], read_buf[PRIV_KEY_LEN];
    dbg_printf("\r\nefuse secure boot: Test Start\r\n");

    switch (flag)
    {
    case 1:
    {
        // read SS key
        dbg_printf("Inside Private Secure keys\n");
        device_mutex_lock(RT_DEV_LOCK_EFUSE);
        for(i=0; i<PRIV_KEY_LEN; i+=8){
            dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
                    i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
        }
        ret = hal_susec_key_get(read_buf);
        device_mutex_unlock(RT_DEV_LOCK_EFUSE);
        if(ret < 0){
            dbg_printf("efuse ss key: read address and length error\r\n");
        }
        for(i=0; i<PRIV_KEY_LEN; i+=8){
            dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
                    i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
        }
        dbg_printf("\n");
            // write SS key
        memset(write_buf, 0xFF, PRIV_KEY_LEN);
        if(1){ // fill your data
            for(i=0; i<PRIV_KEY_LEN; i++)
                write_buf[i] = data[i];
        }
        if(1){ // write
            device_mutex_lock(RT_DEV_LOCK_EFUSE);
            ret = efuse_susec_key_write(write_buf);
            device_mutex_unlock(RT_DEV_LOCK_EFUSE);
            if(ret < 0){
                dbg_printf("efuse SS key: write address and length error\r\n");
            }
            dbg_printf("\r\nWrite Done.\r\n");
        }else{
            dbg_printf("\r\nPlease make sure the key is correct before programming in efuse.\r\n");
        }
        dbg_printf("\r\n");
        
        //read SS key
        device_mutex_lock(RT_DEV_LOCK_EFUSE);
        for(i=0; i<PRIV_KEY_LEN; i+=8){
            dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
                    i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
        }
        ret = hal_susec_key_get(read_buf);
        device_mutex_unlock(RT_DEV_LOCK_EFUSE);

        //memcpy(read_buf, write_buf, PRIV_KEY_LEN);

        if(ret < 0){
            dbg_printf("efuse ss key: read address and length error\r\n");
        }
        for(i=0; i<PRIV_KEY_LEN; i+=8){
            dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
                i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
        }
        if(memcmp(write_buf, read_buf, PRIV_KEY_LEN)){
            dbg_printf("efuse ss key: read error\r\n");
        }
    }
    break;

    case 2:
    {
        //read S key, only key index 0 is used for secure boot
        dbg_printf("Inside Private Hash Keys\n");
        device_mutex_lock(RT_DEV_LOCK_EFUSE);
        ret = hal_sec_key_get(read_buf, 0, PRIV_KEY_LEN);
        device_mutex_unlock(RT_DEV_LOCK_EFUSE);
        if(ret < 0){
            dbg_printf("efuse s key: read address and length error\r\n");
            
        }
        dbg_printf("private hash keys:");
        for(i=0; i<PRIV_KEY_LEN; i+=8){
            dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
                i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
        }
        dbg_printf("\n");
        // write S key
        memset(write_buf, 0xFF, PRIV_KEY_LEN);
        if(1){ // fill your data
            for(i=0; i<PRIV_KEY_LEN; i++)
                write_buf[i] = data[i];
        }
        if(1){ // write
            device_mutex_lock(RT_DEV_LOCK_EFUSE);
            ret = efuse_sec_key_write(write_buf, 0);
            device_mutex_unlock(RT_DEV_LOCK_EFUSE);
            if(ret < 0){
                dbg_printf("efuse S key: write address and length error\r\n");
                
            }
            dbg_printf("\r\nWrite Done.\r\n");
        }else{
            dbg_printf("\r\nPlease make sure the key is correct before programming in efuse.\r\n");
        }
        dbg_printf("\r\n");

        //read S key
        device_mutex_lock(RT_DEV_LOCK_EFUSE);
        ret = hal_sec_key_get(read_buf, 0, PRIV_KEY_LEN);

        //memcpy(read_buf, write_buf, PRIV_KEY_LEN);

        device_mutex_unlock(RT_DEV_LOCK_EFUSE);
        if(ret < 0){
            dbg_printf("efuse s key: read address and length error\r\n");
            
        }
        for(i=0; i<PRIV_KEY_LEN; i+=8){
            dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
                i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
        }
        dbg_printf("efuse secure boot keys: Test Done\r\n");
    }
    break;

    case 3:
    {
        dbg_printf("Inside Enabling the Secure mode\n");
        if(1)
        {
            dbg_printf("lock and protect the SS key from being read by CPU\n");
            device_mutex_lock(RT_DEV_LOCK_EFUSE);
            ret = efuse_lock_susec_key();
            device_mutex_unlock(RT_DEV_LOCK_EFUSE);
            if(ret < 0)
            {
                dbg_printf("efuse SS key lock error\r\n");
            }
        }

        if(1)
        {
            dbg_printf("enable the secure boot so that device will only boot with encrypted image\n");

            device_mutex_lock(RT_DEV_LOCK_EFUSE);
            ret = efuse_fw_verify_enable();
            device_mutex_unlock(RT_DEV_LOCK_EFUSE);
            if(ret < 0)
            {
                dbg_printf("efuse secure boot enable error\r\n");
            }
            device_mutex_lock(RT_DEV_LOCK_EFUSE);
            ret = efuse_fw_verify_check();
            device_mutex_unlock(RT_DEV_LOCK_EFUSE);
            if(ret)
                dbg_printf("secure boot is enabled!");
        }

    }
    break;

    default:
        dbg_printf("Invalid command !!!\n");
        break;
    }

}

static void efuse_secure_boot_task(void *param)
{
    int ret;
    u8 i, write_buf[PRIV_KEY_LEN], read_buf[PRIV_KEY_LEN];

    dbg_printf("\r\nefuse secure boot: Test Start\r\n");

    /*
    Step 1: program the super secure private key on eFUSE for image encryption
    */
    // read SS key
    device_mutex_lock(RT_DEV_LOCK_EFUSE);
	for(i=0; i<PRIV_KEY_LEN; i+=8){
        dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
        		i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
    }
    ret = hal_susec_key_get(read_buf);
    device_mutex_unlock(RT_DEV_LOCK_EFUSE);
    if(ret < 0){
        dbg_printf("efuse ss key: read address and length error\r\n");
        goto exit;
    }
    for(i=0; i<PRIV_KEY_LEN; i+=8){
        dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
        		i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
    }

    // write SS key
    memset(write_buf, 0xFF, PRIV_KEY_LEN);
    if(1){ // fill your data
        for(i=0; i<PRIV_KEY_LEN; i++)
            write_buf[i] = susec_key[i];
    }
    if(0){ // write
        device_mutex_lock(RT_DEV_LOCK_EFUSE);
        ret = efuse_susec_key_write(write_buf);
        device_mutex_unlock(RT_DEV_LOCK_EFUSE);
        if(ret < 0){
            dbg_printf("efuse SS key: write address and length error\r\n");
            goto exit;
        }
        dbg_printf("\r\nWrite Done.\r\n");
    }else{
        dbg_printf("\r\nPlease make sure the key is correct before programming in efuse.\r\n");
    }
    dbg_printf("\r\n");
	
     //read SS key
    device_mutex_lock(RT_DEV_LOCK_EFUSE);
    for(i=0; i<PRIV_KEY_LEN; i+=8){
        dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
        		i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
    }
    ret = hal_susec_key_get(read_buf);
    device_mutex_unlock(RT_DEV_LOCK_EFUSE);
    if(ret < 0){
        dbg_printf("efuse ss key: read address and length error\r\n");
        goto exit;
    }
    for(i=0; i<PRIV_KEY_LEN; i+=8){
        dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
            i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
    }
    if(memcmp(write_buf, read_buf, PRIV_KEY_LEN)){
        dbg_printf("efuse ss key: read error\r\n");
        goto exit;
    }

    /*
    Step 2: program the secure hash key which is encrypted by SS key on eFUSE for image hashing
    */
    // read S key, only key index 0 is used for secure boot
    device_mutex_lock(RT_DEV_LOCK_EFUSE);
    ret = hal_sec_key_get(read_buf, 0, PRIV_KEY_LEN);
    device_mutex_unlock(RT_DEV_LOCK_EFUSE);
    if(ret < 0){
        dbg_printf("efuse s key: read address and length error\r\n");
        goto exit;
    }
    for(i=0; i<PRIV_KEY_LEN; i+=8){
        dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
            i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
    }
	
    // write S key
    memset(write_buf, 0xFF, PRIV_KEY_LEN);
    if(1){ // fill your data
        for(i=0; i<PRIV_KEY_LEN; i++)
            write_buf[i] = sec_key[i];
    }
    if(0){ // write
        device_mutex_lock(RT_DEV_LOCK_EFUSE);
        ret = efuse_sec_key_write(write_buf, 0);
        device_mutex_unlock(RT_DEV_LOCK_EFUSE);
        if(ret < 0){
            dbg_printf("efuse S key: write address and length error\r\n");
            goto exit;
        }
        dbg_printf("\r\nWrite Done.\r\n");
    }else{
        dbg_printf("\r\nPlease make sure the key is correct before programming in efuse.\r\n");
    }
    dbg_printf("\r\n");

     //read S key
    device_mutex_lock(RT_DEV_LOCK_EFUSE);
    ret = hal_sec_key_get(read_buf, 0, PRIV_KEY_LEN);
    device_mutex_unlock(RT_DEV_LOCK_EFUSE);
    if(ret < 0){
        dbg_printf("efuse s key: read address and length error\r\n");
        goto exit;
    }
    for(i=0; i<PRIV_KEY_LEN; i+=8){
        dbg_printf("[%d]\t%02X %02X %02X %02X  %02X %02X %02X %02X\r\n",
            i, read_buf[i], read_buf[i+1], read_buf[i+2], read_buf[i+3], read_buf[i+4], read_buf[i+5], read_buf[i+6], read_buf[i+7]);
    }
    dbg_printf("efuse secure boot keys: Test Done\r\n");

    /*
    Step 3: lock and protect the SS key from being read by CPU
    */
    // lock SS key, make SS key unreadable forever.
    // this configure is irreversible, so please do this only if you are certain about SS key
    if(0){
        device_mutex_lock(RT_DEV_LOCK_EFUSE);
        ret = efuse_lock_susec_key();
        device_mutex_unlock(RT_DEV_LOCK_EFUSE);
        if(ret < 0){
            dbg_printf("efuse SS key lock error\r\n");
            goto exit;
        }
    }

    /*
    Step 4: enable the secure boot so that device will only boot with encrypted image
    */
    // enable secure boot, make device boot only with correctly encrypted image
    // this configure is irreversible, so please do this only if you are certain that the fw image is encrypted and hashed with the correct SS key and S key
    if(0){
        device_mutex_lock(RT_DEV_LOCK_EFUSE);
        ret = efuse_fw_verify_enable();
        device_mutex_unlock(RT_DEV_LOCK_EFUSE);
        if(ret < 0){
            dbg_printf("efuse secure boot enable error\r\n");
            goto exit;
        }
        device_mutex_lock(RT_DEV_LOCK_EFUSE);
        ret = efuse_fw_verify_check();
        device_mutex_unlock(RT_DEV_LOCK_EFUSE);
        if(ret)
            dbg_printf("secure boot is enabled!");
    }
    vTaskDelete(NULL);

exit:
    dbg_printf("efuse secure boot: Test Fail!\r\n");
    vTaskDelete(NULL);
}

void example_secure_boot(void)
{
    if(xTaskCreate(efuse_secure_boot_task, ((const char*)"efuse_secure_boot_task"), 512, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
        printf("\r\n\r%s xTaskCreate(efuse_secure_boot_task) failed", __FUNCTION__);

    /*Enable Schedule, Start Kernel*/
    if(rtw_get_scheduler_state() == OS_SCHEDULER_NOT_STARTED)
        vTaskStartScheduler();
    else
        vTaskDelete(NULL);
}