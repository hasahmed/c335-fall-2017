#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "node.h"
#include "rpnlib.h"

String strArr[MAX_STR_ARR_LEN];

#define MAX_USER_INPUT_LEN 256

int main(){
    List *list = NULL;
    char user_input[MAX_USER_INPUT_LEN];
    while(1){
        printf("> ");
        int result = scanf("%s", user_input);
        if(result == EOF)
            break;

        char proc_res = process_store_scanned(&list, user_input);

        switch(proc_res){
            case 'q':
                goto cleanup;
                break;
            case 'p':
                print_top(&list);
                break;
            case 'f':
                print_list_values(&list);
                break;
            case 'c':
                list_free(&list);
                break;
        }
    }

    goto cleanup;

cleanup:
    list_free(&list);
    puts("program memory has been freed");
    if((length(&list) != 0)){
        puts("There has been an error freeing the memory of the program");
    }

}

