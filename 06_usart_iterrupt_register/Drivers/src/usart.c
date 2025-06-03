#include "usart.h"

/**
 * 简    介：初始化USART1通信接口
 * 参    数：无
 * 返 回 值：无
 * 功能描述：
 * 1. 配置GPIO时钟和USART1时钟
 * 2. 设置PA9为推挽输出（TX）
 * 3. 设置PA10为浮空输入（RX）
 * 4. 配置波特率为115200（基于72MHz系统时钟）
 * 5. 配置8位数据位，1位停止位，无校验位
 */
void Usart1_Init(void)
{
    // 使能GPIOA时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    // 使能USART1时钟
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // PA9发送配置：推挽输出，最大速度50MHz
    GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9); // 清除原有配置
    GPIOA->CRH |= GPIO_CRH_MODE9;                    // 设置输出模式
    GPIOA->CRH |= GPIO_CRH_CNF9_1;                   // 复用推挽输出

    // PA10接收配置：浮空输入
    GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10); // 清除原有配置
    GPIOA->CRH |= GPIO_CRH_CNF10_0;                    // 浮空输入模式

    // 设置波特率寄存器（72MHz/16/115200≈39.0625 → 0x0271）
    USART1->BRR = 0x0271;

    // 配置USART控制寄存器
    USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE); // 使能USART，发送/接收
    USART1->CR1 &= ~USART_CR1_M;                                 // 8位数据位
    USART1->CR1 &= ~USART_CR1_PCE;                               // 无校验位
    USART1->CR2 &= ~USART_CR2_STOP;                              // 1位停止位

    // 使能接收缓冲区非空中断和空闲帧中断
    USART1->CR1 |= USART_CR1_RXNEIE; // 接收缓冲区非空中断使能
    USART1->CR1 |= USART_CR1_IDLEIE; // 空闲帧检测中断使能

    // 配置NVIC中断优先级
    NVIC_SetPriorityGrouping(3);      // 设置优先级分组为3（4位抢占优先级，0位子优先级）
    NVIC_SetPriority(USART1_IRQn, 3); // 设置USART1中断优先级为3
    NVIC_EnableIRQ(USART1_IRQn);      // 启用USART1全局中断
}

/**
 * 简    介：发送单个字符
 * 参    数：ch - 要发送的字节
 * 返 回 值：无
 * 功能描述：等待发送缓冲区空标志，发送数据
 */
void Usart1_SendChar(uint8_t ch)
{
    // 等待发送缓冲区为空
    while ((USART1->SR & USART_SR_TXE) == 0)
        ;
    USART1->DR = ch; // 写入发送数据寄存器,对USART_DR的写操作，将TXE清零
}

/**
 * 简    介：发送字符串
 * 参    数：srt - 字符串指针，len - 字符串长度
 * 返 回 值：无
 * 功能描述：循环发送每个字符
 */
void Usart1_SendString(uint8_t *srt, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        Usart1_SendChar(srt[i]); // 逐个发送字符
    }
}

/**
 * 简    介：USART1全局中断服务例程
 * 参    数：无
 * 返 回 值：无
 * 功能描述：
 * 1. 处理接收缓冲区非空事件(RXNE)
 * 2. 处理空闲线检测事件(IDLE)
 */
void USART1_IRQHandler(void)
{
    // 检查接收缓冲区非空中断标志
    if (USART1->SR & USART_SR_RXNE)
    {
        // 读取数据寄存器并存储到缓冲区
        buffer[len] = USART1->DR; // 数据读取清除RXNE标志
        len++;                    // 更新缓冲区索引
    }
    // 检测到空闲帧
    else if (USART1->SR & USART_SR_IDLE)
    {
        // 清除IDLE标志（先读SR再读DR）
        (void)USART1->SR; // 读取状态寄存器
        (void)USART1->DR; // 读取数据寄存器

        ReceptionIsComplete = 1; // 设置接收完成标志
    }
}