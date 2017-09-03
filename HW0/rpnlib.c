#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
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

    char strbuf[MAX_STR_LEN]; //create a buffer to scan in strings
    clear_buf(strbuf);
    int buf_write_index = 0; //this is the index where we are going to write into the buffer

    for(int i = 0;;i++){ //loop thorugh the scanned string
        if(scanned[i] == '\0'){ //until we reach a null character
            int scanned_int = atoi(strbuf);
            push(head, atoi(strbuf));//when null character is reached convert the contents of the buffer to an integer and push it 
            return 'z'; // then the string no longer needs any processesing so return
        }

        if(scanned[i] == ' '){ //if a space is reached
            strbuf[buf_write_index] = '\0'; //then and end the string with a null character
            push(head, atoi(strbuf)); //convert to int and push to stack
            buf_write_index = 0; //restart the buffer write index
            break;
        }

        if(isdigit(scanned[i])) {
            strbuf[buf_write_index] = scanned[i];
        } else if(scanned[i] == -1){
            break;
        } else {
            switch(scanned[i]){
                case 'q':
                case 'p':
                case 'f':
                case 'c':
                    return scanned[i];
                case '+':
                    {
                    if(*head == NULL)
                        return 'e';
                    int second = pop(head);

                    if(second == INT_MAX)
                        return 'e';

                    int first = pop(head);
                    if(first == INT_MAX){
                        push(head, second);
                        return 'e';
                    }
                    push(head, first + second);
                    return 'z';
                    break;
                    }
                case '*':
                    {
                    if(*head == NULL)
                        return 'e';
                    int second = pop(head);

                    if(second == INT_MAX)
                        return 'e';

                    int first = pop(head);
                    if(first == INT_MAX){
                        push(head, second);
                        return 'e';
                    }
                    push(head, first * second);
                    return 'z';
                    break;
                    }
                case '/':
                    {
                    if(*head == NULL)
                        return 'e';
                    int second = pop(head);

                    if(second == INT_MAX)
                        return 'e';

                    int first = pop(head);
                    if(first == INT_MAX){
                        push(head, second);
                        return 'e';
                    }
                    if(second == 0){
                        push(head, 0);
                        return 'd';
                    }
                    push(head, first / second);
                    return 'z';
                    break;
                    }
                case '-':
                    {
                    if(*head == NULL)
                        return 'e';
                    int second = pop(head);

                    if(second == INT_MAX)
                        return 'e';

                    int first = pop(head);
                    if(first == INT_MAX){
                        push(head, second);
                        return 'e';
                    }
                    push(head, first - second);
                    return 'z';
                    break;
                    }
                default:
                    return 'z';
            }
        }
        buf_write_index++;
    }
    return 'z';
}
