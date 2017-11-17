#include <stdio.h>
#include "game_util.h"
#include "player.h"
void init_game_screen(Player *p){
    printf("Here we are calling some stuff\n");
    f3d_lcd_fillScreen(BGCOLOR);
    player_init(p, PLAYER_STARTING_X - (PLAYER_WIDTH/2), PLAYER_STARTING_Y - (PLAYER_HEIGHT/2), PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_COLOR);
    player_draw(p);
}
