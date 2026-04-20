#ifndef __APP_GENERIC_H
#define __APP_GENERIC_H

#ifdef __cplusplus
extern "C"
{
#endif

	
/*
 *	V1.0.0:
 *			一、Dw3000(PDoA)
 *
 *	V1.0.2:
 *			一、增加标签显示角度/距离值
 *			二、修改bug,RESP_MSG_TAGADDR_SN_IDX
 *
 *	V1.0.3:
 *			一、测距延迟时间20ms->10ms
 */	
	
/**************************************************************************************************
 * 																				INCLUDES
 **************************************************************************************************/	
#include <stdbool.h>

#include "Generic_CMD.h"
#include "OSAL_Comdef.h"

#include "default_config.h"
#include "hal_led.h"


	
/**************************************************************************************************
 * 																				CONSTANTS
 **************************************************************************************************/
#define IS_FISRT_POEWRON(x) ((x) != 0xAAAA)

//软件版本
#define uwb_software_ver "v01_00_002"
#ifdef HW_PA
	#define uwb_hardware_ver "v01_00_000(PA)"
#else
	#define uwb_hardware_ver "v01_00_000(xPA)"
#endif
								
/***************************************************************************************************
 * 																				TYPEDEF
 ***************************************************************************************************/
typedef struct
{
	uint32_t flag;
	uint32_t start_count;

	uint32_t HardFault_error_bit;
	uint32_t MemManage_error_bit;
	uint32_t BusFault_error_bit;
	uint32_t UsageFault_error_bit;
	
	param_block_t param_Config;
	
	uint32_t flash_error_count;
    uint32_t check_sum;       			//校验和:用于flash验证		
} System_Para_t; 

typedef struct
{
	uint8_t uart_dma_tx[1400];
	uint8_t uart_dma_tx_tmp[1400];	
	int uart_dma_report;
	int uart_dma_index;
}System_uart_dma_t;

enum Sys_mode_led_blink
{
	Sys_mode_led_blink_invalid 		= 0,
		
	/*闪烁一次周期 */
	Sys_mode_led_blink_fast_time 	= 2,	//0.2s
	Sys_mode_led_blink_slow_time 	= 10,	//1s
};

typedef enum
{
	/*工作模式 主*/
	Sys_Operate_Mode_INVAILD 		= 0x0000,		//无效
	Sys_Operate_Mode_CFG_ING 		= 0x0001,		//配置中
	Sys_Operate_Mode_WORK_DONE		= 0x0002,		//工作中	
}Sys_Work_Mode;


/***************************************************************************************************
 * 																				GLOBAL VARIABLES
 ***************************************************************************************************/
extern System_Para_t sys_para;
extern System_uart_dma_t sys_uart_dma_buf;




/**************************************************************************************************
 *                                        FUNCTIONS - API
 **************************************************************************************************/	
extern void App_Module_Init(void);	

extern void App_Module_Sys_Work_Mode_Event();

extern void App_Module_Sys_Deal_UART_USB_CMD_Event(bool flag);

extern void App_Modelu_Sys_Deal_IO_LED_Event(uint16_t count);

extern void App_Module_Sys_IO_Led_Mode_Set(Sys_Work_Mode Mode);

extern void App_Module_Sys_Write_NVM(void);

extern void App_Module_Sys_Read_NVM(void);


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif
#endif//__APP_GENERIC_H

