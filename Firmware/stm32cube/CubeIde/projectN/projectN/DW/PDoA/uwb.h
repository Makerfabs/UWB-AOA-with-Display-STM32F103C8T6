#ifndef UWB_H
#define UWB_H

#include "deca_types.h"
#include "spi.h"


#ifndef DEV_ID_ID
#define DEV_ID_ID                       (0x00)
#endif
#define DWT_DEVICE_ID               	(0xDECA0130)		//!< DW1000 MP device ID

#define DWT_SUCCESS                 	(0)
#define DWT_ERROR                   	(-1)

#define writetospi                  	writetospi_serial
#define readfromspi                		readfromspi_serial
#define port_GetEXT_IRQStatus()         EXTI_GetITEnStatus(DW1000_IRQ_EXTI_IRQn)

// DW1000 相关引脚宏
#ifndef DEV_ID_ID
#define DEV_ID_ID                       (0x00)
#endif

#ifndef DW1000_CS_PORT
//#define DW1000_CS_PORT                  DW1000_CS_GPIO_Port
#endif

#ifndef DW1000_CS_PIN
//#define DW1000_CS_PIN                   DW1000_CS_Pin
#endif

#ifndef DW1000_IRQ_PORT
//#define DW1000_IRQ_PORT                 DW1000_IRQ_GPIO_Port
#endif

#ifndef DW1000_IRQ_PIN
//#define DW1000_IRQ_PIN                  DW1000_IRQ_Pin
#endif

#ifndef DW1000_RSTIRQ_PORT
//#define DW1000_RSTIRQ_PORT              DW1000_RST_GPIO_Port
#endif

#ifndef DW1000_RSTIRQ_PIN
//#define DW1000_RSTIRQ_PIN               DW1000_RST_Pin
#endif

#ifndef DW1000_RSTIRQ_EXTI
//#define DW1000_RSTIRQ_EXTI              EXTI_LINE_5
#endif

#ifndef DW1000_RSTIRQ_EXTI_IRQn
//#define DW1000_RSTIRQ_EXTI_IRQn         EXTI_5_IRQn
#endif

// 外部中断线定义 (PB5 使用 EXTI Line 5)
#define DW1000_IRQ_EXTI_IRQn    EXTI9_5_IRQn

// 启用外部中断
#define port_EnableEXT_IRQ()     HAL_NVIC_EnableIRQ(DW1000_IRQ_EXTI_IRQn)

// 禁用外部中断
#define port_DisableEXT_IRQ()    HAL_NVIC_DisableIRQ(DW1000_IRQ_EXTI_IRQn)
#define port_CheckEXT_IRQ()    HAL_GPIO_ReadPin(DW1000_IRQ_PORT, DW1000_IRQ_PIN)



/*               定时器相关函数
*******************************************/
void TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
uint32_t portGetTickCnt(void);

/******************************************
*               延时相关函数
*******************************************/
void sleep_ms(unsigned int time_ms);
void Sleep(unsigned int time_ms);
void deca_usleep(unsigned int usec);
void deca_sleep(unsigned int time_ms);

/******************************************
*               UWB复位相关函数
*******************************************/
void reset_DWIC(void);

/******************************************
*               SPI速率配置函数
*******************************************/
void port_set_dw_ic_spi_slowrate(void);
void port_set_dw_ic_spi_fastrate(void);
void SPI_ConfigFastRate(uint32_t scalingfactor);

/******************************************
*               UWB唤醒函数
*******************************************/
void wakeup_device_with_io(void);

/******************************************
*               中断状态相关函数
*******************************************/
ITStatus EXTI_GetITEnStatus(uint32_t EXTI_Line);
void setup_DW1000RSTnIRQ(uint8_t enable);
void DW1000_RSTIRQ_EXTI_IRQHandler(void);
void HAL_EXTI_Callback(EXTI_HandleTypeDef *hexti);



/******************************************
*               中断处理函数
*******************************************/
void process_deca_irq(void);




#endif /* UWB_H */
