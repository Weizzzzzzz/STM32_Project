#include "delay.h"
#include "usart.h"
#include <string.h>

uint8_t buffer[100] = {}; // 接收缓冲区（最大容量100字节）
uint8_t len = 0;		  // 实际接收数据长度存储变量

int main(void)
{
	// 初始化USART1通信接口
	Usart1_Init();

	// 发送初始测试字符
	Usart1_SendChar('W');
	Usart1_SendChar('E');
	Usart1_SendChar('I');
	Usart1_SendChar('\n'); // 发送换行符

	// 无限循环
	while (1)
	{
		// // 定时发送心跳字符
		// Usart1_SendChar('X'); // 发送单字节
		// Delay_s(1);			  // 延时1秒

		// // 回环测试模式
		// uint8_t ch = Usart1_ReceiveChar(); // 接收单个字符
		// Usart1_SendChar(ch);			   // 即时回显接收到的字符

		// // 发送固定字符串
		// uint8_t *str = "Hello WEI\n";				 // 定义测试字符串
		// Usart1_SendString(str, strlen((char *)str)); // 发送带长度的字符串
		// Delay_s(1);									 // 保持发送间隔

		// 接收并转发字符串
		Usart1_ReceiveString(buffer, &len); // 接收数据到缓冲区
		Usart1_SendString(buffer, len);		// 转发接收的完整数据包
	}
}
