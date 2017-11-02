#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include <stdio.h>
#include <string.h>
#include "bmplib.h"

/*
void die (FRESULT rc) {
    printf("Failed with rc=%u.\n", rc);
    while (1);
}
*/

FATFS Fatfs;

struct bmpfile_magic magic;
struct bmpfile_header header;
BITMAPINFOHEADER info;

void get_image_info(char *filename, image_info_t *imageinfo){
    FIL f;	//file object	
    FRESULT rc;			//result code
    UINT bytes_read;

    rc = f_open(&f, filename, FA_READ);
    if (rc) die(rc);

    //magic
    rc = f_read(&f, (void*)&magic, sizeof magic, &bytes_read); //read magic numbers of file
    if (rc || !bytes_read) die(rc);	                        //error, or no file header

    //header
    rc = f_read(&f, (void*)&header, sizeof header, &bytes_read); //read the header of the file, the cursor has been moved foward the number of bytes already read
    if (rc || !bytes_read) die(rc);	                        //error, or no file header

    //info
    rc = f_read(&f, (void*)&info, sizeof info, &bytes_read); //read the information of the file, the cursor has been moved foward the number of bytes already read
    if (rc || !bytes_read) die(rc);	                        //error, or no file header

    //close file
    rc = f_close(&f);
    if (rc) die(rc);

    imageinfo->file_size = header.file_size;
    imageinfo->width = info.width;
    imageinfo->height = info.height;
    imageinfo->bmp_offset = header.bmp_offset;
    strcpy(imageinfo->filename, filename);
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

    f_mount(0, &Fatfs);		/* Register volume work area (never fails) */
}
void setBuffs(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void) { 
    struct bmppixel pixel_bufer[128];
    image_info_t imageinfo;
    //char imagename[] = "friends.bmp";
    setBuffs();
    initAll();
    f3d_lcd_fillScreen2(BLACK);
    get_image_info("friends.bmp", &imageinfo);
    draw_image(&imageinfo, pixel_bufer);
    /*
    char footer[20];
    int count = 0;
    int i;

    FRESULT rc;			
    DIR dir;		
    FILINFO fno;
    UINT bw;
    UINT br; //number of bytes to read
    unsigned int retval;






    */
    /*

       printf("\nOpen an existing file (message.txt).\n");
       rc = f_open(&Fil, "MESSAGE.TXT", FA_READ);
       if (rc) die(rc);
       printf("\nThis is the contents of the file 'message.txt'\n\n     ");
       for (;;) {
       rc = f_read(&Fil, Buff, sizeof Buff, &br);	
       if (rc || !br) break;			
       for (i = 0; i < br; i++)	
       putchar(Buff[i]);
       }
       if (rc) die(rc);

       printf("\nClose the file.\n");
       rc = f_close(&Fil);
       if (rc) die(rc);

       printf("\nCreate a new file (hello.txt).\n");
       rc = f_open(&Fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
       if (rc) die(rc);

       printf("\nWrite a text data. (Hello world!)\n");
       rc = f_write(&Fil, "Hello world!\r\n", 14, &bw);
       if (rc) die(rc);
       printf("%u bytes written.\n", bw);

       printf("\nClose the file.\n");
       rc = f_close(&Fil);
       if (rc) die(rc);

       printf("\nOpen root directory.\n");
       rc = f_opendir(&dir, "");
       if (rc) die(rc);

       printf("\nDirectory listing...\n");
       for (;;) {
       rc = f_readdir(&dir, &fno);		// Read a directory item 
       if (rc || !fno.fname[0]) break;	//Error or end of dir
       if (fno.fattrib & AM_DIR)
       printf("   <dir>  %s\n", fno.fname);
       else
       printf("%8lu  %s\n", fno.fsize, fno.fname);
       }
       if (rc) die(rc);

       printf("\nTest completed.\n");

       rc = disk_ioctl(0,GET_SECTOR_COUNT,&retval);
       printf("%d %d\n",rc,retval);
       */


    while (1);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
}
#endif

/* main.c ends here */
