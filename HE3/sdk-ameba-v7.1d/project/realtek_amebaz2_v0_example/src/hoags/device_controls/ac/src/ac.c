#include "ac.h"
#include "hoags_config.h"
#include "packets.h"
#include "htap_config.h"

#include "FreeRTOS.h"
#include "timers.h"
#include "timer_api.h"

#if ENABLE_AC
extern uint8_t FanConfigured;
extern uint8_t LightConfigured;
extern uint8_t UARTConfigured;
extern struct serial_s superFanObj;
unsigned short currentTemp;

#if VIRTUALFOREST_AC
extern unsigned char vfDefCmd[24];
extern unsigned char vfAck[24];
extern BOOL isAckReceived;
#endif

extern unsigned char omniDefCmd[15];
extern unsigned char omniAck[15];
extern BOOL isAckReceived;

#if HAVELLS_AC
char switchOn[]= {0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x01, 0x01, 0x00, 0x01, 0x01, 0x0E};
char switchOff[]= {0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x01, 0x01, 0x00, 0x01, 0x00, 0x0D};
char autoMode[] ={0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x04, 0x04, 0x00, 0x01, 0x00, 0x13};
char dryMode[] ={0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x04, 0x04, 0x00, 0x01, 0x03, 0x16};
char coolMode[] ={0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x04, 0x04, 0x00, 0x01, 0x01, 0x14};
char lowspeed[]={0x55, 0xAA, 0X00, 0X06, 0X00, 0X05, 0X05, 0X04, 0X00, 0X01, 0X00, 0x14};
char midspeed[]={0x55, 0xAA, 0X00, 0X06, 0X00, 0X05, 0X05, 0X04, 0X00, 0X01, 0X00, 0x15};
char highspeed[]={0x55, 0xAA, 0X00, 0X06, 0X00, 0X05, 0X05, 0X04, 0X00, 0X01, 0X00, 0x16};
char autospeed[]={0x55, 0xAA, 0X00, 0X06, 0X00, 0X05, 0X05, 0X04, 0X00, 0X01, 0X00, 0x17};
char tinyspeed[]={0x55, 0xAA, 0X00, 0X06, 0X00, 0X05, 0X05, 0X04, 0X00, 0X01, 0X00, 0x18};
char turbospeed[]={0x55, 0xAA, 0X00, 0X06, 0X00, 0X05, 0X05, 0X04, 0X00, 0X01, 0X00, 0x19};
#endif

