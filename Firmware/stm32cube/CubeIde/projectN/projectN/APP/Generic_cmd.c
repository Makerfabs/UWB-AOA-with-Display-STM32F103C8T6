#include <stdint.h>

#ifndef _WINT_T
#define _WINT_T
typedef uint32_t wint_t;
#endif
#include <string.h>

#include "Generic.h"
#include "Generic_cmd.h"

#include "usart.h"
#include "hal_flash.h"
#include "hw_config.h"
#include "usbd_cdc_if.h"
#include "OSAL.h"
#include "Queue.h"

static QUEUE uart_queue;
extern QUEUE8_t m_QueueUsbComTx;   // 发送队列

#define USART1_RX_ISR_MAX_LEN  		64 
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
 static uint16_t usart1_rx_sta = 0 ;//接收状态标记
 static uint8_t usart1_rx_buf[USART1_RX_ISR_MAX_LEN] = { 0 };

extern char USART1_DMA_RX_BYTE;

int App_Module_CMD_Queue_Init(void)
{

	memset(usart1_rx_buf,0,sizeof(usart1_rx_buf));

	
	osal_CreateQueue(&uart_queue, QUEUE_MSG_MAX);
}

int App_Module_Process_USB_CMD(void)
{
	uint8_t USB_RxBuff[512];
	memset(USB_RxBuff, 0, sizeof(USB_RxBuff));
	int len = USB_RxRead (USB_RxBuff, sizeof(USB_RxBuff));
	if( len != 0)
	{
		for(int i = 0; i< len; i++)
		{
			if(usart1_recv_msg_handler(USB_RxBuff[i]))
			{
				//写入队列
				Message msg;
				memset(&msg, 0, sizeof(msg));
				msg.flag = UART_FRAME_JS;
				msg.len = usart1_rx_sta & 0x3FFF ;
				memcpy(msg.buf, usart1_rx_buf, msg.len);

				osal_Enqueue(&uart_queue, msg);

				//清零结构体
				usart1_rx_sta = 0;
				memset(usart1_rx_buf, 0, sizeof(usart1_rx_buf));
			}
		}
	}
}

int App_Module_Process_USART_CMD(void)
{
	Message msg;
	if(osal_Dequeue(&uart_queue, &msg) == TRUE)
	{
		command_parser(msg.buf);
	}
}

/*
 *	功能:串口发送函数1
 *	形参:buf(发送数组)，len(发送数组长度)
 *
 */
int App_Module_Uart_Send(uint8_t *buf, uint16_t len)
{
	int ret = 0;
	if((sys_uart_dma_buf.uart_dma_index + len) < sizeof(sys_uart_dma_buf.uart_dma_tx_tmp))
	{
		/*赋值到缓存区*/
		memcpy(sys_uart_dma_buf.uart_dma_tx_tmp + sys_uart_dma_buf.uart_dma_index, buf, len);
		sys_uart_dma_buf.uart_dma_index += len;
	}
	else
	{
//		while(1);
	}

	if(sys_uart_dma_buf.uart_dma_report == true)
	{
		/*赋值到发送区*/
		memcpy(sys_uart_dma_buf.uart_dma_tx, sys_uart_dma_buf.uart_dma_tx_tmp, sys_uart_dma_buf.uart_dma_index);
//		_dbg_printf("usartsend\n");

		HalUsbWrite(sys_uart_dma_buf.uart_dma_tx, sys_uart_dma_buf.uart_dma_index);
		USART1_SendBuffer(sys_uart_dma_buf.uart_dma_tx, sys_uart_dma_buf.uart_dma_index, false);
		sys_uart_dma_buf.uart_dma_report = false;
		sys_uart_dma_buf.uart_dma_index = 0;
	}

	return ret;

//轮询
/*	int ret = 0;

	    // 拷贝到缓冲区
	    if((sys_uart_dma_buf.uart_dma_index + len) < sizeof(sys_uart_dma_buf.uart_dma_tx_tmp))
	    {
	        memcpy(sys_uart_dma_buf.uart_dma_tx_tmp + sys_uart_dma_buf.uart_dma_index, buf, len);
	        sys_uart_dma_buf.uart_dma_index += len;
	    }

	    // 不管标志如何，只要缓冲区有数据就发送
	    if(sys_uart_dma_buf.uart_dma_index > 0)
	    {
	        memcpy(sys_uart_dma_buf.uart_dma_tx, sys_uart_dma_buf.uart_dma_tx_tmp, sys_uart_dma_buf.uart_dma_index);

	        // 使用轮询模式发送（阻塞，直到发送完成）
	        USART1_SendBuffer(sys_uart_dma_buf.uart_dma_tx, sys_uart_dma_buf.uart_dma_index, true);  // true=轮询

	        sys_uart_dma_buf.uart_dma_index = 0;
	    }

	    return ret;

*/

}

/*
 *	功能:串口发送函数2
 *	形参:buf(发送数组)，len(发送数组长度)
 *
 */
void port_tx_msg(uint8_t *buf, uint16_t len)
{
//	for(uint16_t i = 0; i < len; i++)
//{
//    _dbg_printf("%02X ", buf[i]);
//}
//_dbg_printf("\r\n");

	App_Module_Uart_Send(buf, len);
}

static uint8_t get_Xor_CRC(uint8_t *bytes, int offset, int len) 
{
	uint8_t xor_crc = 0;
    int i;
    for (i = 0; i < len; i++) {
		xor_crc ^= bytes[offset + i];
    }
	    
    return xor_crc;
}  


