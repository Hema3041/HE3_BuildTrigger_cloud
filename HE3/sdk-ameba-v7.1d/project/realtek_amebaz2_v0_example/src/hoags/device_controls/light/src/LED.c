#include "LED.h"
#if LIVPURE_CHIMNEY
#include "chimney.h"
extern i2c_t i2cObj;
extern unsigned char LEd;
unsigned char wwLight;
extern unsigned char irDisable;
extern unsigned char displayByte;
extern unsigned char inductionByte;
extern unsigned short int writeByte;
#endif
#if AMBER_AC
extern gpio_t Amber_ww_led;
#endif

struct htap_led htap_led_obj;
struct htap_led* htapledPtr = &htap_led_obj;

void initialize_Htap_LED(uint32_t Led_Ctrl_Pin)
{
    //Suvarna: use below if using with already released HTAP mini LFS(v55)
    //init_htap_led(htapledPtr, PWM_PERIOD_LED, PA_17, PWM_CHANNEL_LED);

    //Suvarna: use below if using with already released HTAP LFS(v55)
    //Suvarna: also use below if using latest LFS and latest HTAP mini
    printf("AT %s,%d\n",__func__,__LINE__);
	#if HTAP_MODULE
	    init_htap_led(htapledPtr, PWM_PERIOD_LED, PA_22, PWM_CHANNEL_LED);
	#else
        #if LIVPURE_CHIMNEY
        // wwLight = 0xff;
        // i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &wwLight, 1, 1, I2C_TIMEOUT);
        //init_htap_led(htapledPtr, PWM_PERIOD_LED, PA_22, PWM_CHANNEL_LED);
        #elif AMBER_AC
        init_htap_led(htapledPtr, PWM_PERIOD_LED, PA_19, PWM_CHANNEL_LED);
        #elif LIVPURE_PURIFIER
        printf("AT %s,%d...\n",__func__,__LINE__);
        init_htap_led(htapledPtr, PWM_PERIOD_LED, PA_20, PWM_CHANNEL_LED);
        #else
	    init_htap_led(htapledPtr, PWM_PERIOD_LED, PA_17, PWM_CHANNEL_LED);
        #endif
	#endif
}

void init_htap_led(struct htap_led* l, int period, int pin, int channel)
{
    HOAGS_DBG("period=%d pin=%d\n", period, pin);
    l->pwm_htap_led.pwm_idx = channel;  
    pwmout_init(&(l->pwm_htap_led), pin);
}

void set_led_blink_speed(struct htap_led* l, enum htap_led_blink_speed level, int period)
{
    //HOAGS_DBG("level=%d\n", level);
    pwmout_period_us(&(l->pwm_htap_led), period);
    pwmout_pulsewidth_us(&(l->pwm_htap_led), level);
}

/*HTAP NEW API*/ 

void wakeword_det_led_on()
{
    set_led_blink_speed(htapledPtr,100,100);

    #if POLYCAB_FAN || VGUARD_FAN || ATOMBERG_FAN || VGUARD_NEW_FAN
    return;
    #endif
    #if LIVPURE_CHIMNEY
    
    displayByte = displayByte & (~(0x01<<6));
    writeByte = displayByte;
    writeByte = (displayByte<<8)|inductionByte;
    i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
    // wwLight = 0x00;
    // i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &wwLight, 1, 1, I2C_TIMEOUT);
    return;
    #endif

    #if AMBER_AC
    gpio_write(&Amber_ww_led, 1);
    vTaskDelay(2000);
    gpio_write(&Amber_ww_led, 0);
    vTaskDelay(200);
    #endif
    struct hdcp wakeword_det ={0xFF,DEV_TO_MCU_INFO,1,1,0,1,{0,0,0,0,0},1,0,WAKEWORD_DETECTED};

    uart_send_bytes(&superFanObj, &wakeword_det, sizeof(wakeword_det)); //ww det
    swapStructEndianness(&wakeword_det, sizeof(wakeword_det));
    displayData(&wakeword_det, sizeof(wakeword_det));
}

void mic_mute_led()
{
    set_led_blink_speed(htapledPtr,100,100);
    #if POLYCAB_FAN || VGUARD_FAN || ATOMBERG_FAN || VERSADEVICES_SUPERFAN_IOT || VGUARD_NEW_FAN
    return;
    #endif
    #if LIVPURE_CHIMNEY
    //irDisable = 1;
    return;
    #endif
    struct hdcp mic_mute ={0xFF,DEV_TO_MCU_INFO,1,1,0,1,{0,0,0,0,0},1,0,MIC_MUTED};

    uart_send_bytes(&superFanObj, &mic_mute, sizeof(mic_mute)); //ww det
    swapStructEndianness(&mic_mute, sizeof(mic_mute));
    displayData(&mic_mute, sizeof(mic_mute));
}


void wifi_ble_conn()
{
    #if POLYCAB_FAN || VGUARD_FAN || ATOMBERG_FAN || LIVPURE_CHIMNEY || VGUARD_NEW_FAN
    return;
    #endif
    struct hdcp wifi_BLE_conn   ={0xFF,DEV_TO_MCU_INFO,1,1,0,1,{0,0,0,0,0},1,0,WIFI_OR_BLE_CONNECTED}; 
    uart_send_bytes(&superFanObj, &wifi_BLE_conn, sizeof(wifi_BLE_conn)); //OTA update
    swapStructEndianness(&wifi_BLE_conn, sizeof(wifi_BLE_conn));
    displayData(&wifi_BLE_conn, sizeof(wifi_BLE_conn));
}

