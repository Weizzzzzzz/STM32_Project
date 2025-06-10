#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

// 延时函数，延时us微秒
void Delay_us(uint16_t us);
// 延时函数，延时ms毫秒
void Delay_ms(uint16_t ms);
// 延时函数，延时s秒
void Delay_s(uint16_t s);

#endif
