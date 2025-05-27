#include "led.h"

// 初始化LED（PA1/PA2推挽输出）
void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIOA时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2; // 选择PA1/PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       // 推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      // 输出速度50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 // 应用配置

    LED_Off(GPIO_Pin_1); // 初始关闭LED1
    LED_Off(GPIO_Pin_2); // 初始关闭LED2
}

// 点亮LED
void LED_On(uint32_t led)
{
    GPIO_ResetBits(GPIOA, led); // 清零对应引脚（输出低电平）
}

// 熄灭LED
void LED_Off(uint32_t led)
{
    GPIO_SetBits(GPIOA, led); // 置位对应引脚（输出高电平）
}

// 切换LED状态
void LED_Toggle(uint32_t led)
{
    if (GPIO_ReadOutputDataBit(GPIOA, led) == Bit_RESET)
    {
        LED_Off(led); // 低电平→熄灭
    }
    else
    {
        LED_On(led); // 高电平→点亮
    }
}