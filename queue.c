#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "queue.h"

//typedef struct queue *queue, queue_store; - in header file

queue create_queue();
void* queue_pop(queue);
void* queue_peek(queue);
int queue_append(void*);
int queue_size(queue);
int queue_free(queue);

typedef struct queue_cell{
    void *contents;
    struct queue_cell *next;
} *queue_cell, queue_cell_store;

struct queue{
    queue_cell front;
    queue_cell rear;
    int size;
};

queue create_queue(){
    queue newQueue=(queue) malloc(sizeof(queue_store));
    newQueue->front=NULL;
    newQueue->rear=NULL;
    newQueue->size=0;
};

void *queue_pop(queue input){
    queue_cell cell=input->front;
    if (cell==NULL){
        fprintf(stderr,"Warning: Tried to pop empty queue.\n");
        return NULL;
    }
    void *temp=cell->contents;
    if (input->size > 1){
        void* next=cell->next;
        input->front=next;
    }
    else{
        input->front=NULL;
        input->rear=NULL;
    }
    input->size--;
    free(cell);
    return temp;
}

void* queue_peek(queue input){
    if (input->front==NULL)
        return NULL;
    return input->front->contents;
}

int queue_append(queue input, void *contents){
    queue_cell newCell = (queue_cell) malloc(sizeof(queue_cell_store));
    newCell->contents=contents;
    newCell->next=NULL;
    if (input->size>0)
        input->rear->next=newCell;
    else
        input->front=newCell;
    input->rear=newCell;
    input->size++;
    return 0;
    }
    
int queue_size(queue input){
    return input->size;
}

int queue_free(queue input){
    while (input->size>0)
    queue_pop(input);
    
    free(input);
}
    
