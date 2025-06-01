#include "delay.h"
#include "led.h"

int main(void)
{
	// 定义一个包含三个LED灯的数组
	uint32_t leds[] = {LED1, LED2, LED3};

	// 初始化LED灯
	LED_Init();

	// 无限循环
	while (1)
	{
		// 循环遍历数组中的每个LED灯
		for (uint8_t i = 0; i < 3; i++)
		{
			LED_Off_All(leds, 3); //  关闭所有LED灯
			LED_On(leds[i]);	  //  打开第i个LED灯
			Delay_ms(500);		  //  延时500毫秒
		}
		LED_Off_All(leds, 3); // 关闭所有LED灯
		Delay_ms(500);		  // 延时500毫秒
	}
}
