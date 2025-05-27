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
		if (LightSensor_Get() == 1)
		{
			Buzzer_On(GPIO_Pin_12);
		}
		else
		{
			Buzzer_Off(GPIO_Pin_12);
		}
	}
}