int App_Module_format_conver_uint8(Msg_Hex_Output_t msg, uint8_t *buf)
{
	int index = 0;
	buf[index++] = msg.header;
	buf[index++] = msg.length;
	buf[index++] = msg.gerneal_para.sn;
	buf[index++] = LO_UINT16(msg.gerneal_para.Addr);
	buf[index++] = HI_UINT16(msg.gerneal_para.Addr);	
		
	buf[index++] = BREAK_UINT32(msg.gerneal_para.angle, 0);
	buf[index++] = BREAK_UINT32(msg.gerneal_para.angle, 1);
	buf[index++] = BREAK_UINT32(msg.gerneal_para.angle, 2);
	buf[index++] = BREAK_UINT32(msg.gerneal_para.angle, 3);	

	buf[index++] = BREAK_UINT32(msg.gerneal_para.distance, 0);
	buf[index++] = BREAK_UINT32(msg.gerneal_para.distance, 1);
	buf[index++] = BREAK_UINT32(msg.gerneal_para.distance, 2);
	buf[index++] = BREAK_UINT32(msg.gerneal_para.distance, 3);
	
	buf[index++] = LO_UINT16(msg.gerneal_para.user_cmd);
	buf[index++] = HI_UINT16(msg.gerneal_para.user_cmd);		

	buf[index++] = BREAK_UINT32(*(int *)&msg.gerneal_para.F_Path_Power_Level, 0);
	buf[index++] = BREAK_UINT32(*(int *)&msg.gerneal_para.F_Path_Power_Level, 1);
	buf[index++] = BREAK_UINT32(*(int *)&msg.gerneal_para.F_Path_Power_Level, 2);
	buf[index++] = BREAK_UINT32(*(int *)&msg.gerneal_para.F_Path_Power_Level, 3);		

	buf[index++] = BREAK_UINT32(*(int *)&msg.gerneal_para.RX_Level, 0);
	buf[index++] = BREAK_UINT32(*(int *)&msg.gerneal_para.RX_Level, 1);
	buf[index++] = BREAK_UINT32(*(int *)&msg.gerneal_para.RX_Level, 2);
	buf[index++] = BREAK_UINT32(*(int *)&msg.gerneal_para.RX_Level, 3);		

	buf[index++] = LO_UINT16(msg.gerneal_para.Acc_X);
	buf[index++] = HI_UINT16(msg.gerneal_para.Acc_X);

	buf[index++] = LO_UINT16(msg.gerneal_para.Acc_Y);
	buf[index++] = HI_UINT16(msg.gerneal_para.Acc_Y);		

	buf[index++] = LO_UINT16(msg.gerneal_para.Acc_Z);
	buf[index++] = HI_UINT16(msg.gerneal_para.Acc_Z);		

	buf[index++] = get_Xor_CRC(buf, 2, msg.length);
	buf[index++] = msg.footer;

	return (msg.length + 4);
}


uint8_t usart1_recv_msg_handler(uint8_t ch)
{
	//_dbg_printf("usart1:%02X", ch);
	uint8_t ret = FALSE;
	if((usart1_rx_sta & 0x8000)==0)//接收未完成
	{
		if(usart1_rx_sta & 0x4000)//接收到了0x0d
		{
			if(ch!=0x0a)
				usart1_rx_sta=0;//接收错误,重新开始
			else{ 
				usart1_rx_sta|=0x8000;//接收完成了
				ret = TRUE;
			}
		}
		else 									//还没收到0X0D
		{	
			if(ch==0x0d)
				usart1_rx_sta|=0x4000;
			else{
				usart1_rx_buf[ usart1_rx_sta & 0x3FFF] = ch ;
				usart1_rx_sta++;
				if(usart1_rx_sta > (USART1_RX_ISR_MAX_LEN-1) )
					usart1_rx_sta=0;//接收数据错误,重新开始接收
			}		 
		}
	} 
//	_dbg_printf("usart2");
	return ret;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//_dbg_printf("HAL_UART_RxCpltCallback\n");
	if(huart->Instance == USART1)//DMA通道5传输完成，即接收的数据在USART1_RX[]中
	{
        // 处理接收到的数据
        // 重新启动DMA接收
        HAL_UART_Receive_DMA(&huart1, (uint8_t*)&USART1_DMA_RX_BYTE, 1);

		static uint8_t temp_rx_byte = 0;  // 修复：添加初始值


		// 从UART数据寄存器读取接收到的字节
		temp_rx_byte = (uint8_t)(huart->Instance->DR);
		//_dbg_printf("recv %02X\n", temp_rx_byte);
		if(usart1_recv_msg_handler(temp_rx_byte))
		{
			//写入队列
			Message msg;
			memset(&msg, 0, sizeof(msg));
			msg.flag = UART_FRAME_JS;
			msg.len = usart1_rx_sta & 0x3FFF ;
			memcpy(msg.buf, usart1_rx_buf, msg.len);

			osal_Enqueue(&uart_queue, msg);
			//_dbg_printf("GET a data\n");
			//清零结构体
			usart1_rx_sta = 0;
			memset(usart1_rx_buf, 0, sizeof(usart1_rx_buf));
		}
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
	}
}

void HAL_DMA_XferCpltCallback(DMA_HandleTypeDef *hdma)
{
    if(hdma->Instance == DMA1_Channel4)
    {
        sys_uart_dma_buf.uart_dma_report = TRUE;
    }
}
