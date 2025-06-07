#ifndef __TIM4_H
#define __TIM4_H

#include "stm32f10x.h"

void TIM4_Init(void);

void TIM4_Start(void);

void TIM4_Stop(void);

double TIM4_GetPWMCycle(void);

double TIM4_GetPWMFreq(void);

#endif
