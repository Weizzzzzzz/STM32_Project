#include "delay.h"
#include "usart.h"
#include <string.h>

uint8_t buffer[100] = {};		 // 接收缓冲区（最大容量100字节）
uint8_t len = 0;				 // 实际接收数据长度存储变量
uint8_t ReceptionIsComplete = 0; //	接收结束标志位

int main(void)
{
	// 初始化USART1通信接口
	Usart1_Init();

	// 发送初始测试字符
	Usart1_SendString("WEI\n", 4);

	// 无限循环
	while (1)
	{
		// 检查接收完成标志
		if (ReceptionIsComplete)
		{
			ReceptionIsComplete = 0;		// 清除接收完成标志
			Usart1_SendString(buffer, len); // 回显接收到的数据
			len = 0;						// 重置接收长度计数器
		}
	}
}
