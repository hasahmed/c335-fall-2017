#include <f3d_lcd_sd.h>
#include <f3d_led.h>
#include "apps.h"

void firstCall(){
    f3d_led_all_off();
    LCD_drawTiltAppScreen();
}

void tiltApp(float x, float y, int *dirtyArea, int appHasChanged){
    if (appHasChanged)
        firstCall();
    cleanDirtyArea(dirtyArea[0], dirtyArea[1]);
    drawMiddleSquare();
    drawBubble(x, y, dirtyArea);
}

void cleanDirtyArea(int dirtyX, int dirtyY){
    int bubbleOffset = -2;
    int bubbleSize = SQUARESIZE + bubbleOffset;
    int i, j;
    for(i = 0; i < bubbleSize; i++) { //horizontal
        for(j = 0; j < bubbleSize; j++) { //vertical
            f3d_lcd_drawPixel(dirtyX + i, dirtyY + j, BLACK);
        }
    }

}

void drawBubble(int x, int y, int* dirtyArea){
    int bubbleOffset = -2;
    int bubbleSize = SQUARESIZE + bubbleOffset;
    int i, j;
    int drawX = ((SQUARE_START_X) + bubbleOffset) + (int)y;
    int drawY = ((SQUARE_START_Y) + bubbleOffset) + (int)x;
    for(i = 0; i < bubbleSize; i++) { //horizontal
        for(j = 0; j < bubbleSize; j++) { //vertical
            f3d_lcd_drawPixel(drawX + i, drawY + j, WHITE);
        }
    }
    dirtyArea[0] = drawX;
    dirtyArea[1] = drawY;
}

void drawMiddleSquare() {
    //draw middle square
    int i, j;
    for(i = 0; i < SQUARESIZE; i++){ //horizontal
        for(j = 0; j < SQUARESIZE; j++){ //vertical
            if ((j == 0 || j == SQUARESIZE -1) || (i == 0 || i == SQUARESIZE -1))
                f3d_lcd_drawPixel(SQUARE_START_X + i, SQUARE_START_Y + j, WHITE);
        }
    }
}

void LCD_drawTiltAppScreen() {
    f3d_lcd_fillScreen2(BLACK);
    //drawString(12, HEIGHT / 2, "This The Tilt App", RED, BLACK); 
}
