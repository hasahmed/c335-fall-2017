#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <stdint.h>
#include <f3d_nunchuk.h>
#include "game_util.h"
#include "game_types.h"
void player_init(Player *p, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color);
void player_draw(Player *p);
void player_move(Player *p, int8_t x, int8_t y);
void player_listen_move(Player *p, struct nunchuk_data *nundata);
//enemy stuff
void enemies_draw(Player *enemy_list, uint8_t enemy_list_len);


//bullet stuff
void bullet_move(Bullet *b, int8_t x, int8_t y);
void bullet_listen_shoot(Player *p, Bullet *b, struct nunchuk_data *nundata);


//general object stuff
void object_move(Object *o, int8_t x, int8_t y);
void object_update_loc_by_speed(Object *o);
#endif //_PLAYER_H_
