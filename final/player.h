#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <stdint.h>
#include <f3d_nunchuk.h>
#include <stdio.h>
#include "game_util.h"
#include "game_types.h"
void player_init(Player *p, int16_t x, int16_t y, uint8_t width, uint8_t height, uint16_t color);
void player_draw(Player *p);
void player_move(Player *p, GDIR dir, int16_t x, int16_t y);
void player_listen_move(Player *p, struct nunchuk_data *nundata);
//enemy stuff
void enemies_draw(Player *enemy_list, uint8_t enemy_list_len);


//bullet stuff
void bullet_move(Bullet *b, int16_t x, int16_t y);
void bullet_listen_shoot(Player *p, Bullet *bullet_buf, uint8_t bullet_buf_length, struct nunchuk_data *nundata);


//general object stuff
void object_move(Object *o, int16_t x, int16_t y);
void object_update_loc_by_speed(Object *o);
void object_print(Object *o);


// DirtyArea
void dirty_area_zeros(DirtyArea *d);
void dirty_area_fill_right(Player *p, uint8_t area_num, int x, int y);
void dirty_area_fill_left(Player *p, uint8_t area_num, int x, int y);
void dirty_area_fill_down(Player *p, uint8_t area_num, int x, int y);
void dirty_area_fill_up(Player *p, uint8_t area_num, int x, int y);
#endif //_PLAYER_H_
