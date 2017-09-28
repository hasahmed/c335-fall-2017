//*
// Mac Vogelsang - madvogel
// Hasan Ahmed - hasahmed
// Lab 05 - main.c
// Sept. 28th, 2017
//
//main.c for lab6
#include <f3d_uart.h>
#include <stdio.h>
#include <stdlib.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

void light_by_rate(float axisValue){
    f3d_led_all_off();
    //number of leds to turn on in positive or negative direction
    int num = (int) abs(axisValue) / 100;
    int j;
    if (abs(axisValue) > 5) {
        f3d_led_on(0);
    }
    if (axisValue > 0){
        for (j = 1; j < num; j++){
            f3d_led_on(j);
        }
    } else {
        for (j = 7; j > (8-num); j--){
            f3d_led_on(j);
        }
    }
}

int main(void){

    f3d_uart_init();
    f3d_gyro_init();
    f3d_led_init();
    f3d_user_btn_init();

    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    //stores current state of the gyo axis
    //0:X, 1:Y, 2:Z
    int axis = 0;


    int i;
    float test[3];
    float gyroData[3];

    while(1){
        int val =  user_btn_read();
        if (val) {
            axis = (axis + 1) % 3;
            while (user_btn_read() != 0);
        } else {
            //do nothing
        }

        //*
        //getchar() modification
        if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != (uint16_t)RESET) {
            char input = USART_ReceiveData(USART1);
            if (input == 'X' || input == 'x') axis = 0;
            if (input == 'Y' || input == 'y') axis = 1;
            if (input == 'Z' || input == 'z') axis = 2;
        }

        //printf("%c\n",input[0]);
        //*/

        f3d_gyro_getdata(gyroData);
        light_by_rate(gyroData[axis]);

        printf("%c: %f\n", axis + 'X', gyroData[axis]);
        //putchar(axis);
        //putchar(getchar());

        /* READ DATA TESTER
        f3d_gyro_getdata(test);
        for (i=0;i<3;i++){
            printf("%f ", test[i]);
        }
        printf("\n");
        //*/
    };
}

void assert_failed(uint8_t* file, uint32_t line) {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
}
