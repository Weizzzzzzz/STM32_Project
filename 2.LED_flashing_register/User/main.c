#include "stm32f10x.h"
#include "delay.h"

int main(void)
{
	// 开启时钟
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	// GPIO初始化
	GPIOA->CRL &= ~GPIO_CRL_CNF;
	GPIOA->CRL |= GPIO_CRL_MODE;

	uint16_t led_pins[] = {GPIO_ODR_ODR0, GPIO_ODR_ODR1, GPIO_ODR_ODR2, GPIO_ODR_ODR3,
						   GPIO_ODR_ODR4, GPIO_ODR_ODR5, GPIO_ODR_ODR6, GPIO_ODR_ODR7};

	while (1)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			// 关闭所有LED
			for (uint8_t j = 0; j < 8; j++)
			{
				GPIOA->ODR |= led_pins[j];
			}

			GPIOA->ODR &= ~led_pins[i];
			Delay_ms(500);
		}
	}
}
