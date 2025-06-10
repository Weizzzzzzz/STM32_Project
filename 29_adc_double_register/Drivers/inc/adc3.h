#ifndef __ADC3_H
#define __ADC3_H

#include "stm32f10x.h"

void ADC3_Init(void);

void ADC3_DMA_Init(void);

void ADC3_DMA_StartConvert(uint32_t dsetAddr, uint8_t len);

#endif
