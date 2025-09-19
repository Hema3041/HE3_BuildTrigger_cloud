#include "log_service.h"
#include "main.h"
#include "stdio.h"
#include "hoags_commands.h"
#include "scheduler.h"
extern BOOL uartEnable;
extern void bist_gpio_test(void);

extern void hoags_efuse_secure(int flag, unsigned char *data);

void printHoagsHelp()
{
    HOAGS_MAN_RAW("\nHOAGS AT COMMAND SET:\n");
    HOAGS_MAN_RAW("==============================\n");
    HOAGS_MAN_RAW("1. henv <-w/r/a> <key> <value> [Set/Get/Print an envitem value]\n");
    HOAGS_MAN_RAW("2. hreset  <enable/disable> [Factory Reset]\n");
	HOAGS_MAN_RAW("3. hstat <cpu/ram> [Prints CPU/RAM load]\n");
	HOAGS_MAN_RAW("4. hstat ram [Prints RAM load]\n");
    HOAGS_MAN_RAW("5. hlist <folder> [List files in folder]\n");
    // HOAGS_MAN_RAW("6. huart <enable/disable> [Enable or Disable UART]");
	// HOAGS_MAN_RAW("7. hmic -hv <mic-vol> -hm <mic-name> -hg <mic-gain> [Starts hoags' mic-record thread]\n");
    // HOAGS_MAN_RAW("8. hsensory -s <score> -t <threshold> [Starts hoags' sensory thread]\n");
	// HOAGS_MAN_RAW("9a. hnr <nr enabled/disabled> <noise suppression level> <agc enabled/disabled> <agc target level> [When UART_DUMP is disabled]\n");
	// HOAGS_MAN_RAW("9b. hnr <nr enabled/disabled> <noise suppression level> <agc enabled/disabled> <agc target level> <mic-gain> <mic-volume> (mic-gain=0, mic-vol=5, preferred) [When UART_DUMP is enabled]\n");
    // HOAGS_MAN_RAW("10. hnr_enable [Enable noise reduction]\n");
    // HOAGS_MAN_RAW("11. hnr_disable [Disable noise reduction]\n");
    // HOAGS_MAN_RAW("12. hnr_threshold [threshold * 1000]\n");
    // HOAGS_MAN_RAW("13. hnr_max_agc_gain [AGC max gain]\n");
    // HOAGS_MAN_RAW("14. hfil_weiner <enable/disable> <snr-value> [Enables/Disables Weiner Filter for NR]\n");
    // HOAGS_MAN_RAW("15. hfil_mean <enable/disable> <filtersize> [Enable/Disable Mean Filter]\n");
    // HOAGS_MAN_RAW("16. hfil_median <enable/disable> [Enable/Disable Median filter]\n");
    // HOAGS_MAN_RAW("17. hfil_iir <enable/disable> <a-coeff> <b-coeff> [Enable/Disable IIR filter]\n");   
    // HOAGS_MAN_RAW("18. hfil_lms <enable/disable> <tapLength> <stepSize> [Enable/Disable LMS filter]\n");
    // HOAGS_MAN_RAW("19. hfil_wavelet <enable/disable> <threshold> [Enable/Disable Wavelet filter]\n");   
    // HOAGS_MAN_RAW("20. hfil_incgain <enable/disable> <gain-factor> [Enable/Disable Gain-increase]\n");
    // HOAGS_MAN_RAW("21. hfil_mediancalc <enable/disable> [Enable/Disable Median Filter]\n");
    // HOAGS_MAN_RAW("22. hfil_wienierref <enable/disable> <iterations> [Enable/Disable Wienier Reference Filter]\n");   
    // HOAGS_MAN_RAW("23. hfil_spectralgate <enable/disable> <threshold> [Enable/Disable Spectral Gating Filter]\n");
    //  HOAGS_MAN_RAW("24. hfactool_test gpio [Run the GPIO test]\n");
}

//enable->1 and disable->0 

int hoagsEFUSERead()
{
    //printf("EFUSE addr=%p cnts=%d\n", addr, cnts);
    uint8_t* EfuseBuf = hoagsMalloc(1024);
    int ret = efuse_logical_read(0x00, 1024, EfuseBuf);

    for (int index = 0; index < 1024; index += 16) {
			printf("EFUSE[%03x]: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", index,
						EfuseBuf[index], EfuseBuf[index + 1], EfuseBuf[index + 2], EfuseBuf[index + 3],
						EfuseBuf[index + 4], EfuseBuf[index + 5], EfuseBuf[index + 6], EfuseBuf[index + 7],
						EfuseBuf[index + 8], EfuseBuf[index + 9], EfuseBuf[index + 10], EfuseBuf[index + 11],
						EfuseBuf[index + 12], EfuseBuf[index + 13], EfuseBuf[index + 14], EfuseBuf[index + 15]);
		}
    
    free(EfuseBuf);
    
}

