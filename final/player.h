#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <stdint.h>
#include <f3d_nunchuk.h>
#include <stdio.h>
#include "game_util.h"
#include "game_types.h"
void player_init(Player *p, int16_t x, int16_t y, uint8_t width, uint8_t height, uint16_t color);
void player_draw(Player *p);
void player_move(Player *p, int16_t x, int16_t y);
void player_listen_move(Player *p, struct nunchuk_data *nundata);
//enemy stuff
void enemies_draw(Enemy *enemy_list, uint8_t enemy_list_len);
void enemy_move_towards_player(Player *p, Enemy *e);
void enemy_move_towards_player_many(Player *p, Enemy *enemy_list, uint8_t enemy_list_len);
GDIR enemy_get_player_direction(Player *p, Enemy *e);
void enemy_reset(Enemy *e);
void enemy_reset_many(Enemy *enemy_list, uint8_t enemy_list_len);
void enemy_init(Enemy *e);
void enemy_init_many(Enemy *enemy_list, uint8_t enemy_list_len);


void handle_enemy_bullet_collision(Enemy *enemies_list, uint8_t enemies_list_len, Bullet *active_bullets_list, uint8_t bullets_list_len, uint16_t *score);


//bullet stuff
void bullet_move(Bullet *b, int16_t x, int16_t y);
void bullet_listen_shoot(Player *p, Bullet *bullet_buf, uint8_t bullet_buf_length, struct nunchuk_data *nundata);
void bullet_disable_out(Bullet *bullet_arr, uint8_t arr_len);
void bullet_reset(Bullet *b);
void bullet_init(Bullet *b);


//object stuff
bool object_check_collision(Object *obj1, Object *obj2);
void object_draw(Object *obj);
void object_draw_many(Object *obj_arr, uint8_t arr_len);
void object_move(Object *obj, int16_t x, int16_t y);
void object_update_loc_by_speed_and_dir(Object *o);
void object_update_loc_by_speed_and_dir_many(Object *object_arr, uint8_t arr_len);
void object_print(Object *o);
bool object_is_out(Object *o);


// DirtyArea
void dirty_area_zeros(DirtyArea *d);
void dirty_area_fill_right(Player *p, uint8_t area_num, int x, int y);
void dirty_area_fill_left(Player *p, uint8_t area_num, int x, int y);
void dirty_area_fill_down(Player *p, uint8_t area_num, int x, int y);
void dirty_area_fill_up(Player *p, uint8_t area_num, int x, int y);


//misc

void debugDirection(GDIR dir);
GDIR getDirection(int16_t x, int16_t y);
#endif //_PLAYER_H_
