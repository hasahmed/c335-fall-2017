#include "abs.h"

void abs_test(void) {
    printf("this is the return value of abs %d\n", abs_x(-9100));

    /*
    int error_count=0;
    int i;
    for (i = -100; i < 100; i++) {
        if (abs(i) != abs_c(i)) {    
            printf("ABS Error: Input %d, Expected %d, Received %d\n",i,abs_c(i),abs(i));
            error_count++;
        }
    }
    if (!error_count) {
        printf("ABS Tests Passed\n");
    }
    else {
        printf("ABS Test: %d errors\n",error_count);
    }
    */
}
