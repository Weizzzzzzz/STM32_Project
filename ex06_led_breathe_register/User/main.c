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
		if ((dutyCycle <= 0) | (dutyCycle >= 99))
		{
			step = -step;
		}
		dutyCycle += step;
		TIM3_SetCH2DutyCycle(dutyCycle);
		TIM3_SetCH3DutyCycle(100 - dutyCycle);
		Delay_ms(20);
	}
}
