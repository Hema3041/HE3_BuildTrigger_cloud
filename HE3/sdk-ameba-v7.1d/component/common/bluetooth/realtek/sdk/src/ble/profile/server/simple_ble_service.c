/**
*********************************************************************************************************
*               Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
**********************************************************************************************************
* @file     simple_ble_service.c
* @brief    simple BLE profile source file.
* @details  Demonstration of how to implement a self-definition profile.
* @author
* @date
* @version
*********************************************************************************************************
*/

#include <string.h>
#include <stdio.h>
#include <trace_app.h>
#include <simple_ble_service.h>
#include <gap.h>


#include <version.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <packets.h>
#include "wifi_structures.h"
#include "env.h"

#define SIMPLE_BLE_SERVICE_CHAR_V1_READ_INDEX           0x02
#define SIMPLE_BLE_SERVICE_CHAR_V2_WRITE_INDEX          0x05
#define SIMPLE_BLE_SERVICE_CHAR_V3_NOTIFY_INDEX         0x07
#define SIMPLE_BLE_SERVICE_CHAR_V4_INDICATE_INDEX       0x0a
#define SIMPLE_BLE_SERVICE_CHAR_NOTIFY_CCCD_INDEX       (SIMPLE_BLE_SERVICE_CHAR_V3_NOTIFY_INDEX + 1)
#define SIMPLE_BLE_SERVICE_CHAR_INDICATE_CCCD_INDEX     (SIMPLE_BLE_SERVICE_CHAR_V4_INDICATE_INDEX + 1)

#define IS_HOAGS 1
struct hdcpr hdcpr_obj;
extern hwifi scannedSSIDs;
uint8_t conn_ID, service_ID;
BOOL SCAN_FROM_APP = FALSE;
//char* strrr = NULL;

extern unsigned char statusonoff[15];   
extern unsigned char statusmode[15]; 
extern unsigned char statusfansp[15];
extern unsigned char lastUpdate;

/*rehan : begin hardcode some var.*/
//char frdlyn[16]="HVLS__333A";
//char local_bd_addr[13] ="701d0806331a";
uint16_t g_conn_handle;
size_t	notifyCounter = 0;
/*rehan : end hardcode some var.*/


T_SERVER_ID simp_service_id;
/**<  Value of simple read characteristic. */
static uint8_t simple_char_read_value[SIMP_READ_V1_MAX_LEN];
static uint16_t simple_char_read_len = 1;
char v1_user_descr[] = "V1 read characteristic";

/**<  Function pointer used to send event to application from simple profile. Initiated in simp_ble_service_add_service. */
static P_FUN_SERVER_GENERAL_CB pfn_simp_ble_service_cb = NULL;

