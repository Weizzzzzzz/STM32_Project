#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"
#include "lightsensor.h"

int main(void)
{
	Buzzer_Init();
	LightSensor_Init();

	while (1)
	{
		// Buzzer_On(GPIO_ODR_ODR12);
		// Delay_ms(500);
		// Buzzer_Off(GPIO_ODR_ODR12);
		// Delay_ms(500);
		if (LightSensor_Get() == 1)
		{
			Buzzer_On(GPIO_ODR_ODR12);
		}
		else
		{
			Buzzer_Off(GPIO_ODR_ODR12);
		}
	}
}
