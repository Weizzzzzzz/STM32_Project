#include "key.h"

// 初始化按键
void Key_Init(void)
{
    // 使能GPIOA时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    // 使能AFIO时钟
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // 配置GPIOA的引脚0为输入模式
    GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
    // 配置GPIOA的引脚0为浮空输入
    GPIOA->CRL |= GPIO_CRL_CNF0_1;
    // 关闭GPIOA的引脚0的输出
    GPIOA->ODR &= ~GPIO_ODR_ODR0;


    // 将GPIOC的CRH寄存器的第0位清零，即关闭GPIOC的第0位
    GPIOC->CRH &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);

    // 将GPIOC的CRH寄存器的第0位设置为1，即配置GPIOC的第0位为复用功能
    GPIOC->CRH |= GPIO_CRL_CNF0_1;

    // 将GPIOC的ODR寄存器的第0位清零，即关闭GPIOC的第0位
    GPIOC->ODR &= ~GPIO_ODR_ODR0;


    // 将AFIO的EXTICR[0]寄存器的第0位设置为1，即配置外部中断线0为PA
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;
    // 将AFIO的EXTICR[4]寄存器的第13位设置为1，即配置外部中断线13为PC
    AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI13_PC;

    // 使能EXTI线0的中断
    EXTI->IMR |= EXTI_IMR_MR0;
    // 使能EXTI线0的上升沿触发
    EXTI->RTSR |= EXTI_RTSR_TR0;

    // 使能外部中断线13
    EXTI->IMR |= EXTI_IMR_MR13;

    // 设置外部中断线13为上升沿触发
    EXTI->RTSR |= EXTI_RTSR_TR13;

    // 设置NVIC优先级分组为3
    NVIC_SetPriorityGrouping(3);

    // 设置EXTI0中断优先级为3
    NVIC_SetPriority(EXTI0_IRQn, 3);
    // 设置EXTI15_10中断优先级为3
    NVIC_SetPriority(EXTI15_10_IRQn, 3);

    // 使能EXTI0中断
    NVIC_EnableIRQ(EXTI0_IRQn);
    // 使能EXTI15_10中断
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

// 中断处理函数，当EXTI0引脚产生中断时调用
void EXTI0_IRQHandler(void)
{
    // 清除外部中断线0的挂起位
    EXTI->PR |= EXTI_PR_PR0;

    // 延时15ms
    Delay_ms(15);
    // 如果GPIOA的输入数据寄存器IDR的第0位为1，则切换LED1的状态
    if ((GPIOA->IDR & GPIO_IDR_IDR0) != 0)
    {
        // 切换LED1的状态
        LED_Toggle(LED1);
    }
}

// 中断处理函数，当EXTI15_10引脚产生中断时调用
void EXTI15_10_IRQHandler(void)
{
    // 清除外部中断线0的挂起位
    EXTI->PR |= EXTI_PR_PR13;

    // 延时15ms
    Delay_ms(15);
    // 如果PC13引脚的电平为高
    if ((GPIOC->IDR & GPIO_IDR_IDR13) != 0)
    {
        // 切换LED1的状态
        LED_Toggle(LED2);
    }
}
