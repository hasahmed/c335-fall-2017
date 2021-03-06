#include <stdint.h>
/*
typedef struct bmpfile_header{
    unsigned int size; //size of bmp file in 4 bytes
    unsigned int data_start_offset; //the starting address of the pixel information within the file

} bmpfile_info_t;
*/

struct bmpfile_magic { //magic numbers associated with the bmp files
    unsigned char magic[2];
};

struct bmpfile_header {
    uint32_t file_size;
    uint16_t unknown1;
    uint16_t unknown2;
    uint32_t bmp_offset;
};

typedef struct {
    uint32_t header_sz;
    int32_t width;
    int32_t height;
    uint16_t nplanes;
    uint16_t bitspp;
    uint32_t compress_type;
    uint32_t bmp_bytesz;
    int32_t hres;
    int32_t vres;
    uint32_t ncolors;
    uint32_t nimpcolors;
} BITMAPINFOHEADER;

typedef struct {
    uint32_t file_size;
    uint32_t bmp_offset;
    int32_t width;
    int32_t height;
    char filename[60];
} image_info_t;

struct bmppixel { // little endian byte order
    uint8_t b;
    uint8_t g;
    uint8_t r;
};
void draw_image(image_info_t *imageinfo, struct bmppixel *pixel_buffer);

//void drawImage(char *filename, struct bmpfile_header BITMAPINFOHEADER *info);


/*
void get_image_info(char *filename, 
        struct bmpfile_magic *magic, 
        struct bmpfile_header *header, 
        BITMAPINFOHEADER *bmpinfo);
        */
void die (FRESULT rc);
