//main.c for lab6
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

int main(void){

    
    f3d_uart_init();
    f3d_gyro_init();
    f3d_led_init();
    f3d_user_btn_init();

    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    float gyroData[3];
    while(1){
        f3d_gyro_getdata(gyroData);

        printf("%f ", gyroData[0]);
        printf("%f ", gyroData[1]);
        printf("%f\n", gyroData[2]);
        //printf("Hello World!\n");
    }
}

void assert_failed(uint8_t* file, uint32_t line) {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
}
