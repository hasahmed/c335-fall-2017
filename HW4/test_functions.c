/**
 * Hasan Y Ahmed
 * CSCI-C335
 * HW4
 * 11/08/17
 */
#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "abs.h"
#include "gcd.h"
#include "abs.h"
#include "fib.h"

void abs_test(void) {
    int error_count=0;
    int i;
    for (i = -100; i < 100; i++) {
        if (abs_s(i) != abs_c(i)) {    
            printf("ABS Error: Input %d, Expected %d, Received %d\n",i,abs_c(i), abs_s(i));
            error_count++;
        }
    }
    if (!error_count) {
        printf("ABS Tests Passed\n");
    }
    else {
        printf("ABS Test: %d errors\n",error_count);
    }
}

void gcd_test(void) {
    int error_count=0;
    uint32_t i,j;
    for (i=1;i<100;i++) {
        for (j=1;j<100;j++) {
            if (gcd(i,j)!=gcd_c(i,j)) {
                printf("GCD Error: Input (%lu,%lu), Expected %d, Received %d\n",i,j,gcd_c(i,j),gcd(i,j));
                error_count++;
            }
        }
    }
    /*
       for (i=1;i<100;i++) {
       for (j=1;j<100;j++) {
       printf("GCD of %d, %d : %d\n", i, j, gcd_c(i, j));
       }
       }
       */
    if (!error_count) {
        printf("GCD Tests Passed\n");
    }
    else {
        printf("GCD Test: %d errors\n",error_count);
    }
}

void fib_test(void) {
    int i;
    int error_count=0;
    for (i=0;i<=46;i++) {
        if (fib(i) != fib_c(i)) {
            printf("Fib Error: Input %d, Expected %d, Received %d\n",i,fib_c(i),fib(i));
            error_count++;
        }
    }
    if (!error_count) {
        printf("Fib Tests Passed\n");
    }
    else {
        printf("Fib Test: %d errors\n",error_count);
    }
}


/* test.c ends here */
