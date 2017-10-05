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
#define BARWIDTH 12 //the width of the bar in the bar graph

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
void drawPositiveBar(float amount, uint16_t color, uint16_t bgColor){
    
}


int main(void) {
    //inits
    f3d_uart_init();
    f3d_gyro_init();
    f3d_led_init();
    f3d_user_btn_init();
    f3d_lcd_init();

    f3d_lcd_fillScreen2(BLACK);
    drawString(10, 10, "Hasan loves Katie!", RED, BLACK);

    drawMiddleLine(RED);

    while(1){


        /*
           int TIME = 2000;
           f3d_lcd_fillScreen2(RED);
           delay(TIME);
           f3d_lcd_fillScreen2(BLACK);
           delay(TIME);
           f3d_lcd_fillScreen2(BLUE);
           delay(TIME);
           f3d_lcd_fillScreen2(CYAN);
           delay(TIME);
           f3d_lcd_fillScreen2(GREEN);
           delay(TIME);
           f3d_lcd_fillScreen2(MAGENTA);
           delay(TIME);
           f3d_lcd_fillScreen2(YELLOW);
           delay(TIME);
           f3d_lcd_fillScreen2(WHITE);
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