/**< @brief  profile/service definition.  */
const T_ATTRIB_APPL simple_ble_service_tbl[] =
{
    /* <<Primary Service>>, .. */
    {
        (ATTRIB_FLAG_VALUE_INCL | ATTRIB_FLAG_LE),  /* flags     */
        {                                           /* type_value */
            LO_WORD(GATT_UUID_PRIMARY_SERVICE),
            HI_WORD(GATT_UUID_PRIMARY_SERVICE),
            LO_WORD(GATT_UUID_SIMPLE_PROFILE),      /* service UUID */
            HI_WORD(GATT_UUID_SIMPLE_PROFILE)
        },
        UUID_16BIT_SIZE,                            /* bValueLen     */
        NULL,                                       /* p_value_context */
        GATT_PERM_READ                              /* permissions  */
    },
    /* <<Characteristic>> demo for read */
    {
        ATTRIB_FLAG_VALUE_INCL,                     /* flags */
        {                                           /* type_value */
            LO_WORD(GATT_UUID_CHARACTERISTIC),
            HI_WORD(GATT_UUID_CHARACTERISTIC),
            GATT_CHAR_PROP_READ                     /* characteristic properties */
            /* characteristic UUID not needed here, is UUID of next attrib. */
        },
        1,                                          /* bValueLen */
        NULL,
        GATT_PERM_READ                              /* permissions */
    },
    {
        ATTRIB_FLAG_VALUE_APPL,                     /* flags */
        {                                           /* type_value */
            LO_WORD(GATT_UUID_CHAR_SIMPLE_V1_READ),
            HI_WORD(GATT_UUID_CHAR_SIMPLE_V1_READ)
        },
        0,                                          /* bValueLen */
        NULL,
#if defined(SIMP_SRV_AUTHEN_EN) && SIMP_SRV_AUTHEN_EN
        GATT_PERM_READ_AUTHEN_REQ                   /* permissions */
#else
        GATT_PERM_READ                              /* permissions */
#endif
    },
    {
        ATTRIB_FLAG_VOID | ATTRIB_FLAG_ASCII_Z,     /* flags */
        {                                           /* type_value */
            LO_WORD(GATT_UUID_CHAR_USER_DESCR),
            HI_WORD(GATT_UUID_CHAR_USER_DESCR),
        },
        (sizeof(v1_user_descr) - 1),                                           /* bValueLen */
        (void *)v1_user_descr,
        GATT_PERM_READ           /* permissions */
    },
    /* <<Characteristic>> demo for write */
    {
        ATTRIB_FLAG_VALUE_INCL,                     /* flags */
        {                                           /* type_value */
            LO_WORD(GATT_UUID_CHARACTERISTIC),
            HI_WORD(GATT_UUID_CHARACTERISTIC),
            (GATT_CHAR_PROP_WRITE | GATT_CHAR_PROP_WRITE_NO_RSP) /* characteristic properties */
            /* characteristic UUID not needed here, is UUID of next attrib. */
        },
        1,                                          /* bValueLen */
        NULL,
        GATT_PERM_READ                              /* permissions */
    },
    {
        ATTRIB_FLAG_VALUE_APPL,                     /* flags */
        {                                          /* type_value */
            LO_WORD(GATT_UUID_CHAR_SIMPLE_V2_WRITE),
            HI_WORD(GATT_UUID_CHAR_SIMPLE_V2_WRITE)
        },
        0,                                          /* bValueLen */
        NULL,
#if defined(SIMP_SRV_AUTHEN_EN) && SIMP_SRV_AUTHEN_EN
        GATT_PERM_WRITE_AUTHEN_REQ                  /* permissions */
#else
        GATT_PERM_WRITE                             /* permissions */
#endif
    },
    /* <<Characteristic>>, demo for notify */
    {
        ATTRIB_FLAG_VALUE_INCL,                     /* flags */
        {                                          /* type_value */
            LO_WORD(GATT_UUID_CHARACTERISTIC),
            HI_WORD(GATT_UUID_CHARACTERISTIC),
            (GATT_CHAR_PROP_NOTIFY)                 /* characteristic properties */
            /* characteristic UUID not needed here, is UUID of next attrib. */
        },
        1,                                          /* bValueLen */
        NULL,
        GATT_PERM_READ                              /* permissions */
    },
    {
        ATTRIB_FLAG_VALUE_APPL,                     /* flags */
        {                                         /* type_value */
            LO_WORD(GATT_UUID_CHAR_SIMPLE_V3_NOTIFY),
            HI_WORD(GATT_UUID_CHAR_SIMPLE_V3_NOTIFY)
        },
        0,                                          /* bValueLen */
        NULL,
        GATT_PERM_NONE                              /* permissions */
    },
    /* client characteristic configuration */
    {
        ATTRIB_FLAG_VALUE_INCL | ATTRIB_FLAG_CCCD_APPL,                 /* flags */
        {                                          /* type_value */
            LO_WORD(GATT_UUID_CHAR_CLIENT_CONFIG),
            HI_WORD(GATT_UUID_CHAR_CLIENT_CONFIG),
            /* NOTE: this value has an instantiation for each client, a write to */
            /* this attribute does not modify this default value:                */
            LO_WORD(GATT_CLIENT_CHAR_CONFIG_DEFAULT), /* client char. config. bit field */
            HI_WORD(GATT_CLIENT_CHAR_CONFIG_DEFAULT)
        },
        2,                                          /* bValueLen */
        NULL,
#if defined(SIMP_SRV_AUTHEN_EN) && SIMP_SRV_AUTHEN_EN
        (GATT_PERM_READ_AUTHEN_REQ | GATT_PERM_WRITE_AUTHEN_REQ) /* permissions */
#else
        (GATT_PERM_READ | GATT_PERM_WRITE)          /* permissions */
#endif
    },
    /* <<Characteristic>> demo for indicate */
    {
        ATTRIB_FLAG_VALUE_INCL,                     /* flags */
        {                                           /* type_value */
            LO_WORD(GATT_UUID_CHARACTERISTIC),
            HI_WORD(GATT_UUID_CHARACTERISTIC),
            (GATT_CHAR_PROP_INDICATE)               /* characteristic properties */
            /* characteristic UUID not needed here, is UUID of next attrib. */
        },
        1,                                          /* bValueLen */
        NULL,
        GATT_PERM_READ                              /* permissions */
    },
    {
        ATTRIB_FLAG_VALUE_APPL,                     /* flags */
        {                                           /* type_value */
            LO_WORD(GATT_UUID_CHAR_SIMPLE_V4_INDICATE),
            HI_WORD(GATT_UUID_CHAR_SIMPLE_V4_INDICATE)
        },
        0,                                          /* bValueLen */
        NULL,
        GATT_PERM_NONE                              /* permissions */
    },
    /* client characteristic configuration */
    {
        ATTRIB_FLAG_VALUE_INCL | ATTRIB_FLAG_CCCD_APPL,                 /* flags */
        {                                         /* type_value */
            LO_WORD(GATT_UUID_CHAR_CLIENT_CONFIG),
            HI_WORD(GATT_UUID_CHAR_CLIENT_CONFIG),
            /* NOTE: this value has an instantiation for each client, a write to */
            /* this attribute does not modify this default value:                */
            LO_WORD(GATT_CLIENT_CHAR_CONFIG_DEFAULT), /* client char. config. bit field */
            HI_WORD(GATT_CLIENT_CHAR_CONFIG_DEFAULT)
        },
        2,                                          /* bValueLen */
        NULL,
#if defined(SIMP_SRV_AUTHEN_EN) && SIMP_SRV_AUTHEN_EN
        (GATT_PERM_READ_AUTHEN_REQ | GATT_PERM_WRITE_AUTHEN_REQ) /* permissions */
#else
        (GATT_PERM_READ | GATT_PERM_WRITE)          /* permissions */
#endif
    },
};

