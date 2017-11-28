#ifndef _GAME_OBJS_H_
#define _GAME_OBJS_H_
#include <stdint.h>
#include <f3d_nunchuk.h>
struct bullet{
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
    uint16_t color;
};
typedef struct bullet Bullet;
void player_init(Player *p, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color);
void player_draw(Player *p);
void player_move(Player *p, int8_t x, int8_t y);
void player_listen_move(Player *p, struct nunchuk_data *nundata);
//enemy stuff
void enemies_draw(Player *enemy_list, uint8_t enemy_list_len);
#endif //_GAME_OBJS_H_
