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
    object_draw(p);
} 
void player_move(Player *p, GDIR dir, int16_t x, int16_t y){
    if (
            (p->x + p->width) + x >= SCREEN_WIDTH   || // right wall
            p->x + x <= 0                           || // left wall
            (p->y + p->height) + y >= SCREEN_HEIGHT || // floor
            p->y + y <= 0                           || //ceiling
            0) return;
    object_move(p, dir, x, y);
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
void object_move(Object *obj, GDIR dir, int16_t x, int16_t y){
    //dirty area allocation
    dirty_area_zeros(&obj->dirty_area[1]);
    if (dir == RIGHT){
        dirty_area_fill_right(obj, 0, x, y);
    } else if (dir == LEFT){
        dirty_area_fill_left(obj, 0, x, y);
    } else if (dir == DOWN){
        dirty_area_fill_down(obj, 0, x, y);
    } else if (dir == UP){
        dirty_area_fill_up(obj, 0, x, y);
    } else if (dir == UP_RIGHT){
        dirty_area_fill_up(obj, 0, x, y);
        dirty_area_fill_right(obj, 1, x, y);
    } else if (dir == UP_LEFT){
        dirty_area_fill_up(obj, 0, x, y);
        dirty_area_fill_left(obj, 1, x, y);
    } else if (dir == DOWN_RIGHT){
        dirty_area_fill_down(obj, 0, x, y);
        dirty_area_fill_right(obj, 1, x, y);
    } else if (dir == DOWN_LEFT){
        dirty_area_fill_down(obj, 0, x, y);
        dirty_area_fill_left(obj, 1, x, y);
    }

    obj->x += x;
    obj->y += y;

}
void object_draw(Object *obj){
    draw_rect(obj->x, obj->y, obj->width, obj->height,  obj->color);
    draw_rect(obj->dirty_area[0].x, obj->dirty_area[0].y, obj->dirty_area[0].width, obj->dirty_area[0].height, BGCOLOR); //erase dirty area
    draw_rect(obj->dirty_area[1].x, obj->dirty_area[1].y, obj->dirty_area[1].width, obj->dirty_area[1].height, BGCOLOR); //erase dirty area
} 

void object_draw_many(Object *obj_arr, uint8_t arr_len){
    int i;
    for(i = 0; i < arr_len; i++){
        Object *obj = &obj_arr[i];
        draw_rect(obj->x, obj->y, obj->width, obj->height,  obj->color);
        draw_rect(obj->dirty_area[0].x, obj->dirty_area[0].y, obj->dirty_area[0].width, obj->dirty_area[0].height, BGCOLOR); //erase dirty area
        draw_rect(obj->dirty_area[1].x, obj->dirty_area[1].y, obj->dirty_area[1].width, obj->dirty_area[1].height, BGCOLOR); //erase dirty area
    }
} 

void object_update_loc_by_speed(Object *o){
    //object_move(o, (int8_t)o->speed, 0);
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





// DirtyArea
void dirty_area_zeros(DirtyArea *d){
    d->x = 0;
    d->y = 0;
    d->width = 0;
    d->height = 0;
}


void dirty_area_fill_right(Player *p, uint8_t area_num, int x, int y){
    p->dirty_area[area_num].x = p->x;
    p->dirty_area[area_num].y = p->y;
    p->dirty_area[area_num].width = min(x, p->width);
    p->dirty_area[area_num].height = p->height;
}
void dirty_area_fill_left(Player *p, uint8_t area_num, int x, int y){
    p->dirty_area[area_num].x = p->x + (p->width -1);
    p->dirty_area[area_num].y = p->y;
    p->dirty_area[area_num].width = min(-x, p->width);
    p->dirty_area[area_num].height = p->height;
}
void dirty_area_fill_down(Player *p, uint8_t area_num, int x, int y){
    p->dirty_area[area_num].x = p->x;
    p->dirty_area[area_num].y = p->y;
    p->dirty_area[area_num].width = p->width;
    p->dirty_area[area_num].height = min(y, p->height);
}
void dirty_area_fill_up(Player *p, uint8_t area_num, int x, int y){
    p->dirty_area[area_num].x = p->x;
    p->dirty_area[area_num].y = p->y + p->height -1; // -1?
    p->dirty_area[area_num].width = p->width;
    p->dirty_area[area_num].height = min(-y, p->height);
}



GDIR getDirection(int16_t x, int16_t y){
    if (x < 0 && y < 0)
        return DOWN_LEFT;
    else if (x > 0 && y < 0)
        return DOWN_RIGHT;
    else if (x < 0 && y > 0)
        return UP_LEFT;
    else if (x > 0 && y > 0)
        return UP_RIGHT;
    else if (x < 0)
        return LEFT;
    else if (x > 0)
        return RIGHT;
    else if (y < 0)
        return UP;
    else if (y > 0)
        return DOWN;
    return NONE;
}
