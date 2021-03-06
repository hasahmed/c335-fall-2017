/*
 * Hasan Y Ahmed
 * Lab4
 * 9/18/17
 * Partner: None
 */
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_uart.h>     // Pull in include file for the local drivers
#include <stdio.h>
#include "mywc/mywc.h"

// Simple looping delay function
void delay(void) {
    int i = 2000000;
    while (i-- > 0) {
        asm("nop"); 
    }
}

int main(void) {

    //to make output unbuffered
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    f3d_uart_init();

    while(1)
        printf("%s\n", "hello");
        //putchar(getchar());
        //wc();
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
}
#endif
