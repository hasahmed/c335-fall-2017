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
#include "helpers.h"
#include "player.h"
#include "game_util.h"


#define SCREEN_HEIGHT ST7735_height
#define SCREEN_WIDTH ST7735_width

//#define TIMER 20000
//#define AUDIOBUFSIZE 128
#define BGCOLOR BLACK

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

    int pressed_direction = NA;
    int back_to_neutral = 1;
    int should_play_audio = 0;

    //draw_stringlist(L_INDENT, L_START, audiofiles, 3, L_SEP,  TEXTCOLOR, BGCOLOR);
    //draw_rect(L_INDENT - 10, L_START + (L_SEP * audiofile_index), SEL_SIZE, SEL_SIZE, TEXTCOLOR);


    while(1){
        /*
        //printf("width %d, height %d\n", WIDTH, HEIGHT);
        f3d_nunchuk_read(&nundata);
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
