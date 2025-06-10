#include "dma1.h"

/**
 * @brief  初始化DMA1通道4.
 * @param  None
 * @retval None
 */
void DMA1_Init(void)
{
    // --- DMA1时钟配置 ---
    RCC->AHBENR |= RCC_AHBENR_DMA1EN; // DMA1时钟: 使能

    // --- DMA1通道4配置 ---
    DMA1_Channel4->CCR |= DMA_CCR4_DIR; // DIR=1: 从存储器读

    DMA1_Channel4->CCR &= ~DMA_CCR4_MSIZE; // MSIZE=00: 存储器数据宽度8位
    DMA1_Channel4->CCR &= ~DMA_CCR4_PSIZE; // PSIZE=00: 外设数据宽度8位

    DMA1_Channel4->CCR |= DMA_CCR4_MINC;  // MINC=1: 存储器地址增量模式
    DMA1_Channel4->CCR &= ~DMA_CCR4_PINC; // PINC=0: 外设地址无增量模式

    DMA1_Channel4->CCR |= DMA_CCR4_TCIE; // TCIE=1: 传输完成中断使能

    USART1->CR3 |= USART_CR3_DMAT;

    // --- NVIC配置 ---
    NVIC_SetPriorityGrouping(3);             // 设置中断优先级分组
    NVIC_SetPriority(DMA1_Channel4_IRQn, 2); // DMA1通道1中断优先级
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);      // 使能DMA1通道1中断
}

/**
 * @brief  启动DMA1通道1传输.
 * @param  SrcAddr: 源地址
 * @param  DestAddr: 目标地址
 * @param  DataLen: 数据长度
 * @retval None
 */
void DMA1_Transmit(uint32_t SrcAddr, uint32_t DestAddr, uint16_t DataLen)
{
    // --- 传输配置 ---
    DMA1_Channel4->CMAR = SrcAddr;  // 源地址
    DMA1_Channel4->CPAR = DestAddr; // 目标地址
    DMA1_Channel4->CNDTR = DataLen; // 数据长度

    // --- 启动传输 ---
    DMA1_Channel4->CCR |= DMA_CCR4_EN; // EN=1: 使能DMA通道
}

/**
 * @brief  DMA1通道1中断服务函数.
 * @param  None
 * @retval None
 */
void DMA1_Channel4_IRQHandler(void)
{
    if (DMA1->ISR & DMA_ISR_TCIF4) // 判断是否为传输完成中断
    {
        DMA1->IFCR |= DMA_IFCR_CTCIF4; // 清除传输完成中断标志

        DMA1_Channel4->CCR &= ~DMA_CCR4_EN; // EN=0: 失能DMA通道
    }
}
