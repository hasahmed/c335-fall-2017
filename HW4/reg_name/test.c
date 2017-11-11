#include <stdio.h>
#include <string.h>
#include "reg_name.h"


void test_reg_name(){
    int errorcount = 0;
    int i;
    for(i = 0; i < NAMES_LEN; i++){
        if(strcmp(reg_name_c(i), reg_name(i)) != 0){
            printf("Error in reg_name. Expected: %s, Actual %s\n", reg_name_c(i), reg_name(i));
            errorcount++;
        }
    }
    for(i = NAMES_LEN; i < 1000; i++){
        if(reg_name_c(i) != 0 || reg_name(i) != 0){
            printf("Error in reg_name. Expected: %d, Actual %d\n", reg_name_c(i), reg_name(i));
            errorcount++;
        }
    }
    //printf("%d\n", reg_name(180));
    //printf("%d\n", reg_name_c(180));
    if (errorcount == 0)
        printf("All Test Passed 'reg_name'\n");
}
