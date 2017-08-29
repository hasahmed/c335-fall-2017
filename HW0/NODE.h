#ifndef CELL_H_
#define CELL_H_

typedef struct CELL LIST;
struct CELL{
    int val;
    LIST *next;
};

LIST* add_node(LIST *head, int value);
void print_node_values(LIST *head);

#endif
