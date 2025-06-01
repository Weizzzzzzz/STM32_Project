#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

// 定义LED1、LED2、LED3的引脚
#define LED1 GPIO_ODR_ODR5
#define LED2 GPIO_ODR_ODR0
#define LED3 GPIO_ODR_ODR1

// 初始化LED
void LED_Init(void);
// 点亮LED
void LED_On(uint32_t led);
// 熄灭LED
void LED_Off(uint32_t led);
// 切换LED状态
void LED_Toggle(uint32_t led);
// 点亮多个LED
void LED_On_All(uint32_t leds[],uint8_t size);
// 熄灭多个LED
void LED_Off_All(uint32_t leds[], uint8_t size);

#endif
