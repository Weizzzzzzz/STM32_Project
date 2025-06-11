#include "spi.h"

void SPI2_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

    GPIOB->CRH &= ~(GPIO_CRH_CNF12 | GPIO_CRH_MODE12);
    GPIOB->CRH |= GPIO_CRH_MODE12;

    // PB13 (SCK) - AF Push-pull
    GPIOB->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13);  // 清零CNF和MODE
    GPIOB->CRH |= (GPIO_CRH_CNF13_1 | GPIO_CRH_MODE13); // CNF=10, MODE=11 (50MHz)

    // PB15 (MOSI) - AF Push-pull
    GPIOB->CRH &= ~(GPIO_CRH_CNF15 | GPIO_CRH_MODE15);  // 清零CNF和MODE
    GPIOB->CRH |= (GPIO_CRH_CNF15_1 | GPIO_CRH_MODE15); // CNF=10, MODE=11 (50MHz)

    GPIOB->CRH &= ~(GPIO_CRH_MODE14 | GPIO_CRH_CNF14);
    GPIOB->CRH |= GPIO_CRH_CNF14_0;

    SPI2->CR1 |= SPI_CR1_MSTR;

    SPI2->CR1 |= SPI_CR1_SSM;
    SPI2->CR1 |= SPI_CR1_SSI;

    SPI2->CR1 &= ~SPI_CR1_CPOL;
    SPI2->CR1 &= ~SPI_CR1_CPHA;

    SPI2->CR1 &= ~SPI_CR1_BR;

    SPI2->CR1 &= ~SPI_CR1_DFF;

    SPI2->CR1 &= ~SPI_CR1_LSBFIRST;

    SPI2->CR1 |= SPI_CR1_SPE;
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
    while ((SPI2->SR & SPI_SR_TXE) == 0)
        ;

    SPI2->DR = byte;

    while ((SPI2->SR & SPI_SR_RXNE) == 0)
        ;
    return (uint8_t)(SPI2->DR & 0xff);
}