void printBits(unsigned char value) {
    printf("\n");
    printf("Binary representation: ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}
#if HAVELLS_AC
void sendhavell_ww(){
    char havellsWwDetected[] = {0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x9B, 0x01, 0x00, 0x01, 0x01, 0xA8};
    displayData(&havellsWwDetected, sizeof(havellsWwDetected));
    uart_send_bytes(&superFanObj, &havellsWwDetected, sizeof(havellsWwDetected));
}
#endif

unsigned char modifyBit(unsigned char value, int position, int newValue) {
    if (newValue != 0 && newValue != 1) {
        printf("Invalid new bit value. It should be 0 or 1.\n");
        return value;
    }

    if (position < 0 || position > 7) {
        printf("Invalid bit position. It should be between 0 and 7.\n");
        return value;
    }

    unsigned char mask = 1 << position;

    if (newValue == 0) {
        // Clear the bit at the specified position
        value &= ~mask;
    } else {
        // Set the bit at the specified position
        value |= mask;
    }

    return value;
}
#if HAVELLS_AC
unsigned char hvl_Checksum(unsigned char* bytes){
    unsigned char sum = 0;
    for (int i = 0; i < 11; i++) 
    {
        sum += *(bytes+i);
    }

    unsigned char checksum = sum&0xFF;

    return checksum;
}
#endif

char getCurrentTemp()
{
  char amberLowTemp[18] = {0x57, 0x31, 0x0F, 0x31, 0x13, 0x00, 0x00, 0x1C, 0x5A, 0x5A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x45};
  uart_send_bytes(&superFanObj, amberLowTemp, sizeof(amberLowTemp));
  char data[18];
  uart_receive_bytes(&superFanObj, sizeof(amberLowTemp), data);
  #if 1 //Just for printing purpose
  for(int i = 0; i < sizeof(amberLowTemp); ++i)
  {
    HOAGS_ERR("%x %c %d\n", data[i], data[i], data[i]);
  }
  #endif
  return data[4];
}

#if VIRTUALFOREST_AC
void getAcknowledgement(unsigned char* state, size_t len)
{
  unsigned char ackPacket[] = {0x24, 0x16, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE5, 0x23};
  //printf("Ack data\n");
  displayDataUC((unsigned char*)&ackPacket, sizeof(ackPacket));         
  uart_send_bytes(&superFanObj, (char*)&ackPacket, sizeof(ackPacket));
  //char data[23];
  //uart_receive_bytes(&superFanObj, 2, data);

  vTaskDelay(pdMS_TO_TICKS(500));

  #if 1
  size_t index = -1;
  char tmp;
  BOOL collectStart = FALSE;
  while(len)
  {
    tmp = serial_getc(&superFanObj);
    //printf("ACK:%c %x %d\n", tmp, tmp, tmp);
    if(tmp == '$') 
      collectStart = TRUE;
    
    if(collectStart)
    {
      ++index;
      *(state+index) = tmp;
      --len;
      //printf("ACK-RECORD:%c %x %d %x\n", tmp, tmp, tmp, *(state+index));
    }
    
  } 
  isAckReceived = TRUE;
  printf("Acknowledgement\n");
  displayDataUC(state, len);

  #endif
}


unsigned char vfChecksum(unsigned char* bytes, size_t len)
{
    unsigned char sum = 0;
    for (int i = 0; i < len; i++) 
    {
        sum += *(bytes+i);
    }

    unsigned char checksum = ~sum + 1;

    return checksum;

}
#endif

#if AMBER_AC || OMNI_AC
unsigned char ambChecksum(unsigned char* bytes, size_t len)
{
    unsigned char sum = 0;

    for (int i = 0; i < len; i++) 
    {
        sum += bytes[i];

        //printf("sum:0x%02X\n", sum);
    }

    unsigned char checksum = sum;

    //printf("Checksum:0x%02X\n", checksum);

    return checksum;

}
#endif

#if OMNI_AC
unsigned char omniChecksum(unsigned char* bytes, size_t len)
{
    unsigned char sum = 0;

    for (int i = 0; i < len; i++) 
    {
        sum += bytes[i];

        //printf("sum:0x%02X\n", sum);
    }

    unsigned char checksum = sum;

    //printf("Checksum:0x%02X\n", checksum);

    return checksum;

}
#endif

extern gtimer_t timer_7;

void SendHeartBeat_Amb()
{
  unsigned char sentamb[] = {0x55, 0xAA, 0x00, 0x08, 0x00, 0x00, 0x07};
	displayDataUC((unsigned char*)&sentamb, sizeof(sentamb)); 
	uart_send_bytes(&superFanObj,  (char*)&sentamb, sizeof(sentamb));
	HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void Initheartbeat_Amb()
{
    gtimer_init(&timer_7,TIMER4);
    HOAGS_INFO("Amber Timer initialized\n");
}

void AmbHeartbeatTask()
{
    gtimer_start_periodical(&timer_7,15000000,(void *)SendHeartBeat_Amb,NULL); 
}

void switchOnAC()
{
	if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  ///Suvarna: Verified Command
  vfDefCmd[4] = VF4_POWER_ON;
  if(isAckReceived)
  {
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[5] = vfAck[5];
    //vfDefCmd[7] = vfAck[6];
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC || OMNI_AC
  char Ambon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x01 ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};
  Ambon[11] = ambChecksum(Ambon, sizeof(Ambon));
  HOAGS_INFO("Inside ON\n");
  displayData(&Ambon, sizeof(Ambon));
  uart_send_bytes(&superFanObj, &Ambon, sizeof(Ambon));

  #elif HAVELLS_AC
  
  //swapStructEndianness(&switchOn, sizeof(switchOn));
  displayDataUC((char*)&switchOn, sizeof(switchOn));
  uart_send_bytes(&superFanObj, (char*)&switchOn, sizeof(switchOn));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #else
  
  struct hdcp hdcpSwitchOn = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_POWER_CONTROL}, 1, 0, AC_CMD_ON};
  swapStructEndianness(&hdcpSwitchOn, sizeof(hdcpSwitchOn));
  displayDataUC((char*)&hdcpSwitchOn, sizeof(hdcpSwitchOn));
  uart_send_bytes(&superFanObj, (char*)&hdcpSwitchOn, sizeof(hdcpSwitchOn));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  #endif
}

void switchOffAC()
{
	if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  ///Suvarna: Verified Command
  vfDefCmd[4] = VF4_POWER_OFF;
  if(isAckReceived)
  {
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[5] = vfAck[5];
    //vfDefCmd[7] = vfAck[6];
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }
  HOAGS_INFO("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  HOAGS_INFO("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;
	
  #elif AMBER_AC || OMNI_AC
  char Amboff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x01 ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};
  Amboff[11] = ambChecksum(Amboff, sizeof(Amboff));
  HOAGS_INFO("Inside OFF\n");
  displayData(&Amboff, sizeof(Amboff));
  uart_send_bytes(&superFanObj, &Amboff, sizeof(Amboff));

  #elif HAVELLS_AC
  //swapStructEndianness(&switchOff, sizeof(switchOff));
  displayDataUC((char*)&switchOff, sizeof(switchOff));
  uart_send_bytes(&superFanObj, (char*)&switchOff, sizeof(switchOff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  
  #else
    
  struct hdcp hdcpSwitchOff = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_POWER_CONTROL}, 1, 0, AC_CMD_OFF};
  swapStructEndianness(&hdcpSwitchOff, sizeof(hdcpSwitchOff));
  displayDataUC((char*)&hdcpSwitchOff, sizeof(hdcpSwitchOff));

  uart_send_bytes(&superFanObj, (char*)&hdcpSwitchOff, sizeof(hdcpSwitchOff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  
  #endif
}

void chillModeAC()
{
  if(!UARTConfigured) 
		return;
  
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  ///Suvarna: Verified Command
  //cool mode on
  vfDefCmd[5] = VF5_MODE_COOL;

  //set temp to 17
  vfDefCmd[7] = 0x11 - 0x0F;

  //turbo on
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 5, 0);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 4, 1);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 7, 0);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 6, 0);
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[6] = vfAck[10];
    //vfDefCmd[5] = vfAck[5];
    vfDefCmd[8] = vfAck[18];
    //vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }
  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #endif  
  
  struct hdcp hdcpIncTemp = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_TEMP_CONTROL}, 1, 0, AC_CMD_TEMP_INCREASE};
  swapStructEndianness(&hdcpIncTemp, sizeof(hdcpIncTemp));
  displayDataUC((char*)&hdcpIncTemp, sizeof(hdcpIncTemp));

  uart_send_bytes(&superFanObj, (char*)&hdcpIncTemp, sizeof(hdcpIncTemp));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void comfortModeAC(char c)
{
  if(!UARTConfigured) 
		return;
  
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  ///Suvarna: Verified Command

  //cool mode on
  vfDefCmd[5] = VF5_MODE_COOL;

  //fan speed medium
  vfDefCmd[6] = VF6_FAN_MID;

  //set temp to 22.c
  vfDefCmd[7] = 0x16 - 0x0F;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    //vfDefCmd[6] = vfAck[10];
    //vfDefCmd[5] = vfAck[5];
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }
  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #endif  
  
  struct hdcp hdcpIncTemp = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_TEMP_CONTROL}, 1, 0, AC_CMD_TEMP_INCREASE};
  swapStructEndianness(&hdcpIncTemp, sizeof(hdcpIncTemp));
  displayDataUC((char*)&hdcpIncTemp, sizeof(hdcpIncTemp));

  uart_send_bytes(&superFanObj, (char*)&hdcpIncTemp, sizeof(hdcpIncTemp));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}


