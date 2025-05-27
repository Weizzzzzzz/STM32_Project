#include "led.h"

// LED初始化函数：配置GPIOA的PA1和PA2为推挽输出模式
void LED_Init(void)
{
    // 开启 GPIOA 时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // 使能 GPIOA 的时钟（APB2 总线）

    // 配置 PA1 和 PA2 为推挽输出模式，50MHz
    GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_CNF2);  // 清除 CNF1 和 CNF2 位域（设置为 00 → 推挽输出）
    GPIOA->CRL |= (GPIO_CRL_MODE1 | GPIO_CRL_MODE2); // 设置 MODE1 和 MODE2 位域（输出模式，50MHz）

    // 初始关闭 LED
    LED_Off(GPIO_ODR_ODR1); // PA1 输出高电平（LED1 熄灭）
    LED_Off(GPIO_ODR_ODR2); // PA2 输出高电平（LED2 熄灭）
}

// 点亮 LED
void LED_On(uint32_t led)
{
    GPIOA->ODR &= ~led; // 清除 ODR 中的对应位（输出低电平 → LED 点亮）
}

// 熄灭 LED
void LED_Off(uint32_t led)
{
    GPIOA->ODR |= led; // 设置 ODR 中的对应位（输出高电平 → LED 熄灭）
}

// 切换 LED 状态（读取当前电平并翻转）
void LED_Toggle(uint32_t led)
{
    // 通过 IDR 读取当前 GPIO 状态（IDR 与 ODR 一致，适用于推挽输出模式）
    if ((GPIOA->IDR & led) == 0)
    {
        LED_Off(led); // 当前低电平 → 切换为高电平（熄灭）
    }
    else
    {
        LED_On(led); // 当前高电平 → 切换为低电平（点亮）
    }
}
