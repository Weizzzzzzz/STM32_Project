#include "delay.h"
#include "usart.h"
#include "i2c.h"
#include "at24c02.h"
#include <string.h>

uint8_t buffer[100] = {0};		 // 接收缓冲区（最大容量100字节）
uint8_t len = 0;				 // 实际接收数据长度存储变量
uint8_t ReceptionIsComplete = 0; //	接收结束标志位

int main(void)
{
	Usart1_Init();
	AT24C02_Init();

	printf("Hello WEI!\n");

	AT24C02_WriteByte(0x00, 'a');
	AT24C02_WriteByte(0x01, 'b');
	AT24C02_WriteByte(0x02, 'c');
	uint8_t byte1 = AT24C02_ReadByte(0x00);
	uint8_t byte2 = AT24C02_ReadByte(0x01);
	uint8_t byte3 = AT24C02_ReadByte(0x02);
	printf("byte1 = %c\t byte2 = %c\t byte3 = %c\n", byte1, byte2, byte3);

	AT24C02_WriteBytes(0x00, "123456", 6);
	AT24C02_ReadBytes(0x00, buffer, 6);
	printf("bytes = %s\n", buffer);

	memset(buffer, 0, sizeof(buffer));
	AT24C02_WriteBytes(0x00, "1234567890abcde", 15);
	AT24C02_ReadBytes(0x00, buffer, 15);
	printf("bytes = %s\n", buffer);

	// 无限循环
	while (1)
	{
	}
}
