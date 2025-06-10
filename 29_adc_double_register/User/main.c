#include "delay.h"
#include "usart.h"
#include "adc3.h"

uint16_t data[2] = {0};

int main(void)
{
	// 初始化USART1通信接口
	Usart1_Init();
	ADC3_Init();
	ADC3_DMA_Init();

	printf("Hello World!\n");

	ADC3_DMA_StartConvert((uint32_t)data, 2);

	while (1)
	{
		printf("V_ls1 = %.2f, V_PF10 = %.2f\n", data[0] * 3.3 / 4096, data[1] * 3.3 / 4096);
		Delay_ms(1000);
	}
}
