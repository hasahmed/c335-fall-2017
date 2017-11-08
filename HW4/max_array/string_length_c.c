#include "string_length.h"
int string_length_c(char *c) {
    int i = 0;
    while(c[i] != 0){
        i++;
    }
    return i;
}
