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

	W25Q128_EraseSection(0,0);

	W25Q128_PageWrite(0, 0, 0, "12345678", 8);

	uint8_t buffer[10] = {0};
	W25Q128_Read(0, 0, 0, 2, buffer, 8);

	printf("buffer = %s\n", buffer);
	while (1)
	{
	}
}
