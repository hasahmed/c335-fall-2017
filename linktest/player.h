#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <stdint.h>
struct player{
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
    uint16_t color;
};
typedef struct player Player;
void player_init(Player *p, uint8_t player_x, uint8_t player_y, uint8_t player_width, uint8_t player_height, uint16_t player_color);
void player_draw(Player *p);
#endif //_PLAYER_H_
