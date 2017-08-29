#include <stdio.h>
#include <stdlib.h>
#include "NODE.h"

int main(){
    LIST node2 = {
        42,
        NULL
    };

    LIST node1 = {
        32,
        &node2
    };

    LIST *list = add_node(&node1, 57);
    print_node_values(list);
    free(list);

    /*

    node2->val = 42;
    node2->next = NULL;


    node->val = 32;
    */
    //node1->next = node2;
}
