#ifndef _GAME_TYPES_H_
#define _GAME_TYPES_H_



#include <f3d_lcd_sd.h>

#define SCREEN_HEIGHT ST7735_height
#define SCREEN_WIDTH ST7735_width
#define PLAYER_HEIGHT 8
#define PLAYER_WIDTH 4
#define PLAYER_STARTING_X SCREEN_WIDTH/2
#define PLAYER_STARTING_Y SCREEN_HEIGHT/2
#define PLAYER_COLOR RED

//bg stuff
#define BGCOLOR BLACK //testing
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
typedef enum dir GDIR;

struct object{
    int8_t x;
    int8_t y;
    uint8_t width;
    uint8_t height;
    uint8_t speed;
    uint16_t color;
    GDIR dir;
};
typedef struct object Player;
typedef struct object Enemy;
typedef struct object Bullet;
#endif //_GAME_TYPES_H_
