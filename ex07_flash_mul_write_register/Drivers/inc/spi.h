#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"

#define F_CS_HIGH (GPIOB->ODR |= GPIO_ODR_ODR12)
#define F_CS_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR12)

void SPI2_Init(void);

void SPI2_Start(void);

void SPI2_Stop(void);

uint8_t SPI2_SwapByte(uint8_t byte);

#endif
