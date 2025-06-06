#include "at24c02.h"

/**
 * @brief  初始化AT24C02. (实际调用I2C初始化)
 * @param  None
 * @retval None
 */
void AT24C02_Init(void)
{
    MX_I2C1_Init(); // 初始化I2C总线
}

/**
 * @brief  向AT24C02写入一个字节.
 * @param  InnerAddr: EEPROM内部地址.
 * @param  byte: 待写入字节.
 * @retval None
 */
void AT24C02_WriteByte(uint8_t InnerAddr, uint8_t byte)
{
    // HAL库I2C内存写操作: 设备地址ADDR, 内存地址InnerAddr, 8位内存地址, 数据源&byte, 长度1, 超时1000ms
    HAL_I2C_Mem_Write(&hi2c1, ADDR, InnerAddr, I2C_MEMADD_SIZE_8BIT, &byte, 1, 1000);

    HAL_Delay(5); // 等待EEPROM写入完成 (典型值5ms)
}

/**
 * @brief  从AT24C02读取一个字节.
 * @param  InnerAddr: EEPROM内部地址.
 * @retval 读取到的字节.
 */
uint8_t AT24C02_ReadByte(uint8_t InnerAddr)
{
    uint8_t byte = 0; // 存储读取数据的变量

    // HAL库I2C内存读操作: 设备地址ADDR+1 (读地址), 内存地址InnerAddr, 8位内存地址, 数据目的&byte, 长度1, 超时1000ms
    HAL_I2C_Mem_Read(&hi2c1, ADDR + 1, InnerAddr, I2C_MEMADD_SIZE_8BIT, &byte, 1, 1000);

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
    // HAL库I2C内存写操作: 设备地址ADDR, 内存地址InnerAddr, 8位内存地址, 数据源bytes, 长度len, 超时1000ms
    HAL_I2C_Mem_Write(&hi2c1, ADDR, InnerAddr, I2C_MEMADD_SIZE_8BIT, bytes, len, 1000);

    HAL_Delay(5); // 等待EEPROM写入完成
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
    // HAL库I2C内存读操作: 设备地址ADDR+1 (读地址), 内存地址InnerAddr, 8位内存地址, 数据目的bytes, 长度len, 超时1000ms
    HAL_I2C_Mem_Read(&hi2c1, ADDR + 1, InnerAddr, I2C_MEMADD_SIZE_8BIT, bytes, len, 1000);
}
