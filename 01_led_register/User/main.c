#include "stm32f10x.h"

int main(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //  使能GPIOB时钟

	GPIOB->CRL |= GPIO_CRL_MODE1; //  将GPIOB的引脚1配置为输出模式
	GPIOB->CRL &= ~GPIO_CRL_CNF1; //  将GPIOB的引脚1配置为推挽输出模式

	GPIOB->ODR &= ~GPIO_ODR_ODR1; //  将GPIOB的引脚1置为低电平
	while (1)
		;
}
