#ifndef __W25Q128_H
#define __W25Q128_H

#include "spi.h"

void W25Q128_Init(void);

void W25Q128_ReadID(uint8_t *mid, uint16_t *did);

void W25Q128_WriteEnable(void);

void W25Q128_WriteDisable(void);

void W25Q128_WaitNotBusy(void);

void W25Q128_EraseSection(uint8_t block, uint8_t sector);

void W25Q128_PageWrite(uint8_t block, uint8_t sector, uint8_t page, uint8_t *data, uint16_t len);

void W25Q128_Read(uint8_t block, uint8_t sector, uint8_t page,uint8_t InnerAddr, uint8_t *buffer, uint16_t len);

#endif
