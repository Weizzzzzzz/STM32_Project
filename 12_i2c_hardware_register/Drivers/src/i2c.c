#include "i2c.h"

/**
 * @brief  初始化I2C1外设.
 * @param  None
 * @retval None
 */
void I2C_Init(void)
{
    // --- 时钟使能 ---
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // GPIOB时钟: 使能
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // I2C1时钟: 使能

    // --- GPIO 配置 (PB6-SCL, PB7-SDA) ---
    GPIOB->CRL |= (GPIO_CRL_CNF6 | GPIO_CRL_MODE6 | GPIO_CRL_CNF7 | GPIO_CRL_MODE7); // PB6/7: 复用开漏, 50MHz

    // --- I2C1 配置 ---
    I2C1->CR2 |= 36 << 0; // I2C1 CR2: FREQ=36 (APB1频率36MHz)

    /*
    Thigh=CCR * Tcplk1
    ccr = Thigh/=Tcplk1 = 5us / (1/36)us = 180
    */
    I2C1->CCR |= 180 << 0; // I2C1 CCR: CCR=180 (SCL 100kHz @36MHz APB1)

    /*
    最大上升沿时间/时钟周期 + 1
    时钟频率是36MHz则 写入：1 /（1/36） + 1 = 37
    */
    I2C1->TRISE = (36 + 1); // I2C1 TRISE: TRISE=37 (SCL最大上升时间)

    I2C1->CR1 |= I2C_CR1_PE; // I2C1 CR1: PE=1 (I2C外设: 使能)
}

/**
 * @brief  产生I2C START条件.
 * @param  None
 * @retval OK: 成功, FAIL: 超时.
 */
uint8_t I2C_Start(void)
{
    I2C1->CR1 |= I2C_CR1_START; // I2C1 CR1: START=1 (产生START条件)

    uint16_t timeout = 0xffff;                       // 超时计数器
    while ((I2C1->SR1 & I2C_SR1_SB) == 0 && timeout) // 等待SB位置1 (START条件已发送)
    {
        timeout--;
    }

    return timeout ? OK : FAIL; // 返回操作结果
}

/**
 * @brief  产生I2C STOP条件.
 * @param  None
 * @retval None
 */
void I2C_Stop(void)
{
    I2C1->CR1 |= I2C_CR1_STOP; // I2C1 CR1: STOP=1 (产生STOP条件)
}

/**
 * @brief  使能I2C ACK. (接收数据后发送ACK)
 * @param  None
 * @retval None
 */
void I2C_ACK(void)
{
    I2C1->CR1 |= I2C_CR1_ACK; // I2C1 CR1: ACK=1 (ACK: 使能)
}

/**
 * @brief  禁止I2C ACK. (接收数据后发送NACK)
 * @param  None
 * @retval None
 */
void I2C_NACK(void)
{
    I2C1->CR1 &= ~I2C_CR1_ACK; // I2C1 CR1: ACK=0 (ACK: 禁止, 发送NACK)
}

/**
 * @brief  发送I2C地址.
 * @param  addr: 从设备地址 (含读写位).
 * @retval OK: 成功, FAIL: 超时.
 */
uint8_t I2C_SendAddr(uint8_t addr)
{
    I2C1->DR = addr; // I2C1 DR: 写入地址

    uint16_t timeout = 0xffff;                         // 超时计数器
    while ((I2C1->SR1 & I2C_SR1_ADDR) == 0 && timeout) // 等待ADDR位置1 (地址已发送, ACK已接收)
    {
        timeout--;
    }
    if (timeout) // 如果未超时
    {
        (void)I2C1->SR2; // 清除ADDR标志 (读SR1后读SR2)
    }

    return timeout ? OK : FAIL; // 返回操作结果
}

/**
 * @brief  发送一字节数据.
 * @param  byte: 待发送数据.
 * @retval OK: 成功, FAIL: 超时.
 */
uint8_t I2C_SendByte(uint8_t byte)
{
    uint16_t timeout = 0xffff;                        // 超时计数器
    while ((I2C1->SR1 & I2C_SR1_TXE) == 0 && timeout) // 等待TXE位置1 (数据寄存器空)
    {
        timeout--;
    }

    I2C1->DR = byte; // I2C1 DR: 写入数据

    timeout = 0xffff;                                 // 重置超时计数器
    while ((I2C1->SR1 & I2C_SR1_BTF) == 0 && timeout) // 等待BTF位置1 (字节传输完成)
    {
        timeout--;
    }

    return timeout ? OK : FAIL; // 返回操作结果
}

/**
 * @brief  读取一字节数据.
 * @param  None
 * @retval 收到的数据字节; 超时则返回0.
 */
uint8_t I2C_ReadByte(void)
{
    uint16_t timeout = 0xffff;                         // 超时计数器
    while ((I2C1->SR1 & I2C_SR1_RXNE) == 0 && timeout) // 等待RXNE位置1 (数据寄存器非空)
    {
        timeout--;
    }

    uint8_t data = timeout ? I2C1->DR : 0; // 读取数据 (超时则为0)

    return data; // 返回数据
}
