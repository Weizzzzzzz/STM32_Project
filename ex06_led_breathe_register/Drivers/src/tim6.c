#include "tim6.h" // TIM6定时器相关头文件

/**
 * @brief  初始化TIM6定时器.
 * @param  None
 * @retval None
 */
void TIM6_Init(void)
{
    // --- TIM6 时钟使能 ---
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; // TIM6时钟: 使能

    // --- TIM6 定时器配置 ---
    TIM6->PSC = 7200 - 1;  // 预分频值: 7199 (72MHz / 7200 = 10kHz)
    TIM6->ARR = 10000 - 1; // 自动重装载值: 9999 (10kHz / 10000 = 1Hz, 即1s)

    // --- TIM6 中断配置 ---
    TIM6->DIER |= TIM_DIER_UIE; // 更新中断: 使能

    // --- NVIC 配置 ---
    NVIC_SetPriorityGrouping(3);    // 优先级分组: 3 (2位抢占, 2位响应)
    NVIC_SetPriority(TIM6_IRQn, 3); // TIM6中断优先级: 3
    NVIC_EnableIRQ(TIM6_IRQn);      // TIM6中断: 使能

    // --- TIM6 控制寄存器 ---
    TIM6->CR1 |= TIM_CR1_CEN; // 计数器: 使能
}

/**
 * @brief  TIM6中断服务程序.
 * @param  None
 * @retval None
 */
void TIM6_IRQHandler(void)
{
    TIM6->SR &= ~TIM_SR_UIF; // 清除更新中断标志位
    LED_Toggle(LED2);        // LED2状态翻转
}