/**
  * @brief  Set service related data from application.
  *
  * @param[in] param_type            parameter type to set.
  * @param[in] len                   value length to be set.
  * @param[in] p_value             value to set.
  * @return parameter set result.
  * @retval 0 false
  * @retval 1 true
  */
bool simp_ble_service_set_parameter(T_SIMP_PARAM_TYPE param_type, uint16_t len, void *p_value)
{
    bool ret = true;

    switch (param_type)
    {
    default:
        ret = false;
        break;
    case SIMPLE_BLE_SERVICE_PARAM_V1_READ_CHAR_VAL:
        if (len <= SIMP_READ_V1_MAX_LEN)
        {
            memcpy(simple_char_read_value, p_value, len);
            simple_char_read_len = len;
        }
        else
        {
            ret = false;
        }
        break;
    }

    if (!ret)
    {
        APP_PRINT_ERROR0("simp_ble_service_set_parameter failed");
    }

    return ret;
}

/**
 * @brief read characteristic data from service.
 *
 * @param service_id          ServiceID of characteristic data.
 * @param attrib_index        Attribute index of getting characteristic data.
 * @param offset              Used for Blob Read.
 * @param p_length            length of getting characteristic data.
 * @param pp_value            data got from service.
 * @return Profile procedure result
*/

