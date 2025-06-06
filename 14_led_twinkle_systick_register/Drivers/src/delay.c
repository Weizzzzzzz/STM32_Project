#include "delay.h"

// 延时函数，延时us微秒
void Delay_us(uint16_t us)
{
    // 设置SysTick的加载值为72 * us
    SysTick->LOAD = 72 * us;

    // 将SysTick的当前值清零
    SysTick->VAL = 0;

    // 启动SysTick计数器
    SysTick->CTRL = 0x5;

    // 等待计数器溢出
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG))
        ;

    // 关闭SysTick计数器
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE;
}

void Delay_ms(uint16_t ms)
{
    while (ms--)
    {
        Delay_us(1000);
    }
}

void Delay_s(uint16_t s)
{
    while (s--)
    {
        Delay_ms(1000);
    }
}
