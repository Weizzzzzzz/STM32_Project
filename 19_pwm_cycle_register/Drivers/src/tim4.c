#include "tim4.h"

/**
 * @brief  初始化TIM4用于输入捕获.
 * @param  None
 * @retval None
 */
void TIM4_Init(void)
{
    // --- 时钟使能 ---
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // TIM4时钟: 使能
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // GPIOB时钟: 使能

    // --- PB6 (TIM4_CH1) 配置 ---
    GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6); // PB6: 清除CNF/MODE
    GPIOB->CRL |= GPIO_CRL_CNF6_0;                   // PB6: CNF=01 (浮空输入)

    // --- TIM4 时基配置 ---
    TIM4->PSC = 72 - 1; // TIM4预分频器: 72 (1MHz计数频率)
    TIM4->ARR = 65535;  // TIM4自动重载值: 65535 (最大计数)

    TIM4->CR1 &= ~TIM_CR1_DIR; // TIM4计数方向: 向上

    // --- TIM4_CH1 输入捕获配置 ---
    TIM4->CR2 |= TIM_CR2_TI1S; // TIM4_CH1/2/3异或输入到TI1

    TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;  // CC1: TI1作为输入
    TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_1; // CC1: TI1作为输入 (清除高位)
    TIM4->CCMR1 &= ~TIM_CCMR1_IC1F;   // CC1: 输入滤波器关闭
    TIM4->CCMR1 &= ~TIM_CCMR1_IC1PSC; // CC1: 输入预分频器关闭

    TIM4->CCER &= ~TIM_CCER_CC1P; // CC1: 上升沿触发
    TIM4->CCER |= TIM_CCER_CC1E;  // CC1: 捕获使能

    // --- TIM4 中断配置 ---
    TIM4->DIER |= TIM_DIER_CC1IE; // CC1中断: 使能

    NVIC_SetPriorityGrouping(3);    // NVIC优先级分组: 3
    NVIC_SetPriority(TIM4_IRQn, 3); // TIM4中断优先级: 3
    NVIC_EnableIRQ(TIM4_IRQn);      // TIM4中断: 使能
}

/**
 * @brief  启动TIM4计数器.
 * @param  None
 * @retval None
 */
void TIM4_Start(void)
{
    TIM4->CR1 |= TIM_CR1_CEN; // TIM4计数器: 使能
}

/**
 * @brief  停止TIM4计数器.
 * @param  None
 * @retval None
 */
void TIM4_Stop(void)
{
    TIM4->CR1 &= ~TIM_CR1_CEN; // TIM4计数器: 禁止
}

/**
 * @brief  TIM4中断服务程序.
 * @param  None
 * @retval None
 */
void TIM4_IRQHandler(void)
{
    if (TIM4->SR & TIM_SR_CC1IF) // 检查CC1捕获中断标志
    {
        TIM4->SR &= ~TIM_SR_CC1IF; // 清除CC1捕获中断标志

        TIM4->CNT = 0; // TIM4计数器: 清零
    }
}

/**
 * @brief  获取PWM周期 (ms).
 * @param  None
 * @retval double PWM周期 (ms).
 */
double TIM4_GetPWMCycle(void)
{
    return TIM4->CCR1 / 1000.0; // 转换为毫秒
}

/**
 * @brief  获取PWM频率 (Hz).
 * @param  None
 * @retval double PWM频率 (Hz).
 */
double TIM4_GetPWMFceq(void)
{
    return 1000000.0 / TIM4->CCR1; // 计算频率
}

// uint8_t NumberOfRisingEdges = 0; // 上升沿计数
// uint16_t t = 0;                  // PWM周期计数值 (us)
// /**
//  * @brief  TIM4中断服务程序.
//  * @param  None
//  * @retval None
//  */
// void TIM4_IRQHandler(void)
// {
//     if (TIM4->SR & TIM_SR_CC1IF) // 检查CC1捕获中断标志
//     {
//         TIM4->SR &= ~TIM_SR_CC1IF;    // 清除CC1捕获中断标志
//         NumberOfRisingEdges++;        // 上升沿计数自增
//         if (NumberOfRisingEdges == 1) // 第一个上升沿
//         {
//             TIM4->CNT = 0; // TIM4计数器: 清零 (开始测量周期)
//         }
//         else if (NumberOfRisingEdges == 2) // 第二个上升沿
//         {
//             t = TIM4->CCR1;          // 读取捕获值 (周期)
//             NumberOfRisingEdges = 0; // 重置上升沿计数
//         }
//     }
// }

// /**
//  * @brief  获取PWM周期 (ms).
//  * @param  None
//  * @retval double PWM周期 (ms).
//  */
// double TIM4_GetPWMCycle(void)
// {
//     return t / 1000.0; // 转换为毫秒
// }

// /**
//  * @brief  获取PWM频率 (Hz).
//  * @param  None
//  * @retval double PWM频率 (Hz).
//  */
// double TIM4_GetPWMFceq(void)
// {
//     return 1000000.0 / t; // 计算频率
// }
