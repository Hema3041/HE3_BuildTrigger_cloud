/*hogasFATFS.h */
#include "ff.h"
#include <fatfs_ext/inc/ff_driver.h>

#include "FreeRTOS.h"
#include "task.h"
#include <platform/platform_stdlib.h>
#include "basic_types.h"
#include "platform_opts.h"
#include "section_config.h"
#include "fatfs_flash_api.h"


/* Config for Ameba-Pro */

FRESULT list_files(char *);
FRESULT del_dir(const TCHAR *path, int del_self);  
FATFS 	fs_sd;
FIL     m_file;

fatfs_flash_params_t fatfs_flash;

int hoags_fatfs_write( char *folder, char *filename , void *data, size_t len, short append );
void* hoags_fatfs_read( char *folder,char *filename , size_t *len );
