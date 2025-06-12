#ifndef __LCD_H
#define __LCD_H

#include "fsmc.h"
#include "font.h"

#define SRAM_BANK1_4 0x6C000000
#define LCD_ADDR_CMD (uint16_t *)SRAM_BANK1_4
#define LCD_ADDR_DATA (uint16_t *)(SRAM_BANK1_4 + (1 << 11))

#define LCD_W 240
#define LCD_H 320

/* 常见颜色 */
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40 // 棕色
#define BRRED 0XFC07 // 棕红色
#define GRAY 0X8430  // 灰色

void LCD_Init(void);
void LCD_Reset(void);
void LCD_BGOn(void);
void LCD_BGOff(void);
void LCD_RegConfig(void);
void LCD_WriteCmd(uint16_t cmd);
void LCD_WriteData(uint16_t data);
uint16_t LCD_ReadData(void);
uint32_t LCD_ReadId(void);

void LCD_SetArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void LCD_ClearAll(uint32_t color);

#endif