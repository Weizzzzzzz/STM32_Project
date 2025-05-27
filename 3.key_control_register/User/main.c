#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"

uint8_t keynum = 0;

int main(void)
{
	LED_Init();
	Key_Init();

	while (1)
	{
		keynum = Key_GetNum();

		if (keynum == 1)
		{
			LED_Toggle(GPIO_ODR_ODR1);
		}
		if (keynum == 2)
		{
			LED_Toggle(GPIO_ODR_ODR2);
		}
	}
}
