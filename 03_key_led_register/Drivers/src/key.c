#include "key.h"

// 初始化按键
void Key_Init(void)
{
    // 使能GPIOA时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    // 使能AFIO时钟
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // 配置GPIOA的引脚0为输入模式
    GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
    // 配置GPIOA的引脚0为浮空输入
    GPIOA->CRL |= GPIO_CRL_CNF0_1;
    // 关闭GPIOA的引脚0的输出
    GPIOA->ODR &= ~GPIO_ODR_ODR0;

    // 将GPIOA的引脚0映射到EXTI线0
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;

    // 使能EXTI线0的中断
    EXTI->IMR |= EXTI_IMR_MR0;
    // 使能EXTI线0的上升沿触发
    EXTI->RTSR |= EXTI_RTSR_TR0;

    // 设置NVIC优先级分组为3
    NVIC_SetPriorityGrouping(3);
    // 设置EXTI0中断的优先级为3
    NVIC_SetPriority(EXTI0_IRQn, 3);
    // 使能EXTI0中断
    NVIC_EnableIRQ(EXTI0_IRQn);
}

// 中断处理函数，当EXTI0引脚产生中断时调用
void EXTI0_IRQHandler(void)
{
    // 清除外部中断线0的挂起位
    EXTI->PR |= EXTI_PR_PR0;

    Delay_ms(15);
    if ((GPIOA->IDR & GPIO_IDR_IDR0) != 0)
    {
        // 切换LED1的状态
        LED_Toggle(LED1);
    }
}
