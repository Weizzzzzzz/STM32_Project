#include "led.h"

// 初始化LED
void LED_Init(void)
{
    // 使能GPIOB时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // 设置PB5为推挽输出模式
    GPIOB->CRL |= GPIO_CRL_MODE5;
    GPIOB->CRL &= ~GPIO_CRL_CNF5;

    // 设置PB0为推挽输出模式
    GPIOB->CRL |= GPIO_CRL_MODE0;
    GPIOB->CRL &= ~GPIO_CRL_CNF0;

    // 设置PB1为推挽输出模式
    GPIOB->CRL |= GPIO_CRL_MODE1;
    GPIOB->CRL &= ~GPIO_CRL_CNF1;

    // 关闭LED1、LED2、LED3
    LED_Off(LED1);
    LED_Off(LED2);
    LED_Off(LED3);
}

// 点亮LED
void LED_On(uint32_t led)
{
    GPIOB->ODR &= ~led;
}

// 熄灭LED
void LED_Off(uint32_t led)
{
    GPIOB->ODR |= led;
}

// 切换LED状态
void LED_Toggle(uint32_t led)
{
    if ((GPIOB->IDR & led) == 0)
    {
        LED_Off(led);
    }
    else
    {
        LED_On(led);
    }
}

// 点亮多个LED
void LED_On_All(uint32_t leds[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        LED_On(leds[i]);
    }
}
// 熄灭多个LED
void LED_Off_All(uint32_t leds[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        LED_Off(leds[i]);
    }
}
