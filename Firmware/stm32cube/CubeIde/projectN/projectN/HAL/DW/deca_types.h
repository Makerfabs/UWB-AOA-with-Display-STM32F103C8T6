/*! ----------------------------------------------------------------------------
 *  @file   deca_types.h
 *  @brief  Decawave general type definitions
 *
 * @attention
 *
 * Copyright 2013-2020 (c) Decawave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 */

#ifndef _DECA_TYPES_H_
#define _DECA_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
	


typedef uint8_t        uint8 ;
typedef int8_t         int8;


typedef uint16_t        uint16 ;
typedef int16_t         int16 ;


typedef uint32_t        uint32 ;
typedef int32_t         int32 ;

typedef uint64_t        uint64 ;
typedef int64_t         int64 ;

#ifndef NULL
#define NULL ((void *)0UL)
#endif

#ifdef __cplusplus
}
#endif

#endif /* DECA_TYPES_H_ */