//int efuse_logical_write(u16 addr, u16 cnts, u8 *data);
int hoagsEFUSEWrite(u16 addr, u16 cnts, u8 *data)
{

    printf("EFUSE write addr=%03x cnts=%d data=%02x ", addr, cnts, data[0]);
    for(int i=0; i<cnts; ++i)
    {
        printf("%02x==", data[i]);
    }
    printf("\n");

    return efuse_logical_write(addr, cnts, data);
}

unsigned char _2char2hex(char high, char low) {
    // Convert a single hex character to its numerical value
    unsigned char hex_value(char c) 
    {
        if (isdigit(c)) return c - '0';      // '0'-'9' -> 0-9
        else return toupper(c) - 'A' + 10;  // 'A'-'F' -> 10-15
    }

    return (hex_value(high) << 4) | hex_value(low); // Combine nibbles into a byte
}

uint16_t hextstrTOshort(const char *str)
{
    return (uint16_t) strtol(str, NULL, 16);
}

BOOL parseHoagsCommands(char* cmdline)
{
    if(!strcmp(cmdline, "reboot"))
    {
        printf("Soft Rebooting...\n");
        sys_reset();
        return 1;
	}
    else if(!strcmp(cmdline, "hreset"))
    {
        printf("Factory Reset...\n");
        factoryReset();
        return 1;
    }
    else if(!strcasecmp(cmdline, "hfactool_test gpio"))
    {
        bist_gpio_test();
        // gpio_check();
        return 1;
    }
    
    char** splitted_cmd = split_string(cmdline, " ");

    size_t pos = 0;

    BOOL isEnvFlag = FALSE;
    BOOL isStatFlag = FALSE;
    BOOL isListFlag = FALSE;
    BOOL isRecordFlag = FALSE;
    BOOL isFactoryReset = FALSE;
    BOOL isEfuse = FALSE;
    BOOL isSecure = FALSE;
    BOOL isReboot = FALSE;
    BOOL isFlashRead = FALSE;

    if(!splitted_cmd[pos])
        return 0;
    
    if(!strcmp(splitted_cmd[pos], HOAGS_CMD_ENV))
        isEnvFlag = TRUE;
    else if(!strcmp(splitted_cmd[pos], HOAGS_CMD_STAT))
        isStatFlag = TRUE;
    else if(!strcmp(splitted_cmd[pos], HOAGS_CMD_LISTDIR))
        isListFlag = TRUE;
    else if(!strcmp(splitted_cmd[pos], HOAGS_CMD_RESET))
        isFactoryReset = TRUE;
    else if(!strcmp(splitted_cmd[pos], HOAGS_CMD_EFUSE))
        isEfuse = TRUE;
    else if(!strcmp(splitted_cmd[pos], HOAGS_CMD_HOAGS_SEC))
        isSecure = TRUE;
    else if(!strcmp(splitted_cmd[pos], HOAGS_CMD_REBOOT))
        isReboot = TRUE;
    #if LIVPURE_PURIFIER
    else if(!strcmp(splitted_cmd[pos], HOAGS_CMD_FLASH_READ)) isFlashRead = TRUE;
    #endif
    else
        return 0;
    ++pos;

    while(splitted_cmd[pos])
    {
        if(isEnvFlag)
        {
            HOAGS_DBG("%s\n", splitted_cmd[pos]);
            if(!strcmp(splitted_cmd[pos], "-w"))
            {
                setEnvItem(splitted_cmd[pos+1], splitted_cmd[pos+2]);
                isEnvFlag = FALSE;
            }
            else if(!strcmp(splitted_cmd[pos], "-r"))
            {
                char value[256];
                getEnvItem(splitted_cmd[pos+1], value);
                HOAGS_DBG("%s -> %s\n", splitted_cmd[pos+1], value);
                isEnvFlag = FALSE;
            }
            else if(!strcmp(splitted_cmd[pos], "-a"))
            {
                print_all_envs();
                isEnvFlag = FALSE;
            }
        }
         else if(isReboot)
        {
            printf("Soft Rebooting...\n");
            sys_reset();
            isReboot = FALSE;
        }
        else if(isStatFlag)
        {
            HOAGS_DBG("%s\n", splitted_cmd[pos]);
            if(!strcmp(splitted_cmd[pos], "ram"))
            {
                char* output = hoagsMalloc(600);
                vTaskList(output);
                printf("%s\n", output);
                printf("Freeheap now=%ld\n", xPortGetFreeHeapSize());
                free(output);
                return 0;
                isStatFlag = FALSE;
            }
            else if(!strcmp(splitted_cmd[pos], "cpu"))
            {
                fATSS();
                isStatFlag = FALSE; 
            }
                
        }
        else if(isFactoryReset)
        {
            printf("Factory Reset...\n");
            factoryReset();
            isFactoryReset = FALSE;
        }
        #if LIVPURE_PURIFIER
        else if(isFlashRead){
            if(!strcmp(splitted_cmd[pos], "read")){
                printf("At hflash Read\n");
                printStoredData();
            }
            else if(!strcmp(splitted_cmd[pos], "erase")){
                printf("At hflash erase\n");
                eraseWaterConsumptionRegion();
            }
            isFlashRead = FALSE;
        }
        #endif
        else if(isEfuse)
        {
            if(!strcmp(splitted_cmd[pos], "rmap"))
            {
                hoagsEFUSERead();
            }
            else if(!strcmp(splitted_cmd[pos], "wmap"))
            {
                for(int i = 0; i < 5; ++i)
                {
                    printf("splitted_cmd[%d]=%s\n", i, splitted_cmd[i]);
                }
                int index = pos;
                uint16_t address = 0x00;
                u16 length = 0x00;
                u8* data = NULL;

                address = hextstrTOshort(splitted_cmd[index+1]);

                length = strlen(splitted_cmd[index+3])/2;

                data = hoagsMalloc(length*2);
                memset(data, 0x00, length*2);

                for(int i=0; i<length; ++i)
                {
                    data[i] = _2char2hex(splitted_cmd[index+3][i*2], splitted_cmd[index+3][i*2+1]);
                }

                int ret = hoagsEFUSEWrite(address, length, data);
                free(data);
                printf("%s:ret=%d\n", __func__, ret);
                MAC_Id_Read();
            }
            else if(!strcmp(splitted_cmd[pos], "uartlogdisable"))
            {
                uint8_t ddd = 0x00;
                int ret = hoagsEFUSEWrite(0x010, 1, &ddd);
                printf("%s:ret=%d\n", __func__, ret);
            }
            else if(!strcmp(splitted_cmd[pos], "appmode"))
            {
                uint8_t ddd = 0x01;
                int ret = hoagsEFUSEWrite(0x011, 1, &ddd);
                printf("%s:ret=%d\n", __func__, ret);
            }
            else if(!strcmp(splitted_cmd[pos], "bistmode"))
            {
                uint8_t ddd = 0xFF;
                int ret = hoagsEFUSEWrite(0x011, 1, &ddd);
                printf("%s:ret=%d\n", __func__, ret);
            }

        }
        else if(isSecure)
        {
            u8* buff = NULL;
           // printf("Inside Secure\n");

            int flag = atoi(splitted_cmd[1]);
            printf("flag:%d\n",flag);
            printf("Keys values: %s\n",splitted_cmd[2]);
            
            int len = strlen(splitted_cmd[2]);
            printf("len:%d\n",len);

            if(strlen(splitted_cmd[2]))
            buff = hoagsMalloc(len);

            memset(buff, 0x00, len);

            for(int i=0; i<len/2; ++i)
                {
                    buff[i] = _2char2hex(splitted_cmd[2][i*2], splitted_cmd[2][i*2+1]);
                }

            hoags_efuse_secure(flag, buff); 
            isSecure = FALSE;

            if(buff) free(buff);
            
        }
        ++pos;
    }

    return 1;
    
}

char** split_string(char* str, const char* delimiter)
{
    char* copy = strdup(str); 
    char** result = NULL;
    size_t count = 0;

    char* token = strtok(copy, delimiter);
    while (token != NULL) 
    {
        result = realloc(result, sizeof(char*) * (count + 1));
        result[count++] = strdup(token);
        token = strtok(NULL, delimiter);
    }

    result = realloc(result, sizeof(char*) * (count + 1));
    result[count] = NULL;

    free(copy);

    return result;
}



 


