/* includes */   
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hoags_config.h"
#include "htap_config.h"

#include "packets.h"

uint8_t FanConfigured = FALSE;
uint8_t LightConfigured = FALSE;
uint8_t UARTConfigured = FALSE;

uint8_t LedConfRed = FALSE;
uint8_t LedConfGreen = FALSE;
uint8_t LedConfBlue = FALSE;

extern ui_map_st ;
extern HTAP_UART_Pins_St Htap_Uart_Conf;
extern struct circular_buffer;
extern struct Light_Pins_St ;
extern  UART_BAUDRATE_En;

// HTAP_HW_PINS_St HTAP_HW_PINS_Conf[]=
// {
//     {HTAP_HDCP0, RTK_HDCP0},
//     {HTAP_HDCP1, RTK_HDCP1},
//     {HTAP_HDCP2, RTK_HDCP2},
//     {HTAP_HDCP3, RTK_HDCP3},
//     {HTAP_UI0,   RTK_UI0  },
//     {HTAP_UI1,   RTK_UI1  },
//     {HTAP_LED,   HTAP_WW_LED  },
//     {HTAPMINI_LED, HTAP_MINI_WW_LED},
// };

uint32_t HDCP_UART_Baudarte_u32[TOTAL_UART_BAUD] = {0, 0, 0, 600, 1200, 4800, 9600, 28800, 57600, 115200, 153600, 380400, 500000, 1000000, 1500000, 2000000};

