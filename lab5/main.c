//main.c for lab6
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

void delay(void) {
    int i = 2000000;
    while (i-- > 0) {
        asm("nop"); /* This stops it optimising code out */
    }
}


char switchAxis(char currentAxis){
    switch(currentAxis){
        case 'x':
            return 'y';
        case 'y':
            return 'z';
        case 'z':
            return 'x';
        default: return 0;
    }
}

float getCurrentAxisValue(char currentAxis, float *gyroData){
    switch (currentAxis){
        case 'x':
            return gyroData[0];
        case 'y':
            return gyroData[1];
        case 'z':
            return gyroData[2];
        default: return 0;
    }
}


void lightNorth(float av){
    if(av > 5){
        f3d_led_on(1);
    }
    else{
        f3d_led_off(1);
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

    float gyroData[3];
    char currentAxis = 'x';
    int buttonBeenReleased = 1;
    //f3d_led_all_on();
    f3d_led_all_off();
    while(1){

        if (!user_btn_read())
            buttonBeenReleased = 1;

        f3d_gyro_getdata(gyroData);
        if(user_btn_read() && buttonBeenReleased){
            currentAxis = switchAxis(currentAxis);
            buttonBeenReleased = 0;
        }

        float currentAxisValue = getCurrentAxisValue(currentAxis, gyroData);

        printf("%c: %f\n", currentAxis, currentAxisValue);
        lightNorth(currentAxisValue);
    }
}

void assert_failed(uint8_t* file, uint32_t line) {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
}
