/**
 * this file contains game types and constants
 */
#ifndef _GAME_TYPES_H_
#define _GAME_TYPES_H_

#include <f3d_lcd_sd.h>
#include <stdbool.h>

#define SCREEN_HEIGHT ST7735_height
#define SCREEN_WIDTH ST7735_width


//PLAYER STUFF
#define PLAYER_HEIGHT 8
#define PLAYER_WIDTH 4
#define PLAYER_STARTING_X SCREEN_WIDTH/2
#define PLAYER_STARTING_Y SCREEN_HEIGHT/2
#define PLAYER_COLOR RED

//BULLET STUFF
#define BULLET_SIZE 2
#define BULLET_NUM 20 //the size of the bullet buffer
#define BULLET_COLOR WHITE
#define BULLET_BASE_SPEED 2

//ENEMY STUFF
#define ENEMY_WIDTH 8
#define ENEMY_HEIGHT 8
#define ENEMY_COLOR BLUE

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
struct dirty_area{
    int16_t x;
    int16_t y;
    uint8_t width;
    uint8_t height;
};
typedef struct dirty_area DirtyArea;

//16 bytes
struct object{
    int16_t x; 
    int16_t y;
    uint16_t color;
    DirtyArea dirty_area[2];
    uint8_t width;
    uint8_t height;
    uint8_t bullet_fire_rate; //how many game tics must pass before the bullet can be shot again
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
