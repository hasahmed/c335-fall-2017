#ifndef _GENERAL_UTIL_H_
#define _GENERAL_UTIL_H_
#include <stdio.h>
void setBuffs();
void initAll();
#define BLACK 0x0000
#define WHITE 0xFFFF
#define BGCOLOR BLACK
#define DEBUGF(f_, ...) do{ char buf[26]; sprintf(buf, (f_), __VA_ARGS__); draw_string(0, 0, buf, WHITE, BGCOLOR); } while(0);
#endif //_GENERAL_UTIL_H_
