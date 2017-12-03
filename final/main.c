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
#define ENEMIES 0
#define ENEMY_WIDTH 8
#define ENEMY_HEIGHT 8
#define ENEMY_COLOR BLUE



//GLOBAL Variables
Player player;
Enemy enemies[ENEMIES];
Bullet bullet_buf[BULLET_NUM];
struct nunchuk_data nundata;
struct nunchuk_data nundata2;
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

void bullet_init(Bullet *bullet_buf, uint8_t buf_size){
    int i;
    for(i = 0; i < buf_size; i++){
        bullet_buf[i].speed = 0;
        bullet_buf[i].x = -10;
        bullet_buf[i].y = -10;
        bullet_buf[i].color = WHITE;
        bullet_buf[i].width = BULLET_SIZE;
        bullet_buf[i].height = BULLET_SIZE;
        bullet_buf[i].used = false;
        object_print(&bullet_buf[i]);
    }
}


void update(){
    f3d_nunchuk_read(&nundata);
    f3d_nunchuk_read2(&nundata2);
    player_listen_move(&player, &nundata);
    //move_enemies(enemies);
    bullet_listen_shoot(&player, bullet_buf, BULLET_NUM, &nundata2);
    redraw = true;
}

int main(void) { 
    setBuffs();
    initAll();
    printf("////////////////////////////////////////////////////////////\n");
    init_game_screen(&player);
    init_enemies(enemies);
    bullet_init(bullet_buf, BULLET_NUM);
    DEBUGF("sizeof Object %lu", sizeof(Object));
    while(1){
        if (redraw) {
            f3d_lcd_fillScreen(BGCOLOR);
            player_draw(&player);
            //player_draw(bullet_buf); //single bullet
            enemies_draw(enemies, ENEMIES);
            redraw = false;
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