void incTempAC(char c)
{
  if(!UARTConfigured) 
		return;
  
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  ///Suvarna: Verified Command
  vfDefCmd[7] = c - 0x0F;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }
  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC || OMNI_AC
  char Ambtemp[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x08 ,0x02 ,0x02 ,0x00 ,0x04 , 0x00, 0x00, 0x00, c ,0x00};  
  Ambtemp[14] = ambChecksum(Ambtemp, sizeof(Ambtemp));
  HOAGS_INFO("Inside Temp\n");
  displayData(&Ambtemp, sizeof(Ambtemp));
  uart_send_bytes(&superFanObj, &Ambtemp, sizeof(Ambtemp));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #else
  struct hdcp hdcpIncTemp = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_TEMP_CONTROL}, 1, 0, AC_CMD_TEMP_INCREASE};
  swapStructEndianness(&hdcpIncTemp, sizeof(hdcpIncTemp));
  displayDataUC((char*)&hdcpIncTemp, sizeof(hdcpIncTemp));

  uart_send_bytes(&superFanObj, (char*)&hdcpIncTemp, sizeof(hdcpIncTemp));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

   #endif
}

void decTempAC(char *c)
{
  if(!UARTConfigured) 
		return;

  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  ///Suvarna: Verified Command
  vfDefCmd[7] = c - 0x0F;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }
  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #endif 

  struct hdcp hdcpDecTemp = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_TEMP_CONTROL}, 1, 0, AC_CMD_TEMP_DECREASE};
  swapStructEndianness(&hdcpDecTemp, sizeof(hdcpDecTemp));
  displayDataUC((char*)&hdcpDecTemp, sizeof(hdcpDecTemp));

  uart_send_bytes(&superFanObj, (char*)&hdcpDecTemp, sizeof(hdcpDecTemp));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
}

void autospeedAC()
{
  #if AMBER_AC
  char Ambauto[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x05 ,0x04 ,0x00 ,0x01 ,0x00 ,0x00};  
  Ambauto[11] = ambChecksum(Ambauto, sizeof(Ambauto));
  HOAGS_INFO("Inside auto_fan\n");
  displayData(&Ambauto, sizeof(Ambauto));
  uart_send_bytes(&superFanObj, &Ambauto, sizeof(Ambauto));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  #endif
}

void lowSpeedAC()
{
  if(!UARTConfigured) 
		return;
  
  #if VIRTUALFOREST_AC
  ///Suvarna: Verified Command
  vfDefCmd[6] = VF6_FAN_LOW;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC
  char Amblow[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x05 ,0x04 ,0x00 ,0x01 ,0x01 ,0x00};  
  Amblow[11] = ambChecksum(Amblow, sizeof(Amblow));
  HOAGS_INFO("Inside low_fan\n");
  displayData(&Amblow, sizeof(Amblow));
  uart_send_bytes(&superFanObj, &Amblow, sizeof(Amblow));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #elif OMNI_AC
  char Omnilow[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x05 ,0x04 ,0x00 ,0x01 ,0x00 ,0x00};  
  Omnilow[11] = omniChecksum(Omnilow, sizeof(Omnilow));
  HOAGS_INFO("Inside omni low_fan\n");
  displayData(&Omnilow, sizeof(Omnilow));
  uart_send_bytes(&superFanObj, &Omnilow, sizeof(Omnilow));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #else
  struct hdcp hdcpLowSpeed = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_SPEED_CONTROL}, 1, 0, AC_CMD_SPEED_LOW};
  swapStructEndianness(&hdcpLowSpeed, sizeof(hdcpLowSpeed));
  displayDataUC((char*)&hdcpLowSpeed, sizeof(hdcpLowSpeed));

  uart_send_bytes(&superFanObj, (char*)&hdcpLowSpeed, sizeof(hdcpLowSpeed));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  #endif
}

void midSpeedAC()
{
  if(!UARTConfigured) 
		return;

  #if VIRTUALFOREST_AC
  ///Suvarna: Verified Command
  vfDefCmd[6] = VF6_FAN_MID;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC
  char Ambmed[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x05 ,0x04 ,0x00 ,0x01 ,0x02 ,0x00};  
  Ambmed[11] = ambChecksum(Ambmed, sizeof(Ambmed));
  HOAGS_INFO("Inside mid_fan\n");
  displayData(&Ambmed, sizeof(Ambmed));
  uart_send_bytes(&superFanObj, &Ambmed, sizeof(Ambmed));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #elif OMNI_AC
  char Omnimed[] =  {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x05 ,0x04 ,0x00 ,0x01 ,0x01 ,0x00};  
  Omnimed[11] = omniChecksum(Omnimed, sizeof(Omnimed));
  HOAGS_INFO("Inside omni mid_fan\n");
  displayData(&Omnimed, sizeof(Omnimed));
  uart_send_bytes(&superFanObj, &Omnimed, sizeof(Omnimed));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #else
  struct hdcp hdcpMidSpeed = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_SPEED_CONTROL}, 1, 0, AC_CMD_SPEED_MID};
  swapStructEndianness(&hdcpMidSpeed, sizeof(hdcpMidSpeed));
  displayDataUC((char*)&hdcpMidSpeed, sizeof(hdcpMidSpeed));

  uart_send_bytes(&superFanObj, (char*)&hdcpMidSpeed, sizeof(hdcpMidSpeed));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  #endif
}

void highSpeedAC()
{
  if(!UARTConfigured) 
		return;
  
  #if VIRTUALFOREST_AC
  ///Suvarna: Verified Command
  vfDefCmd[6] = VF6_FAN_HIGH;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC
  char Ambhigh[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x05 ,0x04 ,0x00 ,0x01 ,0x03 ,0x00};  
  Ambhigh[11] = ambChecksum(Ambhigh, sizeof(Ambhigh));
  HOAGS_INFO("Inside high_fan\n");
  displayData(&Ambhigh, sizeof(Ambhigh));
  uart_send_bytes(&superFanObj, &Ambhigh, sizeof(Ambhigh));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #elif OMNI_AC
  char Omnihigh[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x05 ,0x04 ,0x00 ,0x01 ,0x02 ,0x00};  
  Omnihigh[11] = omniChecksum(Omnihigh, sizeof(Omnihigh));
  HOAGS_INFO("Inside Omni high_fan\n");
  displayData(&Omnihigh, sizeof(Omnihigh));
  uart_send_bytes(&superFanObj, &Omnihigh, sizeof(Omnihigh));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #else
  struct hdcp hdcpHighSpeed = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_SPEED_CONTROL}, 1, 0, AC_CMD_SPEED_HIGH};
  swapStructEndianness(&hdcpHighSpeed, sizeof(hdcpHighSpeed));
  displayDataUC((char*)&hdcpHighSpeed, sizeof(hdcpHighSpeed));

  uart_send_bytes(&superFanObj, (char*)&hdcpHighSpeed, sizeof(hdcpHighSpeed));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  #endif
}

