#include "stm32f10x.h"
#include "delay.h"

int main(void)
{
	// 开启时钟
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	// GPIO初始化
	GPIOC->CRH &= ~GPIO_CRH_CNF13;
	GPIOC->CRH |= GPIO_CRH_MODE13;

	while (1)
	{
		GPIOC->ODR &= ~GPIO_ODR_ODR13;	// 开
		Delay_ms(500);
		GPIOC->ODR |= GPIO_ODR_ODR13; // 关
		Delay_ms(500);
	}
}
