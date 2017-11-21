/*
 * Hasan Y Ahmed
 * Partner: Cas Sinders
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
//#include "play_audio.h"
#include "nunchuk_util.h"
#include "player.h"
#include "game_util.h"



#define SCREEN_HEIGHT ST7735_height
#define SCREEN_WIDTH ST7735_width

//#define TIMER 20000
//#define AUDIOBUFSIZE 128
#define BGCOLOR BLACK
//#define DEBUGF(f_, ...) do{ char buf[26]; sprintf(buf, (f_), __VA_ARGS__); draw_string(0, 0, buf, WHITE, BGCOLOR); } while(0);

//extern int8_t Audiobuf[AUDIOBUFSIZE];
//extern int audioplayerHalf;
//extern int audioplayerWhole;
//int ret;
//int audiofile_index = 0;

Player player;

struct nunchuk_data nundata;

int main(void) { 
    setBuffs();
    initAll();
    printf("////////////////////////////////////////////////////////////\n");
    init_game_screen(&player);

    //DEBUGF("Hey baby girl %d\n, %f", 100, 1.11f);

    while(1){
        f3d_nunchuk_read(&nundata);
        //player_move(&player, 1, 1);
        player_draw(&player);
        player_listen_move(&player, &nundata);
        //DEBUGF("nd jx: %4lu jy: %4lu", nundata.jx, nundata.jy);
        /*
         *
        //printf("width %d, height %d\n", WIDTH, HEIGHT);
        pressed_direction = check_nun_pressed(&nundata);
        if (pressed_direction != NA){
        if (back_to_neutral){
        audiofile_index = get_next_audio_index(pressed_direction, audiofile_index, FILE_ARR_LEN);
        f3d_lcd_fillScreen2(BLACK);
        }
        back_to_neutral = 0;
        } 
        if (pressed_direction == NA){
        back_to_neutral = 1;
        }

        //draw_stringlist(L_INDENT, L_START, audiofiles, 3, L_SEP,  TEXTCOLOR, BGCOLOR);
        //draw_rect(L_INDENT - 10, L_START + (L_SEP * audiofile_index), SEL_SIZE, SEL_SIZE, TEXTCOLOR);
        }
        */
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
