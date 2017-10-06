/* main.c ---
 *
 * Filename: main.c
 * Description:
 * Author: Hasan Y Ahmed
 * Maintainer:
 * Created: Thu Jan 10 11:23:43 2013
/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h> // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>

#define CHARSTEP 6 //the amount of space to put between characters
#define BARWIDTH 4 //the width of the bar in the bar graph
#define HEIGHT ST7735_height
#define WIDTH ST7735_width

void drawString(int startx, int y, const char *str, uint16_t charColor, uint16_t charBGColor){
    int i = 0;
    while(str[i] != '\0'){
        f3d_lcd_drawChar(startx + (i * CHARSTEP), y, str[i], charColor, charBGColor);
        i++;
    }
}


void bannerString(int speed, int y, const char *str, uint16_t strColor, uint16_t strBGColor){ //mess with this later
    f3d_lcd_fillScreen2(strBGColor);
    int i = 0;
    int drawx = 0;
    while(1){
        if (drawx > ST7735_width -1) //for wrapping
            drawx = 0;
        //f3d_lcd_fillScreen2(strBGColor);
        drawString(drawx , y, str, strColor, strBGColor);
        i++;
        drawx += speed;
    }
}



void drawMiddleLine(uint16_t color){
    int height = ST7735_height;
    int width = ST7735_width;
    int i = 0;
    printf("%d\n", width / 2);
    for(i; i < width; i++)
        f3d_lcd_drawPixel(i, height / 2, color);

}

//bg color needed to 'erase' the part of the bar that shouldn't be showing
void drawPositiveBar(int starting_x, float amount, uint16_t color, uint16_t bgColor){
    int i;
    int j;
    uint8_t halfHeight = (HEIGHT / 2) - 1;
    for(i = 0; i < BARWIDTH; i++){ //the x
        for(j = 0; j < amount; j++){ //the y
            if ((float)halfHeight - ((float)j/3) <= 0)
                break;
            f3d_lcd_drawPixel(starting_x + i, (float)halfHeight - ((float)j/3), color);
        }
    }
}


void clearVerticalStrip(uint8_t initial_x, uint16_t bgColor){
    uint8_t i;
    uint16_t j;
    for(i = 0; i < BARWIDTH; i++){
        for(j = 0; j < HEIGHT / 2; j++){
            //if (j != HEIGHT / 2) //protect the middle white line
                f3d_lcd_drawPixel(initial_x + i, j, bgColor);
        }
    }
}

void drawLedgend(int x, int y, uint16_t xcolor, uint16_t ycolor, uint16_t zcolor, uint16_t bgcolor){
    f3d_lcd_drawChar(x, y, 'X', xcolor, bgcolor);
    f3d_lcd_drawChar(x * 2, y, 'Y', ycolor, bgcolor);
    f3d_lcd_drawChar(x * 3, y, 'Z', zcolor, bgcolor);
}


void drawBar(int starting_x, float *amount, char axis, uint16_t color, uint16_t bgColor){
    uint8_t index = axis == 'X' ? 0 : axis == 'Y' ? 1 : axis == 'Z' ? 2 : 0;
    drawPositiveBar(starting_x, amount[index], color, bgColor);
}



int main(void) {
    //inits
    f3d_uart_init();
    f3d_gyro_init();
    f3d_led_init();
    f3d_user_btn_init();
    f3d_lcd_init();


    uint16_t BGCOLOR = BLACK;
    uint16_t XCOLOR = BLUE;
    uint16_t YCOLOR = GREEN;
    uint16_t ZCOLOR = WHITE;

    uint8_t WIDTHBY3 = WIDTH / 4;
    int BARSTART_X = WIDTHBY3;
    int BARSTART_Y = WIDTHBY3 * 2;
    int BARSTART_Z = WIDTHBY3 * 3;

    f3d_lcd_fillScreen2(BGCOLOR);
    drawString(34, HEIGHT - 12, "Gyro Axes", RED, BGCOLOR); 
    drawMiddleLine(WHITE);
    drawLedgend(WIDTHBY3, (HEIGHT / 2) + 4, XCOLOR, YCOLOR, ZCOLOR, BGCOLOR);


    float gyroData[3];

    while(1){
        clearVerticalStrip(BARSTART_X, BGCOLOR);
        clearVerticalStrip(BARSTART_Y, BGCOLOR);
        clearVerticalStrip(BARSTART_Z, BGCOLOR);
        f3d_gyro_getdata(gyroData);
        drawBar(BARSTART_X, gyroData, 'X', XCOLOR, BGCOLOR);
        drawBar(BARSTART_Y , gyroData, 'Y', YCOLOR, BGCOLOR);
        drawBar(BARSTART_Z , gyroData, 'Z', ZCOLOR, BGCOLOR);
        /*
        sprintf(x_axis, "X: %f", gyroData[0]);
        sprintf(y_axis, "Y: %f", gyroData[1]);
        sprintf(z_axis, "Z: %f", gyroData[2]);
        drawString(10, 25, x_axis, RED, BLACK);
        drawString(10, 35, y_axis, RED, BLACK);
        drawString(10, 45, z_axis, RED, BLACK);
        */
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
