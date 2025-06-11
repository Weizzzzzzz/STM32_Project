#include "at24c02.h"

void AT24C02_Init(void)
{
    I2C_Init();
}

void AT24C02_WriteByte(uint8_t InnerAddr, uint8_t byte)
{
    I2C_Start();

    I2C_SendByte(ADDR);

    uint8_t ack = I2C_WaitACK();
    if (ack == 0)
    {
        I2C_SendByte(InnerAddr);

        I2C_WaitACK();

        I2C_SendByte(byte);

        I2C_WaitACK();

        I2C_Stop();
    }
    Delay_ms(5);
}

uint8_t AT24C02_ReadByte(uint8_t InnerAddr)
{
    I2C_Start();

    I2C_SendByte(ADDR);

    I2C_WaitACK();

    I2C_SendByte(InnerAddr);

    I2C_WaitACK();

    I2C_Start();

    I2C_SendByte(ADDR + 1);

    I2C_WaitACK();

    uint8_t byte = I2C_ReadByte();

    I2C_NACK();

    I2C_Stop();

    return byte;
}

void AT24C02_WriteBytes(uint8_t InnerAddr, uint8_t *bytes, uint8_t len)
{
    I2C_Start();

    I2C_SendByte(ADDR);

    uint8_t ack = I2C_WaitACK();
    if (ack)
    {
        I2C_SendByte(InnerAddr);

        I2C_WaitACK();

        for (uint8_t i = 0; i < len; i++)
        {
            I2C_SendByte(bytes[i]);

            I2C_WaitACK();
        }

        I2C_Stop();
    }
    Delay_ms(5);
}

void AT24C02_ReadBytes(uint8_t InnerAddr, uint8_t *bytes, uint8_t len)
{
    I2C_Start();

    I2C_SendByte(ADDR);

    I2C_WaitACK();

    I2C_SendByte(InnerAddr);

    I2C_WaitACK();

    I2C_Start();

    I2C_SendByte(ADDR + 1);

    I2C_WaitACK();

    for (uint8_t i = 0; i < len; i++)
    {
        bytes[i] = I2C_ReadByte();

        if (i < len - 1)
        {
            I2C_ACK();
        }
        else
        {
            I2C_NACK();
        }
    }

    I2C_Stop();
}
