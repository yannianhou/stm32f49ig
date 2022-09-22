/**
  ******************************************************************************
  * @file    main.c 
  * @author  houyannian
  * @version V1.0
  * @date    2022-08-10
  * @brief   Main program body
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx.h"
//#include "stm32f4xx_conf.h"

#include <stdint.h>

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

void delay(volatile unsigned int count)
{
	for(; count != 0; count--);
}
  
#define GPIOH_BASE      0x40021C00
#define RCC_AHB1_BASE   0x40023800

#define GPIOH_MODER      *(unsigned int*)(GPIOH_BASE + 0x00)
#define GPIOH_IDR        *(unsigned int*)(GPIOH_BASE + 0X10)
#define GPIOH_ODR        *(unsigned int*)(GPIOH_BASE + 0X14)
#define GPIOH_OTYPER	 *(unsigned int*)(GPIOH_BASE + 0x04)
#define GPIOH_OSPEEDR	 *(unsigned int*)(GPIOH_BASE + 0x08)
#define GPIOH_PUPDR		 *(unsigned int*)(GPIOH_BASE + 0x0C)
#define GPIOH_BSRR		 *(unsigned int*)(GPIOH_BASE + 0x18)

#define RCC_AHB1RSTR     *(unsigned int*)(RCC_AHB1_BASE + 0X30)

	
int main(void)
{
	//使能GPIOH时钟
	RCC_AHB1RSTR &= ~(0X1<<7);	//复位
	RCC_AHB1RSTR |= (0X1<<7);	
	
	//配置管脚端口模式（输入、输出）	
	GPIOH_MODER &= ~(0X3 << (2*10));	
	GPIOH_MODER |= (0X1 << (2*10));
	
	//配置管脚输出类型（推挽、开漏），驱动能力不同
	GPIOH_OTYPER &= ~(0X1 << (1*10));
	GPIOH_OTYPER |= (0X1 << (1*10));
	
	//配置管脚输出速率，速率过高会涉及电磁兼容方面的问题，对速率没要求的话建议设置到最低速率
	GPIOH_OSPEEDR &= ~(0X3 << (2*10));
	GPIOH_OSPEEDR |= (0X0 << (2*10));

	//设置上下拉电阻
	GPIOH_PUPDR &= ~(0X3 << (2*10));
	GPIOH_PUPDR |= (0X1 << (2*10));	

	while (1)
	{
		GPIOH_ODR |= (0X1 << (1 * 10));
		delay(0XFFFFFF);
		GPIOH_ODR &= ~(0X1 << (1 * 10));
		delay(0XFFFFFF);
	}

    return 0;  
}

