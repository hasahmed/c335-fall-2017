#include <stdio.h>
#include <ff.h>
#include <diskio.h>
#include <f3d_lcd_sd.h>
#include "bmplib.h"

void draw_image(image_info_t *imageinfo, struct bmppixel *pixel_buffer){
    FIL f;	//file object	
    FRESULT rc;			//result code
    UINT bytes_read;

    rc = f_open(&f, imageinfo->filename, FA_READ);
    if (rc) die(rc);
    printf("file opened successfully '%s'\n", imageinfo->filename);

    rc = f_lseek(&f, imageinfo->bmp_offset);
    if (rc) die(rc);
    struct bmppixel pixel;
    uint8_t x;
    uint8_t y;
    uint16_t color;
    uint32_t pixel_entry;
    int row_size = ((24 * imageinfo->width + 31)/ 32) * 4;
    int pixel_array_size = row_size * imageinfo->height;

    for(y = 0; y < imageinfo->height; y++){
        rc = f_read(&f, (void*)pixel_buffer, sizeof(*pixel_buffer) * imageinfo->width, &bytes_read);
        if (rc || !bytes_read)
            goto done;
        for(x = 0; x < imageinfo->width; x++){
            printf("the first pixel color R is %x\n", pixel_buffer[x].r);
            printf("the first pixel color G is %x\n", pixel_buffer[x].g);
            printf("the first pixel color B is %x\n", pixel_buffer[x].b);
            color = (pixel_buffer[x].r << 11) & 0xf800;
            color =  color & (pixel_buffer[x].g << 5);
            color = color &  pixel_buffer[x].b & 0x1f;
            printf("the first pixel color is %x\n", color);
            goto done;
            f3d_lcd_drawPixel(x, y, color);
        }
    }

    /*
       color = pixel.r & 0x1f;
       color <<= 5;
       color = pixel.g & 0x3f;
       color <<= 6;
       color = pixel.b & 0x1f;
       color <<= 5;
       */
    //color = (uint16_t)pixel_entry;
    //f3d_lcd_drawPixel(x, y, color);
    //printf("R:%d G:%d B:%d\n", pixel.r, pixel.g, pixel.b);
done:
    if (rc) die(rc);
    rc = f_close(&f);
    if (rc) die(rc);
}



/*
   void get_image_info(char *filename, 
   struct bmpfile_magic *magic, 
   struct bmpfile_header *header, 
   BITMAPINFOHEADER *bmpinfo){
   FIL f;		
   FRESULT rc;			
   UINT bytes_read;
   int i;



   rc = f_open(&f, filename, FA_READ);
   if (rc) die(rc);
   printf("file opened successfully '%s'\n", filename);
   rc = f_read(&f, (void*)magic, sizeof magic, &bytes_read);	
   if (rc || !bytes_read) die(rc);	                        //error, or no file header
   if (buff[0] != 'B'){
   printf("The header info in %s is wrong. The first byte shoud be 'B', instead its '%c'\n", filename, buff[0]);
   die(100);
   }
   if (buff[1] != 'M'){
   printf("The header info in %s is wrong. The second byte shoud be 'M', instead its '%c'\n", filename, buff[1]);
   die(101);
   }
   printf("Success reading header\n");
//printf("The size of the file is %d bytes\n", buff[2] + (buff[3] << ) + buff[4] + buff[5]);
bmpinfo->size = *((int*)&buff[2]);
bmpinfo->data_start_offset = *((int*)&buff[10]);
printf("The size of the file is %d bytes\n", bmpinfo->size);
printf("The offset (in bytes) at which the pixel information starts %d\n", bmpinfo->data_start_offset);

for (i = 0; i < bytes_read; i++)		                        //write bytes to struct
putchar(buff[i]);
if (rc) die(rc);

printf("\nClose the file.\n");

rc = f_close(&f);
if (rc) die(rc);
}
*/

void die (FRESULT rc) {
    printf("Failed with rc=%u.\n", rc);
    while (1);
}
