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
#include "general_util.h"
#include "lcdutil.h"
#include "nunchuk_util.h"
#include "player.h"
#include "game_util.h"
#include "main.h"
#include "game_types.h"

#define SCREEN_HEIGHT ST7735_height
#define SCREEN_WIDTH ST7735_width
#define ENEMIES 5
#define ENEMY_WIDTH 8
#define ENEMY_HEIGHT 8
#define ENEMY_COLOR BLUE

Player player;
Enemy enemies[ENEMIES];
Bullet b;
struct nunchuk_data nundata;
int redraw = 0;

void init_enemies(Player *enemies_list){
    int i;
    for (i = 1; i < ENEMIES; i++){
        enemies[i].x = i * ENEMY_WIDTH + i;
        enemies[i].y = i * ENEMY_WIDTH + i;
        enemies[i].width = ENEMY_WIDTH;
        enemies[i].height = ENEMY_HEIGHT;
        enemies[i].color = ENEMY_COLOR;
    }
}

void move_enemies(Player *enemies_list){
    int i = 0;
    for (i = 0; i < ENEMIES; i++){
        player_move(&enemies[i], 1, 0);
    }
}

void bullet_init(Bullet *b){
    b->speed = 0;
    b->x = 10;
    b->y = 10;
    b->color = WHITE;
    b->width = BULLET_SIZE;
    b->height = BULLET_SIZE;
}


void update(){
    f3d_nunchuk_read(&nundata);
    player_listen_move(&player, &nundata);
    move_enemies(enemies);
    bullet_listen_shoot(&player, &b, &nundata);
    //object_move(&b, (int8_t)b.speed, (int8_t)b.speed);
    object_update_loc_by_speed(&b);
    redraw = 1;
}

int main(void) { 
    setBuffs();
    initAll();
    printf("////////////////////////////////////////////////////////////\n");
    init_game_screen(&player);
    init_enemies(enemies);
    bullet_init(&b);
    printf("x:%d, y:%d, width:%d, height:%d\n", b.x, b.y, b.width, b.height);
    while(1){
        if (redraw) {
            f3d_lcd_fillScreen(BGCOLOR);
            player_draw(&player);
            player_draw(&b);
            enemies_draw(enemies, ENEMIES);
            redraw = 0;
        }
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
