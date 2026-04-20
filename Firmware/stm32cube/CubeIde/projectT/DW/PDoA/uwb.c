#include <twr_stdint.h>
#include "uwb.h"
#include "tim.h"
#include "spi.h"
#include "deca_device_api.h"
#include "stm32f1xx_hal.h"  // 根据实际芯片型号修改
#include "stm32f1xx_hal_gpio.h"
#include<stdint.h>
// 全局变量，用于存储系统运行时间(ms)

//volatile uint32_t time32_incr = 0; // 确保加上 volatile 修饰符
#define DW1000_RST_PIN GPIO_PIN_0
#define DW1000_RST_PORT GPIOA
#define DW3000_CS_LOW()    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define DW3000_CS_HIGH()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)


uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    uint8_t bitstatus = 0x00;

    if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET) {
        bitstatus = GPIO_PIN_SET;
    } else {
        bitstatus = GPIO_PIN_RESET;
    }
    return bitstatus;
}

/**
  * @brief  SysTick中断回调函数（非HAL库标准命名，需自行实现）
  * @note   此函数在SysTick中断中被调用，每1ms执行一次
  */


/******************************************
*               获取系统时钟，1ms读取1次
*******************************************/
unsigned long portGetTickCnt(void)
{
	return time32_incr;
}
/**
  * @brief  获取系统时钟（与portGetTickCnt相同，但名称不同）
  * @retval 当前滴答计数值
  */
unsigned long portGetTickCount(void)
{
    return time32_incr;
}
/******************************************
*               休眠函数1
*******************************************/
void sleep_ms(unsigned int time_ms)
{
    unsigned long start = portGetTickCount();
    // 处理计数器溢出情况
    while ((portGetTickCount() - start) < time_ms)
    {
        // 可以添加低功耗模式
        // __WFI(); // 等待中断，进入低功耗
    }
}

/******************************************
*               休眠函数2
*******************************************/
void Sleep(unsigned int time_ms)
{
	sleep_ms(time_ms);
}

void deca_usleep(unsigned int usec)
{
    // 根据CPU频率计算合适的循环次数
    // 假设系统时钟为72MHz，每个NOP大约需要1/72MHz ≈ 13.89ns
    // 因此每微秒大约需要72个NOP指令
    // 这里需要根据实际系统时钟调整系数

    unsigned int cycles_per_us = SystemCoreClock / 1000000; // 每微秒的循环次数
    unsigned int total_cycles = usec * cycles_per_us / 4; // 除以4是因为每次循环大约需要4个周期

    for(unsigned int i = 0; i < total_cycles; i++)
    {
        __NOP();
    }
}

/******************************************
*               重启UWB
*******************************************/
void reset_DWIC(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能DW1000复位引脚所在的GPIO时钟
    // 注意：需要根据实际硬件修改对应的GPIO时钟使能宏
    // 配置复位引脚为推挽输出模式
    GPIO_InitStruct.Pin = DW1000_RST_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;  // 无上下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;  // 高速模式，对应原50MHz
    HAL_GPIO_Init(DW1000_RST_PORT, &GPIO_InitStruct);

    // 拉低复位引脚
    HAL_GPIO_WritePin(DW1000_RST_PORT, DW1000_RST_PIN, GPIO_PIN_RESET);

    // 重新配置引脚为模拟输入模式（高阻态）
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(DW1000_RST_PORT, &GPIO_InitStruct);

    // 延时2ms
    Sleep(2);



}
/******************************************
*               设置SPI速率
*******************************************/
void SPI_ConfigFastRate(uint32_t scalingfactor)
{
    // 禁用SPI外设
    HAL_SPI_DeInit(&hspi1);
    hspi1.Instance = SPI1;
    // SPI参数配置
    hspi1.Init.Mode               = SPI_MODE_MASTER;                  // 主机模式
    hspi1.Init.Direction          = SPI_DIRECTION_2LINES;             // 双线全双工
    hspi1.Init.DataSize           = SPI_DATASIZE_8BIT;                // 8位数据帧
    hspi1.Init.CLKPolarity        = SPI_POLARITY_LOW;                 // 时钟极性低
    hspi1.Init.CLKPhase           = SPI_PHASE_1EDGE;                  // 第1个时钟沿采样
    hspi1.Init.NSS                = SPI_NSS_SOFT;                     // 软件控制NSS
    hspi1.Init.BaudRatePrescaler  = scalingfactor;                    // 波特率分频系数
    hspi1.Init.FirstBit           = SPI_FIRSTBIT_MSB;                 // 高位在前
    hspi1.Init.TIMode             = SPI_TIMODE_DISABLE;               // 禁用TI模式
    hspi1.Init.CRCCalculation     = SPI_CRCCALCULATION_DISABLE;       // 禁用CRC计算
    //hspi1.Init.CRCPolynomial      = 7;                                // CRC多项式(禁用时无效)
    //hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    // 初始化SPI外设
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        // 初始化失败处理，可以添加错误提示代码
        Error_Handler();
    }

}


