#include <f3d_systick.h>
#include <stdio.h>
#include "../../final/main.h"

volatile int systick_flag = 0;

void f3d_systick_init(void) {
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    SysTick_Config(SystemCoreClock / SYSTICK_INT_SEC);
}

void setTickSpeed(int speed){
    SysTick_Config(SystemCoreClock / speed);
}

void SysTick_Handler(void) {
    update();
}
