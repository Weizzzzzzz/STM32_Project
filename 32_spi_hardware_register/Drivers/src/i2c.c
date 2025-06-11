#include "i2c.h"

void I2C_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    GPIOB->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
    GPIOB->CRL |= GPIO_CRL_MODE6;
    GPIOB->CRL |= GPIO_CRL_CNF6_0;

    GPIOB->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
    GPIOB->CRL |= GPIO_CRL_MODE7;
    GPIOB->CRL |= GPIO_CRL_CNF7_0;

    GPIOB->ODR |= (GPIO_ODR_ODR6 | GPIO_ODR_ODR7);
}

void I2C_Start(void)
{
    SDA_HIGH;
    SCL_HIGH;
    I2C_Delay;

    SDA_LOW;
    I2C_Delay;
}

void I2C_Stop(void)
{
    SDA_LOW;
    SCL_LOW;
    I2C_Delay;

    SCL_HIGH;
    I2C_Delay;

    SDA_HIGH;
    I2C_Delay;
}

void I2C_ACK(void)
{
    SDA_HIGH;
    SCL_LOW;
    I2C_Delay;

    SDA_LOW;
    I2C_Delay;

    SCL_HIGH;
    I2C_Delay;

    SCL_LOW;
    I2C_Delay;

    SDA_HIGH;
    I2C_Delay;
}

void I2C_NACK(void)
{
    SDA_HIGH;
    SCL_LOW;
    I2C_Delay;

    SCL_HIGH;
    I2C_Delay;

    SCL_LOW;
    I2C_Delay;
}

uint8_t I2C_WaitACK(void)
{
    SDA_HIGH;
    SCL_LOW;
    I2C_Delay;

    SCL_HIGH;
    I2C_Delay;

    uint8_t ack = ACK;
    if (READ_SDA)
    {
        ack = NACK;
    }

    SCL_LOW;
    I2C_Delay;

    return ack;
}

void I2C_SendByte(uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        SCL_LOW;
        I2C_Delay;

        if (byte & 0x80)
        {
            SDA_HIGH;
        }
        else
        {
            SDA_LOW;
        }
        I2C_Delay;

        SCL_HIGH;
        I2C_Delay;

        SCL_LOW;
        I2C_Delay;

        byte <<= 1;
    }
}

uint8_t I2C_ReadByte(void)
{
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        SCL_LOW;
        I2C_Delay;

        SCL_HIGH;
        I2C_Delay;

        data <<= 1;
        if (READ_SDA)
        {
            data |= 0x01;
        }

        SCL_LOW;
        I2C_Delay;
    }
    return data;
}
