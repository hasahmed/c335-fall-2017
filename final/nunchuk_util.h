#ifndef _NUNCHUK_UTIL_H_
#define _NUNCHUK_UTIL_H_
#include <f3d_lcd_sd.h>
#include "nunchuk_util.h"
#define NUN_MAX 255
#define NUN_REST 128
#define DEAD_ZONE 36
enum nunchuk_dir{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    NA
};
typedef enum nunchuk_dir nunchuk_dir;
nunchuk_dir get_nunchuk_dir(struct nunchuk_data *nundata);
#endif //_NUNCHUK_UTIL_H_
