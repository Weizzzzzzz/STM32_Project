#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"

// 函数声明：初始化USART1通信接口
void Usart1_Init(void);

// 函数声明：通过USART1发送单个字符
// 参数：ch - 待发送的8位数据字节
void Usart1_SendChar(uint8_t ch);

// 函数声明：通过USART1发送指定长度的字符串
// 参数：srt - 指向待发送字符串的指针
//       len - 需发送的字节长度
void Usart1_SendString(uint8_t *str, uint8_t len);

// 函数声明：从USART1接收单个字符
// 返回值：接收到的8位数据字节
uint8_t Usart1_ReceiveChar(void);

// 函数声明：从USART1接收字符串并存储到缓冲区
// 参数：buffer - 存储接收数据的缓冲区数组
//       len - 用于存储实际接收长度的变量指针
void Usart1_ReceiveString(uint8_t buffer[], uint8_t *len);

#endif
