/**
 * this file contains game types and constants
 */
#ifndef _GAME_TYPES_H_
#define _GAME_TYPES_H_

#include <f3d_lcd_sd.h>
#include <stdbool.h>



#define GAME_TICK 20 //ticks/s

#define SCREEN_HEIGHT ST7735_height
#define SCREEN_WIDTH ST7735_width


//SPAWN STUFF
#define SPAWN_COLOR BROWN
#define SPAWN_THICKNESS 4
//upper
#define UPPER_SPAWN_WIDTH SCREEN_WIDTH / 3
#define UPPER_SPAWN_X (SCREEN_WIDTH / 2) - (UPPER_SPAWN_WIDTH / 2)
#define UPPER_SPAWN_Y 0
#define UPPER_SPAWN_HEIGHT SPAWN_THICKNESS
//left
#define LEFT_SPAWN_HEIGHT SCREEN_WIDTH / 3
#define LEFT_SPAWN_WIDTH SPAWN_THICKNESS
#define LEFT_SPAWN_X 0
#define LEFT_SPAWN_Y (SCREEN_HEIGHT / 2) - (LEFT_SPAWN_HEIGHT / 2)
//right
#define RIGHT_SPAWN_HEIGHT SCREEN_WIDTH / 3
#define RIGHT_SPAWN_WIDTH SPAWN_THICKNESS
#define RIGHT_SPAWN_Y (SCREEN_HEIGHT / 2) - (RIGHT_SPAWN_HEIGHT / 2)
#define RIGHT_SPAWN_X (SCREEN_WIDTH - SPAWN_THICKNESS)
//lower
#define LOWER_SPAWN_WIDTH SCREEN_WIDTH / 3
#define LOWER_SPAWN_X (SCREEN_WIDTH / 2) - (LOWER_SPAWN_WIDTH / 2)
#define LOWER_SPAWN_Y (SCREEN_HEIGHT - SPAWN_THICKNESS)
#define LOWER_SPAWN_HEIGHT SPAWN_THICKNESS


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
#define BULLET_BASE_X -(10 + BULLET_SIZE)
#define BULLET_BASE_Y 0

//ENEMY STUFF
#define ENEMIES 10 //number of enemies
#define ENEMY_BASE_SPEED 1;
#define ENEMY_WIDTH 8
#define ENEMY_HEIGHT 8
#define ENEMY_COLOR BLUE
#define ENEMY_BASE_X -(10 + ENEMY_WIDTH)
#define ENEMY_BASE_Y 0

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
    bool used; //is the object active or not
};
typedef struct object Object;
typedef struct object Player;
typedef struct object Enemy;
typedef struct object Bullet;
typedef struct object Spawn;


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
