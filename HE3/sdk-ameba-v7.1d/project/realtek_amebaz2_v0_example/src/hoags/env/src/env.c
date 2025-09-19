#include "env.h"
#include "flash_api.h"
#include <device_lock.h>
#include "hoags_config.h"


#define ENV_WSIZE 100
#define ENV_COUNT 16

static flash_t flash_env;

void Erased_Env_part(void)
{
    int write_sector1 = 0;
    int erased1 = 0;
    int adress1 = ENV_START_ADDR;
    while (erased1 < ENV_TOTAL_SIZE)
    {
        unsigned int current_address = adress1 + (write_sector1 * 4096);
        device_mutex_lock(RT_DEV_LOCK_FLASH);
        flash_erase_sector(&flash_env, current_address);
        device_mutex_unlock(RT_DEV_LOCK_FLASH);
        write_sector1++;
        erased1 += 4096;
    }
    HOAGS_INFO("ENV_part_Erased_success");
}

static struct env envArray_to_flash[] = {
    {ENV_BLEPASSWORD, "aaaa"},
    {ENV_FRIENDLYNAME, "0"},
    {ENV_CUSTNAME, "Livpure"},
    {ENV_PRODTYPE, "purifier"},
    {ENV_PRODMODEL, PRODUCT_MODEL_NUMBER},
    {ENV_SERIALNO, "<>"},
    {HOT_TEMPERATURE, "0"},
    {ENV_USERID, "0"},
    {WARM_TEMPERATURE, "0"},
    {CHILDLOCKSTATE, "0"},
    {ENV_POWERCONTROL, "0"},
    {ENV_MODECONTROL, "0"},
    {ENV_SPEEDCONTROL, "0"},
    {ENV_TEMPCONTROL, "0"},
    {GLASS_CUST, "0"},
    {BOTTLE_CUST, "0"},
    {INLET_TDS, "0"},
    {INLET_TDS_OFFSET,"0"},
    {OUTLET_TDS, "0"}
};

static struct env envArray[] = {
    {ENV_BLEPASSWORD, NULL},
    {ENV_FRIENDLYNAME, NULL},
    {ENV_CUSTNAME, NULL},
    {ENV_PRODTYPE, NULL},
    {ENV_PRODMODEL, NULL},
    {ENV_SERIALNO, NULL},
    {HOT_TEMPERATURE, NULL},
    {ENV_USERID, NULL},
    {WARM_TEMPERATURE, NULL},
    {CHILDLOCKSTATE, NULL},
    {ENV_POWERCONTROL, NULL},
    {ENV_MODECONTROL, NULL},
    {ENV_SPEEDCONTROL, NULL},
    {ENV_TEMPCONTROL, NULL},
    {GLASS_CUST, NULL},
    {BOTTLE_CUST, NULL},
    {INLET_TDS, NULL},
    {INLET_TDS_OFFSET,NULL},
    {OUTLET_TDS,NULL}
};

