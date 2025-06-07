#ifndef __TIM3_H
#define __TIM3_H

#include "stm32f10x.h"


void TIM3_Init(void);

void TIM3_Start(void);

void TIM3_Stop(void);

void TIM3_SetCH2DutyCycle(uint8_t dutyCycle);

void TIM3_SetCH3DutyCycle(uint8_t dutyCycle);

#endif
