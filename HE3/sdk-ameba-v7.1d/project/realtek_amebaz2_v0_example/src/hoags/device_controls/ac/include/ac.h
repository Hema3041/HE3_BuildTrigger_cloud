#ifndef __HOAGS_AC_CONTROLS_H__
#define __HOAGS_AC_CONTROLS_H__

#include "pwmout_api.h"
#include "hoags_config.h"
#define AMBER_MIN_TEMP	16
#define AMBER_MAX_TEMP	30

//for ble
enum AC_CMD {
	AC_CMD_POWER_CONTROL,
    AC_CMD_SPEED_CONTROL,
    AC_CMD_TEMP_CONTROL,
	AC_CMD_MODE_CONTROL,
	AC_CMD_SWING_CONTROL,
	AC_CMD_TURBO_CONTROL,
	AC_CMD_SLEEP_CONTROL,
	AC_CMD_TIMER_CONTROL,
	AC_CMD_CONDA_CONTROL,
	AC_CMD_ECO_CONTROL,
	AC_CMD_DISPLAY_CONTROL,
};

enum AC_CMD_POWER {
	AC_CMD_ON,
	AC_CMD_OFF
};

enum AC_CMD_SPEED {
    AC_CMD_SPEED_LOW,
    AC_CMD_SPEED_HIGH,
	AC_CMD_SPEED_MID,
	AC_CMD_SPEED_AUTO,
};

enum AC_CMD_TEMP {
    AC_CMD_TEMP_INCREASE,
    AC_CMD_TEMP_DECREASE
};

enum AC_CMD_MODE {
	AC_CMD_MODE_DRY,
	AC_CMD_MODE_COOL,
	AC_CMD_MODE_AUTO,
	AC_CMD_MODE_FAN,
	AC_CMD_MODE_HOT,
	AC_CMD_MODE_WIND
};

enum AC_SWING {
	AC_SWING_VON,
	AC_SWING_VOFF,
	AC_SWING_HON,
	AC_SWING_HOFF,
};

enum AC_TURBO {
	AC_TURBO_ON,
	AC_TURBO_OFF,
};

enum AC_SLEEP {
	AC_SLEEP_ON,
	AC_SLEEP_OFF,
};

enum AC_TIMER {
	AC_TIMER_ON,
	AC_TIMER_OFF,
};

enum AC_CONDA {
	AC_CONDA_ON,
	AC_CONDA_OFF,
};

enum AC_ECO {
	AC_ECO_ON,
	AC_ECO_OFF,
};

enum AC_DISPLAY {
	AC_DISPLAY_ON,
	AC_DISPLAY_OFF,
};

#if HAVELLS_AC
#define HVLS0_BYTE 0x55
#define HVLS1_BYTE 0xAA
#endif
#if HAVELLS_AC
enum ac_fan_speed_level
{
	AC_FAN_LOW = 10,
	AC_FAN_MID = 30,
	AC_FAN_HIGH = 50,
	AC_FAN_AUTO = 60,
	AC_FAN_TINY = 80,
	AC_FAN_TURBO = 100
};
#endif

#if VIRTUALFOREST_AC

#define VF0_START_BYTE  0x24 

#define VF1_LENGTH  0x16

#define VF2_APPLIANCE_TYPE 0x03

#define VF3_CONTROL_TYPE 0x01

#define VF4_POWER_OFF	0x00
#define VF4_POWER_ON	0x01

#define VF5_MODE_COOL	0x01
#define VF5_MODE_DRY	0x02
#define VF5_MODE_HEAT	0x03 //MCU not implemented
#define VF5_MODE_FAN	0x04
#define VF5_MODE_AUTO	0x05


#define VF6_FAN_OFF			0x00
#define VF6_FAN_BREEZE		0x01
#define VF6_FAN_SILENT		0x02
#define VF6_FAN_LOW			0x03
#define VF6_FAN_MID			0x04
#define VF6_FAN_HIGH		0x05
#define VF6_FAN_TURBO		0x06
#define VF6_FAN_AUTO		0x07
#define VF6_FAN_HALFLOAD	0x08
#define VF6_FAN_FULLLOAD	0x09

