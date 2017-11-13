#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ff.h>
#include "play_audio.h"
void die (FRESULT rc) {
    printf("Failed with rc=%u.\n", rc);
    while (1);
}

int8_t Audiobuf[AUDIOBUFSIZE];
int audioplayerHalf;
int audioplayerWhole;
int ret;

void play_audio(char *filename){
    FATFS Fatfs; //global file system
    f_mount(0, &Fatfs);
    FIL fid;
    FRESULT rc;	
    DIR dir;	
    FILINFO fno;	
    UINT bw, br;
    unsigned int retval;
    int bytesread;

    printf("Reset\n");
    printf("\nOpenining %s\n", filename);
    rc = f_open(&fid, filename, FA_READ);


    if (!rc) {
        struct ckhd hd;
        uint32_t  waveid;
        struct fmtck fck;

        //readckhd(&fid, &hd, 'FFIR');

        f_read(&fid, &waveid, sizeof(waveid), &ret);
        printf("sizeof waveid: %lu\n", sizeof(waveid));
        printf("wtf is 'EVAW': %d\n", 'EVAW');
        printf("ret: %d\n", ret);
        if ((ret != sizeof(waveid)) || (waveid != 'EVAW'))
            die(rc);
        printf("we've made it to here");
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
}

void readckhd(FIL *fid, struct ckhd *hd, uint32_t ckID, int ret) {
    f_read(fid, hd, sizeof(struct ckhd), &ret);
    if (ret != sizeof(struct ckhd)){
        printf("Here be the error ret: %d, ckhd: %d\n", ret, sizeof(struct ckhd));
        exit(-1);
    }
    if (ckID && (ckID != hd->ckID))
        exit(-1);
}
