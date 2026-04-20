#include <stdint.h>

#ifndef _WINT_T
#define _WINT_T
typedef uint32_t wint_t;
#endif
#include "hal_flash.h"


void HalFlashInit(void)
{
}
/*******************************************************************************
* 函数名  : Write_Flash
* 描述    : 写STM32指定地址的Flash
* 输入    : buff：写入数据缓冲区，len：写入数据长度
* 输出    : 无
* 返回值  : uint8_t:写稿成功返回1，失败返回0
* 说明    : 无
*******************************************************************************/
uint8_t HalWrite_Flash(uint32_t Address, uint32_t *buff, uint8_t len)
{
	 HAL_StatusTypeDef status;
	    uint32_t PageError = 0;
	    FLASH_EraseInitTypeDef EraseInitStruct;
	    uint8_t k = 0;

	    // 1. 解锁Flash
	    HAL_FLASH_Unlock();

	    // 2. 清除Flash标志位
	    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
	    // 3. 配置擦除参数（STM32F103的Flash页大小为1KB）
	    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	    EraseInitStruct.Banks = FLASH_BANK_1;  // F103只有一个Bank

	    // 计算页地址（F103每页1KB = 0x400）
	    EraseInitStruct.PageAddress = Address;
	    EraseInitStruct.NbPages = 1;  // 擦除1页

	    // 4. 擦除Flash页
	    status = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
	    if (status != HAL_OK) {
	        HAL_FLASH_Lock();
	        return 0;
	    }

	    // 5. 写入数据
	    for (k = 0; k < len; k++) {
	        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, buff[k]);
	        if (status != HAL_OK) {
	            HAL_FLASH_Lock();
	            return 0;
	        }
	        Address += 4;  // 地址增加4字节（一个32位字）
	    }

	    // 6. 锁定Flash
	    HAL_FLASH_Lock();

	    return 1;
}

/*******************************************************************************
* 函数名  : Read_Flash
* 描述    : 读STM32指定地址的Flash
* 输入    : buff：读出数据缓冲区，len：读出数据长度
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void HalRead_Flash(uint32_t Address, uint32_t *buff, uint8_t len)
{
	uint8_t k;

	for(k=0; k<len; k++)
	{
		buff[k] =  (*(volatile uint32_t*) Address);//读指定地址的一个字的数据
		Address += 4;//地址偏移4个字节
	}
}


