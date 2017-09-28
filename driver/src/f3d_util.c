/**
 * f3d_util.c
 * utility functions for f3d board
 * Hasan Y Ahmed
 * 9/28/17
 *
 *
 */
#include <f3d_util.h>

//delay_amount in cpu cycles
void delay(int delay_cycles) {
  int i = delay_cycles * 200; //aribitrary multiplier
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}
