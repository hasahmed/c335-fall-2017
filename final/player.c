#include <f3d_nunchuk.h>
#include <stdio.h>
#include <stdlib.h>
#include "nunchuk_util.h"
#include "player.h"
#include "general_util.h" //includes game_util.h
#include "game_util.h"
#include "game_types.h"

void player_init(Player *p, int16_t x, int16_t y, uint8_t width, uint8_t height, uint16_t color){
    p->x = x;
    p->y = y;
    p->width = width;
    p->height = height;
    p->color = color;
    p->speed = 0;
}
void player_draw(Player *p){
    draw_rect(p->x, p->y, p->width, p->height,  p->color);
    draw_rect(p->dirty_area.x, p->dirty_area.y, p->dirty_area.width, p->dirty_area.height, BGCOLOR); //erase dirty area
} 
void player_move(Player *p, GDIR dir, int16_t x, int16_t y){
    if (
            (p->x + p->width) + x >= SCREEN_WIDTH   || // right wall
            p->x + x <= 0                           || // left wall
            (p->y + p->height) + y >= SCREEN_HEIGHT || // floor
            p->y + y <= 0                           || //ceiling
            0) return;
    //dirty area allocation
    if (dir == RIGHT){
        p->dirty_area.x = p->x;
        p->dirty_area.y = p->y;
        p->dirty_area.width = min(x, p->width);
        p->dirty_area.height = p->height;
    } else if (dir == LEFT){
        p->dirty_area.x = p->x + (p->width -1);
        p->dirty_area.y = p->y;
        p->dirty_area.width = min(-x, p->width);
        p->dirty_area.height = p->height;
    } else if (dir == DOWN){
        p->dirty_area.x = p->x;
        p->dirty_area.y = p->y;
        p->dirty_area.width = p->width;
        p->dirty_area.height = min(y, p->height);
    } else if (dir == UP){
        p->dirty_area.x = p->x;
        p->dirty_area.y = p->y + p->height -1; // -1?
        p->dirty_area.width = p->width;
        p->dirty_area.height = min(-y, p->height);
    }




    p->x += x;
    p->y += y;

}

void player_listen_move(Player *p, struct nunchuk_data *nundata){
    uint8_t player_speed = 1;
    GDIR dir = get_nunchuk_dir(nundata);
    switch(dir){
        case UP:
            player_move(p, UP, 0, -player_speed);
            break;
        case UP_LEFT:
            player_move(p, UP_LEFT, -player_speed, -player_speed);
            break;
        case UP_RIGHT:
            player_move(p, UP_RIGHT, player_speed, -player_speed);
            break;
        case DOWN:
            player_move(p, DOWN, 0, player_speed);
            break;
        case DOWN_LEFT:
            player_move(p, DOWN_LEFT, -player_speed, player_speed);
            break;
        case DOWN_RIGHT:
            player_move(p, DOWN_RIGHT, player_speed, player_speed);
            break;
        case LEFT:
            player_move(p, LEFT, -player_speed, 0);
            break;
        case RIGHT:
            player_move(p, RIGHT, player_speed, 0);
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
void bullet_move(Bullet *b, int16_t x, int16_t y){
    b->x += x;
    b->y += y;
}
void bullet_listen_shoot(Player *p, Bullet *bullet_buf, uint8_t bullet_buf_length, struct nunchuk_data *nundata){
    GDIR dir = get_nunchuk_dir(nundata);
    if(dir != NA){
        //b->speed = 2;
        //b->x = p->x;
        //b->y = p->y;
        //b->dir = RIGHT;
        //b->speed = 1;
    }
}

//OBJECTS (general)

void object_move(Object *o, int16_t x, int16_t y){
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
void object_print(Object *o){
    printf("x: %d\n", o->x);
    printf("y: %d\n", o->y);
    printf("width: %u\n", o->width);
    printf("height: %u\n", o->height);
    printf("color: %u\n", o->color);
    printf("speed: %f\n", o->speed);
    printf("GDIR: %d\n", o->dir);
    printf("GTYPE: %d\n", o->type);
    printf("PTYPE: %d\n", o->powerup);
    printf("used: %d\n", o->used);
}
