/**
  ******************************************************************************
  * @file    hw_config.c
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


/* Includes ------------------------------------------------------------------*/

#include "stm32f1xx_hal.h"
#include "hw_config.h"
#include "Queue.h"

#define USB_COM_RX_BUF_SIZE   128   // 原128
#define USB_COM_TX_BUF_SIZE   256  // 原400

QUEUE8_t m_QueueUsbComRx;
uint8_t m_UsbComRxBuf[USB_COM_RX_BUF_SIZE];
QUEUE8_t m_QueueUsbComTx;
uint8_t m_UsbComTxBuf[USB_COM_TX_BUF_SIZE];
/* USB 上拉引脚定义（可根据需要改为宏） */
#define USB_DISCONNECT_PORT   GPIOB
#define USB_DISCONNECT_PIN    GPIO_PIN_1

void Set_System(void)
{
    /* 队列初始化 */
    QUEUE_PacketCreate(&m_QueueUsbComRx, m_UsbComRxBuf, sizeof(m_UsbComRxBuf));
    QUEUE_PacketCreate(&m_QueueUsbComTx, m_UsbComTxBuf, sizeof(m_UsbComTxBuf));

    /* 使能 GPIOB 时钟 */
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* 配置 PB1 为推挽输出 */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = USB_DISCONNECT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(USB_DISCONNECT_PORT, &GPIO_InitStruct);

    /* 初始状态：断开 USB（拉低 PB1） */
    HAL_GPIO_WritePin(USB_DISCONNECT_PORT, USB_DISCONNECT_PIN, GPIO_PIN_RESET);

    /* USB 唤醒中断（可选） */
    HAL_NVIC_SetPriority(USBWakeUp_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(USBWakeUp_IRQn);
}

void USB_Config(){

	Set_System();

}

void USB_Cable_Config(FunctionalState NewState)
{
    if (NewState == DISABLE)
        HAL_GPIO_WritePin(USB_DISCONNECT_PORT, USB_DISCONNECT_PIN, GPIO_PIN_RESET);
    else
        HAL_GPIO_WritePin(USB_DISCONNECT_PORT, USB_DISCONNECT_PIN, GPIO_PIN_SET);
}

/* 队列读写函数保持不变 */
uint32_t USB_RxRead(uint8_t *buffter, uint32_t buffterSize)
{
    return QUEUE_PacketOut(&m_QueueUsbComRx, buffter, buffterSize);
}

uint32_t USB_RxWrite(uint8_t *buffter, uint32_t writeLen)
{
    return QUEUE_PacketIn(&m_QueueUsbComRx, buffter, writeLen);
}

uint32_t USB_TxRead(uint8_t *buffter, uint32_t buffterSize)
{
    return QUEUE_PacketOut(&m_QueueUsbComTx, buffter, buffterSize);
}

uint32_t USB_TxWrite(uint8_t *buffter, uint32_t writeLen)
{
    return QUEUE_PacketIn(&m_QueueUsbComTx, buffter, writeLen);
}

