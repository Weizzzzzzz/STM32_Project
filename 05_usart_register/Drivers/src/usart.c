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
    USART1->DR = ch; // 写入发送数据寄存器
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
 * 简    介：接收单个字符
 * 参    数：无
 * 返 回 值：接收到的字节
 * 功能描述：等待接收缓冲区非空标志，读取数据
 */
uint8_t Usart1_ReceiveChar(void)
{
    // 等待接收缓冲区非空
    while ((USART1->SR & USART_SR_RXNE) == 0)
    {
        if (USART1->SR & USART_SR_IDLE)
        {
            return 0;         // 返回空字符
        }
    }
    return USART1->DR; // 读取接收数据寄存器
}

/**
 * 简    介：接收字符串（空闲帧触发）
 * 参    数：
 *   buffer - 接收缓冲区指针
 *   len    - 实际接收长度指针
 * 返 回 值：无
 * 功能描述：
 * 1. 持续接收直到检测到空闲帧
 * 2. 将接收到的数据存储到缓冲区
 * 3. 返回实际接收长度（不包含空闲帧）
 * 限制说明：
 * - 最大接收长度为255字节（受限于uint8_t类型）
 * - 未实现缓冲区大小检查
 */
void Usart1_ReceiveString(uint8_t buffer[], uint8_t *len)
{
    uint8_t i = 0;
    uint8_t ch;

    // 等待空闲帧
    while ((USART1->SR & USART_SR_IDLE) == 0)
    {
        ch = Usart1_ReceiveChar(); // 接收单个字符
        if (ch != 0)               // 仅存储有效数据
        {
            buffer[i++] = ch;
        }
    }

    // 清除IDLE标志（先读SR再读DR）
    USART1->SR; // 读取状态寄存器
    USART1->DR; // 读取数据寄存器

    *len = i; // 保存实际接收长度
}

// /**
//  * 简    介：接收字符串（空闲中断模式）
//  * 参    数：buffer - 接收缓冲区，len - 实际接收长度
//  * 返 回 值：无
//  * 功能描述：持续接收直到检测到空闲帧
//  */
// void Usart1_ReceiveString(uint8_t buffer[], uint8_t *len)
// {
//     uint8_t i = 0;

//     while (1)
//     {
//         // 等待接收缓冲区非空
//         while ((USART1->SR & USART_SR_RXNE) == 0)
//         {
//             // 检测到空闲帧时返回
//             if (USART1->SR & USART_SR_IDLE)
//             {
//                 *len = i; // 保存接收长度
//                 return;
//             }
//         }
//         buffer[i] = USART1->DR; // 读取接收到的数据
//         i++;
//     }
// }
