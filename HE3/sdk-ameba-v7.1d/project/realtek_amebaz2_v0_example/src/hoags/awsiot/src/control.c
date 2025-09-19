#include "packets.h"
#include "env.h"
#include "chimney.h"
#include "ac.h"
#include "fan.h"
extern struct fan* fanPtr;
extern struct serial_s superFanObj;
#if 0
void controlACAWSIoT(struct hdcp* hdcpObj)
{
    for(int level = 2, levelIndex = 0; level <= hdcpObj->total_level; ++level)
    {
        if(level == 2)//for now only 2 levels, if third level comes add more if/else
        {
            switch(hdcpObj->level[levelIndex])
            {
                case AC_CMD_POWER_CONTROL:
                    acPowerControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case AC_CMD_SPEED_CONTROL:
                    acSpeedControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case AC_CMD_TEMP_CONTROL:
                    acTempControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case AC_CMD_MODE_CONTROL:
                    acModeControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case AC_CMD_SWING_CONTROL:
                    acSwingControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case AC_CMD_TURBO_CONTROL:
                    acTurboControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case AC_CMD_SLEEP_CONTROL:
                    acSleepControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case AC_CMD_TIMER_CONTROL:
                    if((hdcpObj->level[levelIndex+1]) == 0)
                    {
                        acTimerControl(hdcpObj->payload, hdcpObj->level);
                    }
                    else
                    {
                        cancelAllTimer();
                    }
                    return;
                case AC_CMD_CONDA_CONTROL:
                    acCondaControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case AC_CMD_ECO_CONTROL:
                    acEcoControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case AC_CMD_DISPLAY_CONTROL:
                    acDisplayControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
            }
        }    
    }
}
#endif
void unpackAWSIoT(uint8_t* buffer, struct hdcp* hdcpObj)
{
    HOAGS_INFO("start\n");

	memset(hdcpObj, 0, sizeof(struct hdcp));
    memcpy(hdcpObj, buffer, sizeof(struct hdcp));
   
	hdcpObj->action = __ntohs(hdcpObj->action);
	hdcpObj->len = __ntohs(hdcpObj->len);
	hdcpObj->seq_num = __ntohs(hdcpObj->seq_num);
	hdcpObj->checksum = __ntohl(hdcpObj->checksum);
	hdcpObj->total_size = __ntohl(hdcpObj->total_size);
    hdcpObj->params = __ntohl(hdcpObj->params);

    HOAGS_INFO("end\n");

}

void printAWSIoT(struct hdcp* hdcpObj)
{

	HOAGS_MAN_RAW("header:%02x\n", hdcpObj->header);
	HOAGS_MAN_RAW("action:%d\n", hdcpObj->action);
	HOAGS_MAN_RAW("len:%d\n", hdcpObj->len);
	HOAGS_MAN_RAW("seq_num:%d\n", hdcpObj->seq_num); 
	HOAGS_MAN_RAW("checksum:%d\n",  hdcpObj->checksum);
    HOAGS_MAN_RAW("total_level:%d\n",  hdcpObj->total_level);
    for(int i = 0; i < 5; ++i)
        HOAGS_MAN_RAW("level[%d]:%d ", i, hdcpObj->level[i]);
	HOAGS_MAN_RAW("\ntotal_size:%d\n", hdcpObj->total_size);
    HOAGS_MAN_RAW("\nparams:%d\n", hdcpObj->params);
	HOAGS_MAN_RAW("payload:%02x %02x %02x %02x %02x...%02x %02x %02x %02x %02x\n", 
    hdcpObj->payload[0], hdcpObj->payload[1], hdcpObj->payload[2], hdcpObj->payload[3], hdcpObj->payload[4],
    hdcpObj->payload[hdcpObj->len-1], hdcpObj->payload[hdcpObj->len-2], hdcpObj->payload[hdcpObj->len-3], hdcpObj->payload[hdcpObj->len-4], hdcpObj->payload[hdcpObj->len-5]);
	
}

#if 0

//Hindware chimney& Livpurechimney

void controlChimneyAWSIoT(struct hdcp* hdcpObj)
{
    for(int level = 2, levelIndex = 0; level <= hdcpObj->total_level; ++level)
    {
        if(level == 2)//for now only 2 levels, if third level comes add more if/else
        {
            switch(hdcpObj->level[levelIndex])
            {
                case CHIMNEY_CMD_POWER_CONTROL:
                    chimneyPowerControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case CHIMNEY_CMD_FANSPEED_CONTROL:
                    chimneyFanControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case CHIMNEY_CMD_LED_CONTROL:
                    chimneyLedControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case CHIMNEY_CMD_AUTOCLEAN_CONTROL:
                    chimneyAutocleanControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case CHIMNEY_CMD_MODE:
                    chimneyModeControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case CHIMNEY_SMOKE_HEIGHT_CONTROL:
                    chimneySmokeHeightControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                
            }
        }    
    }
}
#endif

