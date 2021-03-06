#include <f3d_nunchuk.h>
#include <f3d_lcd_sd.h>
#include "helpers.h"
enum dir check_nun_pressed(struct nunchuk_data *nundata){
    if (nundata->jy < 96)
        return UP;
    if (nundata->jy > 156)
        return DOWN;
    return NA;
}

int get_next_audio_index(enum dir thedirection, int current_file_index, int file_arr_len){
    if(thedirection == UP){
        if(current_file_index >= file_arr_len -1)
            return 0;
        return current_file_index + 1;
    } else if (thedirection == DOWN){
        if(current_file_index <= 0)
            return file_arr_len -1;
        else if (current_file_index <= 0)
            return file_arr_len -1;
        return current_file_index - 1;
    }
    return -1;
}
