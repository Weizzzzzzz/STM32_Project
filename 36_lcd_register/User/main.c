#include "delay.h"
#include "usart.h"
#include "lcd.h"

int main(void)
{
	Usart1_Init();
	LCD_Init();

	printf("Hello WEI!\n");

	uint32_t id = LCD_ReadId();
	printf("id = %#x\n", id);

	LCD_ClearAll(WHITE);
	while (1)
	{
	}
}
