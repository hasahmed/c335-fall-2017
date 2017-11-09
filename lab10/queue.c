#include <stdio.h>
#include "queue.h"

void init_queue(queue_t *q){
    q->head = 0;
    q->tail = 0;
}
int enqueue(queue_t *q, int i){
    if (q->tail < QUEUE_SIZE){
        q->buffer[q->tail] = i;
        q->tail++;
        return 1;
    }
    return 0;
}

int dequeue(queue_t *q){
    if(queue_empty(q))
        return 0;

    int ret = q->buffer[0];
    int i; 
    for(i = 1; i < q->tail; i++) //shift everything left
        q->buffer[i - 1] = q->buffer[i];
    q->tail--;

    return ret;
}
int queue_empty(queue_t *q){
    if (q->tail <= 0)
        return 1;
    return 0;
}
