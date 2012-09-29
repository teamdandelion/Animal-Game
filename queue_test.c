// queue-test.c
#include <stdlib.h>
#include <stdio.h>
#include <libgen.h> //for basename
#include <string.h>

#include "queue.h"

char *progname;

int main(int argc, char **argv) {
    progname = strdup(basename(*argv)); //basename might get re-written
    printf("Starting program\n");
    //allocate a queue
    queue q = create_queue();
    
    
    char* stry= "a string";
    printf("Attempting to print void string: %s",(void*)stry);
    
    
    printf("Allocated queue with pointer %p\n",q);
    
    for(int i=0; i<100; ++i){
        int *ip = (int *) malloc(sizeof(int));
        if (ip == NULL) {
            exit(-1);
        }
        *ip = i;
        queue_append(q,ip);
    }
    
    printf("About to empty queue\n");
    printf("Queue size is %d\n",queue_size(q));
    printf("Top pointer %p\n",queue_pop(q));
    while (queue_size(q)>0){
        int *ip = (int *) queue_pop(q);
        printf("%d\n",*ip);
        free((void*)ip);
    }
}
        
        //.... he moved to the next file