void wifi_ble_disconn()
{
    #if POLYCAB_FAN || VGUARD_FAN || ATOMBERG_FAN  || LIVPURE_CHIMNEY || VGUARD_NEW_FAN
    return;
    #endif
    struct hdcp wifi_BLE_disconN    ={0xFF,DEV_TO_MCU_INFO,1,1,0,1,{0,0,0,0,0},1,0,WIFI_DISCONNECTED};
    uart_send_bytes(&superFanObj, &wifi_BLE_disconN, sizeof(wifi_BLE_disconN)); //OTA update
    swapStructEndianness(&wifi_BLE_disconN, sizeof(wifi_BLE_disconN));
    displayData(&wifi_BLE_disconN, sizeof(wifi_BLE_disconN));

}
void ota_update_mod_tranfer()
{
    #if POLYCAB_FAN || VGUARD_FAN || ATOMBERG_FAN  || LIVPURE_CHIMNEY || VGUARD_NEW_FAN
    return;
    #endif
    struct hdcp ota_mod_tranfer ={0xFF,DEV_TO_MCU_INFO,1,1,0,1,{0,0,0,0,0},1,0,OTA_OR_MODEL_TRANSFER};

    uart_send_bytes(&superFanObj, &ota_mod_tranfer, sizeof(ota_mod_tranfer)); //OTA update
    swapStructEndianness(&ota_mod_tranfer, sizeof(ota_mod_tranfer));
    displayData(&ota_mod_tranfer, sizeof(ota_mod_tranfer));

}
void WW_LEDNoColor()  // duplicate
{
    set_led_blink_speed(htapledPtr,0,0);  // 100 off 0 on
    
}

void cmd_det_led_off()
{
    set_led_blink_speed(htapledPtr,0,0);  // 100 off 0 on
    #if POLYCAB_FAN || VGUARD_FAN || ATOMBERG_FAN || VGUARD_NEW_FAN
    return;
    #endif
    #if LIVPURE_CHIMNEY
    displayByte = displayByte|(0x01<<6);
    writeByte = displayByte;
    writeByte = (displayByte<<8)|inductionByte;
    i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
    return;
    #endif
    struct hdcp command_det     ={0xFF,DEV_TO_MCU_INFO,1,1,0,1,{0,0,0,0,0},1,0,COMMAND_DETECTED};;
    
    uart_send_bytes(&superFanObj, &command_det, sizeof(command_det)); // cmd det
}

void cmd_det_fail_led_off()
{
    set_led_blink_speed(htapledPtr,0,0);  // 100 off 0 on
    #if POLYCAB_FAN || VGUARD_FAN || ATOMBERG_FAN || VGUARD_NEW_FAN
    return;
    #endif
    #if LIVPURE_CHIMNEY
    displayByte = displayByte|(0x01<<6);
    writeByte = displayByte;
    writeByte = (displayByte<<8)|inductionByte;
    i2c_write_timeout(&i2cObj,MBED_I2C_SLAVE_ADDR0, &writeByte, 2, 1, I2C_TIMEOUT);
    return;
    #endif
    struct hdcp command_not_det ={0xFF,DEV_TO_MCU_INFO,1,1,0,1,{0,0,0,0,0},1,0,COMMAND_NOT_DETECTED};
    
    uart_send_bytes(&superFanObj, &command_not_det, sizeof(command_not_det)); // cmd det failure
}

void blink_LED()
{
    set_led_blink_speed(htapledPtr,100,50000); //pulseWidth,period
    #if POLYCAB_FAN || VGUARD_FAN || ATOMBERG_FAN || LIVPURE_CHIMNEY || VGUARD_NEW_FAN
    return;
    #endif
    struct hdcp something_wrong ={0xFF,DEV_TO_MCU_INFO,1,1,0,1,{0,0,0,0,0},1,0,SOMETHING_IS_WRONG}; // ota failure,sensory error,model tranfer error,vfs issue
    uart_send_bytes(&superFanObj, &something_wrong, sizeof(something_wrong)); 
}

extern BOOL isBIST;
void breathe_LED()
{
	if(isBIST == TRUE)
        return;
    
    int i;
    for(i = 0; ; i += 10) 
	{ 
       set_led_blink_speed(htapledPtr, i, 100); 
       vTaskDelay(100); // delay for difference in output
       if (i >= 100) { 
          break; 
        }
    }
    
    for(i = 100; ; i -= 10) 
	{ 
        set_led_blink_speed(htapledPtr, i, 100); 
        vTaskDelay(100); 
        if (i <= 0) {
            break;
        }
    }

    #if POLYCAB_FAN || VGUARD_FAN || ATOMBERG_FAN || LIVPURE_CHIMNEY || VGUARD_NEW_FAN || LIVPURE_PURIFIER
    return;
    #endif
    struct hdcp network_set_up  ={0xFF,DEV_TO_MCU_INFO,1,1,0,1,{0,0,0,0,0},1,0,SETUP_IN_ACTION};
    uart_send_bytes(&superFanObj, &network_set_up, sizeof(network_set_up)); // network set up

}

void led_always_on()
{
    set_led_blink_speed(htapledPtr, 100, 100); // 100% duty = always ON
}


void led_always_off()
{
    set_led_blink_speed(htapledPtr, 0, 100); // 0% duty = always OFF
}

