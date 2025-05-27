#include "key.h"

// 按键扫描函数：返回按键编号（1 或 2），无按键时返回 0
uint8_t Key_GetNum(void)
{
    uint8_t keynum = 0; // 初始化为无按键

    // 检测 PB1 按键（Key1）
    if (HAL_GPIO_ReadPin(GPIOB, KEY1_Pin) == 0) // 检测到低电平（按键按下）
    {
        HAL_Delay(20); // 延时 20ms 去抖动
        while (HAL_GPIO_ReadPin(GPIOB, KEY1_Pin) == 0)
            ;          // 等待按键释放（阻塞式）
        HAL_Delay(20); // 二次去抖动
        keynum = 1;    // 有效按键，返回编号 1
    }

    // 检测 PB11 按键（Key2）
    if (HAL_GPIO_ReadPin(GPIOB, KEY2_Pin) == 0) // 检测到低电平（按键按下）
    {
        HAL_Delay(20); // 延时 20ms 去抖动
        while (HAL_GPIO_ReadPin(GPIOB, KEY2_Pin) == 0)
            ;          // 等待按键释放（阻塞式）
        HAL_Delay(20); // 二次去抖动
        keynum = 2;    // 有效按键，返回编号 2
    }

    return keynum; // 返回按键值（0:无按键, 1:Key1, 2:Key2）
}
