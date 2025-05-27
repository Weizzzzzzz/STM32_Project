#ifndef __BUZZER_H
#define __BUZZER_H

#include "stm32f10x.h"

// 初始化buzzer（PB12推挽输出）
void Buzzer_Init(void);
// 开启buzzer
void Buzzer_On(uint32_t buzzer);
// 关闭buzzer
void Buzzer_Off(uint32_t buzzer);
// 切换buzzer状态
void Buzzer_Toggle(uint32_t buzzer);

#endif
