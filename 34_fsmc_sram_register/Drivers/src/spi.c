#include "spi.h"

void SPI2_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    GPIOB->CRH |= GPIO_CRH_MODE12;
    GPIOB->CRH &= ~GPIO_CRH_CNF12;

    GPIOB->CRH |= GPIO_CRH_MODE13;
    GPIOB->CRH &= ~GPIO_CRH_CNF13;

    GPIOB->CRH |= GPIO_CRH_MODE15;
    GPIOB->CRH &= ~GPIO_CRH_CNF15;

    GPIOB->CRH &= ~(GPIO_CRH_MODE14 | GPIO_CRH_CNF14);
    GPIOB->CRH |= GPIO_CRH_CNF14_0;

    SPI2_SCK_LOW;
    F_CS_HIGH;
    SPI_Delay;
}

void SPI2_Start(void)
{
    F_CS_LOW;
}

void SPI2_Stop(void)
{
    F_CS_HIGH;
}

uint8_t SPI2_SwapByte(uint8_t byte)
{
    uint8_t rbyte = 0x00;

    for (uint8_t i = 0; i < 8; i++)
    {
        if (byte & 0x80)
        {
            SPI2_MOSI_HIGH;
        }
        else
        {
            SPI2_MOSI_LOW;
        }
        byte <<= 1;

        SPI2_SCK_HIGH;
        SPI_Delay;

        rbyte <<= 1;
        if (SPI2_MISO_READ)
        {
            rbyte |= 0x01;
        }

        SPI2_SCK_LOW;
        SPI_Delay;
    }
    return rbyte;
}
