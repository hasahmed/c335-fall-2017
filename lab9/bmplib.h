#include <stdint.h>
typedef struct bmp_file_info{
    unsigned int size; //size of bmp file in 4 bytes
    unsigned int data_start_offset; //the starting address of the pixel information within the file

} bmp_file_info_t;

struct bmpfile_magic {
    unsigned char magic[2];
};

struct bmpfile_header {
    uint32_t filesz;
    uint16_t creator1;
    uint16_t creator2;
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

struct bmppixel { // little endian byte order
    uint8_t b;
    uint8_t g;
    uint8_t r;
};


void get_image_info(char *filename, bmp_file_info_t *bmpinfo);
void die (FRESULT rc);