T_APP_RESULT  simp_ble_service_attr_read_cb(uint8_t conn_id, T_SERVER_ID service_id,
                                            uint16_t attrib_index, uint16_t offset, uint16_t *p_length, uint8_t **pp_value)
{
    (void)offset;
    T_APP_RESULT  cause  = APP_RESULT_SUCCESS;

    switch (attrib_index)
    {
    default:
        APP_PRINT_ERROR1("simp_ble_service_attr_read_cb, Attr not found, index %d", attrib_index);
        cause = APP_RESULT_ATTR_NOT_FOUND;
        break;
    case SIMPLE_BLE_SERVICE_CHAR_V1_READ_INDEX:
    {
        
        TSIMP_CALLBACK_DATA callback_data;
        
        getDevState(&hdcpr_obj);
        printDevState(&hdcpr_obj);


        callback_data.msg_type = SERVICE_CALLBACK_TYPE_READ_CHAR_VALUE;
        callback_data.msg_data.read_value_index = SIMP_READ_V1;
        callback_data.conn_id = conn_id;
        if (pfn_simp_ble_service_cb)
        {
            pfn_simp_ble_service_cb(service_id, (void *)&callback_data);
        }

        *pp_value = (uint8_t *)&hdcpr_obj;
        *p_length = sizeof(struct hdcpr);
        
        conn_ID = conn_id;
        service_ID = service_id;
        printf("length:%d\n", *p_length);  
        printf("conn_id:%d\n", conn_ID);
        printf("service_id:%d\n", service_ID);
        

    }
    break;
    }
    return (cause);
    #if 0
    //   ORIGINAL
    case SIMPLE_BLE_SERVICE_CHAR_V1_READ_INDEX:
        {
            TSIMP_CALLBACK_DATA callback_data;
            callback_data.msg_type = SERVICE_CALLBACK_TYPE_READ_CHAR_VALUE;
            callback_data.msg_data.read_value_index = SIMP_READ_V1;
            callback_data.conn_id = conn_id;
            if (pfn_simp_ble_service_cb)
            {
                pfn_simp_ble_service_cb(service_id, (void *)&callback_data);
            }
           *pp_value = simple_char_read_value;
           *p_length = simple_char_read_len;
            // *pp_value = "rehan";
            // *p_length = strlen("rehan");
          //shaik: 
           if(cause==APP_RESULT_SUCCESS)
           printf("Ble sent Respones Success\n");

        }
        break;
        default:
        APP_PRINT_ERROR1("simp_ble_service_attr_read_cb, Attr not found, index %d", attrib_index);
      //  printf("simp_ble_service_attr_read_cb, Attr not found, index %d", attrib_index);
        cause = APP_RESULT_ATTR_NOT_FOUND;
        break;

    }
    #endif
}

void simple_write_post_callback(uint8_t conn_id, T_SERVER_ID service_id, uint16_t attrib_index,
                                uint16_t length, uint8_t *p_value)
{
    (void)p_value;
    APP_PRINT_INFO4("simple_write_post_callback: conn_id %d, service_id %d, attrib_index 0x%x, length %d",
                    conn_id, service_id, attrib_index, length);
   //  printf("simple_write_post_callback: conn_id %d, service_id %d, attrib_index 0x%x, length %d",
                 //   conn_id, service_id, attrib_index, length);//shaik:
}
/**
 * @brief write characteristic data from service.
 *
 * @param conn_id
 * @param service_id        ServiceID to be written.
 * @param attrib_index      Attribute index of characteristic.
 * @param length            length of value to be written.
 * @param p_value           value to be written.
 * @return Profile procedure result
*/
T_APP_RESULT simp_ble_service_attr_write_cb(uint8_t conn_id, T_SERVER_ID service_id,
                                            uint16_t attrib_index, T_WRITE_TYPE write_type, uint16_t length, uint8_t *p_value,
                                            P_FUN_WRITE_IND_POST_PROC *p_write_ind_post_proc)
{
    TSIMP_CALLBACK_DATA callback_data;
   // T_ATTRIB_APPL ble_shaik;
    T_APP_RESULT  cause = APP_RESULT_SUCCESS;
    APP_PRINT_INFO1("simp_ble_service_attr_write_cb write_type = 0x%x", write_type);
  //  printf("simp_ble_service_attr_write_cb write_type = 0x%x", write_type); //shaik:
    
    *p_write_ind_post_proc = simple_write_post_callback;
    
    TSIMP_UPSTREAM_MSG_DATA rec;
    if (SIMPLE_BLE_SERVICE_CHAR_V2_WRITE_INDEX == attrib_index)
    {
       
      // initMetaData();
		
        /* Make sure written value size is valid. */
        if (p_value == NULL)
        {
            cause  = APP_RESULT_INVALID_VALUE_SIZE;
        }
        else
        {
            /* Notify Application. */
            callback_data.msg_type = SERVICE_CALLBACK_TYPE_WRITE_CHAR_VALUE;
            callback_data.conn_id  = conn_id;
            callback_data.msg_data.write.opcode = SIMP_WRITE_V2;
            callback_data.msg_data.write.write_type = write_type;
            callback_data.msg_data.write.len = length;
            callback_data.msg_data.write.p_value = p_value;
             
             
            //printf("\n %x\n",p_value);
            initMetaData();
            deserialize(callback_data.msg_data.write.p_value);
		    action();
        
            
     /*printf("length: %d\n",callback_data.msg_data.write.len = length);
    for(int i=0;i<length;i++)
    printf("%02x ",*((callback_data.msg_data.write.p_value)+i));
    printf("\n");*/
        
            if (pfn_simp_ble_service_cb)
            {
                pfn_simp_ble_service_cb(service_id, (void *)&callback_data);
            }
        }
    }
    else
    {
      //   if(herr!=ALL_FINE)
        // rebootIfRequired(herr);
        
        APP_PRINT_ERROR2("simp_ble_service_attr_write_cb Error: attrib_index 0x%x, length %d",
                         attrib_index,
                         length);
        cause = APP_RESULT_ATTR_NOT_FOUND;
    }
    return cause;
}


