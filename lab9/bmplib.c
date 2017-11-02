#include <stdio.h>
#include <ff.h>
#include <diskio.h>
#include "bmplib.h"




void get_image_info(char *filename, bmp_file_info_t *bmpinfo){
    FIL f;		/* File object */
    FRESULT rc;			/* Result code */
    BYTE buff[14];		/* File read buffer in bytes*/
    UINT bytes_read;
    int i;



    rc = f_open(&f, filename, FA_READ);
    if (rc) die(rc);
    printf("file opened successfully '%s'\n", filename);
    rc = f_read(&f, buff, sizeof buff, &bytes_read);	/* Read a chunk of file */
    if (rc || !bytes_read) die(rc);	                        		//error, or no file header
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

    /*
       for (i = 0; i < bytes_read; i++)		                        //write bytes to struct
       putchar(buff[i]);
       if (rc) die(rc);

       printf("\nClose the file.\n");
       */

       rc = f_close(&f);
       if (rc) die(rc);
}

void die (FRESULT rc) {
    printf("Failed with rc=%u.\n", rc);
    while (1);
}
