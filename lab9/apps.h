#ifndef _APPS_H_
#define _APPS_H_

#include <f3d_nunchuk.h>

enum Apps{
    COMPASS = 0,
    TILT = 1
};

enum Joydir{
    LEFT,
    RIGHT,
    NA
};

#define CHARSTEP 6 //the amount of space to put between characters
#define HEIGHT ST7735_height
#define WIDTH ST7735_width

#define SQUARESIZE  10 //the size of the "bubble"
#define SQUARE_START_X  WIDTH/2 - (SQUARESIZE / 2)
#define SQUARE_START_Y  HEIGHT/2 - (SQUARESIZE / 2)



void compassApp(float *accelData, float *magData, int appHasChanged);
float getCompassAngle(float *accelData, float *magData);
void compassLights(float compassData);
void compassApp_callOnce();
void LCD_drawCompassApp();
enum Joydir checkJoyDir(nunchuk_t *chuky);
int ledNumberConvert(int led);


void tiltApp(float x, float y, int *dirtyArea, int appHasChanged);
void firstCall();
void cleanDirtyArea(int dirtyX, int dirtyY);
void drawBubble(int x, int y, int *dirtyArea);
void drawMiddleSquare();
void LCD_drawTiltAppScreen();
#endif //_APPS_H_
