#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QUEUE_SIZE 32

typedef struct queue {
    int head;
    int tail;
    int buffer[QUEUE_SIZE];
} queue_t;



void init_queue(queue_t *q);
int enqueue(queue_t *q, int i);
int dequeue(queue_t *q);
int queue_empty(queue_t *q);

#endif // _QUEUE_H_
