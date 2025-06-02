#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

typedef enum
{
    No_LED = -1,
    L1,
    L2,
    L3
} FLOW_STATES;

extern FLOW_STATES flow_states;

void Key_Init(void);

#endif
