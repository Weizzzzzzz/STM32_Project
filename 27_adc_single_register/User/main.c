#include "delay.h"
#include "usart.h"
#include "adc3.h"

int main(void)
{
	// 初始化USART1通信接口
	Usart1_Init();
	printf("Hello World!\n");

	ADC3_Init();

	ADC3_StartConvert();
	
	while (1)
	{
		printf("V = %.2f\n", ADC3_ReturnVoltage());
		Delay_ms(1000);
	}
}
