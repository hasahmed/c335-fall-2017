#include <stdio.h>
#include "general_util.h"
void initAll(){
    f3d_delay_init();
    delay(310);
    f3d_uart_init();
    delay(310);
    f3d_lcd_init();
    delay(310);
    f3d_i2c1_init();
    delay(310);
    f3d_nunchuk_init();
    delay(310);
    f3d_rtc_init();
    delay(310);
    f3d_systick_init();
    delay(310);
    f3d_dac_init();
    delay(310);
    f3d_timer2_init();
}
void setBuffs(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}