bool envAry_write_to_flash(void)
{
    bool sts = false;
    printf("%s\n", __func__);
    int pos = 0;
    unsigned char *buff = (unsigned char *)calloc(ENV_WSIZE, sizeof(char));

    for (int i = 0; i < sizeof(envArray_to_flash) / sizeof(struct env); ++i)
    {
        if (envArray_to_flash[i].value != 0x00)
        {
            int val_len = strlen(envArray_to_flash[i].value) + 1;
            memcpy(buff + pos, envArray_to_flash[i].value, val_len);
            pos += val_len;
        }
    }
    device_mutex_lock(RT_DEV_LOCK_FLASH);
    if (flash_burst_write(&flash_env, ENV_START_ADDR, ENV_WSIZE, buff) < 0)
    {
        printf("\n\r[%s] Write stream failed", __func__);
        device_mutex_unlock(RT_DEV_LOCK_FLASH);
        sts = false;
    }
    else
    {
     device_mutex_unlock(RT_DEV_LOCK_FLASH);
     sts = true;
    }
    //sts = flash_write_locked(ENV_START_ADDR, ENV_WSIZE, buff);
    if(buff) free(buff);

    return sts;
}
bool envAry_read_from_flash(void)
{
    printf("%s\n", __func__);
    unsigned char *buff = (unsigned char *)calloc(ENV_WSIZE, sizeof(char));
    bool sts = false;
    size_t index = 0;

    // DBG_DIRECT("size_env:%d", size_env);
    // sts = flash_read_locked(ENV_START_ADDR, ENV_WSIZE, buff);
    // for(int i=0;i<size_env;i++)
    // DBG_DIRECT("%c",buff[i]);
    device_mutex_lock(RT_DEV_LOCK_FLASH);
    sts = flash_burst_read(&flash_env, ENV_START_ADDR, ENV_WSIZE, buff);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);


    char *ptr = buff;
    for (int pos = 0; pos < ENV_WSIZE; ++pos)
    {
        if (*(ptr + pos) != 0x00)
        {
            int len = strlen((char *)(ptr + pos));
            char *val = malloc(len + 1);
            memcpy(val, ptr + pos, len + 1);
            //  printf("val:%s",val);
            envArray[index].value = val;
            ++index;
            pos += len;
        }
        else if (*(ptr + pos) == 0xff)
            break;
    }

    if(buff) free(buff);
    return sts;
}

void print_all_envs(void)
{
    size_t index = 0;
    char *key = NULL;
    char *value = NULL;
    size_t maxSize = sizeof(envArray) / sizeof(struct env);
    printf("%s\n", __func__);
    while (index < maxSize)
    {
        key = envArray[index].key;
        value = envArray[index].value;
        // if(strncmp(key, "reserved", 8) != 0)
        printf("%s->%s\n", key, value);
        ++index;
    }
}
static int getIndex(const char *key)
{
    for (int index = 0; index < sizeof(envArray) / sizeof(struct env); ++index)
    {
        if (!strcmp(key, envArray[index].key))
            return index;
    }

    return -1;
}
bool getEnvItem(const char *key, char *value)
{
    int index = getIndex(key);
    if (index < 0)
    {
        printf("Requested env not found '%s'\n", key);
        return false;
    }
    if (envArray[index].value != NULL)
    {
        size_t len = strnlen(envArray[index].value, ENV_WSIZE); // use max bound
        strncpy(value, envArray[index].value, len);
        value[len] = '\0';  // null-terminate just in case
    }
    return true;
}
bool setEnvItem(const char *key, char *value)
{
    if (!key || !value || *value == '\0') {
        printf("Invalid key or value\n");
        return false;
    }

    int index = getIndex(key);
    if (index < 0) {
        printf("Requested env not found '%s'\n", key);
        return false;
    }

    // Determine max length for value
    size_t max_len = ENV_WSIZE;
    if (strcmp(key, ENV_FRIENDLYNAME) == 0) {
        max_len = 12;
        printf("friendlyname=%s\n", value);
    }

    // Safe trimming (don't modify input directly)
    size_t val_len = strnlen(value, max_len);
    char *new_value = (char *)malloc(val_len + 1);
    if (!new_value) {
        printf("Memory allocation failed\n");
        return false;
    }

    strncpy(new_value, value, val_len);
    new_value[val_len] = '\0';

    // Free and clear old value
    if (envArray[index].value) {
        memset(envArray[index].value, 0x00, strnlen(envArray[index].value, ENV_WSIZE));
        free(envArray[index].value);
    }

    // Assign new value
    envArray[index].value = new_value;

    // Rebuild flash buffer
    int pos = 0;
    unsigned char *buff = (unsigned char *)calloc(ENV_WSIZE, sizeof(char));
    if (!buff) {
        printf("Failed to allocate flash buffer\n");
        return false;
    }

    for (int i = 0; i < sizeof(envArray) / sizeof(struct env); ++i) {
        if (envArray[i].value) {
            size_t len = strnlen(envArray[i].value, ENV_WSIZE) + 1;
            if ((pos + len) > ENV_WSIZE) {
                printf("Flash buffer overflow while writing env values\n");
                break;
            }
            memcpy(buff + pos, envArray[i].value, len);
            pos += len;
        }
    }

    // Write to flash
    Erased_Env_part();
    device_mutex_lock(RT_DEV_LOCK_FLASH);
    flash_burst_write(&flash_env, ENV_START_ADDR, ENV_WSIZE, buff);
    device_mutex_unlock(RT_DEV_LOCK_FLASH);

    printf("flash_read_Rslt:%d\n", envAry_read_from_flash());

    free(buff);
    return true;
}