#if 0
int8_t readUiConfig(ui_map_st *ui_arr)
{
    HOAGS_INFO("\n");
    size_t sz = 0;
    int errCode = 0;
    void* fileBuffer = hoagsLFSRead(DATA_FOLDER_NAME, UI_MAP_FILE, &sz, &errCode);
    HOAGS_INFO("\n");
    HOAGS_INFO("Size of Stuct : %d\n",sizeof(ui_map_st));
    if(fileBuffer)
    {
        HOAGS_DBG("UI config file  read size=%d\n", sz);
    }
    else
    {
        blink_LED();
        HOAGS_ERR("Error reading UI config file size=%d fileBuffer=%p\n", sz, fileBuffer);
        return -1;
    }
    memset(ui_arr, 0, sizeof(ui_map_st) * UI_MAX_PARAMS);
    memcpy(ui_arr, fileBuffer, sz);

    //ui_arr = (ui_map_st *)fileBuffer;

    if(fileBuffer) {
        free(fileBuffer);
    }

    for(int pos = 0; pos < (sz/sizeof(ui_map_st)); ++pos)
    {
        HOAGS_DBG("ui_arr[%d]. Func Name : %d PinName :%d, Color : %d, Active : %d\n", pos, ui_arr[pos].FuncName, ui_arr[pos].PinName, ui_arr[pos].ActStat_Baud_u32);
        
    }
    return sz;

}
#endif
void HTAP_Init()
{
    int8_t Fan_Pin;
    int8_t WW_Led_Pin;
    //ui_map_st ui_arr[UI_MAX_PARAMS];
    HTAP_UART_Pins_St Htap_Uart_Conf;
    // Htap_Uart_Conf.Rx = HTAP_PIN_NOT_USED;
    Htap_Uart_Conf.Rx = PA_2;
    // Htap_Uart_Conf.Tx = HTAP_PIN_NOT_USED;
    Htap_Uart_Conf.Tx = PA_3;
    Light_Pins_St Htap_Light_Red;
    Htap_Light_Red.Pin = HTAP_PIN_NOT_USED;
    Light_Pins_St Htap_Light_Green;
    Htap_Light_Green.Pin = HTAP_PIN_NOT_USED;
    Light_Pins_St Htap_Light_Blue;
    Htap_Light_Blue.Pin = HTAP_PIN_NOT_USED;
    // Fan_Pin = HTAP_PIN_NOT_USED;
    Fan_Pin = PA_23;
    WW_Led_Pin = HTAP_PIN_NOT_USED;
    // Reading the UI Config file
    #if 0
    int8_t ret = readUiConfig(ui_arr);
    //HOAGS_DBG("return after readuiconfig : %d\n",ret);
    
    // if(ret < 0)
    // {
    //     // blink_LED();
    //     HOAGS_ERR("%s:%d:Error reading command-map file, aborting sensory thread\n");
    //     //vTaskDelete(NULL);    
    //     return;    
    // }
    // Initialization of HTAP Pins
    for(int pos = 0; pos < (ret/sizeof(ui_map_st)); ++pos)
    {
        HOAGS_DBG("Functionality name : %d\n",ui_arr[pos].FuncName);
        switch(ui_arr[pos].FuncName)
        {
        case HDCP_UART_TX :
            // Htap_Uart_Conf.Tx = HTAP_HW_PINS_Conf[ui_arr[pos].PinName].RTK_PinName; 

            // if((BAUD_600 <= ui_arr[pos].ActStat_Baud_u32) && (ui_arr[pos].ActStat_Baud_u32 <= TOTAL_UART_BAUD))
            // {
            //     if (BAUD_600 <= ui_arr[pos].ActStat_Baud_u32)
            //     {
            //         Htap_Uart_Conf.Baudrate_HDCP_u32 = HDCP_UART_Baudarte_u32[ui_arr[pos].ActStat_Baud_u32];
            //         HOAGS_DBG("baudrate configured  in TX = %d\n",Htap_Uart_Conf.Baudrate_HDCP_u32);
            //     }
            // }
            break;
        case HDCP_UART_RX :
            // Htap_Uart_Conf.Rx = HTAP_HW_PINS_Conf[ui_arr[pos].PinName].RTK_PinName;      
            
            // if((BAUD_600 <= ui_arr[pos].ActStat_Baud_u32) && (ui_arr[pos].ActStat_Baud_u32 <= TOTAL_UART_BAUD))
            // {
            //     if (BAUD_600 <= ui_arr[pos].ActStat_Baud_u32)
            //     {
            //         Htap_Uart_Conf.Baudrate_HDCP_u32 = HDCP_UART_Baudarte_u32[ui_arr[pos].ActStat_Baud_u32];
            //         HOAGS_DBG("baudrate configured IN RX = %d\n",Htap_Uart_Conf.Baudrate_HDCP_u32);
            //     }  
            // }
            break;
        case HDCP_SPI_MISO :  
            break;
        case HDCP_SPI_MOSI :
            break;
        case HDCP_SPI_CLK :
            break;
        case HDCP_SPI_CS :
            break;
        case HDCP_I2C_CLK :
            break;
        case HDCP_I2C_DATA :
            break;
        #if 0
        case HTAP_LIGHT_RED :
            Htap_Light_Red.Pin = HTAP_HW_PINS_Conf[ui_arr[pos].PinName].RTK_PinName;  
            Htap_Light_Red.Color = COLOR_RED; 
            Htap_Light_Red.ActStat = HTAP_HW_PINS_Conf[ui_arr[pos].ActStat_Baud_u32].RTK_PinName; 
            break;
        case HTAP_LIGHT_GREEN : 
            Htap_Light_Green.Pin = HTAP_HW_PINS_Conf[ui_arr[pos].PinName].RTK_PinName;  
            Htap_Light_Green.Color = COLOR_GREEN; 
            Htap_Light_Green.ActStat = HTAP_HW_PINS_Conf[ui_arr[pos].ActStat_Baud_u32].RTK_PinName; 
            break;
        case HTAP_LIGHT_BLUE :
            Htap_Light_Blue.Pin = HTAP_HW_PINS_Conf[ui_arr[pos].PinName].RTK_PinName;  
            Htap_Light_Blue.Color = COLOR_BLUE; 
            Htap_Light_Blue.ActStat = HTAP_HW_PINS_Conf[ui_arr[pos].ActStat_Baud_u32].RTK_PinName; 
            break;
        #endif
        case HTAP_FAN_CTRL :
            Fan_Pin = HTAP_HW_PINS_Conf[ui_arr[pos].PinName].RTK_PinName;
            break;
        case HTAP_BTN_1 :
            break;
        case HTAP_BTN_2 :
            break;
        // case HTAP_DETECT_LED :
        //     WW_Led_Pin = HTAP_HW_PINS_Conf[ui_arr[pos].PinName].RTK_PinName;
        //     break;
        default :
            break;

        case  HTAP_RECERVED_2 | HTAP_RECERVED_3 | HTAP_RECERVED_4 | HTAP_RECERVED_5 | HTAP_RECERVED_5 :
            break;

      }
      HOAGS_DBG("Htap hw pin config : %d\n",ui_arr[pos].PinName);
      
    }
    #endif
    //initializeEVBLed();
    // if((!(HTAP_PIN_NOT_USED == Htap_Light_Red.Pin)) | (!(HTAP_PIN_NOT_USED == Htap_Light_Green.Pin )) | (!(HTAP_PIN_NOT_USED == Htap_Light_Blue.Pin )))
    // {
    //     printf("Calling initializelight\n");
    //     LightConfigured = TRUE;
    //     HOAGS_DBG("Red : %d, Green : %d, Blue : %d\n",Htap_Light_Red.Pin, Htap_Light_Green.Pin, Htap_Light_Blue.Pin);
    //     initializeLight(Htap_Light_Red, Htap_Light_Green, Htap_Light_Blue);
        
    // }
	
    if(HTAP_PIN_NOT_USED != Fan_Pin)
    {
       HOAGS_DBG("Calling initializeFan\n");
       FanConfigured = TRUE;
       initializeFan(Fan_Pin);
       
    }
	WW_Led_Pin = PA_20;
    printf("WW_LED_PIN IS INITIALIZED:");
    if(HTAP_PIN_NOT_USED != WW_Led_Pin)
    {
       HOAGS_DBG("Calling initialize WW LED\n");
       initialize_Htap_LED(WW_Led_Pin);
	    WW_LEDNoColor();
    }

	//initializeAc();
    //initializeButton();

    Htap_Uart_Conf.Baudrate_HDCP_u32=HE3_NEW_BAUDRATE;
    
    if(!((HTAP_PIN_NOT_USED == Htap_Uart_Conf.Rx) | (HTAP_PIN_NOT_USED == Htap_Uart_Conf.Tx)))
    {
        #if HOAGS_UART_DUMP
            UARTConfigured = TRUE;
            initializeDumpUart(Htap_Uart_Conf);
        #else
            HOAGS_DBG("Calling initialize_HDCP_Uart\n");
            UARTConfigured = TRUE;
            initialize_HDCP_Uart(Htap_Uart_Conf);
            
        #endif
    }

//    mic_mute_update();
    
    return;
}
