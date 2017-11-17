#include "player.h"
void player_draw(Player *p, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color){
    p->x = x;
    p-> y = y;
    p->width = width;
    p->height = height;
    p->color = color;
}
void player_draw(Player *p){
    draw_rect(p->x, p->y, p->width, p->height,  p->color);
}
