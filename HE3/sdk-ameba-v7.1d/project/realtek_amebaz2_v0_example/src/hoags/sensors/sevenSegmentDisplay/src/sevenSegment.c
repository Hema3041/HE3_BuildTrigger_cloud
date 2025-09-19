#include "i2c_api.h"

#if 1
unsigned short int Zero=(0xfc00);
unsigned short int One=(0x6000);
unsigned short int Two=(0xda00);
unsigned short int Three=(0xf200);
unsigned short int Four=(0x1900);
unsigned short int Five=(0x1200);
unsigned short int Six=(0x0200);
unsigned short int Seven=(0x7800);
unsigned short int Eight=(0x0000);
unsigned short int Nine=(0x1800);
#endif


#define MBED_I2C_SLAVE_ADDR0    0x20
#define MBED_I2C_BUS_CLK        100000  //hz

void CircularDisplay(i2c_t *i2cObj)
{
    unsigned short int One=0x7800;
    unsigned short int Two=0x7100;
    unsigned short int Three=0x6300;
    unsigned short int Four=0x4700;
    unsigned short int Five=0x4E00;
    unsigned short int Six=0x5C00;

    i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&One,2,0);
    DelayMs(300);
    i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Two,2,0);
    DelayMs(300);
    i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Three,2,0);
    DelayMs(300);
    i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Four,2,0);
    DelayMs(300);
    i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Five,2,0);
    DelayMs(300);
    i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Six,2,0);
    DelayMs(300);

}

void sevenSegmentDisplay(short int value,i2c_t *i2cObj)
{
    //i2c_start(&i2cObj);
	printf("*** Start Cond sent ***\n");
    #if 1
    switch(value)
    {
        case 0: i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Zero,2,1);
        printf("*** 0 Displayed ***\n");
		//DelayMs(2000);
        break;

         case 1: i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&One,2,1);
         printf("*** 1 Displayed ***\n");
		//DelayMs(2000);
        break;

         case 2: i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Two,2,1);
         printf("*** 2 Displayed ***\n");
		//DelayMs(2000);
        break;

         case 3: i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Three,2,1);
         printf("*** 3 Displayed ***\n");
		//DelayMs(2000);
        break;

         case 4: i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Four,2,1);
         printf("*** 4 Displayed ***\n");
		//DelayMs(2000);
        break;

         case 5: i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Five,2,1);
         printf("*** 5 Displayed ***\n");
		//DelayMs(2000);
        break;

         case 6: i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Six,2,1);
         printf("*** 6 Displayed ***\n");
		//DelayMs(2000);
        break;

         case 7: i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Seven,2,1);
         printf("*** 7 Displayed ***\n");
		//DelayMs(2000);
        break;

         case 8: i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Eight,2,1);
         printf("*** 8 Displayed ***\n");
		//DelayMs(2000);
        break;

         case 9: i2c_write(i2cObj,MBED_I2C_SLAVE_ADDR0,&Nine,2,1);
         printf("*** 9 Displayed ***\n");
		//DelayMs(2000);
        break;

        default : printf("Unknown***\n");

    }
    #endif
}
