#include <f3d_nunchuk.h>
#include "apps.h"


enum Joydir checkJoyDir(nunchuk_t *chuky){
    if (chuky->jx > 240 || chuky->c == 1)
        return RIGHT;
    else if (chuky->jx < 10 || chuky->z == 1)
        return LEFT;
    return NA;
}


