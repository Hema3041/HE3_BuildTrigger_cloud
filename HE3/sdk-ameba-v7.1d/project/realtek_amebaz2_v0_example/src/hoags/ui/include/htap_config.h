#include "PinNames.h"

#define MAX_HTPA_PINS (sizeof(HTAP_HW_PINS_Conf)/sizeof(HTAP_HW_PINS_St))
#define HTAP_PIN_NOT_USED -1

typedef enum GPIO_PIN_STATE
{
    NA = 0,
    ACTIVE_HIGH = 1,
    ACTIVE_LOW
}GPIO_PIN_STATE_En;


typedef enum HDCP_UART_BAUDRATE
{
    BAUD_INVALID0 = 0,
    BAUD_INVALID1 = 1,    //As the place holder for ACTIVE_HIGH/LOW are same as Baudrate adding 3 invlaid position to skip ACTIVE HIGH/LOW indexes
    BAUD_INVALID2 = 2,
    BAUD_600 = 3,
    BAUD_1200,
    BAUD_4800,
    BAUD_9600,
    BAUD_28800,
    BAUD_57600,
    BAUD_115200,
    BAUD_153600,
    BAUD_380400,
    BAUD_500000,
    BAUD_1000000,
    BAUD_1500000,
    BAUD_2000000,
    BAUD_3000000,
    TOTAL_UART_BAUD = BAUD_3000000
}UART_BAUDRATE_En;


typedef enum HTAP_PINS
{
    HTAP_HDCP0 = 0 ,
    HTAP_HDCP1 ,
    HTAP_HDCP2 ,
    HTAP_HDCP3 ,
    HTAP_UI0 ,
    HTAP_UI1 ,
    HTAP_LED,
    HTAPMINI_LED
}HTAP_PINS_En;

typedef enum LIGHT_COLOR
{
    COLOR_RED = 0,
    COLOR_GREEN,
    COLOR_BLUE,
}LIGHT_COLOR_En;


typedef enum HTAP_FUNCTIONALITIES
{
    HDCP_UART_TX = 1 ,  
    HDCP_UART_RX ,
    HDCP_SPI_MISO ,
    HDCP_SPI_MOSI,
    HDCP_SPI_CLK,
    HDCP_SPI_CS,
    HDCP_I2C_CLK,
    HDCP_I2C_DATA,
    HTAP_LIGHT_RED,
    HTAP_LIGHT_GREEN,
    HTAP_LIGHT_BLUE,
    HTAP_FAN_CTRL,
    HTAP_BTN_1,
    HTAP_BTN_2,
    HTAP_DETECT_LED,
    HTAP_RECERVED_2,
    HTAP_RECERVED_3,
    HTAP_RECERVED_4,
    HTAP_RECERVED_5,
    HTAP_RECERVED_6,
}HTAP_FUNCTIONALITIES_En;

typedef struct ui_map
{
    HTAP_FUNCTIONALITIES_En FuncName;
    HTAP_PINS_En PinName;
    uint8_t ActStat_Baud_u32; 
}ui_map_st;

typedef struct HTAP_UART_Pins
{
    int8_t Tx;
    int8_t Rx;
    uint32_t Baudrate_HDCP_u32;
}HTAP_UART_Pins_St;

typedef struct Light_Pins
{
    int8_t Pin;
    LIGHT_COLOR_En Color;
    GPIO_PIN_STATE_En ActStat;
}Light_Pins_St;

typedef struct Button_Pins
{
    char Pin;
    char ActStat;
}Button_Pins_St;

typedef struct HTAP_HW_PINS
{
    HTAP_PINS_En HTAP_PinName;
    char RTK_PinName;
}HTAP_HW_PINS_St;
