/* USER CODE BEGIN Header */

#include <stdint.h>

#ifndef _WINT_T
#define _WINT_T
typedef uint32_t wint_t;
#endif
#include <stddef.h>
#include "usart.h";

#include "OSAL.h"           // 提供 Message 类型、osal_Enqueue 等
#include "Generic.h"        // 可能包含 UART_FRAME_JS 定义
#include "Generic_cmd.h"    // 提供 usart1_recv_msg_handler
#define HAL_USART1_DMA
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <stdarg.h>
#include "main.h"
#include "stdbool.h"
#include <stdio.h>

// 外部变量声明


#define DMA1_MEM_LEN 256 // 保存DMA每次数据传送的长度
char _dbg_TXBuff[DMA1_MEM_LEN];

char USART1_DMA_RX_BYTE;


/* USER CODE END 0 */

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel5;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA1_Channel4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

  /* USER CODE BEGIN USART1_MspInit 1 */
    /* 使能USART1中断 */
    HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);  // 设置优先级
    HAL_NVIC_EnableIRQ(USART1_IRQn);          // 使能中断
  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/*
 *******************************************************************************
 *   串口1发送函数
 *   使用HAL库实现，支持DMA和轮询两种模式
 *******************************************************************************
 */
uint16_t USART1_SendBuffer(const char* buffer, uint16_t length, int flag)
{
#ifdef HAL_USART1_DMA

    if(flag == true)
    {

        // 使用轮询模式发送
        HAL_UART_Transmit(&huart1, (uint8_t*)buffer, length, HAL_MAX_DELAY);

    }
    else
    {

        // 使用DMA模式发送
        if(HAL_UART_Transmit_DMA(&huart1, (uint8_t*)buffer, length) != HAL_OK)
        {
            return 0; // 发送失败
        }

    }
#else
    // 使用轮询模式发送

    HAL_UART_Transmit(&huart1, (uint8_t*)buffer, length, HAL_MAX_DELAY);
#endif
    return length;
}
/*
 *******************************************************************************
 *    DMA方式的_dbg_printf
 *******************************************************************************
 */
void _dbg_printf(const char *format,...)
{
#ifdef HW_RELEASE
#else
    uint32_t length;
    va_list args;

    va_start(args, format);
    length = vsnprintf((char*)_dbg_TXBuff, sizeof(_dbg_TXBuff), (char*)format, args);
    va_end(args);

    USART1_SendBuffer((const char*)_dbg_TXBuff, length, true);
#endif
}
/*
 *******************************************************************************
 *    USART1初始化
 *    使用CubeMX生成的配置，这里只需启动串口
 *******************************************************************************
 */


// DMA传输完成回调
void UART_TX_DMA_Complete(DMA_HandleTypeDef *hdma)
{
    if(hdma->Instance == DMA1_Channel4)
    {
        // 设置发送完成标志
        sys_uart_dma_buf.uart_dma_report = true;

        // 可选：添加调试信息
        // _dbg_printf("DMA TX Complete\r\n");
    }
}

/*
 *******************************************************************************
 *    USART1 DMA发送完成回调函数
 *******************************************************************************
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
    	 sys_uart_dma_buf.uart_dma_report = true;// 处理USART1 DMA发送完成


    }
}

void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}
///*
// *******************************************************************************
// *    USART1 DMA接收完成回调函数
// *******************************************************************************
// */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	//_dbg_printf("HAL_UART_RxCpltCallback\n");
//	if(huart->Instance == USART1)//DMA通道5传输完成，即接收的数据在USART1_RX[]中
//	{
//        // 处理接收到的数据
//        // 重新启动DMA接收
//        HAL_UART_Receive_DMA(&huart1, (uint8_t*)&USART1_DMA_RX_BYTE, 1);
//
//		static uint8_t temp_rx_byte = 0;  // 修复：添加初始值
//
//
//		// 从UART数据寄存器读取接收到的字节
//		temp_rx_byte = USART1_DMA_RX_BYTE;
////		_dbg_printf("recv %02X\n", temp_rx_byte);
//		if(usart1_recv_msg_handler(temp_rx_byte))
//		{
//			//写入队列
//			Message msg;
//			memset(&msg, 0, sizeof(msg));
//			msg.flag = UART_FRAME_JS;
//			msg.len = usart1_rx_sta & 0x3FFF ;
//			memcpy(msg.buf, usart1_rx_buf, msg.len);
//
//			osal_Enqueue(&uart_queue, msg);
//
//			//清零结构体
//			usart1_rx_sta = 0;
//			memset(usart1_rx_buf, 0, sizeof(usart1_rx_buf));
//		}
//	}
//
//}




/* USER CODE END 1 */
