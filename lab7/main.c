/* main.c ---
 *
 * Filename: main.c
 * Description:
 * Author:
 * Maintainer:
 * Created: Thu Jan 10 11:23:43 2013
/* Code: */


#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_gyro.h>

#include <math.h>
#include <stdio.h>


#define TIMER 20000

int main(void) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    // Set up your inits before you go ahead
    f3d_i2c1_init();
    delay(10);
    f3d_accel_init();
    delay(10);
    f3d_mag_init();
    delay(10);
    f3d_gyro_init();


    float mag[3];
    float accel[3];






float pitch;
float roll;
float Xh;
float Yh;
float compassAngle;



int i;




    while(1){
        f3d_mag_read(mag);
        f3d_accel_read(accel);


        pitch = (atanf(accel[0]/sqrt(pow(accel[1],2) +pow(accel[2], 2))));
        roll = (atanf(accel[1]/sqrt(pow(accel[0], 2) + pow(accel[2], 2))));
        Xh = mag[0]*cos(pitch)+mag[2]*sin(pitch);
        Yh = mag[0]*sin(roll)*sin(pitch)+mag[1]*cos(roll)-mag[2]*sin(roll)*cos(pitch);
        compassAngle = fabs((atan2(Yh, Xh)) * 180 / 3.1415926535 + 180.0f);

        //printf("pitch:%f, roll:%f, Xh:%f, Yh:%f\ncompassAngle:%f\n", pitch, roll, Xh, Yh, compassAngle);
        //printf("pitch:%f\n", pitch); 
        //printf("roll:%f\n", roll); 
        printf("compassAngle:%f\n", compassAngle); 
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

