//
// Hasan Ahmed - hasahmed
// debug_printf - main.c
// 9/28/17
//
//main.c for debug_printf
//
#include <f3d_uart.h>
#include <stdio.h>
#include <stdlib.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>


void onOffWithPrints(){
    int j;
    f3d_led_on(0);
    for(j = 0; j < 10; j++)
        printf("%s\n", "hello");
    f3d_led_off(0);
    for(j = 0; j < 10; j++)
        printf("%s\n", "goodbye");
}

void onOffNoPrints(){
    f3d_led_on(0);
    f3d_led_off(0);

}
int main(void){

    f3d_uart_init();
    f3d_gyro_init();
    f3d_led_init();
    f3d_user_btn_init();

    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    while(1){
        if (user_btn_read())
            onOffWithPrints();
        else
            onOffNoPrints();

    }
}

void assert_failed(uint8_t* file, uint32_t line) {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
}
