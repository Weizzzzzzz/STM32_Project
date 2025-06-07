#include "tim3.h"

/**
 * @brief  初始化TIM3用于PWM输出 (CH2/PB5, CH3/PB0).
 * @param  None
 * @retval None
 */
void TIM3_Init(void)
{
    // --- 时钟使能 ---
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // GPIOB 时钟: 使能
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // TIM3 时钟: 使能
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // AFIO 时钟: 使能 (用于重映射)

    // --- TIM3 重映射配置 ---
    AFIO->MAPR &= ~AFIO_MAPR_TIM3_REMAP;  // TIM3_REMAP: 清除位
    AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_1; // TIM3_REMAP: 部分重映射 (CH2->PB5, CH3->PB0)

    // --- GPIO 配置 (PB0: TIM3_CH3, PB5: TIM3_CH2) ---
    // PB0 (TIM3_CH3): AF推挽输出, 50MHz
    GPIOB->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_CNF0_1); // PB0: MODE=11 (50MHz), CNF=10 (AF推挽)
    GPIOB->CRL &= ~GPIO_CRL_CNF0_0;                   // PB0: CNF0_0 清零

    // PB5 (TIM3_CH2): AF推挽输出, 50MHz
    GPIOB->CRL |= (GPIO_CRL_MODE5 | GPIO_CRL_CNF5_1); // PB5: MODE=11 (50MHz), CNF=10 (AF推挽)
    GPIOB->CRL &= ~GPIO_CRL_CNF5_0;                   // PB5: CNF5_0 清零

    // --- TIM3 时基配置 ---
    TIM3->PSC = 7200 - 1; // 预分频器: 7199 (10kHz @ 72MHz PCLK1)
    TIM3->ARR = 100 - 1;  // 自动重载值: 99 (100Hz PWM频率)

    TIM3->CR1 &= ~TIM_CR1_DIR; // 计数方向: 向上计数

    // --- TIM3 PWM 通道2/3 配置 (50% 占空比) ---
    TIM3->CCR2 = 50; // CH2 比较值
    TIM3->CCR3 = 50; // CH3 比较值

    // 配置通道为输出
    TIM3->CCMR1 &= ~TIM_CCMR1_CC2S; // CC2S: CH2 配置为输出
    TIM3->CCMR2 &= ~TIM_CCMR2_CC3S; // CC3S: CH3 配置为输出

    // 配置PWM模式1 (向上计数时, CNT<CCR 时输出高电平)
    // CH2: PWM模式1
    TIM3->CCMR1 |= TIM_CCMR1_OC2M_2; // OC2M: 110 (PWM模式1)
    TIM3->CCMR1 |= TIM_CCMR1_OC2M_1;
    TIM3->CCMR1 &= ~TIM_CCMR1_OC2M_0;

    // CH3: PWM模式1
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_2; // OC3M: 110 (PWM模式1)
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_1;
    TIM3->CCMR2 &= ~TIM_CCMR2_OC3M_0;

    // --- TIM3 捕获/比较使能 ---
    TIM3->CCER |= TIM_CCER_CC2E; // CC2E: CH2 输出使能
    TIM3->CCER |= TIM_CCER_CC3E; // CC3E: CH3 输出使能

    // CH2/CH3: 输出极性配置为低电平有效 (PWM模式1下, CNT<CCR时输出低)
    TIM3->CCER |= TIM_CCER_CC2P; // CC2P: CH2 输出极性: 低电平有效
    TIM3->CCER |= TIM_CCER_CC3P; // CC3P: CH3 输出极性: 低电平有效
}

void TIM3_Start(void)
{
    TIM3->CR1 |= TIM_CR1_CEN;
}

void TIM3_Stop(void)
{
    TIM3->CR1 &= ~TIM_CR1_CEN;
}

void TIM3_SetCH2DutyCycle(uint8_t dutyCycle)
{
    TIM3->CCR2 = dutyCycle;
}

void TIM3_SetCH3DutyCycle(uint8_t dutyCycle)
{
    TIM3->CCR3 = dutyCycle;
}
