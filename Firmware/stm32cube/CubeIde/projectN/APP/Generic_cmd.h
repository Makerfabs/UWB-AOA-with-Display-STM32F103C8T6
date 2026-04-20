#ifndef __GENERIC_AT_H
#define __GENERIC_AT_H

#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************************************
 * 																				INCLUDES
 **************************************************************************************************/	
#include "OSAL_Comdef.h"
	
#include <stdbool.h>	
/**************************************************************************************************
 * 																				CONSTANTS
 **************************************************************************************************/		
#define CMD_SOP                    	 0x2A  
#define CMD_FOOT                     0x23 

#define SOP_STATE      0x00
#define LEN_STATE      0x01
#define DATA_STATE     0x02
#define FCS_STATE      0x03
#define END_STATE      0x04

#define IS_RIGTH_FOOT(x)	(x == CMD_FOOT)

	
#define MSG_HEX_OUTPUT_LEN (1+2+4+4+2+2+2+4+4)

/***************************************************************************************************
 * 																				TYPEDEF
 ***************************************************************************************************/
#pragma pack(push,1)


typedef struct
{
    uint8_t sn;
    uint16_t Addr;
	int angle;
	int distance;
	uint16_t user_cmd;
	float F_Path_Power_Level;
	float RX_Level;
	uint16_t Acc_X;
	uint16_t Acc_Y;
	uint16_t Acc_Z;	
}General_t;

typedef struct
{
    uint8_t header;
    uint8_t length;
    General_t gerneal_para;
    uint8_t check;
    uint8_t footer;
}Msg_Hex_Output_t;	
#pragma pack(pop)

enum UART_FRAME{
	UART_FRAME_JS
};


/***************************************************************************************************
 * 																				GLOBAL VARIABLES
 ***************************************************************************************************/
	
/**************************************************************************************************
 *                                        FUNCTIONS - API
 **************************************************************************************************/	
 static uint8_t usart1_recv_msg_handler(uint8_t ch);

extern int App_Module_CMD_Queue_Init(void);

extern int App_Module_format_conver_uint8(Msg_Hex_Output_t msg, uint8_t *buf);

extern int App_Module_Process_USART_CMD(void);

extern int App_Module_Process_USB_CMD(void);


extern void port_tx_msg(uint8_t *buf, uint16_t len);


#ifdef __cplusplus
}
#endif
#endif//__GENERIC_AT_H