void dryModeAC()
{
  if(!UARTConfigured) 
		return;
   #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  ///Suvarna: Verified Command
  vfDefCmd[5] = VF5_MODE_DRY;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[7] = vfAck[6]-15;
    //printf("Ranjeet tempsend=%02x %d, prevAck=%02x, %d assign=%02x %d\n", vfDefCmd[7], vfDefCmd[7], vfAck[6], vfAck[6], vfAck[6]-0x0F, vfAck[6]-0x0F);
    //vfDefCmd[7] = vfAck[6];
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }
  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC || OMNI_AC
	  char Ambdry[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x04 ,0x04 ,0x00 ,0x01 ,0x03 ,0x00};
	  Ambdry[11] = ambChecksum(Ambdry, sizeof(Ambdry));
	  HOAGS_INFO("Inside dry\n");
	  displayData(&Ambdry, sizeof(Ambdry));
	  uart_send_bytes(&superFanObj, &Ambdry, sizeof(Ambdry));
	  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #elif HAVELLS_AC
  //swapStructEndianness(&dryMode, sizeof(dryMode));
  displayDataUC((char*)&dryMode, sizeof(dryMode));

  uart_send_bytes(&superFanObj, (char*)&dryMode, sizeof(dryMode));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  
  #else

  struct hdcp hdcpDryMode = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_MODE_CONTROL}, 1, 0, AC_CMD_MODE_DRY};
  swapStructEndianness(&hdcpDryMode, sizeof(hdcpDryMode));
  displayDataUC((char*)&hdcpDryMode, sizeof(hdcpDryMode));

  uart_send_bytes(&superFanObj, (char*)&hdcpDryMode, sizeof(hdcpDryMode));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  
  #endif

}

void hotModeAC()
{
  #if AMBER_AC || OMNI_AC
  char Ambhot[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x04 ,0x04 ,0x00 ,0x01 ,0x02 ,0x00};
  Ambhot[11] = ambChecksum(Ambhot, sizeof(Ambhot));
  HOAGS_INFO("Inside hot\n");
  displayData(&Ambhot, sizeof(Ambhot));
  uart_send_bytes(&superFanObj, &Ambhot, sizeof(Ambhot));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  #endif

}

void coolModeAC()
{
  if(!UARTConfigured) 
		return;

  #if VIRTUALFOREST_AC
   HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[5] = VF5_MODE_COOL;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[7] = vfAck[6]-15;
    //printf("Ranjeet tempsend=%02x %d, prevAck=%02x, %d assign=%02x %d\n", vfDefCmd[7], vfDefCmd[7], vfAck[6], vfAck[6], vfAck[6]-0x0F, vfAck[6]-0x0F);
    //vfDefCmd[7] = vfAck[6];
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  HOAGS_INFO("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  HOAGS_INFO("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC || OMNI_AC
  char Ambcool[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x04 ,0x04 ,0x00 ,0x01 ,0x01 ,0x00};
  Ambcool[11] = ambChecksum(Ambcool, sizeof(Ambcool));
  HOAGS_INFO("Inside COOL\n");
  displayData(&Ambcool, sizeof(Ambcool));
  uart_send_bytes(&superFanObj, &Ambcool, sizeof(Ambcool));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #elif HAVELLS_AC
  //swapStructEndianness(&coolMode, sizeof(coolMode));
  displayDataUC((char*)&coolMode, sizeof(coolMode));

  uart_send_bytes(&superFanObj, (char*)&coolMode, sizeof(coolMode));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  
  #else

  struct hdcp hdcpCoolMode = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_MODE_CONTROL}, 1, 0, AC_CMD_MODE_COOL};
  swapStructEndianness(&hdcpCoolMode, sizeof(hdcpCoolMode));
  displayDataUC((char*)&hdcpCoolMode, sizeof(hdcpCoolMode));

  uart_send_bytes(&superFanObj, (char*)&hdcpCoolMode, sizeof(hdcpCoolMode));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  
  #endif
}

void autoModeAC()
{
  if(!UARTConfigured) 
		return;

  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[5] = VF5_MODE_AUTO;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-0x0F;
    //printf("Ranjeet tempsend=%02x %d, prevAck=%02x, %d assign=%02x %d\n", vfDefCmd[7], vfDefCmd[7], vfAck[6], vfAck[6], vfAck[6]-0x0F, vfAck[6]-0x0F);
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  HOAGS_INFO("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  HOAGS_INFO("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC || OMNI_AC
  char Ambauto[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x04 ,0x04 ,0x00 ,0x01 ,0x00 ,0x00};
  Ambauto[11] = ambChecksum(Ambauto, sizeof(Ambauto));
  HOAGS_INFO("***Inside auto***\n");
  displayData(&Ambauto, sizeof(Ambauto));
  uart_send_bytes(&superFanObj, &Ambauto, sizeof(Ambauto));

  #elif HAVELLS_AC
  
  //swapStructEndianness(&autoMode, sizeof(autoMode));
  displayDataUC((char*)&autoMode, sizeof(autoMode));
  uart_send_bytes(&superFanObj, (char*)&autoMode, sizeof(autoMode));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  
  #else

  struct hdcp hdcpAutoMode = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_MODE_CONTROL}, 1, 0, AC_CMD_MODE_AUTO};
  swapStructEndianness(&hdcpAutoMode, sizeof(hdcpAutoMode));
  displayDataUC((char*)&hdcpAutoMode, sizeof(hdcpAutoMode));

  uart_send_bytes(&superFanObj, (char*)&hdcpAutoMode, sizeof(hdcpAutoMode));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  
  #endif
}


