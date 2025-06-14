#include "delay.h"
#include "tim3.h"

int main(void)
{
	TIM3_Init();

	TIM3_Start();

	uint8_t dutyCycle = 1;
	int8_t step = -1;

	// 无限循环
	while (1)
	{
		if ((dutyCycle <= 1) | (dutyCycle > 100))
		{
			step = -step;
		}
		dutyCycle += step;
		TIM3_SetDutyCycle(dutyCycle);
		Delay_ms(20);
	}
}
