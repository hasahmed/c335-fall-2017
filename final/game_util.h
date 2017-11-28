#ifndef _GAME_UTIL_H_
#define _GAME_UTIL_H_
#include <f3d_lcd_sd.h>
#include "player.h"

//player stuff
#define SCREEN_HEIGHT ST7735_height
#define SCREEN_WIDTH ST7735_width
#define PLAYER_HEIGHT 8
#define PLAYER_WIDTH 4
#define PLAYER_STARTING_X SCREEN_WIDTH/2
#define PLAYER_STARTING_Y SCREEN_HEIGHT/2
#define PLAYER_COLOR RED

//bg stuff
#define BGCOLOR BLACK //testing
void init_game_screen(Player *p);

enum dir{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    NA
};
//typedef enum dir DIR;
typedef enum dir GDIR;
#endif //_GAME_UTIL_H_
