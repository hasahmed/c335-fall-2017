#ifndef _LCDUTIL_H_
#define _LCDUTIL_H_
#define CHARSTEP 6 //the amount of space to put between characters
#define HEIGHT ST7735_height
#define WIDTH ST7735_width
#include <stdint.h>

void draw_string(int startx, int y, const char *str, uint16_t charColor, uint16_t charBGColor);
void draw_stringlist(int startx, 
                    int starty, 
                    char **strlist, 
                    unsigned int arr_len, 
                    unsigned int linegap, 
                    uint16_t charColor, 
                    uint16_t charBGColor);
void draw_rect(int x, int y, int width, int height,  uint16_t color);
#endif