/******************************************
*               设置SPI低速率 低于3MHz
*******************************************/
void port_set_dw_ic_spi_slowrate(void)
{
	SPI_ConfigFastRate(SPI_BAUDRATEPRESCALER_32);
}

/******************************************
*               设置SPI高速率 尽可能接近20MHz
*******************************************/
void port_set_dw_ic_spi_fastrate(void)
{
	SPI_ConfigFastRate(SPI_BAUDRATEPRESCALER_4);
}

/******************************************
*               仅使用CS引脚唤醒DW1000（慢）
*******************************************/
void wakeup_device_with_io(void)
{
    // 拉低CS引脚
    HAL_GPIO_WritePin(DW1000_CS_PORT, DW1000_CS_PIN, GPIO_PIN_RESET);
    Sleep(1);
    // 拉高CS引脚
    HAL_GPIO_WritePin(DW1000_CS_PORT, DW1000_CS_PIN, GPIO_PIN_SET);
    // 延时7ms
    Sleep(7);
}

/******************************************
*               休眠函数
*******************************************/
void deca_sleep(unsigned int time_ms)
{
	Sleep(time_ms);
}

int readfromspi_serial
(
		uint16_t headerLength, /*const*/ uint8_t *headerBuffer, uint16_t readlength, uint8_t *readBuffer
)
{

	int i=0;

    int  stat ;

    stat = decamutexon() ;

    	    DW3000_CS_LOW();
    	    // 发送命令并接收数据
    	  //  HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 6, 100);
    	    // 发送Header并忽略接收的数据
    	       if (headerLength > 0) {
    	           HAL_SPI_Transmit(&hspi1, headerBuffer, headerLength, HAL_MAX_DELAY);
    	       }
    	       // 接收数据（发送dummy字节0x00）
    	       if (readlength > 0) {
    	           HAL_SPI_Receive(&hspi1, readBuffer, readlength, HAL_MAX_DELAY);
    	       }

    	    DW3000_CS_HIGH();

} // end readfromspi()

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: writetospi()
 *
 * Low level abstract function to write to the SPI
 * Takes two separate byte buffers for write header and write data
 * returns 0 for success, or -1 for error
 */

int writetospi_serial
(
		uint16_t headerLength, const uint8_t *headerBuffer, uint16_t bodylength, const uint8_t *bodyBuffer
)
{

	int i=0;

    int  stat ;

    stat = decamutexon() ;

    DW3000_CS_LOW();
	 // 发送Header
    if (headerLength > 0) {
        HAL_SPI_Transmit(&hspi1, (uint8_t *)headerBuffer, headerLength, HAL_MAX_DELAY);
    }

    // 发送Body
    if (bodylength > 0) {
        HAL_SPI_Transmit(&hspi1, (uint8_t *)bodyBuffer, bodylength, HAL_MAX_DELAY);
    }
    DW3000_CS_HIGH();

    decamutexoff(stat) ;

    return 0;
} // end writetospi()

/******************************************
*               获取中断引脚状态
*******************************************/
ITStatus EXTI_GetITEnStatus(uint32_t EXTI_Line)
{
	ITStatus bitstatus = RESET;
	uint32_t enablestatus = 0;
	/* Check the parameters */
	assert_param(IS_GET_EXTI_LINE(EXTI_Line));

	enablestatus =  EXTI->IMR & EXTI_Line;
	if (enablestatus != (uint32_t)RESET)
	{
		bitstatus = SET;
	}
	else
	{
		bitstatus = RESET;
	}
	return bitstatus;
}
/**
 * 功能：dw1000中断回调函数
 *
 */
void process_deca_irq(void)
{
	while(port_CheckEXT_IRQ() != 0)
	{
		dwt_isr();
	} //while DW1000 IRQ line active
}
