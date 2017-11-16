#include <f3d_lcd_sd.h>
enum dir{
    UP,
    DOWN,
    NA
};
enum dir check_nun_pressed(struct nunchuk_data *nundata);
int get_next_audio_index(enum dir thedirection, int current_file_index, int file_arr_len);
void draw_screen_message(char *message);
