#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "rpnlib.h"
#include "node.h"


void print_top(List **head){
    printf("%d\n", (*head)->value);
}
void clear_buf(char strbuf[MAX_STR_LEN]){
    for(int i = 0; i < MAX_STR_LEN; i++){
        strbuf[i] = -1;
    }
}

char process_store_scanned(List **head, char *scanned){
    puts("we are processing scanned string");

    char strbuf[MAX_STR_LEN]; //create a buffer to scan in strings
    clear_buf(strbuf);
    int buf_write_index = 0; //this is the index where we are going to write into the buffer

    for(int i = 0;;i++){ //loop thorugh the scanned string
        puts("we are looping throught the scanned string");
        if(scanned[i] == '\0'){ //until we reach a null character
            puts("The null character was the ith element of the scanned string");
            if(1){
                int scanned_int = atoi(strbuf);
                printf("we are pushing %d to the stack\n", scanned_int);
                push(head, atoi(strbuf));//when null character is reached convert the contents of the buffer to an integer and push it 
            }
            return 'z'; // then the string no longer needs any processesing so return
        }

        if(scanned[i] == ' '){ //if a space is reached
            puts("a space has been reached in the input");
            strbuf[buf_write_index] = '\0'; //then and end the string with a null character
            printf("this is the scanned string: %s\n", strbuf);
            push(head, atoi(strbuf)); //convert to int and push to stack
            buf_write_index = 0; //restart the buffer write index
            break;
        }

        if(isdigit(scanned[i])) {
            strbuf[buf_write_index] = scanned[i];
        } else if(scanned[i] == -1){
            break;
        } else {
            printf("The scanned character '%c' is not a digit\n", scanned[i]);
            switch(scanned[i]){
                case 'q':
                case 'p':
                case 'f':
                case 'c':
                    return scanned[i];
                case '+':
                    push(head, pop(head) + pop(head));
                    return 'z';
                    break;
                case '*':
                    push(head, pop(head) * pop(head));
                    return 'z';
                    break;
                case '/':
                    {
                    int second = pop(head);
                    int first = pop(head);
                    push(head, first / second);
                    return 'z';
                    break;
                    }
                case '-':
                    {
                    int second = pop(head);
                    int first = pop(head);
                    push(head, first - second);
                    return 'z';
                    break;
                    }
            }
        }
        buf_write_index++;
    }
    return 'z';
}
