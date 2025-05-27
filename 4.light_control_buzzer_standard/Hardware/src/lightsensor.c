#include "lightsensor.h"

/**
 * 光传感器硬件初始化
 * 配置GPIOB.13为上拉输入模式作为光敏检测接口
 */
void LightSensor_Init(void)
{
    // 开启GPIOB时钟并配置IO口参数
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;        // 配置GPIOB.13
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     // 设置为上拉输入模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 配置IO驱动频率

    // 执行GPIO初始化配置
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * 获取光传感器状态
 * @return 返回当前光敏检测状态（0：有光，1：无光）
 */
uint8_t LightSensor_Get(void)
{
    // 读取GPIOB.13引脚电平状态
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}
