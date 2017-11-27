#include <stdio.h>
#include "max_array.h"


void test_max_array(){
    int i;
    int errorcount = 0;
#define ARRLEN 5
    unsigned int arr_of_arrs[ARRLEN][ARRLEN] = {
        {0, 1, 2, 3, 5}, //0
        {6, 5, 100, 3, 1}, //6
        {47, 2, 1, 1, 1}, //47
        {8, 2, 3, 1, 6}, //4
        {5, 6, 2, 1, 3} //6
    };
#define ARRLEN2 3
    unsigned int arr_of_arrs2[ARRLEN2][ARRLEN2] = {
        {0, 1, 2}, //0
        {6, 5, 100}, //6
        {47, 2, 1}, //47
    };
    for(i = 0; i < ARRLEN; i++){
        if(max_array_c(arr_of_arrs[i], ARRLEN) != max_array(arr_of_arrs[i], ARRLEN)){
            printf("Error in max_array. Expected: %d, Actual %d\n", max_array_c(arr_of_arrs[i], ARRLEN), max_array(arr_of_arrs[i], ARRLEN));
            errorcount++;
        }
    }
    for(i = 0; i < ARRLEN2; i++){
        if(max_array_c(arr_of_arrs2[i], ARRLEN2) != max_array(arr_of_arrs2[i], ARRLEN2)){
            printf("Error in max_array. Expected: %d, Actual %d\n", max_array_c(arr_of_arrs2[i], ARRLEN2), max_array(arr_of_arrs2[i], ARRLEN2));
            errorcount++;
        }
    }
    if (errorcount == 0)
        printf("All Test Passed 'max_array'\n");
}
