#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "node.h"
#include "rpnlib.h"

String strArr[MAX_STR_ARR_LEN];

#define MAX_USER_INPUT 256

int main(){
    List *list = NULL;

    char user_input[MAX_USER_INPUT];
    while(1){
        printf("> ");
        scanf("%s", user_input);
        process_store_scanned(&list, user_input);
        if(user_input[0] == 'q')
            break;
    }
        print_list_values(&list);


    goto cleanup;

cleanup:
    list_free(&list);

}

