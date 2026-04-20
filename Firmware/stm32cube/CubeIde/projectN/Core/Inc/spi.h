/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "uwb.h"
/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN Private defines */
#define SPI_I2S_FLAG_RXNE               ((uint16_t)0x0001)

#define HAL_SPI_DECA


//DECAWAVE SPI端口定义
#define SPI1_PRESCALER		SPI_BaudRatePrescaler_8

#define DW1000_RCC			RCC_APB2Periph_GPIOB

//Decawave SPI端口A
#define DW1000_RST_PORT		GPIOA
//#define DW1000_RST_PIN		GPIO_Pin_0	//PA0
#define DW1000_CS_PORT		GPIOA
#define DW1000_CS_PIN		GPIO_PIN_4	//PA4
#define DW1000_WUP_PORT		GPIOB
#define DW1000_WUP_PIN   	GPIO_Pin_0	//PB0
#define DW1000_IRQ_PORT		GPIOB
#define DW1000_IRQ_PIN  	GPIO_PIN_5	//PB5

#define DW1000_RSTIRQ_PIN              GPIO_Pin_0
#define DW1000_RSTIRQ_PORT             GPIOA
#define DW1000_RSTIRQ_EXTI             EXTI_Line0
#define DW1000_RSTIRQ_EXTI_PORT        GPIO_PortSourceGPIOA
#define DW1000_RSTIRQ_EXTI_PIN         GPIO_PinSource0
#define DW1000_RSTIRQ_EXTI_IRQn        EXTI0_IRQn

#define DW1000_IRQ_EXTI                EXTI_Line5
#define DW1000_IRQ_EXTI_PORT           GPIO_PortSourceGPIOB
#define DW1000_IRQ_EXTI_PIN            GPIO_PinSource5
#define DW1000_IRQ_EXTI_IRQn           EXTI9_5_IRQn
#define DW1000_IRQ_EXTI_USEIRQ         ENABLE
#define DW1000_IRQ_EXTI_NOIRQ          DISABLE


//Decawave 公共端口
#define SPI1_PORT						GPIOA
#define SPI1_SCK_PIN					GPIO_Pin_5
#define SPI1_MISO_PIN					GPIO_Pin_6
#define SPI1_MOSI_PIN					GPIO_Pin_7

#define SPIx                        	SPI1
/* USER CODE END Private defines */

void MX_SPI1_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

