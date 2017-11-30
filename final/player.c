#include <f3d_nunchuk.h>
#include <stdio.h>
#include "nunchuk_util.h"
#include "player.h"
#include "general_util.h" //includes game_util.h
#include "game_util.h"
#include "game_types.h"

void player_init(Player *p, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color){
    p->x = x;
    p->y = y;
    p->width = width;
    p->height = height;
    p->color = color;
    p->speed = 0;
}
void player_draw(Player *p){
    draw_rect(p->x, p->y, p->width, p->height,  p->color);
}
void player_move(Player *p, int8_t x, int8_t y){
    if (
            (p->x + p->width) + x >= SCREEN_WIDTH   ||
            p->x + x <= 0                           ||
            (p->y + p->height) + y >= SCREEN_HEIGHT ||
            p->y + y <= 0) return;
    p->x += x;
    p->y += y;
}

void player_listen_move(Player *p, struct nunchuk_data *nundata){
    uint8_t player_speed = 1;
    GDIR dir = get_nunchuk_dir(nundata);
    switch(dir){
        case UP:
            player_move(p, 0, -player_speed);
            break;
        case UP_LEFT:
            player_move(p, -player_speed, -player_speed);
            break;
        case UP_RIGHT:
            player_move(p, player_speed, -player_speed);
            break;
        case DOWN:
            player_move(p, 0, player_speed);
            break;
        case DOWN_LEFT:
            player_move(p, -player_speed, player_speed);
            break;
        case DOWN_RIGHT:
            player_move(p, player_speed, player_speed);
            break;
        case LEFT:
            player_move(p, -player_speed, 0);
            break;
        case RIGHT:
            player_move(p, player_speed, 0);
            break;
    }
}
//ENEMIES
void enemies_draw(Player *enemy_list, uint8_t enemy_list_len) {
    uint8_t i = 0;
    for(i = 0; i < enemy_list_len; i++)
        player_draw(&enemy_list[i]);
}

//BULLETS
void bullet_move(Bullet *b, int8_t x, int8_t y){
    b->x += x;
    b->y += y;
}
void bullet_listen_shoot(Player *p, Bullet *b, struct nunchuk_data *nundata){
    if(nundata->c == 1){
        b->speed = 2;
        b->x = p->x;
        b->y = p->y;
        //b->dir = RIGHT;
        //b->speed = 1;
    }
}

//OBJECTS (general)

void object_move(Object *o, int8_t x, int8_t y){
    o->x += x;
    o->y += y;
}

void object_update_loc_by_speed(Object *o){
    object_move(o, (int8_t)o->speed, 0);
    /*
    switch(o->dir){
        case UP:
            object_move(o, (int8_t)o->speed, (int8_t)o->speed);
            return;
        case DOWN:
            object_move(o, (int8_t)o->speed, (int8_t)o->speed);
            return;
        case LEFT:
            object_move(o, (int8_t)o->speed, (int8_t)o->speed);
            return;
        case RIGHT:
            object_move(o, (int8_t)o->speed, (int8_t)o->speed);
            return;
        case UP_LEFT:
            object_move(o, (int8_t)o->speed, (int8_t)o->speed);
            return;
        case UP_RIGHT:
            object_move(o, (int8_t)o->speed, (int8_t)o->speed);
            return;
        case DOWN_LEFT:
            object_move(o, (int8_t)o->speed, (int8_t)o->speed);
            return;
        case DOWN_RIGHT:
            object_move(o, (int8_t)o->speed, (int8_t)o->speed);
            return;
    }
    */
}
