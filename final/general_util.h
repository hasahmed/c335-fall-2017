#ifndef _GENERAL_UTIL_H_
#define _GENERAL_UTIL_H_
#include <stdio.h>
#include <f3d_lcd_sd.h>
#include <stdint.h>
#include "game_util.h"
void setBuffs();
void initAll();
#define DEBUGF(f_, ...) do{\
    char buf[26];\
    sprintf(buf, (f_), __VA_ARGS__);\
    draw_string(0, 0, "HHHHHHHHHHHHHHHHHHHHHHHHH", BGCOLOR, BGCOLOR);\
    draw_string(0, 0, buf, WHITE, BGCOLOR);\
} while(0);
int min(int a, int b);
#endif //_GENERAL_UTIL_H_
