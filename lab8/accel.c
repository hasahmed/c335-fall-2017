#include <f3d_lcd_sd.h>
#include "displayFunctions.h"

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

void drawAccel() {
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