void initEnv(void)
{
    char buf[16]={0};
    device_mutex_lock(RT_DEV_LOCK_FLASH);
    flash_burst_read(&flash_env, ENV_START_ADDR, 16, buf);
    device_mutex_unlock(RT_DEV_LOCK_FLASH);
    // printf("EnvAdr:");
    // for(int i=0;i<16;i++)
    // printf("%02x ",buf[i]);
    // printf("\n");
    if(buf[0] == 0xff && buf[2] == 0xff && buf[9] == 0xff)
    {
       char frdlyn[16];
       memset(frdlyn, 0x00, sizeof(frdlyn));

       envAry_write_to_flash();
       vTaskDelay(pdMS_TO_TICKS(50));
       envAry_read_from_flash();
       //uint8_t mac_addr[6];
       memcpy(frdlyn, PREFIX_FN, sizeof(PREFIX_FN));

       for(int i = 0; i<4; ++i)
        {
            frdlyn[strlen(PREFIX_FN)+i] = umObj.macid[i + 8];   
        }
        setEnvItem(ENV_FRIENDLYNAME, frdlyn);
    }
    #if 0
    char frdlyn[16];
    memset(frdlyn, 0x00, sizeof(frdlyn));
    memcpy(frdlyn, PREFIX_FN, sizeof(PREFIX_FN));
    for(int i = 0; i<4; ++i)
    {
        frdlyn[strlen(PREFIX_FN)+i] = umObj.macid[i + 8];   
    }
    envAry_read_from_flash();
    setEnvItem(ENV_FRIENDLYNAME, frdlyn);
    
    #endif
    envAry_read_from_flash();
    vTaskDelay(pdMS_TO_TICKS(50));
    //print_all_envs();
    vTaskDelay(pdMS_TO_TICKS(50));
}
void displayEnvInRAM()
{
    for(int i = 0; i < sizeof(envArray)/sizeof(struct env); ++i)
    {
        HOAGS_ERR("%s=%s\n", envArray[i].key, envArray[i].value);
    }
}
    // char properFN[16];
    // memset(properFN, 0, sizeof(properFN));
    // memcpy(properFN, PREFIX_FN, sizeof(PREFIX_FN));
    // HOAGS_INFO("\n");
    // for(int i = 0; i<4; ++i)
    // {
    //     properFN[strlen(PREFIX_FN)+i] = umObj.macid[i + 8];   
    // }
    // HOAGS_INFO("properFN=%s\n", properFN);
#if 0
extern BOOL isEnvInitialized;
QueueHandle_t envQ = NULL;
extern struct univMacid umObj;
#define ENV_WSIZE 100

#define ENV_COUNT 16
static struct env envArray[ENV_COUNT];
QueueHandle_t envTaskHandle;

// static struct env envArray[] = {
//     {ENV_SSID,                 "0"},
//     {ENV_BLEPASSWORD,       "aaaa"},
//     {ENV_FRIENDLYNAME,         "0"},
//     {ENV_CUSTNAME,         "Versa_Devices"},
//     {ENV_PRODTYPE,            "fan"},
//     {ENV_PRODMODEL,           "FAN"},
//     {ENV_SCHEDULER,           "0"},
//     {ENV_RESERVED_7,           "0"},
//     {ENV_RESERVED_8,           "0"},
//     {ENV_RESERVED_9,           "0"},
//     {ENV_RESERVED_10,          "0"},
//     {ENV_POWERCONTROL,         "0"},
//     {ENV_MODECONTROL,          "0"},
//     {ENV_SPEEDCONTROL,         "0"},
//     {ENV_TEMPCONTROL,          "0"},
//     {ENV_RESERVED_15,          "0"}
// };

