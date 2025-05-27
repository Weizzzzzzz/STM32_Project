#include "buzzer.h"

/**
 * 蜂鸣器使能控制
 * @param buzzer 位掩码标识（需指定GPIO_Pin_x）
 */
void Buzzer_On(uint32_t buzzer)
{
    // 输出低电平驱动蜂鸣器
    HAL_GPIO_WritePin(GPIOB, buzzer, GPIO_PIN_RESET); // 清零对应输出位
}

/**
 * 蜂鸣器关闭控制
 * @param buzzer 位掩码标识（需指定GPIO_Pin_x）
 */
void Buzzer_Off(uint32_t buzzer)
{
    // 输出高电平关闭蜂鸣器
    HAL_GPIO_WritePin(GPIOB, buzzer, GPIO_PIN_SET); // 置位对应输出位
}

/**
 * 蜂鸣器状态切换
 * @param buzzer 位掩码标识（需指定GPIO_Pin_x）
 */
void Buzzer_Toggle(uint32_t buzzer)
{
    // 检测当前引脚输入状态
    if (HAL_GPIO_ReadPin(GPIOB, buzzer) == 0)
    {
        Buzzer_Off(buzzer); // 低电平→关闭
    }
    else
    {
        Buzzer_On(buzzer); // 高电平→开启
    }
}
