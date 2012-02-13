#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue *queue, queue_store;

queue create_queue();
void* queue_pop(queue);
void* queue_peek(queue);
int queue_append(queue, void*);
int queue_size(queue);
int queue_free(queue);

#endif