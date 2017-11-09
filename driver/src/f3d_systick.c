#include <f3d_systick.h>
#include <stdio.h>
//#include <f3d_led.h> 
//#include "f3d_button.h"
//#include <f3d_uart.h>

volatile int systick_flag = 0;

int ledon = 0;

void f3d_systick_init(void) {
    TIM_ITConfig(TIM2, TIM_IT_Update , ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    SysTick_Config(SystemCoreClock / SYSTICK_INT_SEC);
}

void setTickSpeed(int speed){
    SysTick_Config(SystemCoreClock / speed);
}

int startingLed[1] = {0};

void setNextLed(int *currentLed){
    if (currentLed[0] < 7){
        currentLed[0]++;
        return;
    }
    currentLed[0] = 0;
}
int getPrevLed(int currentLed){
    if (currentLed <= 0)
        return 0;
    return currentLed--;
}

void SysTick_Handler(void) {
    if (user_btn_read())
        setTickSpeed(10);
    else
        setTickSpeed(SYSTICK_INT_SEC);

    f3d_led_on(startingLed[0]);
    f3d_led_all_off_except(startingLed[0]);
    setNextLed(startingLed);
}
