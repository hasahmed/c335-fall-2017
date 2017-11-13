#include <ff.h>

#define TIMER 20000
#define AUDIOBUFSIZE 128

struct ckhd{
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

void die (FRESULT rc);
void play_audio(char *filename);
void readckhd(FIL *fid, struct ckhd *hd, uint32_t ckID, int ret);

