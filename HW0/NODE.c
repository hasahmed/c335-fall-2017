#include <stdio.h>
#include <stdlib.h>
#include "NODE.h"

LIST* add_node(LIST *head, int value){
    LIST newNode = {
        value,
        head
    };
    LIST *tmp = (LIST*) malloc(sizeof(LIST));
    *tmp = newNode;
    return tmp;
}

void print_node_values(LIST *head){
    LIST *tmp = head;
    while(tmp != NULL){
        printf("%d\n", tmp->val);
        tmp = tmp->next;
    }
}

//free_nodes


