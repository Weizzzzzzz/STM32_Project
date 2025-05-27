#include "lightsensor.h"

/**
 * 光传感器硬件初始化
 * 配置GPIOB.13为上拉输入模式作为光敏检测接口
 */
void LightSensor_Init(void)
{
    // 开启GPIOB时钟并配置IO口参数
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // 配置PB13为上拉输入模式：
    // CNF13=10(上拉输入) MODE13=00(输入模式)
    GPIOB->CRH &= ~GPIO_CRH_CNF13;  // 清除CNF13位
    GPIOB->CRH |= GPIO_CRH_CNF13_1; // 设置CNF13_1位启用上拉
    GPIOB->CRH &= ~GPIO_CRH_MODE13; // 输入模式

    // 启用内部上拉电阻
    GPIOB->ODR |= GPIO_ODR_ODR13; // PB13输出高电平
}

/**
 * 获取光传感器状态
 * @return 返回当前光敏检测状态（0：有光，1：无光）
 */
uint8_t LightSensor_Get(void)
{
    // 通过读取IDR寄存器判断光敏状态：
    // 高电平(1)表示无光(上拉有效) 低电平(0)表示有光(光敏导通)
    return (GPIOB->IDR & GPIO_IDR_IDR13) ? 1 : 0;
}
