#include "stm32f10x.h"
#include "delay.h"

int main(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	// GPIO初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	while (1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13); // 开
		Delay_ms(500);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);	// 关
		Delay_ms(500);
	}
}
