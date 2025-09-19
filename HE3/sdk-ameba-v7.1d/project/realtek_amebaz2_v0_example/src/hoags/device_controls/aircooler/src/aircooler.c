#include "aircooler.h"
#include "hoags_config.h"
#include "packets.h"
#include "htap_config.h"

extern FanConfigured;
extern LightConfigured;
extern UARTConfigured;
extern struct serial_s superFanObj;

void powerOnAirCooler()
{
    unsigned char powerOn[] = {
                                AMBER0_START_IDENTIFIER, AMBER1_DATA_ATTR, AMBER2_START_DATA,
                                AMBER3_POWERON, AMBER4_FANSPEED_LOW, AMBER5_SWINGOFF, 
                                AMBER6_MOSQUITOOFF, AMBER7_PUMPOFF, AMBER_TBD, AMBER_TBD, 
                                AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD,
                                AMBER17_END_IDENTIFIER
                            };
    
    displayDataUC(powerOn, sizeof(powerOn));
    uart_send_bytes(&superFanObj, powerOn, sizeof(powerOn));
}
void powerOffAirCooler()
{
    unsigned char powerOff[] = {
                                AMBER0_START_IDENTIFIER, AMBER1_DATA_ATTR, AMBER2_START_DATA,
                                AMBER3_POWEROFF, AMBER4_FANSPEED_LOW, AMBER5_SWINGOFF, 
                                AMBER6_MOSQUITOOFF, AMBER7_PUMPOFF, AMBER_TBD, AMBER_TBD, 
                                AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD,
                                AMBER17_END_IDENTIFIER
                            };
    
    displayDataUC(powerOff, sizeof(powerOff));
    uart_send_bytes(&superFanObj, powerOff, sizeof(powerOff));
}
void fanSpeedLowAirCooler()
{
    unsigned char fanSpeedLow[] = {
                                AMBER0_START_IDENTIFIER, AMBER1_DATA_ATTR, AMBER2_START_DATA,
                                AMBER3_POWERON, AMBER4_FANSPEED_LOW, AMBER5_SWINGOFF, 
                                AMBER6_MOSQUITOOFF, AMBER7_PUMPOFF, AMBER_TBD, AMBER_TBD, 
                                AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD,
                                AMBER17_END_IDENTIFIER
                            };
    
    displayDataUC(fanSpeedLow, sizeof(fanSpeedLow));
    uart_send_bytes(&superFanObj, fanSpeedLow, sizeof(fanSpeedLow));
}
void fanSpeedMidAirCooler()
{
    unsigned char fanSpeedMid[] = {
                                AMBER0_START_IDENTIFIER, AMBER1_DATA_ATTR, AMBER2_START_DATA,
                                AMBER3_POWERON, AMBER4_FANSPEED_MID, AMBER5_SWINGOFF, 
                                AMBER6_MOSQUITOOFF, AMBER7_PUMPOFF, AMBER_TBD, AMBER_TBD, 
                                AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD,
                                AMBER17_END_IDENTIFIER
                            };
    
    displayDataUC(fanSpeedMid, sizeof(fanSpeedMid));
    uart_send_bytes(&superFanObj, fanSpeedMid, sizeof(fanSpeedMid));
}
void fanSpeedHighAirCooler()
{
    unsigned char fanSpeedHigh[] = {
                                AMBER0_START_IDENTIFIER, AMBER1_DATA_ATTR, AMBER2_START_DATA,
                                AMBER3_POWERON, AMBER4_FANSPEED_HIGH, AMBER5_SWINGOFF, 
                                AMBER6_MOSQUITOOFF, AMBER7_PUMPOFF, AMBER_TBD, AMBER_TBD, 
                                AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD,
                                AMBER17_END_IDENTIFIER
                            };
    
    displayDataUC(fanSpeedHigh, sizeof(fanSpeedHigh));
    uart_send_bytes(&superFanObj, fanSpeedHigh, sizeof(fanSpeedHigh));
}
void swingOnAirCooler()
{
    unsigned char swingOn[] = {
                                AMBER0_START_IDENTIFIER, AMBER1_DATA_ATTR, AMBER2_START_DATA,
                                AMBER3_POWERON, AMBER4_FANSPEED_LOW, AMBER5_SWINGON, 
                                AMBER6_MOSQUITOOFF, AMBER7_PUMPOFF, AMBER_TBD, AMBER_TBD, 
                                AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD,
                                AMBER17_END_IDENTIFIER
                            };
    
    displayDataUC(swingOn, sizeof(swingOn));
    uart_send_bytes(&superFanObj, swingOn, sizeof(swingOn));
}
void swingOffAirCooler()
{
    unsigned char swingOff[] = {
                                AMBER0_START_IDENTIFIER, AMBER1_DATA_ATTR, AMBER2_START_DATA,
                                AMBER3_POWERON, AMBER4_FANSPEED_LOW, AMBER5_SWINGOFF, 
                                AMBER6_MOSQUITOOFF, AMBER7_PUMPOFF, AMBER_TBD, AMBER_TBD, 
                                AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD,
                                AMBER17_END_IDENTIFIER
                            };
    
    displayDataUC(swingOff, sizeof(swingOff));
    uart_send_bytes(&superFanObj, swingOff, sizeof(swingOff));
}
void mosquitoOnAirCooler()
{
    unsigned char mosquitoOn[] = {
                                AMBER0_START_IDENTIFIER, AMBER1_DATA_ATTR, AMBER2_START_DATA,
                                AMBER3_POWERON, AMBER4_FANSPEED_LOW, AMBER5_SWINGOFF, 
                                AMBER6_MOSQUITOON, AMBER7_PUMPOFF, AMBER_TBD, AMBER_TBD, 
                                AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD,
                                AMBER17_END_IDENTIFIER
                            };
    
    displayDataUC(mosquitoOn, sizeof(mosquitoOn));
    uart_send_bytes(&superFanObj, mosquitoOn, sizeof(mosquitoOn));
}
void mosquitoOffAirCooler()
{
    unsigned char mosquitoOff[] = {
                                AMBER0_START_IDENTIFIER, AMBER1_DATA_ATTR, AMBER2_START_DATA,
                                AMBER3_POWERON, AMBER4_FANSPEED_LOW, AMBER5_SWINGOFF, 
                                AMBER6_MOSQUITOOFF, AMBER7_PUMPOFF, AMBER_TBD, AMBER_TBD, 
                                AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD,
                                AMBER17_END_IDENTIFIER
                            };
    
    displayDataUC(mosquitoOff, sizeof(mosquitoOff));
    uart_send_bytes(&superFanObj, mosquitoOff, sizeof(mosquitoOff));
}
void pumpOnAirCooler()
{
    unsigned char pumpOn[] = {
                                AMBER0_START_IDENTIFIER, AMBER1_DATA_ATTR, AMBER2_START_DATA,
                                AMBER3_POWERON, AMBER4_FANSPEED_LOW, AMBER5_SWINGOFF, 
                                AMBER6_MOSQUITOOFF, AMBER7_PUMPON, AMBER_TBD, AMBER_TBD, 
                                AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD,
                                AMBER17_END_IDENTIFIER
                            };
    
    displayDataUC(pumpOn, sizeof(pumpOn));
    uart_send_bytes(&superFanObj, pumpOn, sizeof(pumpOn));
}
void pumpOffAirCooler()
{
    unsigned char pumpOff[] = {
                                AMBER0_START_IDENTIFIER, AMBER1_DATA_ATTR, AMBER2_START_DATA,
                                AMBER3_POWERON, AMBER4_FANSPEED_LOW, AMBER5_SWINGOFF, 
                                AMBER6_MOSQUITOOFF, AMBER7_PUMPOFF, AMBER_TBD, AMBER_TBD, 
                                AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD, AMBER_TBD,
                                AMBER17_END_IDENTIFIER
                            };
    
    displayDataUC(pumpOff, sizeof(pumpOff));
    uart_send_bytes(&superFanObj, pumpOff, sizeof(pumpOff));
}