/**
  * @brief send notification of simple notify characteristic value.
  *
  * @param[in] conn_id           connection id
  * @param[in] service_id        service ID of service.
  * @param[in] p_value           characteristic value to notify
  * @param[in] length            characteristic value length to notify
  * @return notification action result
  * @retval 1 true
  * @retval 0 false
  */
bool simp_ble_service_send_v3_notify(uint8_t conn_id, T_SERVER_ID service_id, void *p_value,
                                     uint16_t length)
{
    
    //p_value = (void*)data;
    //length = strlen(data);
    APP_PRINT_INFO0("simp_ble_service_send_v3_notify");
    // send notification to client
    return server_send_data(conn_id, service_id, SIMPLE_BLE_SERVICE_CHAR_V3_NOTIFY_INDEX, p_value,
                            length,
                            GATT_PDU_TYPE_ANY);
}

uint16_t getBleConnHandle() {
	return g_conn_handle;
}

void simple_ble_srv_cccd_notify(uint16_t conn_handle, char* str, int flag)
{
    if (xSemaphoreTake(getMutexBleSend(), portMAX_DELAY) == pdTRUE) {
        char strrr[600 + 1];
        memset(strrr, 0, sizeof(strrr));
        
        switch(flag)
        {
            case STATUS_FLAG:
                snprintf(strrr, sizeof(strrr),"Status:%d:%s", notifyCounter, str);
                break;

            case DIAG_FLAG:
                snprintf(strrr, sizeof(strrr),"Diag:%d:%s", notifyCounter, str);
                break;
            
            #if 1 //Suvarna: TODO
            case POLLACK_FLAG:
                #if VIRTUALFOREST_AC
                sprintf(strrr, "Poll:%d:%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
                                        notifyCounter, 
                                        *(str+0), *(str+1), *(str+2), *(str+3),	*(str+4), *(str+5), *(str+6), *(str+7),
                                        *(str+8), *(str+9), *(str+10), *(str+11), *(str+12), *(str+13), *(str+14), *(str+15),
                                        *(str+16), *(str+17), *(str+18), *(str+19), *(str+20), *(str+21), *(str+22), *(str+23));
                HOAGS_MAN_RAW("%s\n", strrr);
                #elif HAVELLS_AC
                sprintf(strrr, "Poll:%d:%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
                                        notifyCounter, 
                                        *(str+0), *(str+1), *(str+2), *(str+3),	*(str+4), *(str+5), *(str+6), *(str+7),
                                        *(str+8), *(str+9), *(str+10), *(str+11));
                HOAGS_MAN_RAW("%s\n", strrr);
                #elif VERSADEVICES_SUPERFAN_IOT
                sprintf(strrr, "Poll:%d:%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
                                        notifyCounter, 
                                        *(str+0), *(str+1), *(str+2), *(str+3),	*(str+4), *(str+5), *(str+6), *(str+7),
                                        *(str+8), *(str+9), *(str+10), *(str+11), *(str+12), *(str+13), *(str+14));
                HOAGS_MAN_RAW("%s\n", strrr);
                
                if(*(str+6) == 0x02 && *(str+11) == 0x01){
                    statusonoff[11] = 0x01;
                    HOAGS_INFO("statuson: %02x\n",statusonoff[11]);
                }else if(*(str+6) == 0x02 && *(str+11) == 0x00){
                    statusonoff[11] = 0x00;
                    HOAGS_INFO("statusoff: %02x\n",statusonoff[11]);
                }else if(*(str+6) == 0x04) {
                    lastUpdate = 1;	
                    statusonoff[11] = 0x01;
                    HOAGS_INFO("lastupdate: %d, statusonoff: %02x\n", lastUpdate, statusonoff[11]);
                }else if(*(str+6) == 0x21) {
                    lastUpdate = 2;
                    statusonoff[11] = 0x01;
                    HOAGS_INFO("lastupdate: %dstatusonoff: %02x\n", lastUpdate, statusonoff[11]);
                }else if(*(str+6) == 0x22) {
                    lastUpdate = 3;
                    statusonoff[11] = 0x01;
                    HOAGS_INFO("lastupdate: %dstatusonoff: %02x\n", lastUpdate, statusonoff[11]);
                }

                #elif LIVPURE_CHIMNEY
                snprintf(strrr, sizeof(strrr), "Poll:%d:", notifyCounter);
                for (int i = 0; i < strlen(str); i++) {
                snprintf(strrr + strlen(strrr), sizeof(strrr) - strlen(strrr), "%02x", *(str + i));
                }
                HOAGS_MAN_RAW("%s\n", strrr);

                #elif LIVPURE_PURIFIER
                snprintf(strrr, sizeof(strrr), "Poll:%d:", notifyCounter);
                for (int i = 0; i < strlen(str); i++) {
                snprintf(strrr + strlen(strrr), sizeof(strrr) - strlen(strrr), "%02x", *(str + i));
                }
                printf("%s\n", strrr);
                
                #endif
                break;			
            #endif
            case SSID_LIST:
                {
                    int offset = snprintf(strrr, sizeof(strrr), "SSIDList:%d", notifyCounter);
                    printf("scannedSSIDs.len:%d\n",scannedSSIDs.len);
                    for (int i = 0; i < scannedSSIDs.len; i++) {
                        if (scannedSSIDs.ssidList[i][0] != '\0') {
                            printf("scannedSSIDs.ssidList[%d]:%s\n",i,scannedSSIDs.ssidList[i]);
                            int remaining = sizeof(strrr) - offset - 1;
                            int written = snprintf(strrr + offset, remaining, ":%s", scannedSSIDs.ssidList[i]);

                            if (written < 0 || written >= remaining) {
                                HOAGS_INFO("Buffer full. Truncating at index %d\n", i);
                                break;
                            }

                            offset += written;
                        }
                    }
                    // for (int i = 0; i < scannedSSIDs.len; i++) {
                    //     if (scannedSSIDs.ssidList[i]) {
                    //         free(scannedSSIDs.ssidList[i]);
                    //         scannedSSIDs.ssidList[i] = NULL;
                    //     }
                    // }
                    scannedSSIDs.len = 0;
                    memset(scannedSSIDs.ssidList, 0, sizeof(scannedSSIDs.ssidList));
                    HOAGS_MAN_RAW("%s\n", strrr);
                    HOAGS_INFO("\nSSID_LIST list size %ld.\n", strlen(strrr));
                    SCAN_FROM_APP = FALSE;
                }
                break;
            
            case CONNECTION_STATUS:
                snprintf(strrr,sizeof(strrr), "CONNECTIONStatus:%d:%s", notifyCounter, str);
                HOAGS_MAN_RAW("%s", strrr);
                break;
            case BLE_PASSKEY_STATUS:
                snprintf(strrr,sizeof(strrr), "BLEPASSKEYStatus:%d:%s", notifyCounter, str);
                HOAGS_MAN_RAW("%s", strrr);
                break;

            case EVENT_SCHEDULE:
            {
                vTaskDelay(3000);
                char Schedulerevent[500];
                getEnvItem(ENV_SCHEDULER, Schedulerevent);
                snprintf(strrr,sizeof(strrr), "scheduler:0:%s", Schedulerevent);
                HOAGS_MAN_RAW("%s\n", strrr);
            }
            break;

            default:
                break;
        }
        

        if(++notifyCounter > 5000)
                notifyCounter = 0;
        
        simp_ble_service_send_v3_notify(0, 1, strrr, ((strlen(strrr) + 1) < 240) ? (strlen(strrr) + 1) : 240);
        xSemaphoreGive(getMutexBleSend());
    }
    
    return;
}

