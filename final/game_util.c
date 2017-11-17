#include "game_util.h"
#include "player.h"
void init_game_screen(Player *p){
    Player pl;
    f3d_lcd_fillScreen(BGCOLOR);
    player_init(p, PLAYER_STARTING_X, PLAYER_STARTING_Y, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_COLOR);
    //player_draw(p);
}
