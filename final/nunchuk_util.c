#include <f3d_nunchuk.h>
#include "nunchuk_util.h"
nunchuk_dir gen_nunchuk_dir(struct nunchuk_data *nundata){
    if (nundata->jy < 96)
        return UP;
    if (nundata->jy > 156)
        return DOWN;
    return NA;
}
