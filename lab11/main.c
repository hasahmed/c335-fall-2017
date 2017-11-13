/*
 * Hasan Y Ahmed
 * Partner: Cas Sinders
 * Lab 11
 * 11/09/17
 */
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <f3d_systick.h>
#include <ff.h>
#include <diskio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stm32f30x_dma.h>
#include <stm32f30x_dac.h>
#include "play_audio.h"


FATFS Fatfs; //global file system

#define TIMER 20000
#define AUDIOBUFSIZE 128

extern int8_t Audiobuf[AUDIOBUFSIZE];
extern int audioplayerHalf;
extern int audioplayerWhole;
int ret;

void initAll(){
    f3d_delay_init();
    delay(310);
    f3d_uart_init();
    delay(310);
    f3d_gyro_init();
    delay(310);
    f3d_led_init();
    delay(310);
    f3d_lcd_init();
    delay(310);
    f3d_i2c1_init();
    delay(310);
    f3d_accel_init();
    delay(310);
    f3d_mag_init();
    delay(310);
    f3d_nunchuk_init();
    delay(310);
    f3d_rtc_init();
    delay(310);
    f3d_systick_init();
    delay(310);
    f3d_dac_init();
    delay(310);
    f3d_timer2_init();
    f3d_lcd_fillScreen2(BLACK);
    f_mount(0, &Fatfs);
}
void setBuffs(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void) { 
    setBuffs();
    initAll();
    //play_audio("thermo.wav");
    char *audiofiles[] = {"thermo.wav", "taco.wav", "lettuce.wav"};

    if(1){
        FRESULT rc;	
        DIR dir;	
        FILINFO fno;	
        UINT bw, br;
        unsigned int retval;
        int bytesread;
        FIL fid;

        printf("Reset\n");
        printf("\nOpen thermo.wav\n");
        rc = f_open(&fid, audiofiles[0], FA_READ);
        printf("successfully opened");

        if (!rc) {
            struct ckhd hd;
            uint32_t  waveid;
            struct fmtck fck;

            readckhd(&fid, &hd, 'FFIR', ret);

            f_read(&fid, &waveid, sizeof(waveid), &ret);
            printf("sizeof waveid: %lu\n", sizeof(waveid));
            printf("wtf is 'EVAW': %d\n", 'EVAW');
            printf("ret: %d\n", ret);
            if ((ret != sizeof(waveid)) || (waveid != 'EVAW'))
                return -1;

            readckhd(&fid, &hd, ' tmf', ret);

            f_read(&fid, &fck, sizeof(fck), &ret);

            // skip over extra info

            if (hd.cksize != 16) {
                printf("extra header info %d\n", hd.cksize - 16);
                f_lseek(&fid, hd.cksize - 16);
            }

            printf("audio format 0x%x\n", fck.wFormatTag);
            printf("channels %d\n", fck.nChannels);
            printf("sample rate %d\n", fck.nSamplesPerSec);
            printf("data rate %d\n", fck.nAvgBytesPerSec);
            printf("block alignment %d\n", fck.nBlockAlign);
            printf("bits per sample %d\n", fck.wBitsPerSample);

            // now skip all non-data chunks !

            while(1){
                readckhd(&fid, &hd, 0, ret);
                if (hd.ckID == 'atad')
                    break;
                f_lseek(&fid, hd.cksize);
            }

            printf("Samples %d\n", hd.cksize);

            // Play it !

            //audioplayerInit(fck.nSamplesPerSec);

            f_read(&fid, Audiobuf, AUDIOBUFSIZE, &ret);
            hd.cksize -= ret;
            audioplayerStart();
            while (hd.cksize) {
                int next = hd.cksize > AUDIOBUFSIZE/2 ? AUDIOBUFSIZE/2 : hd.cksize;
                if (audioplayerHalf) {
                    if (next < AUDIOBUFSIZE/2)
                        bzero(Audiobuf, AUDIOBUFSIZE/2);
                    f_read(&fid, Audiobuf, next, &ret);
                    hd.cksize -= ret;
                    audioplayerHalf = 0;
                }
                if (audioplayerWhole) {
                    if (next < AUDIOBUFSIZE/2)
                        bzero(&Audiobuf[AUDIOBUFSIZE/2], AUDIOBUFSIZE/2);
                    f_read(&fid, &Audiobuf[AUDIOBUFSIZE/2], next, &ret);
                    hd.cksize -= ret;
                    audioplayerWhole = 0;
                }
            }
            audioplayerStop();
        }

        printf("\nClose the file.\n"); 
        rc = f_close(&fid);

        if (rc) die(rc);
        while (1);
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
