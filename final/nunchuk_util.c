#include <f3d_nunchuk.h>
#include <stdio.h>
#include "nunchuk_util.h"
#include "game_util.h"
GDIR get_nunchuk_dir(struct nunchuk_data *nundata){
    if (nundata->jy < NUN_REST - DEAD_ZONE && nundata->jx < NUN_REST - DEAD_ZONE)
        return DOWN_LEFT;
    if (nundata->jy < NUN_REST - DEAD_ZONE && nundata->jx > NUN_REST + DEAD_ZONE)
        return DOWN_RIGHT;
    if (nundata->jy > NUN_REST + DEAD_ZONE && nundata->jx > NUN_REST + DEAD_ZONE)
        return UP_RIGHT;
    if (nundata->jy > NUN_REST + DEAD_ZONE && nundata->jx < NUN_REST - DEAD_ZONE)
        return UP_LEFT;
    if (nundata->jy < NUN_REST - DEAD_ZONE)
        return DOWN;
    if (nundata->jy > NUN_REST + DEAD_ZONE)
        return UP;
    if (nundata->jx < NUN_REST - DEAD_ZONE)
        return LEFT;
    if (nundata->jx > NUN_REST + DEAD_ZONE)
        return RIGHT;
    return NA;
}

void nunchuk_print_values(struct nunchuk_data *nundata){
    printf("jx: %d jy: %d\n", nundata->jx, nundata->jy);
    //printf("ax: %d\n", nundata->ax);
    //printf("ay: %d\n", nundata->ay);
    //printf("az: %d\n", nundata->az);
    //printf("c: %d\n", nundata->c);
    //printf("z: %d\n", nundata->z);
}
