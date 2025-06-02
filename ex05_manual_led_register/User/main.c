#include "delay.h"
#include "led.h"
#include "key.h"

FLOW_STATES flow_states = No_LED;

int main(void)
{
	// 初始化
	LED_Init();
	Key_Init();

	// 无限循环
	while (1)
	{
		// 根据状态机(flow_states)控制LED显示状态
		// 实现三色LED状态轮转效果
		switch (flow_states)
		{
		case L1:
			LED_On(LED1);  // 点亮LED1（状态L1指示）
			LED_Off(LED3); // 熄灭LED3（状态L1期间不显示）
			break;
		case L2:
			LED_On(LED2);  // 点亮LED2（状态L2指示）
			LED_Off(LED1); // 熄灭LED1（状态L2期间不显示）
			break;
		case L3:
			LED_On(LED3);  // 点亮LED3（状态L3指示）
			LED_Off(LED2); // 熄灭LED2（状态L3期间不显示）
			break;
		default:
			break; // 无效状态不执行任何操作
		}
	}
}