#define V7_TEMP_16	0x01
#define V7_TEMP_17	0x02
#define V7_TEMP_18	0x03
#define V7_TEMP_19	0x04
#define V7_TEMP_20	0x05
#define V7_TEMP_21	0x06
#define V7_TEMP_22	0x07
#define V7_TEMP_23	0x08
#define V7_TEMP_24	0x09
#define V7_TEMP_25	0x0A
#define V7_TEMP_26	0x0B
#define V7_TEMP_27	0x0C
#define V7_TEMP_28	0x0D
#define V7_TEMP_29	0x0E
#define V7_TEMP_30	0x0F

#define V8_SWING_VOFF	0x00
#define V8_SWING_VON	0x1
#define V8_SWING_HON	0x10
#define V8_SWING_HOFF	0x00

#define V9_TURBO_ON		0x10
#define V9_TURBO_OFF	0x00

#define V9_SLEEP_ON		0X40
#define V9_SLEEP_OFF	0X00

#define V9_SF_DISP_ON	0x00
#define V9_SF_DISP_OFF	0x1

#define V10_SF_CONDA_OFF	0x00
#define V10_SF_CONDA_ON		0x40

#define V9_ECHO_ON		0X4
#define V9_ECHO_OFF 	0X00

#define V15_SET_TIMER_ON 	0x01
#define V15_SET_TIMER_OFF	0x04
#define V15_TIMER_SET	0x00
#define VF_TIMER_OFF	0x00
#define VF_MIN_SET	0x00

#if 0
#define VF_TIMER_HR1	0x01
#define VF_TIMER_HR2	0x02
#define VF_TIMER_HR3	0x03
#define VF_TIMER_HR4	0x04
#define VF_TIMER_HR5	0x05
#define VF_TIMER_HR6	0x06
#define VF_TIMER_HR7	0x07
#define VF_TIMER_HR8	0x08
#define VF_TIMER_HR9	0x09
#define VF_TIMER_HR10	0x0A
#define VF_TIMER_HR11	0x0B
#define VF_TIMER_HR12	0x0C
#define VF_TIMER_HR13	0x0D
#define VF_TIMER_HR14	0x0E
#define VF_TIMER_HR15	0x0F
#define VF_TIMER_HR16	0x10
#define VF_TIMER_HR17	0x11
#define VF_TIMER_HR18	0x12
#define VF_TIMER_HR19	0x13
#define VF_TIMER_HR20	0x14
#define VF_TIMER_HR21	0x15
#define VF_TIMER_HR22	0x16
#define VF_TIMER_HR23	0x17
#define VF_TIMER_HR24	0x18

#define VF_TIMER_MIN1	0x01
#define VF_TIMER_MIN2	0x02
#define VF_TIMER_MIN3	0x03
#define VF_TIMER_MIN4	0x04
#define VF_TIMER_MIN5	0x05
#define VF_TIMER_MIN6	0x06
#define VF_TIMER_MIN7	0x07

#endif

#define VF15_TIMER_ON_DISABLE	0x00
#define VF15_TIMER_ON_ENABLE	0x01
#define VF15_TIMER_OFF_ENABLE	0x04
#define VF15_TIMER_OFF_DISABLE	0x00

#define V16_ADJUST	0x00

#define VF_RESERVED	0x00

#define VF22_CHECKSUM	0x00
#define VF23_ENDBYTE	0x23


#define V13_TIMEOFF_HR
#define V13_TIMEOFF_MIN




enum vfControlPos
{
	POWERBYTE = 4,
	MODEBYTE = 5,
	FANBYTE = 6,
	TEMPBYTE = 7,
	SWINGBYTE = 8,
	SPECIALFEATURE1 = 9,
	SPECIALFEATURE2 = 10,
	ONTIMERMIN = 12,
	OFFTIMERMIN = 14,
	ONTIMERHOUR = 11,
	OFFTIMERHOUR = 13,
	ONOFFTIMERSTATUS = 15,
};

#endif

#if AMBER_AC
#define AMB0_START_BYTE  0x55
#define AMB1_BYTE  0xAA

#elif OMNI_AC
#define OMNI0_START_BYTE 0x55
#define OMNI1_BYTE 0xAA
#endif

#endif
