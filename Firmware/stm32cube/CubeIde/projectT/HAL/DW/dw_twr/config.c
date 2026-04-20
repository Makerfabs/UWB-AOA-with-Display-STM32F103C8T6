/*
 * @file       config.c
 *
 * @brief      supports NVM and bss configuration sections:
 *             defaultFConfig : section in RAM, where default parameters are saved and is not re-writabele.
 *              FCONFIG_ADDR  : section in NVM, where current parameters are saved and this is re-writabele.
 *                 bssConfig  : section in RAM, which is representing config data exist in FCONFIG_ADDR.
 *
 *             application on startup shall init_bssConfig() : this will copy data from FCONFIG_ADDR -> bssConfig
 *             Accessing to variables is by pointer get_pbssConfig();
 *
 *             if application wants to re-write data in FCONFIG_ADDR, use save_bssConfig(*newRamParametersBlock);
 *
 *             NOTE: The code is very MCU dependent and save will work with nRF52840 only
 *
 * @author     Decawave Software
 *
 * @attention  Copyright 2018 (c) DecaWave Ltd, Dublin, Ireland.
 *             All rights reserved.
 *
 * @modified   2018 PathPartner
 */

#include "config.h"

//#include "dw_pdoa_node_common.h"
#include "shared_functions.h"
#include "Generic.h"

//------------------------------------------------------------------------------

/* 
 * 功能:获取pConfig
 *
 * */
param_block_t *get_pbssConfig(void)
{
    return app.pConfig;
}


/* 
 * 功能:赋值全局变量到app中
 *
 * */
void load_bssConfig(void)
{	
    app.pConfig = &sys_para.param_Config;
	
#if 1
	_dbg_printf("rngOffset_mm：%d,pdoaOffset_deg :%d, motionfilter:%d, user_cmd:%d\n",
										sys_para.param_Config.s.rngOffset_mm, 
										sys_para.param_Config.s.pdoaOffset_deg, 
										sys_para.param_Config.s.motionfilter, 
										sys_para.param_Config.s.user_cmd);

	_dbg_printf("slot:%d,addr:%04X\n",sys_para.param_Config.knownTagList[0].slot,
								sys_para.param_Config.knownTagList[0].addr16);		
#endif
}
