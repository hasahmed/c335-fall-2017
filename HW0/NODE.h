#ifndef CELL_H_
#define CELL_H_

typedef struct cell_t List;
typedef struct cell_t Cell;
struct cell_t{
    int value;
    List *next;
};

//void init_list(Cell **head, int value);
void push(Cell **head, int value);
void print_list_values(Cell **head);
void list_free(Cell **head);
int pop(Cell **head);

#endif
