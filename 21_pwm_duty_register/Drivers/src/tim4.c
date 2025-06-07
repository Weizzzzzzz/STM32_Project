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
    TIM4->PSC = 72 - 1;        // TIM4预分频器: 72 (1MHz计数频率)
    TIM4->ARR = 65535;         // TIM4自动重载值: 65535 (最大计数)
    TIM4->CR1 &= ~TIM_CR1_DIR; // TIM4 CH1计数方向: 向上

    // --- 从模式控制器配置为 PWM 输入模式 ---
    TIM4->SMCR |= TIM_SMCR_TS_2; // TS = 101: 选择 TI1FP1 作为触发源
    TIM4->SMCR &= ~TIM_SMCR_TS_1;
    TIM4->SMCR |= TIM_SMCR_TS_0;

    TIM4->SMCR |= TIM_SMCR_SMS_2; // SMS = 100: 选择复位模式
    TIM4->SMCR &= ~TIM_SMCR_SMS_1;
    TIM4->SMCR &= ~TIM_SMCR_SMS_0;

    // --- TIM4_CH1 配置 (用于周期测量和触发) ---
    TIM4->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_IC1F | TIM_CCMR1_IC1PSC); // 清除配置
    TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;                                      // CC1S = 01: CH1 配置为输入, IC1 映射到 TI1
    // IC1F = 0000: 无滤波器 (如果需要可以配置)
    // IC1PSC = 00: 无预分频器 (每个有效边沿都捕获)

    TIM4->CCER &= ~TIM_CCER_CC1P; // CC1P = 0 (非反相: 上升沿触发)
    TIM4->CCER |= TIM_CCER_CC1E;  // 使能 CH1 输入捕获

    // --- TIM4_CH2 配置 (用于脉宽测量) ---
    TIM4->CCMR1 &= ~(TIM_CCMR1_CC2S | TIM_CCMR1_IC2F | TIM_CCMR1_IC2PSC); // 清除配置
    TIM4->CCMR1 |= TIM_CCMR1_CC2S_1;                                      // CC2S = 10: CH2 配置为输入, IC2 映射到 TI1 (关键点: 与CH1相同的输入源)
    // IC2F = 0000: 无滤波器
    // IC2PSC = 00: 无预分频器

    TIM4->CCER |= TIM_CCER_CC2P; // CC2P = 1 (反相: 下降沿触发)
    TIM4->CCER |= TIM_CCER_CC2E; // 使能 CH2 输入捕获
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
double TIM4_GetPWMFreq(void)
{
    return 1000000.0 / TIM4->CCR1; // 计算频率
}

/**
 * @brief  获取PWM占空比.
 * @param  None
 * @retval double PWM占空比.
 */
double TIM4_GetPWMDutyCycle(void)
{
    return TIM4->CCR2 * 1.0 / TIM4->CCR1;
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
