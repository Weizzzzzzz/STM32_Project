#include "buzzer.h"

// 初始化buzzer（PB12推挽输出）
void Buzzer_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 开启GPIOB时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; // 选择PB12
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       // 推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      // 输出速度50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                 // 应用配置
}

// 开启buzzer
void Buzzer_On(uint32_t buzzer)
{
    GPIO_ResetBits(GPIOB, buzzer); // 清零对应引脚（输出低电平）
}

// 关闭buzzer
void Buzzer_Off(uint32_t buzzer)
{
    GPIO_SetBits(GPIOB, buzzer); // 置位对应引脚（输出高电平）
}

// 切换buzzer状态
void Buzzer_Toggle(uint32_t buzzer)
{
    if (GPIO_ReadOutputDataBit(GPIOB, buzzer) == Bit_RESET)
    {
        Buzzer_Off(buzzer); // 低电平→熄灭
    }
    else
    {
        Buzzer_On(buzzer); // 高电平→点亮
    }
}
