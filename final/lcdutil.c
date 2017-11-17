#ifndef _LCD_UTIL_H_
#define _LCD_UTIL_H_
#include <f3d_lcd_sd.h>
#include "lcdutil.h"
#define HEIGHT ST7735_height
#define WIDTH ST7735_width
void draw_string(int startx, int y, const char *str, uint16_t charColor, uint16_t charBGColor){
    int i = 0;
    while(str[i] != '\0'){
        f3d_lcd_drawChar(startx + (i * CHARSTEP), y, str[i], charColor, charBGColor);
        i++;
    }
}
void draw_stringlist(int startx, 
                    int starty, 
                    char **strlist, 
                    unsigned int arr_len, 
                    unsigned int linegap, 
                    uint16_t charColor, 
                    uint16_t charBGColor){
    int i;
    for(i = 0; i < arr_len; i++){
        draw_string(startx, starty + (linegap * i), strlist[i], charColor, charBGColor);
    }
}

void draw_rect(int x, int y, int width, int height,  uint16_t color) {
    //draw middle square
    int i, j;
    for(i = 0; i < width; i++){ //horizontal
        for(j = 0; j < height; j++){ //vertical
            f3d_lcd_drawPixel(x + i, y + j, color);
        }
    }
}
#endif //_LCD_UTIL_H_
