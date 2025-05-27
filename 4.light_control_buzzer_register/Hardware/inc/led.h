#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

void LED_Init(void);
void LED_On(uint32_t led);
void LED_Off(uint32_t led);
void LED_Toggle(uint32_t led);

#endif
