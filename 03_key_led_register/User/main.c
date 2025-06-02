#include "delay.h"
#include "led.h"
#include "key.h"

int main(void)
{
	// 初始化
	LED_Init();
	Key_Init();

	// 无限循环
	while (1)
	{
	}
}
