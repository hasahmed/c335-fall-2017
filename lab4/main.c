/* Hasan Y Ahmed (hasahmed)
 * Lab 2
 * 9/14/17
 */
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_uart.h>     // Pull in include file for the local drivers

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); 
  }
}

int main(void) {
void f3d_uart_init();
  while(1);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif
