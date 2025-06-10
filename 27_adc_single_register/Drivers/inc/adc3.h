#ifndef __ADC3_H
#define __ADC3_H

#include "stm32f10x.h"

void ADC3_Init(void);

void ADC3_StartConvert(void);

double ADC3_ReturnVoltage(void);

#endif
