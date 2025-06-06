#include "delay.h"
#include "led.h"
#include "systick.h"
#include "tim3.h"
#include "tim6.h"
#include "usart.h"
#include <string.h>

uint8_t buffer[100] = {};		 // 接收缓冲区（最大容量100字节）
uint8_t len = 0;				 // 实际接收数据长度存储变量
uint8_t ReceptionIsComplete = 0; //	接收结束标志位

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
