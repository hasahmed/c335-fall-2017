/* main.c ---
 *
 * Filename: main.c
 * Description:
 * Author: Hasan Y Ahmed
 * Maintainer:
 * Created: Thu Jan 10 11:23:43 2013
/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h> // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>

#define TIMER 20000

int main(void) {
    // If you have your inits set up, this should turn your LCD screen red
    f3d_lcd_init();
    while(1){


        f3d_lcd_drawChar(10, 10, 'H', RED, BLACK);
        /*
        int TIME = 2000;
        f3d_lcd_fillScreen2(RED);
        delay(TIME);
        f3d_lcd_fillScreen2(BLACK);
        delay(TIME);
        f3d_lcd_fillScreen2(BLUE);
        delay(TIME);
        f3d_lcd_fillScreen2(CYAN);
        delay(TIME);
        f3d_lcd_fillScreen2(GREEN);
        delay(TIME);
        f3d_lcd_fillScreen2(MAGENTA);
        delay(TIME);
        f3d_lcd_fillScreen2(YELLOW);
        delay(TIME);
        f3d_lcd_fillScreen2(WHITE);
        */
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
