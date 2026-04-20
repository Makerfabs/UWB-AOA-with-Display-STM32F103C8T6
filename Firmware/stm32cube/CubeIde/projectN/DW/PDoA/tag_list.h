/*! ---------------------------------------------------------------------------
 * @file    tag_list.h
 * @brief
 *
 *
 * @author Decawave Software
 *
 * @attention Copyright 2018 (c) DecaWave Ltd, Dublin, Ireland.
 *            All rights reserved.
 *
 */

#ifndef __INC_TAG_LIST_H__
#define __INC_TAG_LIST_H__ 

#include <stdint.h>

#ifndef _WINT_T
#define _WINT_T
typedef uint32_t wint_t;
#endif
#ifdef __cplusplus
 extern "C" {
#endif


#pragma anon_unions
	 	 
	 
#include <stdint.h>
#include <string.h>
#include "OSAL_Comdef.h"

	 
#define MAX_KNOWN_TAG_LIST_SIZE               (DEFAULT_NUM_SLOTS - 1)/*(9)*/  // MAX_KNOWN_TAG_LIST_SIZE =  DEFAULT_NUM_SLOTS - 1 as Slot 0 is for Beacon
#define MAX_DISCOVERED_TAG_LIST_SIZE          (DEFAULT_NUM_SLOTS - 1)/*(9)*/  // MAX_DISCOVERED_TAG_LIST_SIZE =  DEFAULT_NUM_SLOTS - 1 as Slot 0 is for Beacon

	 
/* Tag list */

typedef struct
{
    uint16_t    slot;
    __packed union {
        uint8_t        addrShort[2];
        uint16_t    addr16;
    };
    __packed union    {
        uint8_t        addrLong[8];
        uint64_t     addr64;
    };
    uint16_t    multFast;
    uint16_t    multSlow;
    uint16_t    mode;                           //IMU = bit 0

    __packed union    {
        uint8_t        req;
    };
}__attribute__((packed))
tag_addr_slot_t;


tag_addr_slot_t *get_tag16_from_knownTagList(uint16_t addr16);
tag_addr_slot_t *get_tag64_from_knownTagList(uint64_t addr64);
tag_addr_slot_t *add_tag_to_knownTagList(uint64_t addr64, uint16_t addr16);
void del_tag64_from_knownTagList(uint64_t addr64);
void del_tag16_from_knownTagList(uint16_t addr16);

int      addTagToDList(uint64_t addr64);


uint16_t getDList_size(void);
uint64_t *getDList(void);

void init_knownTagList(void);
tag_addr_slot_t *get_knownTagList(void);
uint16_t get_knownTagList_size(void);


void initDList(void);

#ifdef __cplusplus
}
#endif

#endif /* __INC_TAG_LIST_H_ */
