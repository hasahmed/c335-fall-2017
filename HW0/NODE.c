#include <stdio.h>
#include <stdlib.h>
#include "node.h"

void push(Cell **head, int value){
    Cell *newNode = (Cell*) malloc(sizeof(Cell));
    if(newNode != NULL){
        newNode->value = value;
        newNode->next = *head;
        *head = newNode;
    }
    else{
        puts("The malloc failed");
        exit(1);
    }
}

int pop(List **head){
    int ans;
    ans = (*head)->value;

    Cell *tmp = (*head)->next;
    free(*head);
    *head = tmp;
    return ans;
}

/*
void init_list(List **head, int val){
    *head = (Cell*) malloc(sizeof(Cell));
    if(*head != NULL){
        (*head)->value = val;
        (*head)->next = NULL;
    }
    else{
        puts("The malloc failed");
        exit(1);
    }
}
*/

void print_list_values(Cell **head){
    Cell *tmp = *head;
    while(tmp != NULL){
        printf("%d\n", tmp->value);
        tmp = tmp->next;
    }
}

void list_free(Cell **head){
    if(*head == NULL)
        return;
    Cell *tmp = *head;
    Cell *nxt = tmp->next;
    while(nxt != NULL){
       free(tmp);
       tmp = nxt;
       nxt = tmp->next;
    }
}
