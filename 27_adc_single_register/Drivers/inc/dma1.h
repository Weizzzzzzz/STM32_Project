#ifndef __DMA1_H
#define __DMA1_H

#include "stm32f10x.h"

extern uint8_t DMATransmitFinished;

void DMA1_Init(void);

void DMA1_Transmit(uint32_t SrcAddr, uint32_t DestAddr, uint16_t DataLen);

#endif