XIP_TEXT_SECTION
void displayEnvInRAM()
{
    for(int i = 0; i < sizeof(envArray)/sizeof(struct env); ++i)
    {
        HOAGS_ERR("%s=%s\n", envArray[i].key, envArray[i].value);
    }
}
#if 0
static void displayEnvInFlash()
{
    u16 len=0;
    void * buff = hoagsReadFATFS(fatfs_flash.drv, ENVUSER, &len);
    if(buff ==  NULL || len == 00)
    {
        return;
    }
    size_t index = 0;
    char *ptr = buff;
    for (int pos = 0; pos < ENV_WSIZE && index < sizeof(envArray)/sizeof(struct env) ; ++pos, ++index)
    {
        if (*(ptr + pos) != 0x00)
        {
            int len = strlen((char *)(ptr + pos));
            char *val = hoagsMalloc(len + 1);
            memcpy(val, ptr + pos, len + 1);
            HOAGS_INFO("%s=%s\n", envArray[index].key, val);
            free(val);
            ++index;
            pos += len;
        }
        else if (*(ptr + pos) == 0xff)
        {
            break;
        }
    }
 
    if(buff)
    {
        free(buff);
    }


}
#endif
XIP_TEXT_SECTION
static void initEnvArray() {

                    XIP_SEC_RODATA_SECTION static struct env temp[] = {
                            {ENV_SSID, "0"},
                            {ENV_BLEPASSWORD, "aaaa"},
                            {ENV_FRIENDLYNAME, "0"},
                            {ENV_CUSTNAME, "Indcool"},
                            {ENV_PRODTYPE, "ac"},
                            {ENV_PRODMODEL, "AC"},
                            {ENV_SCHEDULER, "0"},
                            {ENV_USERID, "0"/*"6183dd1a-6031-70fa-f63d-d6257a5f56b7"*/},
                            {ENV_LOCATION, "0"},
                            {ENV_RESERVED_9, "0"},
                            {ENV_RESERVED_10, "0"},
                            {ENV_POWERCONTROL, "0"},
                            {ENV_MODECONTROL, "0"},
                            {ENV_SPEEDCONTROL, "0"},
                            {ENV_TEMPCONTROL, "0"},
                            {ENV_RESERVED_15, "0"}
                        };

    for (int i = 0; i < sizeof(temp)/sizeof(struct env); i++) {
        envArray[i].key = temp[i].key; // Key is assumed to be constant
        envArray[i].value = strdup(temp[i].value); // Allocate and copy value to heap
    }
}

XIP_TEXT_SECTION
static int getIndex(const char *key)
{
    for (int index = 0; index < sizeof(envArray) / sizeof(struct env); ++index)
    {
        if (!strcmp(key, envArray[index].key))
        {
            return index;
        }
    }

    return -1;
}

XIP_TEXT_SECTION
BOOL getEnvItem(const char *key, char *value)
{
    int index = getIndex(key);
    if (index < 0)
    {
        HOAGS_ERR("Requested env not found '%s'\n", key);
        return FALSE;
    }
    strcpy(value, envArray[index].value);

    return TRUE;
}

XIP_TEXT_SECTION
static BOOL generateMissing(const char* filename)
{
    int sts = -1;
    int pos = 0;
    int len=0;
    unsigned char *buff = (unsigned char *)hoagsMalloc( ENV_WSIZE);
    memset(&buff[0], 0x00, ENV_WSIZE);
   
    for (int i = 0; i < sizeof(envArray) / sizeof(struct env); ++i)
    {
        if (envArray[i].value != 0x00)
        {
            int val_len = strlen(envArray[i].value) + 1;
            memcpy(buff + pos, envArray[i].value, val_len);
            pos += val_len;
            len += val_len;
        }
    }
 
    hoagsWriteFATFS( fatfs_flash.drv, filename , buff , pos, OVERWRITE);
 
    if(buff) 
    {
        free(buff);
    }
   
    return TRUE;
}

