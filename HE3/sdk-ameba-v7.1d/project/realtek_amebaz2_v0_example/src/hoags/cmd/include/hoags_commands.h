#ifndef __HOAGS_COMMANDS_H__
#define __HOAGS_COMMANDS_H__ //header guard

#include "env.h"
#include "hoags_config.h"
//#include "circularbuffer.h"
//#include "micRecord.h"
//#include "filters.h"

//list of supported hoags commands
#define HOAGS_CMD_ENV       "henv"
#define HOAGS_CMD_STAT      "hstat"
#define HOAGS_CMD_LISTDIR   "hlist"
#define HOAGS_CMD_UART      "huart"
#define HOAGS_CMD_RESET     "hreset"
#define HOAGS_CMD_REBOOT     "reboot"
#define HOAGS_CMD_EFUSE     "EFUSE"
#define HOAGS_CMD_FLASH_READ "hflash"
#define HOAGS_CMD_HOAGS_SEC     "HOAGS_SEC"

void printHoagsHelp();
void currentRAMload();
void getCurrentCPUload();
char** split_string(char* str, const char* delimiter);


#endif //__HOAGS_COMMANDS_H__

