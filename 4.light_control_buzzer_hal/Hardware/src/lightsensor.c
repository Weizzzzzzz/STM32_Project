#include "lightsensor.h"

/**
 * 获取光传感器状态
 * @return 返回当前光敏检测状态（0：有光，1：无光）
 */
uint8_t LightSensor_Get(void)
{
    // 通过读取IDR寄存器判断光敏状态：
    // 高电平(1)表示无光(上拉有效) 低电平(0)表示有光(光敏导通)
    return HAL_GPIO_ReadPin(GPIOB, LightSensor_Pin) ? 1 : 0;
}
