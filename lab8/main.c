/* main.c ---
 *
 * Filename: main.c
 * Description:
 * Hasan Y Ahmed, Kyle
 * Created: 10/16/17
/* Code: */


#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_nunchuk.h>
#include <math.h>
#include <stdio.h>

#include "apps.h"

#define TIMER 20000
#define CHARSTEP 6 //the amount of space to put between characters
#define HEIGHT ST7735_height
#define WIDTH ST7735_width

#define SQUARESIZE  10 //the size of the "bubble"
#define SQUARE_START_X  WIDTH/2 - (SQUARESIZE / 2)
#define SQUARE_START_Y  HEIGHT/2 - (SQUARESIZE / 2)


int app_nums = COMPASS;
int joydir = NA;
int appHasChanged = 0;

void drawString(int startx, int y, const char *str, uint16_t charColor, uint16_t charBGColor){
    int i = 0;
    while(str[i] != '\0'){
        f3d_lcd_drawChar(startx + (i * CHARSTEP), y, str[i], charColor, charBGColor);
        i++;
    }
}

enum Apps appSwitch(enum Apps appNum, enum Joydir joydir){
    if (joydir != NA){
        appHasChanged = 1;
        switch(appNum){
            case COMPASS:
                return TILT;
                /*
                   if (joydir == LEFT)
                   return ++appNum;
                   else
                   return COMPASS;
                   */
            case TILT:
                return COMPASS;
        }
    }
    appHasChanged = 0;
    return appNum;
}


void printNunData(nunchuk_t * nunt){
    //printf("jx: %u, jy: %u\n",nunt->jx, nunt->jy); //analog stick
    //printf("ax: %hu, ay: %hu, az: %hu\n",nunt->ax, nunt->ay, nunt->az); //tilts
    //printf("c: %u, z: %u\n",nunt->c, nunt->z); //buttons
    //printf("----------------------------------\n");
}


void initAll(){
    f3d_uart_init();
    delay(10);
    f3d_gyro_init();
    delay(10);
    f3d_led_init();
    delay(10);
    f3d_user_btn_init();
    delay(10);
    f3d_lcd_init();
    delay(10);
    f3d_i2c1_init();
    delay(10);
    f3d_accel_init();
    delay(10);
    f3d_mag_init();
    delay(10);
    f3d_nunchuk_init();
    delay(10);
}

void setBuffs(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void) {
    setBuffs();
    initAll();

    float mag[3];
    float accel[3];
    int dirtyArea[] = {0, 0};
    float x, y, z;
    nunchuk_t chuky;

    while(1){
        f3d_mag_read(mag);
        f3d_accel_read(accel);
        f3d_nunchuk_read(&chuky);
        x = accel[0] * 180;
        y = accel[1] * 180;

        if (user_btn_read()){
            appSwitch(app_nums, RIGHT);
        }

        joydir = checkJoyDir(&chuky);
        app_nums = appSwitch(app_nums, joydir);

        switch(app_nums){
            case COMPASS:
                compassApp(accel, mag, appHasChanged);
                break;
            case TILT:
                tiltApp(x, y, dirtyArea, appHasChanged);
                break;
        }
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    printf("There has been an error, Use GDB to find the source");
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
}
#endif

/* main.c ends here */