XIP_TEXT_SECTION
static BOOL setEnvItemStatic(const char *key, char *value)
{
    HOAGS_ERR("\n");
    if (!value || *value == 0x00)
    {
        return FALSE;
    }

    HOAGS_ERR("\n");
    int index = getIndex(key);
    if (index < 0)
    {
        printf("Requested env not found '%s'\n", key);
        return false;
    }
    HOAGS_ERR("\n");
    if (strcmp(key, ENV_FRIENDLYNAME) == 0)
    {
        if (strlen(value) > 12)
        {
            *(value + 12) = 0x00;
        }
    }
    else
    {
        if (strlen(value) > 1023)
        {
            *(value + 1023) = 0x00;
        }
    }

    HOAGS_ERR("\n");
    if(envArray[index].value)
    {
        free(envArray[index].value);
    }

    HOAGS_ERR("\n");
    char *newValue = hoagsMalloc(strlen(value) + 1);
    
    strcpy(newValue, value);
    
    envArray[index].value = newValue;
    
    int pos = 0;
    unsigned char *buff = (unsigned char *)hoagsMalloc(ENV_WSIZE);

    for (int i = 0; i < sizeof(envArray) / sizeof(struct env); ++i)
    {
        if (envArray[i].value != 0x00)
        {
            int val_len = strlen(envArray[i].value) + 1;
            memcpy(buff + pos, envArray[i].value, val_len);
            pos += val_len;
        }
    }

    HOAGS_ERR("\n");

    if(hoagsFATFSDelFile(ENVUSER) != FR_OK)
    {
        HOAGS_ERR("Error deleting %s\n", ENVUSER);
        if (buff)
        {
            free(buff);
        }

        if (newValue)
        {
            free(newValue);
        }

        return FALSE;
    }
    
    HOAGS_ERR("\n");

    generateMissing(ENVUSER);
    
    if (buff)
    {
        free(buff);
    }  

    HOAGS_ERR("\n");

    return TRUE;
}

XIP_TEXT_SECTION
BOOL setEnvItem(const char* key, const char* value, BOOL block)
{

	while(!isEnvInitialized || !envQ)
	{
		HOAGS_ERR("Waiting for env to be initialized...\n");
        vTaskDelay(1000);
	}

	struct env* newItem = (struct env*) hoagsMalloc(sizeof(struct env));
    newItem->key = strdup(key);
    newItem->value = strdup(value);

	if(xQueueSend(envQ, &newItem, 0) == pdPASS)
	{
		HOAGS_INFO("Sent address=%p keyAdress=%p valueAddress=%p\n", newItem, newItem->key, newItem->value);
	}
	else
	{
		HOAGS_ERR("failed\n");
		return FALSE;
	}

    if(block)
    {
        vTaskDelay(2000);
    }

	return TRUE;
}

XIP_TEXT_SECTION
void freeEnvTask()
{
    //HOAGS_ERR("\n");
    for(int i = 0; i < sizeof(envArray)/sizeof(struct env); ++i)
    {
        //HOAGS_ERR("\n");
        free(envArray[i].value);
    }
    //HOAGS_ERR("\n");
    vTaskDelete(envTaskHandle);
    HOAGS_ERR("\n");
}

