/* Hasan Y Ahmed (hasahmed)
 * C335
 * Lab2
 */


#include <stdio.h>
#include <ctype.h>
#include "mywc.h"

void wc(){
    int c;
    int lines = 0;
    int words = 0;
    int bytes = 0;
    int previous_c;
    while(c != 0x1b){
        c = getchar();
        switch(c){
            case '\n':
                if(previous_c != ' '){
                    words++;
                }
                lines++;
                bytes++;
                break;
            case ' ':
                if(previous_c < 255 && previous_c != ' '
                        && previous_c != '\t'
                        && previous_c != '\r'
                        && previous_c != '\f'
                        && previous_c != '\v'
                        && previous_c != '\n'
                        ){
                    words++;
                }
                bytes++;
                break;
            case '\t':
            case '\r':
            case '\f':
            case '\v':
                bytes++;
                break;
            default:
                bytes++;
        }
        previous_c = c;
    }
    printf("%d     %d     %d\n", lines, words, bytes - 1);
}
