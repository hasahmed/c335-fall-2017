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
    p->bullet_fire_rate = 10;
}
void player_draw(Player *p){
    object_draw(p);
} 
void player_move(Player *p, int16_t x, int16_t y){
    if (
            (p->x + p->width) + x >= SCREEN_WIDTH   || // right wall
            p->x + x <= 0                           || // left wall
            (p->y + p->height) + y >= SCREEN_HEIGHT || // floor
            p->y + y <= 0                           || //ceiling
            0) return;
    object_move(p, x, y);
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
void enemy_move_towards_player_many(Player *p, Enemy *enemy_list, uint8_t enemy_list_len){

}
void enemy_init_many(Enemy *enemy_list, uint8_t enemy_list_len){
    uint8_t i;
    for (i = 0; i < enemy_list_len; i++)
        enemy_init(&enemy_list[i]);
}

void enemy_init(Enemy *e){
    e->x = -10;
    e->y = 100;
    e->width = ENEMY_WIDTH;
    e->height = ENEMY_HEIGHT;
    e->color = ENEMY_COLOR;
    e->speed = 0;
    e->used = false;
}
void enemy_reset(Enemy *e){
    e->x = -10;
    e->y = 100;
    e->speed = 0;
    e->used = false;
}

/**
 * assumes inactive bullets are are already deactivated
 */
void handle_enemy_bullet_collision(Enemy *enemies_list, uint8_t enemies_list_len, Bullet *active_bullets_list, uint8_t bullets_list_len, uint16_t *score){
    uint8_t i;
    uint8_t j;
    for (i = 0; i < enemies_list_len; i++){
        for (j = 0; j < bullets_list_len; j++){
            if (object_check_collision(&active_bullets_list[j], &enemies_list[i])){
                enemy_reset(&enemies_list[i]);
                bullet_reset(&active_bullets_list[j]);
            }
        }
    }
}

void enemy_move_towards_player(Player *p, Enemy *e){
    GDIR dir = enemy_get_player_direction(p, e);
    e->dir = dir;
    object_update_loc_by_speed_and_dir(e);
}

GDIR enemy_get_player_direction(Player *p, Enemy *e){
    float angle = getAngle(p, e);
    if ((angle <= -160.0 && angle >= -180.0) || (angle <= 180 && angle >= 160.0))
        return LEFT;
    else if (angle >= 70.0 && angle <= 110.0)
        return DOWN;
    else if (angle >= -10.0 && angle <= 10.0)
        return RIGHT;
    else if (angle >= -110.0 && angle <= -70.0)
        return UP;
    return NA;
}

//BULLETS
void bullet_move(Bullet *b, int16_t x, int16_t y){
    b->x += x;
    b->y += y;
}


/**
 * disables bullet if its out of bounds
 */
void bullet_disable_out(Bullet *bullet_arr, uint8_t arr_len){
    uint8_t i;
    for (i = 0; i < arr_len; i++){
        if (bullet_arr[i].used == true){
            if (object_is_out(&bullet_arr[i])){
                bullet_reset(&bullet_arr[i]);
            } 
        }
    }
}

void bullet_reset(Bullet *b){
    b->x = -10;
    b->y = -10;
    b->used = false;
    b->speed = 0;
}
bool object_is_out(Object *o){
    if (
            o->x > SCREEN_WIDTH || 
            o-> x < 0 ||
            o-> y > SCREEN_HEIGHT ||
            o-> y < 0
       )
        return true;
    return false;
}

void bullet_init(Bullet *b){
    b->speed = 0;
    b->x = -10;
    b->y = -10;
    b->color = WHITE;
    b->width = BULLET_SIZE;
    b->height = BULLET_SIZE;
    b->used = false;
}

void bullet_listen_shoot(Player *p, Bullet *bullet_buf, uint8_t bullet_buf_length, struct nunchuk_data *nundata){
    uint8_t i;
    GDIR dir = get_nunchuk_dir(nundata);
    if(dir != NA){
        for (i = 0; i < bullet_buf_length; i++){
            if (bullet_buf[i].used == false){
                bullet_buf[i].x = p->x + p->width;
                bullet_buf[i].y = p->y;
                bullet_buf[i].dir = dir;
                bullet_buf[i].speed = BULLET_BASE_SPEED;
                bullet_buf[i].used = true;
                return;
            }
        }
    }
}

//OBJECTS (general)


void object_move(Object *obj, int16_t x, int16_t y){
    GDIR dir = getDirection(x, y);
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

//void object_move_many(Object *object_arr, uint8_t arr_len, )
void object_draw(Object *obj){
    draw_rect(obj->x, obj->y, obj->width, obj->height,  obj->color);
    draw_rect(obj->dirty_area[0].x, obj->dirty_area[0].y, obj->dirty_area[0].width, obj->dirty_area[0].height, BGCOLOR); //erase dirty area
    draw_rect(obj->dirty_area[1].x, obj->dirty_area[1].y, obj->dirty_area[1].width, obj->dirty_area[1].height, BGCOLOR); //erase dirty area
} 

void object_draw_many(Object *obj_arr, uint8_t arr_len){
    int i;
    for(i = 0; i < arr_len; i++){
        object_draw(&obj_arr[i]);
    }
} 

bool object_check_collision(Object *obj1, Object *obj2){
    if (
            (obj1->y <= obj2->y + obj2->width) && //up
            //down
            //left
            //right
            //if (obj1->x + obj1->width);
            1)
        return false;
    return false;
}

void object_update_loc_by_speed_and_dir(Object *o){
    switch(o->dir){
        case UP:
            object_move(o, 0, -(int8_t)o->speed);
            return;
        case DOWN:
            object_move(o, 0, (int8_t)o->speed);
            return;
        case LEFT:
            object_move(o, -(int8_t)o->speed, 0);
            return;
        case RIGHT:
            object_move(o, (int8_t)o->speed, 0);
            return;
        case UP_LEFT:
            object_move(o, -(int8_t)o->speed, -(int8_t)o->speed);
            return;
        case UP_RIGHT:
            object_move(o, (int8_t)o->speed, -(int8_t)o->speed);
            return;
        case DOWN_LEFT:
            object_move(o, -(int8_t)o->speed, (int8_t)o->speed);
            return;
        case DOWN_RIGHT:
            object_move(o, (int8_t)o->speed, (int8_t)o->speed);
            return;
    }
}

void object_update_loc_by_speed_and_dir_many(Object *object_arr, uint8_t arr_len){
    uint8_t i;
    for(i = 0; i < arr_len; i++){
        object_update_loc_by_speed_and_dir(&object_arr[i]);
    }
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


// MAY NEED MULTIPLE CASES FOR WHEN NUMBER IS > THAN WIDTH/HEIGHT OF PLAYER
// BUT I THINK IT CAN BE DONE WITHOUT THAT
void dirty_area_fill_right(Player *p, uint8_t area_num, int x, int y){
    p->dirty_area[area_num].x = p->x;
    p->dirty_area[area_num].y = p->y;
    p->dirty_area[area_num].width = min(x, p->width);
    p->dirty_area[area_num].height = p->height;
}
void dirty_area_fill_left(Player *p, uint8_t area_num, int x, int y){
    p->dirty_area[area_num].y = p->y;
    if (-x > p->width)
        p->dirty_area[area_num].x = p->x;
    else
        p->dirty_area[area_num].x = p->x + x + p->width;
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
    p->dirty_area[area_num].x = p->x; //assign x. Easy
    if (-y > p->height)
        p->dirty_area[area_num].y = p->y + y + p->height + (-y - p->height);
    else
        p->dirty_area[area_num].y = p->y + (p->height + y);
    p->dirty_area[area_num].width = p->width;
    p->dirty_area[area_num].height = min(-y, p->height);
}



GDIR getDirection(int16_t x, int16_t y){
    if (x < 0 && y > 0)
        return DOWN_LEFT;
    else if (x > 0 && y > 0)
        return DOWN_RIGHT;
    else if (x < 0 && y < 0)
        return UP_LEFT;
    else if (x > 0 && y < 0)
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
void debugDirection(GDIR dir){
    switch(dir){
        case UP:
            DEBUGF("UP", NULL);
            return;
        case DOWN:
            DEBUGF("DOWN", NULL);
            return;
        case LEFT:
            DEBUGF("LEFT", NULL);
            return;
        case RIGHT:
            DEBUGF("RIGHT", NULL);
            return;
        case UP_RIGHT:
            DEBUGF("UP_RIGHT", NULL);
            return;
        case UP_LEFT:
            DEBUGF("UP_LEFT", NULL);
            return;
        case DOWN_RIGHT:
            DEBUGF("DOWN_RIGHT", NULL);
            return;
        case DOWN_LEFT:
            DEBUGF("DOWN_LEFT", NULL);
            return;
        case NA:
            DEBUGF("NA", NULL);
            return;
    }

}