XIP_TEXT_SECTION
static BOOL loadEnvs()
{
    size_t index = 0;
 
    if(fatfs_flash_get_param(&fatfs_flash))
    {
        HOAGS_ERR("Error getting params\n");
        return FALSE;
    }

    u16 len=0;
    void * buff = hoagsReadFATFS(fatfs_flash.drv, ENVUSER, &len);
    if(buff ==  NULL || len == 00)
    {
        return FALSE;
    }
    
    while(!umObj.isFetched)
    {
        HOAGS_INFO("Awaiting for macid to update\n");
        vTaskDelay(1000);
    }
    char *ptr = buff;
    for (int pos = 0; pos < ENV_WSIZE && index < sizeof(envArray)/sizeof(struct env) ; ++pos, ++index)
    {
        if (*(ptr + pos) != 0x00)
        {
            int len = strlen((char *)(ptr + pos));
            char *val = hoagsMalloc(len + 1);
            memcpy(val, ptr + pos, len + 1);

            if(envArray[index].value)
            {
                free(envArray[index].value);
            }

            HOAGS_INFO("Fetched env index=%d key=%s macid=%s\n", index, envArray[index].key, umObj.macid);
            /*Handle special condition for Friendlyname*/
            if(strcmp(envArray[index].key, ENV_FRIENDLYNAME) == 0 && len <= 2)
            {
                HOAGS_INFO("\n");
                free(val);
                char properFN[16];
                memset(properFN, 0, sizeof(properFN));
                memcpy(properFN, PREFIX_FN, sizeof(PREFIX_FN));
                HOAGS_INFO("\n");
                for(int i = 0; i<4; ++i)
                {
                    properFN[strlen(PREFIX_FN)+i] = umObj.macid[i + 8];   
                }
                HOAGS_INFO("properFN=%s\n", properFN);

                envArray[index].value = hoagsMalloc(strlen(properFN));
                HOAGS_INFO("\n");
                strcpy(envArray[index].value, &(properFN[0]));
                HOAGS_INFO("\n");
            }
            else
            {
                envArray[index].value = val;
            }
            
            pos += len;
        }
        else if (*(ptr + pos) == 0xff)
        {
            break;
        }
    }
 
    if(buff) 
    {
        free(buff);
    }
    
    return TRUE;
}
 
XIP_TEXT_SECTION
static BOOL isPresent(char* filename)
{

    char filepath[64];
    memset(filepath, 0x00, sizeof(filepath));

    strcpy(filepath, fatfs_flash.drv);
    sprintf(&filepath[strlen(filepath)], "%s", filename);

    FIL flptr;
    FRESULT res = f_open(&flptr, filepath, FA_OPEN_EXISTING | FA_READ);
    if(res == FR_OK)
    {
        f_close(&flptr);
        return TRUE;
    }

    return FALSE;

}

void hlist(void){
    list_files(fatfs_flash.drv);
    HOAGS_INFO("\n");
}

XIP_TEXT_SECTION
void initEnv()
{
    initEnvArray();

    // if(fatfs_flash_get_param(&fatfs_flash))
    // {
	// 	HOAGS_ERR("Not able to get parm\n");
	// 	return;
	// }

    BOOL flag =  isPresent(ENVUSER);

    HOAGS_INFO("isFilePresent=%d\n", flag);

    if(flag == FALSE)
    {
        if(generateMissing(ENVUSER) == TRUE)
        {
            HOAGS_INFO("Successfully generated %s\n", ENVUSER);
        }
        else
        {
            HOAGS_ERR("Error generating %s\n", ENVUSER);
        }
    }

    if(loadEnvs() > 0)
    {
        isEnvInitialized = TRUE;
        HOAGS_INFO("Success loading ENVs\n");
        //displayEnvInRAM();
    }
    else
    {
        HOAGS_ERR("Error loading ENVs\n");
    }

    envQ =  xQueueCreate( 5, sizeof(struct env *) );
    
    struct env* envObj;
    while(TRUE)
    {
        HOAGS_ERR("Keeping busy\n");
        if(xQueueReceive( envQ, &envObj, portMAX_DELAY ) == pdPASS)
        {
            HOAGS_ERR("Setting key=%s value=%s,", envObj->key, envObj->value);
            setEnvItemStatic(envObj->key, envObj->value); 
            free(envObj->key);
            free(envObj->value);
            free(envObj);
            //displayEnvInFlash();
        }
    }

    vTaskDelete(NULL);
}

void envTask(void)
{
    //Suvarna: Don't change the below stack size
	if(xTaskCreate(initEnv, ((const char*)"initEnv"), 1536, NULL, tskIDLE_PRIORITY + 4, &envTaskHandle) != pdPASS)
		HOAGS_ERR("Task creation failed\n");
}
#endif


