#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <stdio.h>

#include "queue.h"

/*
void die (FRESULT rc) {
    printf("Failed with rc=%u.\n", rc);
    while (1);
}
*/

void initAll(){
    f3d_delay_init();
    delay(310);
    f3d_uart_init();
    delay(310);
    f3d_gyro_init();
    delay(310);
    f3d_led_init();
    delay(310);
    f3d_lcd_init();
    delay(310);
    f3d_i2c1_init();
    delay(310);
    f3d_accel_init();
    delay(310);
    f3d_mag_init();
    delay(310);
    f3d_nunchuk_init();
    delay(310);
    f3d_rtc_init();
    f3d_lcd_fillScreen2(BLACK);
}
void setBuffs(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void) { 
    setBuffs();
    initAll();
    while (1){
        //printf("Its on");
        putchar(getchar());
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
}
#endif

/* main.c ends here */
