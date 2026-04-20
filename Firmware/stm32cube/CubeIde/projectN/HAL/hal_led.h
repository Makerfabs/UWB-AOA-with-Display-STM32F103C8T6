#ifndef __HAL_LED_H
#define __HAL_LED_H

#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************************************
 * 																				INCLUDES
 **************************************************************************************************/
#include "stm32f1xx.h"
#include "string.h"
#include "OSAL_Comdef.h"
/*****************************************************************a*********************************
 * 																				CONSTANTS
 **************************************************************************************************/

//LED�˿ڶ���
// 修改宏定义使用HAL风格
#define HAL_LED_PORT GPIOA
#define HAL_LED1_PIN GPIO_PIN_1
#define HAL_LED2_PIN        NULL
#define HAL_LED3_PIN        NULL
#define HAL_LED4_PIN        NULL

#define HAL_LED_POWER		NULL

/***************************************************************************************************
 * 																				TYPEDEF
 ***************************************************************************************************/
typedef enum {
    HAL_LED1 = 0,			//RED
    HAL_LED2,				//GREEN
    HAL_LED3,
    HAL_LED4,
	HAL_LED_ALL
}HAL_LED_SN;

typedef enum {
	HAL_LED_MODE_ON = 0,
	HAL_LED_MODE_OFF = 1,
	HAL_LED_MODE_TOGGLE
}HAL_LED_MODE;

typedef struct{
	uint8_t mode;			//����״̬ 0��ON 	1��OFF 	2��TOGGLE
	uint16_t period;		//����
}hal_led_t;

/***************************************************************************************************
 * 																				GLOBAL VARIABLES
 ***************************************************************************************************/

extern hal_led_t hal_led[HAL_LED_ALL];


/**************************************************************************************************
 *                                        FUNCTIONS - API
 **************************************************************************************************/

/*
 * ʹ��LED
 */
extern void HalLedInit( void );

/*
 * ����LED ��/�ر�/�л�
 */
extern void HalLedSet (HAL_LED_SN leds, HAL_LED_MODE mode);


extern int HalLed_Mode_Set(HAL_LED_SN led, HAL_LED_MODE mode, uint16_t period);


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif
#endif
