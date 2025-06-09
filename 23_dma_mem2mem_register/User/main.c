#include "delay.h"
#include "usart.h"
#include "dma1.h"

const uint8_t scr[] = {10, 20, 30, 40};
uint8_t dest[4] = {0};

int main(void)
{
	// 初始化USART1通信接口
	Usart1_Init();
	printf("Hello World!\n");

	DMA1_Init();
	printf("scr = %p, dest = %p\n", scr, dest);

	DMA1_Transmit((uint32_t)scr, (uint32_t)dest, 4);

	// 无限循环
	while (1)
	{
		if (DMATransmitFinished == 1)
		{
			for (uint8_t i = 0; i < 4; i++)
			{
				printf("%d\t", dest[i]);
			}
			DMATransmitFinished = 0;
		}
	}
}
