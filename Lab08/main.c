/* main.c ---
*  Mac Vogelsang - madvogel
*  October 12th, 2017
*  Lab07 C335
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
#include <f3d_led.h> // Pull in include file for the local drivers
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <stdio.h>
#include <math.h>

#define TIMER 20000
#define WIDTH 128
#define HEIGHT 160
#define RECENT_NUM 10
#define UI_HEIGHT 30
#define PI 3.14159265

void move(int * x, int * y, float vx, float vy, int size){
    vx =  vx * -15;
    int newX = *x + vx;
    if (newX < 0) newX = 0;
    if (newX+size > WIDTH) newX = WIDTH - size;

    vy =  vy * -15;
    int newY = *y + vy;
    if (newY < 0) newY = 0;
    if (newY+size > HEIGHT - UI_HEIGHT) newY = HEIGHT - UI_HEIGHT - size;

    *y = newY;
    *x = newX;
}

void recenter(int * x, int * y, int size){
    int ver = HEIGHT - UI_HEIGHT;
    int hor = WIDTH;
    *x = hor/2 - size/2;
    *y = ver/2 - size/2;
}

void drawBackground(){
    //draw background
    f3d_lcd_fillScreen2(CYAN);
    //draw rect x, y, width, height
    f3d_lcd_drawRect(0, HEIGHT-UI_HEIGHT, WIDTH,UI_HEIGHT, WHITE);
}


void tiltAngle(float * accel){
    //nan correction
    int i;
    for (i = 0; i < 3; i++) {
        if (accel[i] < -1) accel[i] = -1;
        if (accel[i] >  1) accel[i] = 1;
    }
    accel[0] = asinf(accel[0]);
    accel[1] = asinf(accel[1]);
    accel[2] = acosf(accel[2]);
}

float getHeading(float * magdata) {
    //return heading in degrees
    float h = (180/PI) * atan2(magdata[1],  magdata[0]);
    if (h < 0) h = 360 + h;

    return h;
}

void tiltCompensation(float * accel, float * compass, float * headingData) {
    float pitch = accel[0];
    float roll = accel[1];
    float xh = (compass[0] * cosf(pitch)) + (compass[2] * sinf(pitch));
    float yh = (compass[0] * sinf(roll) * sinf(pitch)) + (compass[1] * cosf(roll)) - (compass[2] * sinf(roll) * cosf(pitch));

    headingData[0] = xh;
    headingData[1] = yh;
}

void printData(float * data) {
    int i;
    for (i=0;i<3;i++){
        printf("%f ", data[i]);
    }
    printf("\n");
}

void printNunData(nunchuk_t * nunt){
    //printf("jx: %u, jy: %u\n",nunt->jx, nunt->jy);
    printf("ax: %hu, ay: %hu, az: %hu\n",nunt->ax, nunt->ay, nunt->az);
    //printf("c: %u, z: %u\n",nunt->c, nunt->z);
    //printf("----------------------------------\n");
}

int modeSwitch(int mode, nunchuk_t * nunt) {
    int programs = 4;
    int deadZone = 20;
    int jx = nunt->jx;
    if (jx > 255 - deadZone) {
        mode = (mode + 1) % programs;
        drawBackground();
    }
    if (jx < 0 + deadZone) {
        mode = (mode - 1) % programs;
        drawBackground();
    }
    return mode;
}

int main(void) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    // Set up your inits before you go ahead

    f3d_lcd_init();
    f3d_uart_init();
    f3d_user_btn_init();
    f3d_led_init();

    f3d_i2c1_init();
    delay(10);
    f3d_accel_init();
    delay(10);
    f3d_mag_init();
    delay(10);
    f3d_nunchuk_init();

    float accelData[3];
    float compData[3];
    float headingData[2];
    int i;
    int mode = 0;  // 0 for accelerometer, 1 for compass
    int oldci = 0;

    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    int vx = 0;
    int vy = 0;
    int counter = 0;

    drawBackground();
    //draw center square
    int squareSize = 10;
    recenter(&x,&y,squareSize);
    f3d_lcd_drawRect(x,y,squareSize,squareSize,MAGENTA);

    //cardinal positions on the screen
    int size = 40;
    int corner = size - 10;
    int CPOS[8][2];
    CPOS[0][0] = x;
    CPOS[0][1] = y - size;
    CPOS[1][0] = x + corner;
    CPOS[1][1] = y - corner;
    CPOS[2][0] = x + size;;
    CPOS[2][1] = y;
    CPOS[3][0] = x + corner;;
    CPOS[3][1] = y + corner;
    CPOS[4][0] = x;
    CPOS[4][1] = y + size;
    CPOS[5][0] = x - corner;
    CPOS[5][1] = y + corner;
    CPOS[6][0] = x - size;
    CPOS[6][1] = y;
    CPOS[7][0] = x - corner;
    CPOS[7][1] = y - corner;

    char * compass[8] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};

    //nunchuk data
    nunchuk_t nunt;

    while(1) {
        //if button read, reset square location
        mode = modeSwitch(mode, &nunt);

        //read sensors
        f3d_accel_read(accelData);
        f3d_mag_read(compData);
        //calculate tilt angles (modifies accelData in place)
        tiltAngle(accelData);
        //use tilt angles and compass data to store correct heading vectors into headingData
        tiltCompensation(accelData, compData, headingData);

        //get nunchuk data
        f3d_nunchuk_read(&nunt);
        printNunData(&nunt);

        //get heading value
        float heading = getHeading(headingData);

        //compass mode
        switch (mode) {
            case 0: {
                    char printData1[15];
                    sprintf(printData1, "degree: %3.6f", heading);
                    f3d_lcd_drawString(1, HEIGHT-(UI_HEIGHT-1)+(2* 10), printData1, BLACK, WHITE);

                    //compass index
                    int ci = (((int) (heading / 45)) + 4) % 8;
                    if (ci != oldci){
                        drawBackground();
                        char printData2[10];
                        sprintf(printData2, "heading: %s", compass[ci], heading);
                        f3d_lcd_drawString(1, HEIGHT-(UI_HEIGHT-1)+(0 * 10), printData2, BLACK, WHITE);
                        oldci = ci;
                        int c;
                        int color = BLACK;
                        int background = WHITE;
                        for (c = 0; c < 8; c++){
                            if (compass[ci][0] == 'N' && compass[ci][1] == 0) {
                                color = RED;
                                background = WHITE;
                            } else {
                                color = BLACK;
                                background = WHITE;
                            }
                            f3d_lcd_drawString(CPOS[c][0],CPOS[c][1], compass[ci], color, background);
                            ci = (ci + 1) % 8;
                        }
                    }
                }
                break;
            case 1: {
                    //printf("Accel: ");
                    //printData(accelData);
                    //draw over previous square location
                    f3d_lcd_drawRect(x,y,squareSize,squareSize,CYAN);

                    //modify x and y inplace to move square
                    move(&x,&y,accelData[1],accelData[0],squareSize);
                    //draw new square
                    f3d_lcd_drawRect(x,y,squareSize,squareSize,MAGENTA);

                    char printData[3][10];
                    //k is axis
                    int k;
                    for  (k=0;k<3;k++){
                        sprintf(printData[k], "%c:%+06.3f", k + 'X', accelData[k]);
                        f3d_lcd_drawString(1, HEIGHT-(UI_HEIGHT-1)+(k * 10), printData[k], BLACK, WHITE);
                    }
                }
                break;
        }

        counter++;
    };
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
}
#endif

/* main.c ends here */

