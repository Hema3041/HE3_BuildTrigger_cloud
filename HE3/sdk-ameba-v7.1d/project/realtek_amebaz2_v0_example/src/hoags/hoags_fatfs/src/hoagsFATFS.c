#include "hoagsFATFS.h"

FIL flptr;		//filepointer


XIP_TEXT_SECTION
BOOL hoagsInitFATFS()
{
	FRESULT res; 

	res = fatfs_flash_init();
	if(res < 0){
		HOAGS_ERR("failed (%d)\n", res);
		fatfs_flash_close();
		return FALSE;
	}

	return TRUE;
}


FRESULT hoagsFATFSDelFile(char* filename)
{
    static char filepath[64];
    memset(filepath, 0x00, sizeof(filepath));

    strcpy(filepath, fatfs_flash.drv);
    sprintf(&filepath[strlen(filepath)], "%s", filename);

    const TCHAR* fileToDelete = filename;
    return f_unlink(fileToDelete);
}

XIP_TEXT_SECTION
void* hoagsReadFATFS( char *folder,char *filename , size_t *len ){
    FILINFO fi;
    FRESULT res;
    int br=0;
 
    char path[64] = {0};
 
    //sprintf(path, "%s/%s", folder, filename);
   
    strcpy(path, folder);
    sprintf(&path[strlen(path)],"%s",filename);
 
    printf("Opening=%s\n", path);
    res = f_open(&flptr, path, FA_OPEN_ALWAYS | FA_READ);
    if(res){
        printf("open file (%s) fail.\n", path);
        return NULL;
    }
    printf("\n...............Reading started..........\n");
   
    f_stat(path, &fi);
    size_t filesize = fi.fsize;
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%s:%d \n",__func__,filesize);
   
    if( filesize == 0 ){
        printf("Mostly file is present but size if 0, so to avoid hoagsMalloc(0) we will return from here!");
        return NULL;
    }
 
    *len = filesize;
 
    void* RDBuf = hoagsMalloc(filesize);
    memset(&RDBuf[0], 0x00, filesize);
   
    //ove the file pointer to the file head*/
    res = f_lseek(&flptr, 0);
 
    char* pos = (char*)RDBuf;
 
    do
    {
        res = f_read(&flptr, RDBuf, filesize, (u32*)&br);
        if (filesize < 0)
        {
            printf("lfs_file_size fail %d\n", filesize);
            if(RDBuf)
                free(RDBuf);
 
            res = f_close(&flptr);
            if(res){
                printf("close file (%s) fail.\n", filename);
            }
            printf("\n");
 
            return NULL;
        }
        if(res){
            f_lseek(&flptr, 0);
            printf("Read error.\n");
           
            res = f_close(&flptr);
            if(res){
                printf("close file (%s) fail.\n", filename);
            }
            printf("\n");
           
            return NULL;
        }
 
        memcpy(pos, RDBuf, filesize);
        pos += br;
    }while(br < filesize);
    // printf("Read content:\n%s\n", RDBuf);
    // close source file
    res = f_close(&flptr);
    if(res){
        printf("close file (%s) fail.\n", filename);
    }
    printf("\n");
 
    return RDBuf;
}

XIP_TEXT_SECTION
int hoagsWriteFATFS( char *folder, char *filename , void *data, size_t len, short append ){
/*for write file*/
    printf("%s:%d\n", __func__, __LINE__);
    FRESULT res;
    u16 bw=0;
    char path[16] = {0};
    FIL file;
   
    printf("%s:%d ", __func__, __LINE__);
 
    strcpy(path, folder);
    sprintf(&path[strlen(path)],"%s",filename);
    printf("Opening: %s\n", path);
    printf("%s:%d\n", __func__, __LINE__);
    //sprintf(&path[strlen(path)],"%s",filename);
 
    printf("%s:%d ", __func__, __LINE__);
 
    res = f_open(&file, path, FA_OPEN_ALWAYS | FA_WRITE);
    if (res != FR_OK) {
        printf("Failed to open file: %s\n", path);
        return 0;
    }
   
    printf("%s:%d ", __func__, __LINE__);
 
    void* WRBuf = hoagsMalloc(len);
    if (!WRBuf) {
        printf("Memory allocation failed\n");
        f_close(&file);
        return 0;
    }
   
    if (append) {
        res = f_lseek(&file, f_size(&file));
        if (res != FR_OK) {
            printf("Seek error\n");
            f_close(&file);
            return 0;
        }
    }
 
    memcpy(WRBuf, data, len);
   
    // Write data to file
    res = f_write(&file, WRBuf, len, &bw);
    free(WRBuf);
   
    if (res != FR_OK || bw < len) {
        printf("Write error. Written: %u bytes\n", bw);
        f_close(&file);
        return 0;
    }
   
    // Close file
    f_close(&file);
    printf("Successfully written %u bytes to %s\n", bw, path);
   
    return bw;  
}

