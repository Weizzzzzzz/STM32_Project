#ifndef __AT24C02_H
#define __AT24C02_h

#include "i2c.h"

#define ADDR 0xA0

void AT24C02_Init(void);
void AT24C02_WriteByte(uint8_t InnerAddr, uint8_t byte);
uint8_t AT24C02_ReadByte(uint8_t InnerAddr);
void AT24C02_WriteBytes(uint8_t InnerAddr, uint8_t *bytes, uint8_t len);
void AT24C02_ReadBytes(uint8_t InnerAddr, uint8_t *bytes, uint8_t len);

#endif
