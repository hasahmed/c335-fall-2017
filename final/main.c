/*
 * Author: Hasan Y Ahmed
 * Lab 11
 * 11/09/17
 */
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <f3d_systick.h>
#include <ff.h>
#include <diskio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stm32f30x_dma.h>
#include <stm32f30x_dac.h>
#include <stdbool.h>
#include "general_util.h"
#include "lcdutil.h"
#include "nunchuk_util.h"
#include "player.h"
#include "game_util.h"
#include "main.h"
#include "game_types.h"

#define SCREEN_HEIGHT ST7735_height
#define SCREEN_WIDTH ST7735_width

#define SPAWN_POINTS 4 //don't change this

//GLOBAL Variables
Player player;
Enemy enemies[ENEMIES];
Bullet bullet_buf[BULLET_NUM];
Spawn spawn_points[SPAWN_POINTS];
Spawn tmp;
struct nunchuk_data nundata;
struct nunchuk_data nundata2;
bool gocalled_once = false;
bool redraw = false;
bool gameover = false;
uint8_t ticks_passed_since_bullet_shot = 0;
uint16_t score = 0;

void draw_game_over_screen(){
    f3d_lcd_fillScreen(BGCOLOR);
    draw_string(10, SCREEN_HEIGHT / 2, "GAME OVER", RED, BGCOLOR);
}

void init_game_objects(){
    bullet_init_many(bullet_buf, BULLET_NUM);
    enemy_init_many(enemies, ENEMIES);
    spawn_init(spawn_points);

    tmp.x = UPPER_SPAWN_X;
    tmp.y = UPPER_SPAWN_Y;
    tmp.width = UPPER_SPAWN_WIDTH;
    tmp.height = UPPER_SPAWN_HEIGHT;
    tmp.color = SPAWN_COLOR;
    tmp.used = true;
}

void gameover_handler(){
    if (!gocalled_once) {
        draw_game_over_screen();
        gocalled_once = true;
    }
}

void update(){
    if (gameover){
        gameover_handler(); //will only be called once per game
        return; //protection from the continued update loop
    }
    ticks_passed_since_bullet_shot++;
    f3d_nunchuk_read(&nundata);
    f3d_nunchuk_read2(&nundata2);
    player_listen_move(&player, &nundata);
    if (ticks_passed_since_bullet_shot >= player.bullet_fire_rate){
        bullet_listen_shoot(&player, bullet_buf, BULLET_NUM, &nundata2);
        ticks_passed_since_bullet_shot = 0;
    }
    object_update_loc_by_speed_and_dir_many(bullet_buf, BULLET_NUM);
    enemy_move_towards_player(&player, &enemies[0]);
    bullet_disable_out(bullet_buf, BULLET_NUM);
    handle_enemy_bullet_player_collision(&player, enemies, ENEMIES, bullet_buf, BULLET_NUM, &score, &gameover);
    redraw = true;
}

int main(void) { 
    setBuffs();
    initAll();
    printf("////////////////////////////////////////////////////////////\n");
    init_game_objects();
    init_game_screen(&player);
    object_draw(&tmp);
    /*object_draw_many(spawn_points, SPAWN_POINTS);*/
    enemy_place(&enemies[0], 10, 10);

    setTickSpeed(GAME_TICK);
    /*DEBUGF("sizeof Object %lu", sizeof(Object));*/
    while(1){
        if (redraw) {
            player_draw(&player);
            object_draw_many(bullet_buf, BULLET_NUM);
            object_draw_many(enemies, ENEMIES);
            object_draw_many(spawn_points, SPAWN_POINTS);
            redraw = false;
        }
        /*debugDirection(enemy_get_player_direction(&player, &enemies[0]));*/
        /*DEBUGF_CLEAR_LINE(10, "getAngle %.2f", getAngle(&player, &enemies[0]));*/
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
}
#endif


/* main.c ends here */
