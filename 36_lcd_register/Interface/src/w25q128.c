#include "w25q128.h"
#include "usart.h"

void W25Q128_Init(void)
{
    SPI2_Init();
}

void W25Q128_ReadID(uint8_t *mid, uint16_t *did)
{
    SPI2_Start();

    SPI2_SwapByte(0x9f);

    *mid = SPI2_SwapByte(0xff);

    *did = 0;
    *did |= SPI2_SwapByte(0xff) << 8;
    *did |= SPI2_SwapByte(0xff) & 0xff;

    SPI2_Stop();
}

void W25Q128_WriteEnable(void)
{
    SPI2_Start();

    SPI2_SwapByte(0x06);

    SPI2_Stop();
}

void W25Q128_WriteDisable(void)
{
    SPI2_Start();

    SPI2_SwapByte(0x04);

    SPI2_Stop();
}

void W25Q128_WaitNotBusy(void)
{
    SPI2_Start();

    SPI2_SwapByte(0x05);

    while (SPI2_SwapByte(0x0ff) & 0x01)
        ;

    SPI2_Stop();
}

void W25Q128_EraseSection(uint8_t block, uint8_t sector)
{
    W25Q128_WaitNotBusy();

    W25Q128_WriteEnable();

    uint32_t Addr = (block << 16) + (sector << 12);

    SPI2_Start();

    SPI2_SwapByte(0x20);

    SPI2_SwapByte((Addr >> 16) & 0xff);
    SPI2_SwapByte((Addr >> 8) & 0xff);
    SPI2_SwapByte((Addr >> 0) & 0xff);

    SPI2_Stop();

    W25Q128_WriteDisable();
}

void W25Q128_PageWrite(uint8_t block, uint8_t sector, uint8_t page, uint8_t *data, uint16_t len)
{
    W25Q128_WaitNotBusy();

    W25Q128_WriteEnable();

    uint32_t Addr = (block << 16) + (sector << 12) + (page << 8);

    SPI2_Start();

    SPI2_SwapByte(0x02);

    SPI2_SwapByte((Addr >> 16) & 0xff);
    SPI2_SwapByte((Addr >> 8) & 0xff);
    SPI2_SwapByte((Addr >> 0) & 0xff);

    for (uint16_t i = 0; i < len; i++)
    {
        SPI2_SwapByte(data[i]);
    }

    SPI2_Stop();

    W25Q128_WriteDisable();
}

void W25Q128_Read(uint8_t block, uint8_t sector, uint8_t page, uint8_t InnerAddr, uint8_t *buffer, uint16_t len)
{
    W25Q128_WaitNotBusy();

    uint32_t Addr = (block << 16) + (sector << 12) + (page << 8) + InnerAddr;

    SPI2_Start();

    SPI2_SwapByte(0x03);

    SPI2_SwapByte((Addr >> 16) & 0xff);
    SPI2_SwapByte((Addr >> 8) & 0xff);
    SPI2_SwapByte((Addr >> 0) & 0xff);

    for (uint16_t i = 0; i < len; i++)
    {
        buffer[i] = SPI2_SwapByte(0xff);
    }

    SPI2_Stop();
}
