#ifndef _GAME_TYPES_H_
#define _GAME_TYPES_H_

#include <f3d_lcd_sd.h>
#include <stdbool.h>

#define SCREEN_HEIGHT ST7735_height
#define SCREEN_WIDTH ST7735_width
#define PLAYER_HEIGHT 8
#define PLAYER_WIDTH 4
#define PLAYER_STARTING_X SCREEN_WIDTH/2
#define PLAYER_STARTING_Y SCREEN_HEIGHT/2
#define PLAYER_COLOR RED

//BULLET STUFF
#define BULLET_SIZE 2
#define BULLET_NUM 10

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

enum gtype{
    PLAYER,
    ENEMY,
    BULLET,
    POWERUP,
    NONE
};
typedef enum gtype GTYPE;

enum ptype {
    SPEED,
    RAPID_FIRE,
    EIGHT_DIR
};
typedef enum ptype PTYPE;

struct object{
    int16_t x; 
    int16_t y;
    uint16_t color;
    uint8_t width;
    uint8_t height;
    float speed;
    GDIR dir;
    GTYPE type;
    PTYPE powerup;
    bool used; //for bullet
};
typedef struct object Object;
typedef struct object Player;
typedef struct object Enemy;
typedef struct object Bullet;


/* thinking about having a seperate bullet struct to save the space. Color would not be needed
struct bullet{
    int16_t x;
    int16_t y;
    uint16_t color;
    uint8_t width;
    uint8_t height;
    GDIR dir;
    float speed;
};
*/

#endif //_GAME_TYPES_H_
