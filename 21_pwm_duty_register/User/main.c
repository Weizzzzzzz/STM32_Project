#include "delay.h"
#include "usart.h"
#include "tim3.h"
#include "tim4.h"

int main(void)
{
	Usart1_Init();
	TIM3_Init();
	TIM4_Init();

	printf("Hello WEI!\n");

	TIM3_Start();
	TIM4_Start();

	// 无限循环
	while (1)
	{
		printf("T = %.2fms, f = %.2fHz, duty = %.2f%%\n", TIM4_GetPWMCycle(), TIM4_GetPWMFceq(), TIM4_GetPWMDutyCycle() * 100);
		Delay_s(1);
	}
}
