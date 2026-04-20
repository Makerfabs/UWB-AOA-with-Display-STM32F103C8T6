/*! ---------------------------------------------------------------------------
 * @file    util.h
 * @brief   DecaWave Application Layer utility functions & Macros
 *
 * @author  Decawave Software
 *
 * @attention Copyright 2018 (c) DecaWave Ltd, Dublin, Ireland.
 *            All rights reserved.
 *
 */

#ifndef __UTIL__H__
#define __UTIL__H__ 1

#ifdef __cplusplus
 extern "C" {
#endif


#include <stdint.h>
#include "deca_device_api.h"


#define AR2U32(x)               (((uint32_t)x[3])<<24 |\
                                ((uint32_t)x[2])<<16  |\
                                ((uint32_t)x[1])<<8   |\
                                ((uint32_t)x[0]))

#define AR2U16(x)               ((x[1]<<8) | x[0])


#define TS2U64_MEMCPY(x,y) do{\
                            x = (uint64_t)(((uint64_t)y[4]<<32)|\
                                ((uint64_t)y[3]<<24)|\
                                ((uint64_t)y[2]<<16)|\
                                ((uint64_t)y[1]<<8) |\
                                y[0]); \
                         }while(0)

#define TS2TS_MEMCPY(x,y)  do {\
                            x[0] = y[0];\
                            x[1] = y[1];\
                            x[2] = y[2];\
                            x[3] = y[3];\
                            x[4] = y[4];\
                          }while(0)

#define U642TS_MEMCPY(x,y) do {\
                            x[0] = (uint8_t)(y>>0 & 0xff);\
                            x[1] = (uint8_t)(y>>8 & 0xff);\
                            x[2] = (uint8_t)(y>>16 & 0xff);\
                            x[3] = (uint8_t)(y>>24 & 0xff);\
                            x[4] = (uint8_t)(y>>32 & 0xff);\
                          }while(0)

#define U32TOAR_MEMCPY(x,y) do {\
                            x[0] = (uint8_t)(y>>0 & 0xff);\
                            x[1] = (uint8_t)(y>>8 & 0xff);\
                            x[2] = (uint8_t)(y>>16 & 0xff);\
                            x[3] = (uint8_t)(y>>24 & 0xff);\
                          }while(0)

uint64_t util_us_to_dev_time (double us);
double   util_dev_time_to_sec(uint64_t dt);
uint64_t util_sec_to_dev_time (double sec);
double util_us_to_sy(double us);

int16_t  calc_sfd_to(void * pCfg);

#ifdef __cplusplus
}
#endif

#endif /* __UTIL__H__ */
