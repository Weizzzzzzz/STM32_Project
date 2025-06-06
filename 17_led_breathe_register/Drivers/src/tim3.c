#include "tim3.h"

void TIM3_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    GPIOB->CRL |= (GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
    GPIOB->CRL &= ~GPIO_CRL_CNF5_0;

    TIM3->PSC = 7200 - 1;
    TIM3->ARR = 100 - 1;

    TIM3->CR1 &= ~TIM_CR1_DIR;

    TIM3->CCR2 = 0;

    TIM3->CCMR1 &= ~TIM_CCMR1_CC2S;

    TIM3->CCMR1 |= TIM_CCMR1_OC2M_2;
    TIM3->CCMR1 |= TIM_CCMR1_OC2M_1;
    TIM3->CCMR1 &= ~TIM_CCMR1_OC2M_0;

    TIM3->CCER |= TIM_CCER_CC2E;

    TIM3->CCER |= TIM_CCER_CC2P;
}

void TIM3_Start(void)
{
    TIM3->CR1 |= TIM_CR1_CEN;
}

void TIM3_Stop(void)
{
    TIM3->CR1 &= ~TIM_CR1_CEN;
}

void TIM3_SetDutyCycle(uint8_t dutyCycle)
{
    TIM3->CCR2 = dutyCycle;
}
