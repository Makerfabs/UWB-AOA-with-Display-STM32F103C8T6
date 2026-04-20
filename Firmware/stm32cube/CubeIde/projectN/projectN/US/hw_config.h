/**
  ******************************************************************************
  * @file    hw_config.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Hardware Configuration & Setup
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H


#include "stm32f1xx_hal.h"   // 引入 HAL 库，以获得 FunctionalState、GPIO 类型等
#include <stdint.h>           // 可选，但 HAL 库已包含


#define USART_RX_DATA_SIZE   2048
/* Exported functions ------------------------------------------------------- */
void Set_System(void);
void USB_Cable_Config (FunctionalState NewState);
void USART_Config_Default(void);
//bool USART_Config(void);
void USB_To_USART_Send_Data(uint8_t* data_buffer, uint8_t Nb_bytes);
void USART_To_USB_Send_Data(void);
void Handle_USBAsynchXfer (void);
void Get_SerialNum(void);

void USB_Config(void);



uint32_t USB_RxRead(uint8_t *buffter, uint32_t buffterSize);
uint32_t USB_RxWrite(uint8_t *buffter, uint32_t writeLen);
uint32_t USB_TxRead(uint8_t *buffter, uint32_t buffterSize);
uint32_t USB_TxWrite(uint8_t *buffter, uint32_t writeLen);


/* External variables --------------------------------------------------------*/

#endif  /*__HW_CONFIG_H*/
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
