#include "delay.h"
#include "usart.h"
#include "dma1.h"

uint8_t scr[4] = {'a', 'b', 'c', 'd'};

int main(void)
{
	// 初始化USART1通信接口
	Usart1_Init();
	DMA1_Init();
	
	printf("Hello World!\n");
	Delay_ms(1);

	DMA1_Transmit((uint32_t)scr, (uint32_t)&(USART1->DR), 4);

	// 无限循环
	while (1)
	{
	}
}
