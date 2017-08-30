#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "rpnlib.h"
#include "node.h"


void print_top(List **head){
    printf("%d\n", (*head)->value);
}

void process_store_scanned(List **head, char *scanned){
    char strbuf[MAX_STR_LEN];
    int buf_write_index = 0;
    for(int i = 0;;i++){
        if(scanned[i] == '\0'){
            push(head, atoi(strbuf));
            return;
        }

        if(scanned[i] == ' '){
            strbuf[buf_write_index] = '\0';
            push(head, atoi(strbuf));
            buf_write_index = 0;
            break;
        }

        if(isdigit(scanned[i]))
            strbuf[buf_write_index] = scanned[i];

        buf_write_index++;
    }
    return;
}
