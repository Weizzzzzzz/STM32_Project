#include "systick.h"

/**
 * @brief  初始化SysTick定时器 (1ms中断).
 * @param  None
 * @retval None
 */
void Systick_Init(void)
{
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE; // 时钟源: AHB

    SysTick->CTRL |= SysTick_CTRL_TICKINT; // 中断: 使能

    SysTick->LOAD = 72000 - 1; // 重载值: (72MHz/1000Hz - 1) -> 1ms

    SysTick->CTRL |= SysTick_CTRL_ENABLE; // SysTick: 使能
}

uint16_t count = 0; // Systick中断计数
/**
 * @brief  SysTick中断服务函数.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
    count++;           // 中断计数自增
    if (count == 1000) // 计数达到1000 (1s)
    {
        count = 0;        // 计数清零
        LED_Toggle(LED1); // LED1状态翻转
    }
}
