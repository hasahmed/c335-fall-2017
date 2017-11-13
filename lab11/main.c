/*
 * Hasan Y Ahmed - hasahmed - hasahmed@iu.edu
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

#define TIMER 20000
#define AUDIOBUFSIZE 128

extern uint8_t Audiobuf[AUDIOBUFSIZE];
extern int audioplayerHalf;
extern int audioplayerWhole;

FATFS Fatfs;		
FIL fid;		
BYTE Buff[512];		
int ret;
uint16_t backGroundColor = BLACK;
uint16_t foreGroundColor = WHITE;

struct ckhd {
    uint32_t ckID;
    uint32_t cksize;
};

struct fmtck {
    uint16_t wFormatTag;      
    uint16_t nChannels;
    uint32_t nSamplesPerSec;
    uint32_t nAvgBytesPerSec;
    uint16_t nBlockAlign;
    uint16_t wBitsPerSample;
};

void readckhd(FIL *fid, struct ckhd *hd, uint32_t ckID) {
    f_read(fid, hd, sizeof(struct ckhd), &ret);
    if (ret != sizeof(struct ckhd))
        exit(-1);
    if (ckID && (ckID != hd->ckID))
        exit(-1);
}
void drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color) {
    uint8_t y;
    uint16_t x[x2];
    for (y = 0; y < x2; y++) x[y] = color;
    f3d_lcd_setAddrWindow(x1,y1, x2,y2, MADCTLGRAPHICS);
    for (y = 0; y < y2; y++) {
        f3d_lcd_pushColor(x,x2);
    }
}

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
}
void setBuffs(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void die (FRESULT rc) {
    printf("Failed with rc=%u.\n", rc);
    while (1);
}

int main(void) { 
    setBuffs();
    initAll();
    f_mount(0, &Fatfs);
    printf("\n\n\n\n\n\n\n");




    FRESULT rc;	
    DIR dir;	
    FILINFO fno;	
    UINT bw, br;
    unsigned int retval;
    int bytesread;

    int state = 0;
    char * wavFiles[] = {"bell.wav", "ocean.wav", "thermo.wav"};
    f3d_lcd_fillScreen2(BLACK);
    /*
       print onto screen the three wav files
       */
    int i = 0;
    for (i = 0; i < 3; i++) {
        f3d_lcd_drawString(70, 30 + (i * 30),wavFiles[i], foreGroundColor, backGroundColor);
    }
    drawRectangle(40, 30 + (state * 30) + 6, 50, 30 + (state * 30), foreGroundColor);


    while(1) {

        // read data from nunchuk
        struct nunchuk_data nundata;
        f3d_nunchuk_read(&nundata);
        delay(150);

        if (nundata.jy > 156) {
            drawRectangle(40, 30 + (state * 30) + 6, 50, 30 + (state * 30), backGroundColor);
            state  = ++state % 3;
            drawRectangle(40, 30 + (state * 30) + 6, 50, 30 + (state * 30), foreGroundColor);
        }
        if (nundata.jy < 96) {
            drawRectangle(40, 30 + (state * 30) + 6, 50, 30 + (state * 30), backGroundColor);
            state--;
            if (state < 0) {
                state = 2;
            }
            drawRectangle(40, 30 + (state * 30) + 6, 50, 30 + (state * 30), foreGroundColor);
        }

        if (nundata.c) {
            //play_audio(wavFiles[state]);

            printf("Reset\n");


            printf("\nOpen %s\n", wavFiles[state]);
            rc = f_open(&fid, wavFiles[state], FA_READ);

            if (!rc) {
                struct ckhd hd;
                uint32_t  waveid;
                struct fmtck fck;

                readckhd(&fid, &hd, 'FFIR');

                f_read(&fid, &waveid, sizeof(waveid), &ret);
                if ((ret != sizeof(waveid)) || (waveid != 'EVAW'))
                    return -1;

                readckhd(&fid, &hd, ' tmf');

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
                    readckhd(&fid, &hd, 0);
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
        }
        // may need to wait after the button is pressed    
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
