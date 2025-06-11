#include "delay.h"
#include "usart.h"
#include "spi.h"
#include "w25q128.h"
#include <string.h>

int main(void)
{
	Usart1_Init();
	W25Q128_Init();

	printf("Hello WEI!\n");

	uint8_t mid = 0;
	uint16_t did = 0;

	W25Q128_ReadID(&mid, &did);
	printf("mid = %#X, did = %#X\n", mid, did);

	// W25Q128_EraseSection(0, 0);

	// W25Q128_PageWrite(0, 0, 0, "12345678", 8);

	// uint8_t buffer[10] = {0};
	// W25Q128_Read(0, 0, 0, 0, buffer, 8);

	// printf("buffer = %s\n", buffer);

	uint8_t buffer[300] = {0};

	uint8_t str[260] = {0};
	uint8_t a2z[26] = {0};

	for (uint8_t i = 0; i < 26; i++)
	{
		a2z[i] = 'a' + i;
	}
	printf("a2z = %s\n", a2z);

	for (uint8_t i = 0; i < 10; i++)
	{
		strcat((char *)str, (char *)a2z);
	}
	uint16_t len = strlen((char *)str);
	printf("str = %s\nlen = %d\n", str, len);

	uint32_t addr = 0x32f680;
	uint8_t len1 = 0xff - (addr & 0xff) + 1;
	uint8_t len2 = len - len1;

	printf("len1 = %d\nlen2 = %d\n", len1, len2);

	W25Q128_EraseSection((addr >> 16) & 0xff, (addr >> 12) & 0x0f);

	W25Q128_RandmoWrite(addr, str, len1);
	W25Q128_PageWrite((addr >> 16) & 0xff, (addr >> 12) & 0x0f, ((addr >> 8) & 0x0f) + 1, str + len1, len2);

	W25Q128_RandmoRead(addr, buffer, len);

	printf("buffer = %s\n", buffer);

	while (1)
	{
	}
}