char *print_file_info(FILINFO fileinfo, char *fn, char* path)
{
	char info[256];
	char fname[64];
	memset(fname, 0, sizeof(fname));
	snprintf(fname, sizeof(fname), "%s", fn);	
	
	snprintf(info, sizeof(info), 
		"%c%c%c%c%c  %u/%02u/%02u  %02u:%02u  %9u  %30s  %30s", 
		(fileinfo.fattrib & AM_DIR) ? 'D' : '-',
		(fileinfo.fattrib & AM_RDO) ? 'R' : '-',
		(fileinfo.fattrib & AM_HID) ? 'H' : '-',
		(fileinfo.fattrib & AM_SYS) ? 'S' : '-',
		(fileinfo.fattrib & AM_ARC) ? 'A' : '-',
		(fileinfo.fdate >> 9) + 1980,
		(fileinfo.fdate >> 5) & 15,
		fileinfo.fdate & 31,
		(fileinfo.ftime >> 11),
		(fileinfo.ftime >> 5) & 63,
		fileinfo.fsize,
		fn,
		path);
	printf("%s\n\r", info);
	return info;
}


FRESULT list_files(char* list_path)
{
	DIR m_dir;
	FILINFO m_fileinfo;
	FRESULT res;
	char *filename;
#if _USE_LFN && !defined(FATFS_R_13C)
	char fname_lfn[_MAX_LFN + 1];
	m_fileinfo.lfname = fname_lfn;
	m_fileinfo.lfsize = sizeof(fname_lfn);
#endif
	char cur_path[64];
	//strcpy(cur_path, list_path);

	// open directory
	res = f_opendir(&m_dir, list_path);

	if(res == FR_OK)
	{
		for (;;) {
			strcpy(cur_path, list_path);
			// read directory and store it in file info object
			res = f_readdir(&m_dir, &m_fileinfo);
			if (res != FR_OK || m_fileinfo.fname[0] == 0) {
				break;
			}

#if _USE_LFN && !defined(FATFS_R_13C)
			filename = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
			filename = m_fileinfo.fname;
#endif
			if (*filename == '.' || *filename == '..') 
			{
				continue;
			}

			// check if the object is directory
			if(m_fileinfo.fattrib & AM_DIR)
			{
				print_file_info(m_fileinfo, filename, cur_path);
				sprintf(&cur_path[strlen(list_path)], "/%s", filename);
				res = list_files(cur_path);
				//strcpy(list_path, cur_path);
				if (res != FR_OK) 
				{
					break;
				}
				//list_path[strlen(list_path)] = 0;
			}
			else {
				print_file_info(m_fileinfo, filename, cur_path);
			}

		}
	}

	// close directory
	res = f_closedir(&m_dir);
	if(res){
		printf("close directory fail: %d\n", res);
	}
	return res;
}


 
#if 0
void read_write_test(void){

	if(fatfs_flash_get_param(&fatfs_flash)){
		printf("\n Not able to get parm \n");
		return;
	}
	char test_str[]="I am rehan testing and writing  reading";
	printf("\n start writing fun \n");
	
	hoags_fatfs_write(fatfs_flash.drv ,"flash_drive.txt",test_str);
	printf("\nafter write fun \n");

	void * temp =hoags_fatfs_read(fatfs_flash.drv ,"flash_drive.txt",0);
	printf("\nread data:%s\n",temp);

	vTaskDelete(NULL);

}


void create_fatfs(void)
{
	if(xTaskCreate(read_write_test, ((const char*)"read_write_test"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_fatfs_thread) failed", __FUNCTION__);
}
#endif



















