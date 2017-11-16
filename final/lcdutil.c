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
                    const char **strlist, 
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
/*
void draw_screen_message(char *message){
    f3d_lcd_fillScreen2(RED);
    //draw_string(10, HEIGHT/2, message, 3, L_SEP,  TEXTCOLOR, BGCOLOR);
}
*/
