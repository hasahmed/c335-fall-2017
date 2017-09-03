#include "node.h"


#ifndef RPNLIB_H_
#define RPNLIB_H_

#define MAX_STR_ARR_LEN 2048
#define MAX_STR_LEN 64 

typedef struct string_t String;
struct string_t{
    char string[MAX_STR_LEN];
    int length;
};


void print_top(List **head);
char process_store_scanned(List **head, char *scanned);
void process_nums(int val);
void process_letters(char cmd);
void break_and_store(char **strarr, char *scanned);
void clear_buf(char[MAX_STR_LEN]); 

#endif
