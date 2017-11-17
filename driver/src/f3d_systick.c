#include <f3d_systick.h>
#include <stdio.h>

volatile int systick_flag = 0;

void f3d_systick_init(void) {
    TIM_ITConfig(TIM2, TIM_IT_Update , ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    SysTick_Config(SystemCoreClock / SYSTICK_INT_SEC);
}

void setTickSpeed(int speed){
    SysTick_Config(SystemCoreClock / speed);
}

void SysTick_Handler(void) {
    /*
    if (user_btn_read())
        setTickSpeed(10);
    else
        setTickSpeed(SYSTICK_INT_SEC);

    f3d_led_on(startingLed[0]);
    f3d_led_all_off_except(startingLed[0]);
    setNextLed(startingLed);
    */
}
