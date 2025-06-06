#include "delay.h"
#include "led.h"
#include "systick.h"
#include "tim6.h"
#include "usart.h"
#include <string.h>

uint8_t buffer[100] = {};		 // 接收缓冲区（最大容量100字节）
uint8_t len = 0;				 // 实际接收数据长度存储变量
uint8_t ReceptionIsComplete = 0; //	接收结束标志位

int main(void)
{
	Usart1_Init();
	Systick_Init();
	TIM6_Init();
	LED_Init();

	printf("Hello World!\n");

	// 无限循环
	while (1)
	{
	}
}
