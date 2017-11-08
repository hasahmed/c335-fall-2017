#include <stdio.h>
#include "mult_by_5.h"


void test_mult_by_5(){
    int i;
    int errorcount = 0;
    for(i = 0; i < 101; i++){
        if(mult_by_5(i) != mult_by_5_c(i)){
            printf("Error in mult_by_5. Input: %d, Output: %d, Expected: %d\n", i, mult_by_5(i), mult_by_5_c(i));
            errorcount++;
        }
    }
    if (errorcount == 0)
        printf("All Test Passed 'mult_by_5'\n");
}
