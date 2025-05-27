#include "key.h"
#include "delay.h"

// 按键初始化函数
void Key_Init(void)
{
    // 开启 GPIOB 时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // 使能 GPIOB 的时钟（APB2 总线）

    // 配置 PB1 为上拉输入模式
    GPIOB->CRL |= GPIO_CRL_CNF1;    // 设置 CNF1[1:0] = 11
    GPIOB->CRL &= ~GPIO_CRL_CNF1_0; // 清除 CNF1_0（位 2）→ CNF1[1:0] = 10（上拉/下拉输入模式）
    GPIOB->CRL &= ~GPIO_CRL_MODE1;  // 清除 MODE1[1:0]（输入模式，00）
    GPIOB->ODR |= GPIO_ODR_ODR1;    // 设置 ODR1 为 1 → 启用内部上拉电阻（PB1 默认高电平）

    // 配置 PB11 为上拉输入模式
    GPIOB->CRH |= GPIO_CRH_CNF11;    // 设置 CNF11[1:0] = 11
    GPIOB->CRH &= ~GPIO_CRH_CNF11_0; // 清除 CNF11_0（位 8）→ CNF11[1:0] = 10（上拉/下拉输入模式）
    GPIOB->CRH &= ~GPIO_CRH_MODE11;  // 清除 MODE11[1:0]（输入模式，00）
    GPIOB->ODR |= GPIO_ODR_ODR11;    // 设置 ODR11 为 1 → 启用内部上拉电阻（PB11 默认高电平）
}

// 按键扫描函数：返回按键编号（1 或 2），无按键时返回 0
uint8_t Key_GetNum(void)
{
    uint8_t keynum = 0; // 初始化为无按键

    // 检测 PB1 按键（Key1）
    if ((GPIOB->IDR & GPIO_IDR_IDR1) == 0) // 检测到低电平（按键按下）
    {
        Delay_ms(20); // 延时 20ms 去抖动
        while ((GPIOB->IDR & GPIO_IDR_IDR1) == 0)
            ;         // 等待按键释放（阻塞式）
        Delay_ms(20); // 二次去抖动
        keynum = 1;   // 有效按键，返回编号 1
    }

    // 检测 PB11 按键（Key2）
    if ((GPIOB->IDR & GPIO_IDR_IDR11) == 0) // 检测到低电平（按键按下）
    {
        Delay_ms(20); // 延时 20ms 去抖动
        while ((GPIOB->IDR & GPIO_IDR_IDR11) == 0)
            ;         // 等待按键释放（阻塞式）
        Delay_ms(20); // 二次去抖动
        keynum = 2;   // 有效按键，返回编号 2
    }

    return keynum; // 返回按键值（0:无按键, 1:Key1, 2:Key2）
}
