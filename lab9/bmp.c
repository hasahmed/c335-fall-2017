#include <fcntl.h>
#include <stdio.h>
#include "bmp.h"
struct bmpfile_magic magic;
struct bmpfile_header header;
BITMAPINFOHEADER info;
main(int argc, char *argv[])
{
    int f;
    if (argc > 1){
        if ((f = open(argv[1], O_RDONLY)) == -1)
        {
            perror("problem opening file");
            return 1;
        }
        read(f, (void *) &magic , 2);
        printf("Magic %c%c\n", magic.magic[0], magic.magic[1]);
        read(f, (void *) &header , sizeof(header));
        printf("file size %d offset %d\n", header.filesz ,
                ,→header.bmp_offset);
        read(f, (void *) &info, sizeof(info));
        printf("Width %d Height %d, bitspp %d\n", info.width ,
                info.height , info.bitspp);
        close(f);
    }
}
