#include "key.h"
#include "delay.h"

/**
 * @brief 按键硬件初始化函数
 * 配置GPIOB的Pin1和Pin11为上拉输入模式
 */
void Key_Init(void)
{
    // 开启GPIOB时钟（对应RCC_APB2ENR寄存器的IOPBEN位）
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // 定义GPIO配置结构体
    GPIO_InitTypeDef GPIO_InitStructure;

    // 配置按键引脚（PB1和PB11）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
    // 设置为上拉输入模式（默认高电平，按键按下接地）
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    // 输入模式下速度配置无效，保留默认值
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // 执行GPIO初始化
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief 按键扫描函数
 * @return 按键编号（0:无按键 1:PB1按键 2:PB11按键）
 * @note 若两个按键同时按下，优先返回PB11的按键值
 */
uint8_t Key_GetNum(void)
{
    uint8_t keynum = 0;
    // 检测PB1按键（按键1）
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
    {
        Delay_ms(20); // 按键消抖延时
        // 确认按键持续按下
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
            ;
        Delay_ms(20); // 按键释放延时
        keynum = 1;   // 返回按键编号1
    }

    // 检测PB11按键（按键2）
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
    {
        Delay_ms(20); // 按键消抖延时
        // 确认按键持续按下
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
            ;
        Delay_ms(20); // 按键释放延时
        keynum = 2;   // 返回按键编号2
    }

    return keynum; // 返回按键结果
}
