#if 0
#ifndef OTA_H3_H
#define OTA_H3_H
#include <FreeRTOS.h>
#include <task.h>
#include <platform_stdlib.h>
#include <flash_api.h>
#include <lwip/sockets.h>

/************************Related setting****************************/
// #define HTTP_OTA_UPDATE

// #define BUF_SIZE		4096
// #define HEADER_BAK_LEN	32
/*******************************************************************/


/****************Define the structures used*************************/
// typedef struct{
// 	uint32_t	ip_addr;
// 	uint16_t	port;
// }update_cfg_local_t;

// typedef struct {
// 	uint32_t	status_code;
// 	uint32_t	header_len;
// 	uint8_t		*body;
// 	uint32_t	body_len;
// 	uint8_t		*header_bak;
// 	uint32_t	parse_status;
// } http_response_result_t;

//shaik for ota//

typedef struct {
	u32   ImgValidity;   
	u32	  Pattern;  	
	u32	  Checksum;	
	u32   Rsrvd;
	u32   ImgLen;		
	u32   Rsrvd1;     
	u32   Rsrvd2;     
	u32   Rsrvd3;    
	
} OTA_ImgHdr_St;


/**
  * @brief  OTA target image manifest structure definition
  */
typedef struct {
	u32 Pattern[2];
	u8 Rsvd1[8];
	u8 Ver;
	u8 ImgID;
	u8 AuthAlg;
	u8 HashAlg;
	u16 MajorImgVer;
	u16 MinorImgVer;
} update_manifest_info;


/*******************************************************************/
//void ota_update(struct file_info_t* file);
//int Verify_CheckSum_BLE(uint32_t, u32, uint32_t);

/****************General functions used by ota update***************/
// void *update_malloc(unsigned int size);
// void update_free(void *buf);
// void ota_platform_reset(void);

// uint32_t update_ota_prepare_addr(void);
// int update_ota_erase_upg_region(uint32_t img_len, uint32_t NewFWLen, uint32_t NewFWAddr);
// int update_ota_signature(unsigned char* sig_backup, uint32_t NewFWAddr);
/*******************************************************************/


/*******************Functions called by AT CMD**********************/
/*******************************************************************/


/*************************************************************************************************
** Function Name  : update_ota_local
** Description    : Starting a thread of OTA updating through socket
** Input          : ip:The IP address of OTA server
**					port:The Port of OTA server
** Return         : 0: Task created OK
**					-1: Task created failed
**************************************************************************************************/

#endif
#endif
