#include "delay.h"
#include "usart.h"
#include "fsmc.h"

int main(void)
{
	Usart1_Init();
	FSMC_Init();

	printf("Hello WEI!\n");

	uint8_t *p = (uint8_t*)0x68000001;
	*p = 10;

	printf("*p = %d, @%p\n", *p, p);
	while (1)
	{
	}
}
