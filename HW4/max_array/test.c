#include <stdio.h>
#include "string_length.h"


void test_string_length(){
    int i;
    int errorcount = 0;

#define STRARR_LEN 10
    char *strs[] = {
        "",
        "a",
        "hello", 
        "hey", 
        "how are you?", 
        "whats going on?", 
        "who's there?", 
        "c is cool", 
        "so is assembly", 
        "i think thats enough tests don't you?"
    };

    for(i = 0; i < STRARR_LEN; i++){
        if(string_length(strs[i]) != string_length_c(strs[i])){
            printf("Error in string_length. Input: %s\n, Output: %d, Expected: %d\n", strs[i], string_length(strs[i]), string_length_c(strs[i]));
            errorcount++;
        }
    }
    if (errorcount == 0)
        printf("All Test Passed 'string_length'\n");
}