/**
  * @brief send indication of simple indicate characteristic value.
  *
  * @param[in] conn_id           connection id
  * @param[in] service_id        service ID of service.
  * @param[in] p_value           characteristic value to notify
  * @param[in] length            characteristic value length to notify
  * @return notification action result
  * @retval 1 true
  * @retval 0 false
  */
bool simp_ble_service_send_v4_indicate(uint8_t conn_id, T_SERVER_ID service_id, void *p_value,
                                       uint16_t length)
{
    APP_PRINT_INFO0("simp_ble_service_send_v4_indicate");
    // send indication to client
    return server_send_data(conn_id, service_id, SIMPLE_BLE_SERVICE_CHAR_V4_INDICATE_INDEX, p_value,
                            length, GATT_PDU_TYPE_ANY);
}

/**
 * @brief update CCCD bits from stack.
 *
 * @param conn_id           connection id.
 * @param service_id          Service ID.
 * @param index          Attribute index of characteristic data.
 * @param cccbits         CCCD bits from stack.
 * @return None
*/
void simp_ble_service_cccd_update_cb(uint8_t conn_id, T_SERVER_ID service_id, uint16_t index,
                                     uint16_t cccbits)
{
    TSIMP_CALLBACK_DATA callback_data;
    bool is_handled = false;
    callback_data.conn_id = conn_id;
    callback_data.msg_type = SERVICE_CALLBACK_TYPE_INDIFICATION_NOTIFICATION;
    APP_PRINT_INFO2("simp_ble_service_cccd_update_cb: index = %d, cccbits 0x%x", index, cccbits);
    switch (index)
    {
    case SIMPLE_BLE_SERVICE_CHAR_NOTIFY_CCCD_INDEX:
        {
            if (cccbits & GATT_CLIENT_CHAR_CONFIG_NOTIFY)
            {
                // Enable Notification
                callback_data.msg_data.notification_indification_index = SIMP_NOTIFY_INDICATE_V3_ENABLE;
            }
            else
            {
                // Disable Notification
                callback_data.msg_data.notification_indification_index = SIMP_NOTIFY_INDICATE_V3_DISABLE;
            }
            is_handled =  true;
        }
        break;
    case SIMPLE_BLE_SERVICE_CHAR_INDICATE_CCCD_INDEX:
        {
            if (cccbits & GATT_CLIENT_CHAR_CONFIG_INDICATE)
            {
                // Enable Indication
                callback_data.msg_data.notification_indification_index = SIMP_NOTIFY_INDICATE_V4_ENABLE;
            }
            else
            {
                // Disable Indication
                callback_data.msg_data.notification_indification_index = SIMP_NOTIFY_INDICATE_V4_DISABLE;
            }
            is_handled =  true;
        }
        break;

    default:
        break;
    }
    /* Notify Application. */
    if (pfn_simp_ble_service_cb && (is_handled == true))
    {
        pfn_simp_ble_service_cb(service_id, (void *)&callback_data);
    }
}

/**
 * @brief Simple ble Service Callbacks.
*/
const T_FUN_GATT_SERVICE_CBS simp_ble_service_cbs =
{
    simp_ble_service_attr_read_cb,  // Read callback function pointer
    simp_ble_service_attr_write_cb, // Write callback function pointer
    simp_ble_service_cccd_update_cb // CCCD update callback function pointer
};

/**
  * @brief Add simple BLE service to the BLE stack database.
  *
  * @param[in]   p_func  Callback when service attribute was read, write or cccd update.
  * @return Service id generated by the BLE stack: @ref T_SERVER_ID.
  * @retval 0xFF Operation failure.
  * @retval others Service id assigned by stack.
  *
  */
T_SERVER_ID simp_ble_service_add_service(void *p_func)
{
    if (false == server_add_service(&simp_service_id,
                                    (uint8_t *)simple_ble_service_tbl,
                                    sizeof(simple_ble_service_tbl),
                                    simp_ble_service_cbs))
    {
        APP_PRINT_ERROR0("simp_ble_service_add_service: fail");
        simp_service_id = 0xff;
        return simp_service_id;
    }

    pfn_simp_ble_service_cb = (P_FUN_SERVER_GENERAL_CB)p_func;
    return simp_service_id;
}