void controlFanAWSIoT(struct hdcp* hdcpObj)
{
	for(int level = 2, levelIndex = 0; level <= hdcpObj->total_level; ++level)
    {
        if(level == 2)//for now only 2 levels, if third level comes add more if/else
        {
            switch(hdcpObj->level[levelIndex])
            {
                case FAN_CMD_POWER_CONTROL:
                    //fanPowerControl(hdcpObj->payload, hdcpObj->total_size);
					printf("Hoags fan power control\n");
                    return;
                case FAN_CMD_INCREASE_SPEED:
                    //step_up_fan_speed(fanPtr);
					printf("Hoags fan increase speed\n");
                    return;
                case FAN_CMD_DECREASE_SPEED:
                    //step_down_fan_speed(fanPtr);
					printf("Hoags fan decrease speed\n");
                    return;
                case FAN_CMD_MODE_CONTROL:
                   // fanModeControl(hdcpObj->payload, hdcpObj->total_size);
					printf("Hoags fan mode control\n");
                    return;
                case FAN_CMD_TIMER_CONTROL:
                    //fanTimerControl(hdcpObj->payload, hdcpObj->total_size);
					printf("Hoags fan timer control\n");
                    return;
                case FAN_CMD_SPEED_CONTROL:
                    //fanSpeedControl(hdcpObj->payload, hdcpObj->total_size);
					printf("Hoags fan speed control\n");
                    return;
                #if 0
                case FAN_CMD_TIMER_SPEED:
                    //fandownTimerControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case FAN_CMD_RPM_CONTROL:
                    Rpmfan(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case FAN_CMD_SPEED_REG_CONTROL:
                    fanregulatorControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case FAN_CMD_BREEZE_CONTROL:
                    fanbreezeControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case FAN_CMD_LED_CONTROL:
                    fanvguardled(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case FAN_CMD_BUZZER_CONTROL:
                    fanvguardbuzzer(hdcpObj->payload, hdcpObj->total_size);
                    return;
                case FAN_CMD_REVERSE_CONTROL:
                    fanvguardreverse(hdcpObj->payload, hdcpObj->total_size);
                    return;
                #endif
            }
        }    
    }
}
#if 0
void controlLightAWSIoT(struct hdcp* hdcpObj)
{
	printf("%s:%d\n", __func__,  __LINE__);
    for(int level = 2, levelIndex = 0; level <= hdcpObj->total_level; ++level)
    {
		printf("%s:%d\n", __func__,  __LINE__);
        if(level == 2)//for now only 2 levels, if third level comes add more if/else
        {
			printf("%s:%d\n", __func__,  __LINE__);
            switch(hdcpObj->level[levelIndex])
            {
                case LIGHT_CMD_POWER_CONTROL:
					printf("%s:%d\n", __func__,  __LINE__);
                    lightPowerControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
				#if 0
                case LIGHT_CMD_INCREASE_BRIGHTNESS:
                    lightIncreaseBrightness();
                    return;
                case LIGHT_CMD_DECREASE_BRIGHTNESS:
                    lightDecreaseBrightness();
                    return;
				#endif
                case LIGHT_CMD_MODE_CONTROL:
                    lightModeControl(hdcpObj->payload, hdcpObj->total_size);
                    return;
            }
        }    
    }
}


void controlAWSIoT(struct hdcp* hdcpObj)
{
	switch(hdcpObj->action)
	{
		case MIC_STATUS:
			controlMic();
			break;
		
		case DEV_NAME:
			break;
		
		#if ENABLE_FAN
		case FAN_CTRL:
			controlFan();
			break;
		#endif

		#if ENABLE_LIGHT
		case LIGHT_CTRL:
			printf("%s:%d\n", __func__,  __LINE__);
			controlLightAWSIoT(hdcpObj);
			break;
		#endif
		
		#if ENABLE_AC
		case AC_CTRL:
			controlACAWSIoT(hdcpObj);
			break;
		#endif

		#if ENABLE_AIRCOOLER
		case AIRCOOLER_CTRL:
			controlAirCooler();
			break;
		#endif
        case CHIMNEY_CTRL:
            controlChimneyAWSIoT(hdcpObj);
            break;
		
		case REBOOT:
			sys_reset();
			break;
		
		case FACTORY_RESET:
			factoryReset();
			break;

		case PING:
			HOAGS_DBG("%s:Pinged to app!\n", __func__);
			break;
		
		case MODEL_RESET:
			setEnvItem(ENV_DEF_MODEL, "1");
			sys_reset();
			break;

/*		
#if VIRTUALFOREST_AC
        case VIRTUALFOREST_TX:
        	handleVFACAWSIoT(hdcpObj);   
            break;
#endif
*/
		default:
			HOAGS_ERR("Unknown command\n");
			break;

	}
}
#endif