void fanModeAC()
{
  if(!UARTConfigured) 
		return;

  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[5] = VF5_MODE_FAN;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[7] = vfAck[6]-15;
    //vfDefCmd[7] = vfAck[6];
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));

  return;

  #elif AMBER_AC  || OMNI_AC
  char Ambwind[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x04 ,0x04 ,0x00 ,0x01 ,0x04 ,0x00};
  Ambwind[11] = ambChecksum(Ambwind, sizeof(Ambwind));
  HOAGS_INFO("Inside wind\n");
  displayData(&Ambwind, sizeof(Ambwind));
  uart_send_bytes(&superFanObj, &Ambwind, sizeof(Ambwind));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #else

  struct hdcp hdcpFanMode = {0xFF, AC_CTRL, 1, 1, 0, 2, {0,0,0,0,AC_CMD_MODE_CONTROL}, 1, 0, AC_CMD_MODE_FAN};
  swapStructEndianness(&hdcpFanMode, sizeof(hdcpFanMode));
  displayDataUC((char*)&hdcpFanMode, sizeof(hdcpFanMode));

  uart_send_bytes(&superFanObj, (char*)&hdcpFanMode, sizeof(hdcpFanMode));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void swingVerticalOn()
{
  if(!UARTConfigured) {
    printf("swingvertical on uart_false");
    return;
  }
		
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[8] = V8_SWING_VON;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC
  char Ambvswgon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x6e ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  Ambvswgon[11] = ambChecksum(Ambvswgon, sizeof(Ambvswgon));
  HOAGS_INFO("Inside Vswingon\n");
  displayData(&Ambvswgon, sizeof(Ambvswgon));
  uart_send_bytes(&superFanObj, &Ambvswgon, sizeof(Ambvswgon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

#elif OMNI_AC
  char Omnivswgon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x72 ,0x04 ,0x00 ,0x01 ,0x01 ,0x00};  
  Omnivswgon[11] = omniChecksum(Omnivswgon, sizeof(Omnivswgon));
  HOAGS_INFO("Inside omni Vswingon\n");
  displayData(&Omnivswgon, sizeof(Omnivswgon));
  uart_send_bytes(&superFanObj, &Omnivswgon, sizeof(Omnivswgon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void swingVerticalOff()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[8] = V8_SWING_VOFF;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC
  char Ambvswgoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x6e ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  Ambvswgoff[11] = ambChecksum(Ambvswgoff, sizeof(Ambvswgoff));
  HOAGS_INFO("Inside Vswingoff\n");
  displayData(&Ambvswgoff, sizeof(Ambvswgoff));
  uart_send_bytes(&superFanObj, &Ambvswgoff, sizeof(Ambvswgoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #elif OMNI_AC
  char Omnivswgoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x72 ,0x04 ,0x00 ,0x01 ,0x00 ,0x00};  
  Omnivswgoff[11] = omniChecksum(Omnivswgoff, sizeof(Omnivswgoff));
  HOAGS_INFO("Inside omni Vswingoff\n");
  displayData(&Omnivswgoff, sizeof(Omnivswgoff));
  uart_send_bytes(&superFanObj, &Omnivswgoff, sizeof(Omnivswgoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void swingHorizontalOn()
{
  if(!UARTConfigured) {
    printf("swinghorizontal on uart false");
    return;
  }
		
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[8] = V8_SWING_HON;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");

  #elif AMBER_AC
  char Ambhswgon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x6f ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  Ambhswgon[11] = ambChecksum(Ambhswgon, sizeof(Ambhswgon));
  HOAGS_INFO("Inside Hswingon\n");
  displayData(&Ambhswgon, sizeof(Ambhswgon));
  uart_send_bytes(&superFanObj, &Ambhswgon, sizeof(Ambhswgon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  return;

  #elif OMNI_AC
  char Omnihswgon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x73 ,0x04 ,0x00 ,0x01 ,0x01 ,0x00};  
  Omnihswgon[11] = omniChecksum(Omnihswgon, sizeof(Omnihswgon));
  HOAGS_INFO("Inside omni VHswingon\n");
  displayData(&Omnihswgon, sizeof(Omnihswgon));
  uart_send_bytes(&superFanObj, &Omnihswgon, sizeof(Omnihswgon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void swingHorizontalOff()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[8] = V8_SWING_HOFF;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC
  char Ambhswgoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x6f ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  Ambhswgoff[11] = ambChecksum(Ambhswgoff, sizeof(Ambhswgoff));
  HOAGS_INFO("Inside Hswingoff\n");
  displayData(&Ambhswgoff, sizeof(Ambhswgoff));
  uart_send_bytes(&superFanObj, &Ambhswgoff, sizeof(Ambhswgoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #elif OMNI_AC
  char Omnihswgoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x73 ,0x04 ,0x00 ,0x01 ,0x00 ,0x00};  
  Omnihswgoff[11] = omniChecksum(Omnihswgoff, sizeof(Omnihswgoff));
  HOAGS_INFO("Inside omni VHswingoff\n");
  displayData(&Omnihswgoff, sizeof(Omnihswgoff));
  uart_send_bytes(&superFanObj, &Omnihswgoff, sizeof(Omnihswgoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void turboOn()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[9] = vfAck[13];
  printf("%s:before modify=", __func__);
  printBits(vfDefCmd[9]);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 5, 0);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 4, 1);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 7, 0);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 6, 0);
  printf("%s:after modify=", __func__);
  printBits(vfDefCmd[9]);
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC || OMNI_AC
  char Ambturon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x67 ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  Ambturon[11] = ambChecksum(Ambturon, sizeof(Ambturon));
  HOAGS_INFO("Inside turbo_on\n");
  displayData(&Ambturon, sizeof(Ambturon));
  uart_send_bytes(&superFanObj, &Ambturon, sizeof(Ambturon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void turboOff()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[9] = vfAck[13];
  printf("%s:before modify=", __func__);
  printBits(vfDefCmd[9]);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 5, 0);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 4, 0);
  printf("%s:after modify=", __func__);
  printBits(vfDefCmd[9]);
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC || OMNI_AC
  char Ambturoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x67 ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  Ambturoff[11] = ambChecksum(Ambturoff, sizeof(Ambturoff));
  HOAGS_INFO("Inside turbo_off\n");
  displayData(&Ambturoff, sizeof(Ambturoff));
  uart_send_bytes(&superFanObj, &Ambturoff, sizeof(Ambturoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void sleepOn()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[9] = vfAck[13];
  printf("%s:before modify=", __func__);
  printBits(vfDefCmd[9]);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 7, 0);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 6, 1);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 5, 0);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 4, 0);
  printf("%s:after modify=", __func__);
  printBits(vfDefCmd[9]);
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC
  char Ambsleon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x19 ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  Ambsleon[11] = ambChecksum(Ambsleon, sizeof(Ambsleon));
  HOAGS_INFO("Inside Sleepon\n");
  displayData(&Ambsleon, sizeof(Ambsleon));
  uart_send_bytes(&superFanObj, &Ambsleon, sizeof(Ambsleon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #elif OMNI_AC
  char Omnisleon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x6a ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  Omnisleon[11] = omniChecksum(Omnisleon, sizeof(Omnisleon));
  HOAGS_INFO("Inside omni Sleepon\n");
  displayData(&Omnisleon, sizeof(Omnisleon));
  uart_send_bytes(&superFanObj, &Omnisleon, sizeof(Omnisleon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void sleepOff()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[9] = vfAck[13];
  printf("%s:before modify=", __func__);
  printBits(vfDefCmd[9]);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 7, 0);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 6, 0);
  printf("%s:after modify=", __func__);
  printBits(vfDefCmd[9]);
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC
  char Ambsleoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x19 ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  Ambsleoff[11] = ambChecksum(Ambsleoff, sizeof(Ambsleoff));
  HOAGS_INFO("Inside Sleepoff\n");
  displayData(&Ambsleoff, sizeof(Ambsleoff));
  uart_send_bytes(&superFanObj, &Ambsleoff, sizeof(Ambsleoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #elif OMNI_AC
  char Omnisleoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x6a ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  Omnisleoff[11] = omniChecksum(Omnisleoff, sizeof(Omnisleoff));
  HOAGS_INFO("Inside omni Sleepoff\n");
  displayData(&Omnisleoff, sizeof(Omnisleoff));
  uart_send_bytes(&superFanObj, &Omnisleoff, sizeof(Omnisleoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}


void setTimer(unsigned char hour, unsigned char min, unsigned char c)
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  if(vfAck[4] == VF4_POWER_ON)
  {
    vfDefCmd[15] = V15_SET_TIMER_OFF;
    vfDefCmd[13] = hour;
    //vfDefCmd[14] = VF_MIN_SET;
  }
  else
  {
    vfDefCmd[15] = V15_SET_TIMER_ON;
    vfDefCmd[11] = hour;
    //vfDefCmd[12] = VF_MIN_SET;
  }
  printBits(vfDefCmd[15]);
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  // #elif OMNI_AC
  // char Omnitimer[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x08 ,0x6e ,0x02 ,0x00 ,0x04 , 0x00, 0x00, 0x00, c ,0x00};  
  // Omnitimer[14] = omniChecksum(Omnitimer, sizeof(Omnitimer));
  // printf("Inside OMNI Timer\n");
  // displayData(&Omnitimer, sizeof(Omnitimer));
  // uart_send_bytes(&superFanObj, &Omnitimer, sizeof(Omnitimer));
  // HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void cancelAllTimer()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  vfDefCmd[15] = V15_TIMER_SET;
  printBits(vfDefCmd[15]);
  HOAGS_ERR("CONTROL RECEIVED FROM APP");

  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #endif
}


void condaOn()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[10] = V10_SF_CONDA_ON;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #endif
}

void condaOff()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[10] = V10_SF_CONDA_OFF;
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[9] = vfAck[13];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  HOAGS_INFO("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  HOAGS_INFO("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #endif
}

void echoOn()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[9] = vfAck[13];
  printf("%s:before modify=", __func__);
  printBits(vfDefCmd[9]);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 3, 0);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 2, 1);
  printf("%s:after modify=", __func__);
  printBits(vfDefCmd[9]);
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }
  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC
  char Ambeon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x08 ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  Ambeon[11] = ambChecksum(Ambeon, sizeof(Ambeon));
  HOAGS_INFO("Inside echoon\n");
  displayData(&Ambeon, sizeof(Ambeon));
  uart_send_bytes(&superFanObj, &Ambeon, sizeof(Ambeon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #elif OMNI_AC
  char Omnieon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x68 ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  Omnieon[11] = omniChecksum(Omnieon, sizeof(Omnieon));
  HOAGS_INFO("Inside omni echoon\n");
  displayData(&Omnieon, sizeof(Omnieon));
  uart_send_bytes(&superFanObj, &Omnieon, sizeof(Omnieon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  #endif
}

void echoOff()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
  vfDefCmd[9] = vfAck[13];
  printf("%s:before modify=", __func__);
  printBits(vfDefCmd[9]);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 3, 0);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 2, 0);
  printf("%s:after modify=", __func__);
  printBits(vfDefCmd[9]);
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }
  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC
  char Ambeoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x08 ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  Ambeoff[11] = ambChecksum(Ambeoff, sizeof(Ambeoff));
  HOAGS_INFO("Inside echo_off\n");
  displayData(&Ambeoff, sizeof(Ambeoff));
  uart_send_bytes(&superFanObj, &Ambeoff, sizeof(Ambeoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #elif OMNI_AC
  char Omnieoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x68 ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  Omnieoff[11] = omniChecksum(Omnieoff, sizeof(Omnieoff));
  HOAGS_INFO("Inside omni echoon\n");
  displayData(&Omnieoff, sizeof(Omnieoff));
  uart_send_bytes(&superFanObj, &Omnieoff, sizeof(Omnieoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void displayOn()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
   vfDefCmd[9] = vfAck[13];
  printf("%s:before modify=", __func__);
  printBits(vfDefCmd[9]);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 1, 0);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 0, 0);
  printf("%s:after modify=", __func__);
  printBits(vfDefCmd[9]);
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC
  char Ambdison[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x6D ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  Ambdison[11] = ambChecksum(Ambdison, sizeof(Ambdison));
  HOAGS_INFO("Inside Display_on\n");
  displayData(&Ambdison, sizeof(Ambdison));
  uart_send_bytes(&superFanObj, &Ambdison, sizeof(Ambdison));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

 #elif OMNI_AC
  char Omnilton[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x71 ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  Omnilton[11] = omniChecksum(Omnilton, sizeof(Omnilton));
  HOAGS_INFO("Inside omni light_on\n");
  displayData(&Omnilton, sizeof(Omnilton));
  uart_send_bytes(&superFanObj, &Omnilton, sizeof(Omnilton));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void displayOff()
{
  if(!UARTConfigured) 
		return;
  #if VIRTUALFOREST_AC
  HOAGS_ERR("CONTROL RECEIVED FROM APP");
   vfDefCmd[9] = vfAck[13];
  printf("%s:before modify=", __func__);
  printBits(vfDefCmd[9]);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 1, 0);
  vfDefCmd[9] = modifyBit(vfDefCmd[9], 0, 1);
  printf("%s:after modify=", __func__);
  printBits(vfDefCmd[9]);
  if(isAckReceived)
  {
    vfDefCmd[4] = vfAck[4];
    vfDefCmd[5] = vfAck[5];
    vfDefCmd[6] = vfAck[10];
    vfDefCmd[7] = vfAck[6]-15;
    vfDefCmd[8] = vfAck[18];
    vfDefCmd[10] = vfAck[14];
    vfDefCmd[15] = vfAck[15];
    vfDefCmd[16] = vfAck[17];
  }

  printf("Before checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));

  vfDefCmd[22] = vfChecksum(vfDefCmd+1, 21);

  printf("After checksum\n");
  displayDataUC((unsigned char*)&vfDefCmd, sizeof(vfDefCmd));
  uart_send_bytes(&superFanObj, (char*)&vfDefCmd, sizeof(vfDefCmd));
  HOAGS_INFO("\n");
  return;

  #elif AMBER_AC
  char Ambdisoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x6D ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  Ambdisoff[11] = ambChecksum(Ambdisoff, sizeof(Ambdisoff));
  HOAGS_INFO("Inside Display_off\n");
  displayData(&Ambdisoff, sizeof(Ambdisoff));
  uart_send_bytes(&superFanObj, &Ambdisoff, sizeof(Ambdisoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #elif OMNI_AC
  char Omniltoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x71 ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  Omniltoff[11] = omniChecksum(Omniltoff, sizeof(Omniltoff));
  HOAGS_INFO("Inside omni light_off\n");
  displayData(&Omniltoff, sizeof(Omniltoff));
  uart_send_bytes(&superFanObj, &Omniltoff, sizeof(Omniltoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void heatModeAc()
{
  #if HAVELLS_AC
  char heatMode={0x55, 0xAA, 0x00, 0x06, 0x00, 0x05, 0x04, 0x04, 0x00, 0x01, 0x02, 0x15};
  //swapStructEndianness(&switchOff, sizeof(switchOff));
  displayDataUC((char*)&heatMode, sizeof(heatMode));
  uart_send_bytes(&superFanObj, (char*)&heatMode, sizeof(heatMode));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);    

  #elif AMBER_AC || OMNI_AC
  char Ambheat[] = {0x55 ,0xAA ,0x03 ,0x06 ,0x00 ,0x05 ,0x04 ,0x04 ,0x00 ,0x01 ,0x02 ,0x00};  
  Ambheat[11] = ambChecksum(Ambheat, sizeof(Ambheat));
  HOAGS_INFO("Inside Heat mode\n");
  displayData(&Ambheat, sizeof(Ambheat));
  uart_send_bytes(&superFanObj, &Ambheat, sizeof(Ambheat));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);
  #endif

}

void windModeAC()
{
  #if AMBER_AC || OMNI_AC
  char Ambwind[] = {0x55 ,0xAA ,0x03 ,0x06 ,0x00 ,0x05 ,0x04 ,0x04 ,0x00 ,0x01 ,0x04 ,0x00};  
  Ambwind[11] = ambChecksum(Ambwind, sizeof(Ambwind));
  HOAGS_INFO("Inside windmode\n");
  displayData(&Ambwind, sizeof(Ambwind));
  uart_send_bytes(&superFanObj, &Ambwind, sizeof(Ambwind));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

#if 0
void tempunitcontrolon(){
  
  #if OMNI_AC
  char Omnitempon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x65 ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  Omnitempon[11] = omniChecksum(Omnitempon, sizeof(Omnitempon));
  HOAGS_INFO("Inside omni Temp_control_on \n");
  displayData(&Omnitempon, sizeof(Omnitempon));
  uart_send_bytes(&superFanObj, &Omnitempon, sizeof(Omnitempon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void tempunitcontroloff(){
  
  #if OMNI_AC
  char Omnitempoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x65 ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  Omnitempoff[11] = omniChecksum(Omnitempoff, sizeof(Omnitempoff));
  HOAGS_INFO("Inside omni Temp_control_off \n");
  displayData(&Omnitempoff, sizeof(Omnitempoff));
  uart_send_bytes(&superFanObj, &Omnitempoff, sizeof(Omnitempoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void silenton(){
   #if OMNI_AC
  char Omnislon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x6c ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  Omnislon[11] = omniChecksum(Omnislon, sizeof(Omnislon));
  HOAGS_INFO("Inside omni Silent on \n");
  displayData(&Omnislon, sizeof(Omnislon));
  uart_send_bytes(&superFanObj, &Omnislon, sizeof(Omnislon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void silentoff(){
   #if OMNI_AC
  char Omnisloff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x6c ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  Omnisloff[11] = omniChecksum(Omnisloff, sizeof(Omnisloff));
  HOAGS_INFO("Inside omni Silent on \n");
  displayData(&Omnisloff, sizeof(Omnisloff));
  uart_send_bytes(&superFanObj, &Omnisloff, sizeof(Omnisloff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void blowon(){
  #if OMNI_AC
  char Omniblowon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x74 ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  Omniblowon[11] = omniChecksum(Omniblowon, sizeof(Omniblowon));
  HOAGS_INFO("Inside omni Omniblowon \n");
  displayData(&Omniblowon, sizeof(Omniblowon));
  uart_send_bytes(&superFanObj, &Omniblowon, sizeof(Omniblowon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void blowoff(){
  #if OMNI_AC
  char Omniblowoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x74 ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  Omniblowoff[11] = omniChecksum(Omniblowoff, sizeof(Omniblowoff));
  HOAGS_INFO("Inside omni Omniblowoff \n");
  displayData(&Omniblowoff, sizeof(Omniblowoff));
  uart_send_bytes(&superFanObj, &Omniblowoff, sizeof(Omniblowoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void Auxheaton(){
  #if OMNI_AC
  char OmniAuxon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x75 ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  OmniAuxon[11] = omniChecksum(OmniAuxon, sizeof(OmniAuxon));
  HOAGS_INFO("Inside omni OmniAuxon \n");
  displayData(&Omniblowoff, sizeof(OmniAuxon));
  uart_send_bytes(&superFanObj, &OmniAuxon, sizeof(OmniAuxon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void Auxheatoff(){
  #if OMNI_AC
  char OmniAuxoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x75 ,0x01 ,0x00 ,0x01 ,0x00 ,0x00};  
  OmniAuxoff[11] = omniChecksum(OmniAuxoff, sizeof(OmniAuxoff));
  HOAGS_INFO("Inside omni OmniAuxoff \n");
  displayData(&OmniAuxoff, sizeof(OmniAuxoff));
  uart_send_bytes(&superFanObj, &OmniAuxoff, sizeof(OmniAuxoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void omniautocleanon(){
  #if OMNI_AC
  char OmniAtoClnon[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x76 ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  OmniAtoClnon[11] = omniChecksum(OmniAtoClnon, sizeof(OmniAtoClnon));
  HOAGS_INFO("Inside omni OmniAuxoff \n");
  displayData(&OmniAtoClnon, sizeof(OmniAtoClnon));
  uart_send_bytes(&superFanObj, &OmniAtoClnon, sizeof(OmniAtoClnon));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}

void omniautocleanoff(){
  #if OMNI_AC
  char omniautocleanoff[] = {0x55 ,0xAA ,0x00 ,0x06 ,0x00 ,0x05 ,0x76 ,0x01 ,0x00 ,0x01 ,0x01 ,0x00};  
  omniautocleanoff[11] = omniChecksum(omniautocleanoff, sizeof(omniautocleanoff));
  HOAGS_INFO("Inside omni omniautocleanoff \n");
  displayData(&omniautocleanoff, sizeof(omniautocleanoff));
  uart_send_bytes(&superFanObj, &omniautocleanoff, sizeof(omniautocleanoff));
  HOAGS_DBG("%p %d\n", &superFanObj, superFanObj.uart_idx);

  #endif
}
#endif
void step_up_fan_speed_ac(struct fan* f)
{
    #if HAVELLS_AC
    switch(f->speed)
    {
        case AC_FAN_LOW:
            displayData(&midspeed, sizeof(midspeed));
            uart_send_bytes(&superFanObj, &midspeed, sizeof(midspeed));
            HOAGS_DBG("new_level=%d prev_level=%d\n", AC_FAN_MID, f->speed);
            f->speed = AC_FAN_MID;
            break;
        case AC_FAN_MID:
            displayData(&highspeed, sizeof(highspeed));
            uart_send_bytes(&superFanObj, &highspeed, sizeof(highspeed));
            HOAGS_DBG("new_level=%d prev_level=%d\n", AC_FAN_HIGH, f->speed);
            f->speed = AC_FAN_HIGH;
            break;
        case AC_FAN_HIGH:
            displayData(&autospeed, sizeof(autospeed));
            uart_send_bytes(&superFanObj, &autospeed, sizeof(autospeed));
            HOAGS_DBG("new_level=%d prev_level=%d\n", AC_FAN_AUTO, f->speed);
            f->speed = AC_FAN_AUTO;
            break;
        case AC_FAN_AUTO:
            displayData(&tinyspeed, sizeof(tinyspeed));
            uart_send_bytes(&superFanObj, &tinyspeed, sizeof(tinyspeed));
            HOAGS_DBG("new_level=%d prev_level=%d\n", AC_FAN_TINY, f->speed);
            f->speed = AC_FAN_TINY;
            break;
        case AC_FAN_TINY:
            displayData(&turbospeed, sizeof(turbospeed));
            uart_send_bytes(&superFanObj, &turbospeed, sizeof(turbospeed));
            HOAGS_DBG("new_level=%d prev_level=%d\n", AC_FAN_TURBO, f->speed);
            f->speed = AC_FAN_TURBO;
            break;
    }
    #endif
}

void step_down_fan_speed_ac(struct fan* f)
{
    #if HAVELLS_AC
    switch(f->speed)
    {
        case AC_FAN_TURBO:
            displayData(&tinyspeed, sizeof(tinyspeed));
            uart_send_bytes(&superFanObj, &tinyspeed, sizeof(tinyspeed));
            HOAGS_DBG("new_level=%d prev_level=%d\n", AC_FAN_TINY, f->speed);
            f->speed = AC_FAN_TINY;
            break;
        case AC_FAN_TINY:
            displayData(&autospeed, sizeof(autospeed));
            uart_send_bytes(&superFanObj, &autospeed, sizeof(autospeed));
            HOAGS_DBG("new_level=%d prev_level=%d\n", AC_FAN_AUTO, f->speed);
            f->speed = AC_FAN_AUTO;
            break;
        case AC_FAN_AUTO:
            displayData(&highspeed, sizeof(highspeed));
            uart_send_bytes(&superFanObj, &highspeed, sizeof(highspeed));
            HOAGS_DBG("new_level=%d prev_level=%d\n", AC_FAN_HIGH, f->speed);
            f->speed = AC_FAN_HIGH;
            break;
        case AC_FAN_HIGH:
            displayData(&midspeed, sizeof(midspeed));
            uart_send_bytes(&superFanObj, &midspeed, sizeof(midspeed));
            HOAGS_DBG("new_level=%d prev_level=%d\n", AC_FAN_MID, f->speed);
            f->speed = AC_FAN_MID;
            break;
        case AC_FAN_MID:
            displayData(&lowspeed, sizeof(lowspeed));
            uart_send_bytes(&superFanObj, &lowspeed, sizeof(lowspeed));
            HOAGS_DBG("new_level=%d prev_level=%d\n", AC_FAN_LOW, f->speed);
            f->speed = AC_FAN_LOW;
            break;
    }
    #endif
}


#endif

