#include "at24c02.h"

/**
 * @brief  初始化AT24C02. (实际调用I2C初始化)
 * @param  None
 * @retval None
 */
void AT24C02_Init(void)
{
    I2C_Init(); // 初始化I2C总线
}

/**
 * @brief  向AT24C02写入一个字节.
 * @param  InnerAddr: EEPROM内部地址.
 * @param  byte: 待写入字节.
 * @retval None
 */
void AT24C02_WriteByte(uint8_t InnerAddr, uint8_t byte)
{
    I2C_Start(); // 产生START条件

    I2C_SendAddr(ADDR); // 发送设备地址 (写操作)

    I2C_SendByte(InnerAddr); // 发送内部地址

    I2C_SendByte(byte); // 发送数据字节

    I2C_Stop(); // 产生STOP条件

    Delay_ms(5); // 等待EEPROM写入完成 (典型值5ms)
}

/**
 * @brief  从AT24C02读取一个字节.
 * @param  InnerAddr: EEPROM内部地址.
 * @retval 读取到的字节.
 */
uint8_t AT24C02_ReadByte(uint8_t InnerAddr)
{
    I2C_Start(); // 产生START条件

    I2C_SendAddr(ADDR); // 发送设备地址 (写操作, 用于设置读取地址)

    I2C_SendByte(InnerAddr); // 发送内部地址

    I2C_Start(); // 产生重复START条件

    I2C_SendAddr(ADDR + 1); // 发送设备地址 (读操作)

    I2C_NACK(); // 配置NACK (读取最后一个字节后)

    I2C_Stop(); // 配置STOP (NACK后立即发送)

    uint8_t byte = I2C_ReadByte(); // 读取数据字节

    return byte; // 返回数据
}

/**
 * @brief  向AT24C02写入多个字节 (页写).
 * @param  InnerAddr: EEPROM内部起始地址.
 * @param  bytes: 待写入字节数组指针.
 * @param  len: 待写入字节长度.
 * @retval None
 */
void AT24C02_WriteBytes(uint8_t InnerAddr, uint8_t *bytes, uint8_t len)
{
    I2C_Start(); // 产生START条件

    I2C_SendAddr(ADDR); // 发送设备地址 (写操作)

    I2C_SendByte(InnerAddr); // 发送内部地址

    for (uint8_t i = 0; i < len; i++) // 循环发送数据
    {
        I2C_SendByte(bytes[i]); // 发送数据字节
    }

    I2C_Stop(); // 产生STOP条件

    Delay_ms(5); // 等待EEPROM写入完成
}

/**
 * @brief  从AT24C02读取多个字节.
 * @param  InnerAddr: EEPROM内部起始地址.
 * @param  bytes: 存储读取字节的数组指针.
 * @param  len: 待读取字节长度.
 * @retval None
 */
void AT24C02_ReadBytes(uint8_t InnerAddr, uint8_t *bytes, uint8_t len)
{
    I2C_Start(); // 产生START条件

    I2C_SendAddr(ADDR); // 发送设备地址 (写操作, 用于设置读取地址)

    I2C_SendByte(InnerAddr); // 发送内部地址

    I2C_Start(); // 产生重复START条件

    I2C_SendAddr(ADDR + 1); // 发送设备地址 (读操作)

    for (uint8_t i = 0; i < len; i++) // 循环读取数据
    {
        if (i < len - 1) // 如果不是最后一个字节
        {
            I2C_ACK(); // 配置ACK
        }
        else // 如果是最后一个字节
        {
            I2C_NACK(); // 配置NACK

            I2C_Stop(); // 配置STOP (NACK后立即发送)
        }

        bytes[i] = I2C_ReadByte(); // 读取数据字节
    }
}
