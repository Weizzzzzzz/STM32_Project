#include "buzzer.h"

/**
 * 蜂鸣器硬件初始化
 * 配置PB12为推挽输出模式
 */
void Buzzer_Init(void)
{
    // 开启GPIOB时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // 配置PB12为推挽输出模式
    GPIOB->CRH &= ~GPIO_CRH_CNF12; // 清除CNF12位（通用推挽）
    GPIOB->CRH |= GPIO_CRH_MODE12; // 设置MODE12为输出模式
}

/**
 * 蜂鸣器使能控制
 * @param buzzer 位掩码标识（需指定GPIO_Pin_x）
 */
void Buzzer_On(uint32_t buzzer)
{
    // 输出低电平驱动蜂鸣器
    GPIOB->ODR &= ~buzzer; // 清零对应输出位
}

/**
 * 蜂鸣器关闭控制
 * @param buzzer 位掩码标识（需指定GPIO_Pin_x）
 */
void Buzzer_Off(uint32_t buzzer)
{
    // 输出高电平关闭蜂鸣器
    GPIOB->ODR |= buzzer; // 置位对应输出位
}

/**
 * 蜂鸣器状态切换
 * @param buzzer 位掩码标识（需指定GPIO_Pin_x）
 */
void Buzzer_Toggle(uint32_t buzzer)
{
    // 检测当前引脚输入状态
    if ((GPIOB->IDR & GPIO_IDR_IDR12) == 0)
    {
        Buzzer_Off(buzzer); // 低电平→关闭
    }
    else
    {
        Buzzer_On(buzzer); // 高电平→开启
    }
}
