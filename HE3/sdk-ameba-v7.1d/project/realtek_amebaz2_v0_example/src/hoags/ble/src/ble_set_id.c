#include "ble_set_id.h"
#include "hoags_config.h"
//#include "semphr.h"
#include "gap.h"

uint8_t* get_ble_id()
{	
	uint8_t hci_lgc_efuse[80];
	uint8_t* macid = hoagsMalloc(6);
	uint8_t i, *pbuf;
	pbuf = osif_mem_alloc(0, 1024);
	if (!pbuf || 0 == EFUSE_LMAP_READ(pbuf)) {
		HOAGS_ERR("EFUSE_LMAP_READ failed\n");
		if (pbuf) {
			osif_mem_free(pbuf);
		}

		return NULL;
	}

	memcpy(hci_lgc_efuse, pbuf + 0x1B0, 0x50);
	
	if (pbuf) {
		osif_mem_free(pbuf);
	}

	for(int i = 0; i<6 ; i++){
		macid[i] = hci_lgc_efuse[4+i];
	}

	return macid;

}

