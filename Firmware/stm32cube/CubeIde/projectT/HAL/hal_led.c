
#include <stdint.h>

#ifndef _WINT_T
#define _WINT_T
typedef uint32_t wint_t;
#endif
#include "hal_led.h"
#include "tim.h"

hal_led_t hal_led[HAL_LED_ALL] ={
	{
		.mode =HAL_LED_MODE_OFF,
		.period = 0
	},
	{
		.mode =HAL_LED_MODE_OFF,
		.period = 0
	},
	{
		.mode =HAL_LED_MODE_OFF,
		.period = 0
	},
	{
		.mode =HAL_LED_MODE_OFF,
		.period = 0
	}		

};	   
/***************************************************************************************************
 * @fn      HalLedInit
 *
 * @brief   Initialize LED Service
 *
 * @param   init - pointer to void that contains the initialized value
 *
 * @return  None
 ***************************************************************************************************/
void HalLedInit (void)
{	 GPIO_InitTypeDef GPIO_InitStruct = {0};  // 1. 必须先声明变量
    // 使用HAL库的时钟使能
    __HAL_RCC_GPIOA_CLK_ENABLE();
    // 配置GPIO
    GPIO_InitStruct.Pin = HAL_LED1_PIN | HAL_LED2_PIN | HAL_LED3_PIN | HAL_LED4_PIN;
       GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
       GPIO_InitStruct.Pull = GPIO_NOPULL;
       GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
       HAL_GPIO_Init(HAL_LED_PORT, &GPIO_InitStruct);
	HalLedSet (HAL_LED_ALL, HAL_LED_MODE_ON);
}


/***************************************************************************************************
 * @fn      HalLedSet
 *
 * @brief   Tun ON/OFF/TOGGLE given LEDs
 *
 * @param   led - bit mask value of leds to be turned ON/OFF/TOGGLE
 *          mode - BLINK, FLASH, TOGGLE, ON, OFF
 * @return  None
 ***************************************************************************************************/
void HalLedSet (HAL_LED_SN leds, HAL_LED_MODE mode)
{	
	
	switch(leds){
		case HAL_LED1:
				if(mode == HAL_LED_MODE_ON)
					GPIO_ResetBits(HAL_LED_PORT, HAL_LED1_PIN);						
				else if(mode == HAL_LED_MODE_OFF)
					GPIO_SetBits(HAL_LED_PORT, HAL_LED1_PIN);
				
			break;
		case HAL_LED2:
				if(mode == HAL_LED_MODE_ON)
					GPIO_ResetBits(HAL_LED_PORT, HAL_LED2_PIN);						
				else if(mode == HAL_LED_MODE_OFF)
					GPIO_SetBits(HAL_LED_PORT, HAL_LED2_PIN);	
				
			break;
		case HAL_LED3:
				if(mode == HAL_LED_MODE_ON)
					GPIO_ResetBits(HAL_LED_PORT, HAL_LED3_PIN);						
				else if(mode == HAL_LED_MODE_OFF)
					GPIO_SetBits(HAL_LED_PORT, HAL_LED3_PIN);		
				
			break;
		case HAL_LED4:
				if(mode == HAL_LED_MODE_ON)
					GPIO_ResetBits(HAL_LED_PORT, HAL_LED4_PIN);						
				else if(mode == HAL_LED_MODE_OFF)
					GPIO_SetBits(HAL_LED_PORT, HAL_LED4_PIN);			
				
			break;
		case HAL_LED_ALL:
				if(mode == HAL_LED_MODE_ON)
					GPIO_ResetBits(HAL_LED_PORT, HAL_LED1_PIN | HAL_LED2_PIN | HAL_LED3_PIN | HAL_LED4_PIN);						
				else if(mode == HAL_LED_MODE_OFF)						
					GPIO_SetBits(HAL_LED_PORT, HAL_LED1_PIN | HAL_LED2_PIN | HAL_LED3_PIN | HAL_LED4_PIN);		
				
			break;			

		default:
			break;
	}
}


int HalLed_Mode_Set(HAL_LED_SN led, HAL_LED_MODE mode, uint16_t period)
{		
	if(mode != HAL_LED_MODE_TOGGLE)
	{
		if(led == HAL_LED_ALL){
			for(int i = 0; i < HAL_LED_ALL; i++)
				hal_led[led].mode = mode;
		}
		else
			hal_led[led].mode = mode;

		HalLedSet(led, mode);	
	}
	else				//HAL_LED_MODE_TOGGLE
	{
		switch(led)
		{
			case HAL_LED1:
			case HAL_LED2:
			case HAL_LED3:
			case HAL_LED4:	
					hal_led[led].mode = HAL_LED_MODE_TOGGLE;
					hal_led[led].period = period;
				break;
			
			default:
				break;
		}
	}
}


/***************************************************************************************************
***************************************************************************************************/
