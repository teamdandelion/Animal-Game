#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h" //for serialization
#include "binaryTree.h" //for typedef
#include "basicIO.h"

/*
binaryTree.c
Implements a general binary tree. Each node consists of a void* to contents, a nodeNumber (indexed from 0), and up to two children nodes. 

Data structure is opaque, and dependent files should use interface functions (provided in binaryTree.h) rather than attempting to directly access the data structure. 

Functions provided:

*/

struct binaryNode {
    void *contents;
    int nodeNum;
    int numChildren;
    struct binaryNode *yesChild;
    struct binaryNode *noChild;
};

int isLeaf(biNode); //1 if is leaf, 0 otherwise

biNode makeRootNode(void*); //Makes root node with 2 children

int addChildren(biNode, void*, void*);



static biNode makeLeafNode(void*, int); //Makes a leaf - internal only. Consider changing to get node # from parent instead of manual input

int shiftInsert(biNode, void *newContents, void *yesContents); //Update current node to new contents, and make parent. Subnode A (i.e. 'yesChild' gets new yesContent; previous contents of current node are shifted to noChild 
void* getContents(biNode);
biNode getyesChild(biNode);
biNode getnoChild(biNode);

biNode makeRootNode(void* contents){ //Creates the root node and returns a pointer to it
    biNode rootNode = (biNode) malloc(sizeof(biNode_store));
    rootNode->contents    = contents;
    rootNode->nodeNum     = 0;
    rootNode->numChildren = 0;
    rootNode->yesChild     = NULL;
    rootNode->noChild      = NULL;
    return rootNode;
}

int addChildren(biNode parent, void* yesContents, void* noContents){
    int nodeNum=parent->nodeNum;
    int goodReturn=0;
    if (yesContents != NULL){
        if (parent->yesChild != NULL)
            fprintf(stderr,"Warning: Tried to assign yesChild to a node with existing yesChild\n");
        else {
        parent->yesChild = makeLeafNode(yesContents,nodeNum*2+1);
        parent->numChildren++;
        //goodReturn=1;
        }
    }
    
    if (noContents != NULL){
        if (parent->noChild != NULL)
            fprintf(stderr,"Warning: Tried to assign noChild to a node with existing noChild\n");
        else {
        parent->noChild = makeLeafNode(noContents,nodeNum*2+2);
        parent->numChildren++;
        //goodReturn+=2;
        }
    }
    return goodReturn;
}

int linkChildren(biNode parent, biNode yesChild, biNode noChild){
    int returnNum=0;
    int parentNum=parent->nodeNum;
    if (yesChild != NULL){
        int yesNum=yesChild->nodeNum;
        assert (parentNum*2+1 == yesNum);
        if (parent->yesChild != NULL){
            fprintf(stderr,"Warning: Tried to link yesChild when parent already had a yesChild\n");
            returnNum=1;
        }
        else{
            parent->yesChild=yesChild;
            parent->numChildren++;
        }
    }
    
    if (noChild != NULL){
        int noNum=noChild->nodeNum;
        assert (parentNum*2+2 == noNum);
        if (parent->noChild != NULL){
            fprintf(stderr,"Warning: Tried to link noChild when parent already had a noChild\n");
            returnNum+=2;
        }
        else {
            parent->noChild=noChild;
            parent->numChildren++;
        }
    }
}

void* getContents(biNode currentNode){
    return currentNode->contents;
}

biNode getYesChild(biNode currentNode){
    return currentNode->yesChild;
}

biNode getNoChild(biNode currentNode){
    return currentNode->noChild;
}

static biNode makeLeafNode(void *contents, int nodeNum){
    biNode leafNode = (biNode) malloc(sizeof(biNode_store));
    leafNode->contents = contents;
    leafNode->nodeNum = nodeNum;
    leafNode->numChildren=0;
    leafNode->yesChild = NULL;
    leafNode->noChild = NULL;
//TODO: account for alloc-err
    return leafNode;
}

    
int isLeaf(biNode currentNode){
    if (currentNode->yesChild == NULL && currentNode->noChild == NULL)
        return 1;
    else 
        return 0;
}

int shiftInsert(biNode currentNode, void *newContents, void *yesContents){
    void *noContents=currentNode->contents;
    currentNode->contents=newContents;
    return addChildren(currentNode, yesContents, noContents);
}

int saveTree(biNode root, FILE *fp, char* specifier) {
//Takes root of the tree to be copied, file pointer to write to, and a format specifier
//(e.g. %d or %s) which tells how to print the void* contents.

//uses a queue to keep track of nodes to print.
    printf("About to make queue\n");
    queue q=create_queue();
    printf("Queue made, about to append root\n");
    queue_append(q,root);
    printf("Queue made, root appended\n");
    //char* format[30];
    //format="%d:";
    //format=strncat(format,specifier,20);
    //format=strcat(format,"\n");
    //printf("Format is: %s",format);
    
    biNode currentNode;
    while (queue_size(q)>0){
        currentNode=queue_peek(q);
        if (currentNode->yesChild != NULL)
        queue_append(q,currentNode->yesChild);
        
        if (currentNode->noChild != NULL)
        queue_append(q,currentNode->noChild);
        
        fprintf(fp,":%d:%s\n",currentNode->nodeNum,currentNode->contents);
        queue_pop(q);
    }
}

biNode loadTree(FILE *fp, char *specifier){
    printf("Trying to load tree.\n");
    char* queueContents;
    int nodeNum;
    queue parentQueue  = create_queue();
    queue childQueue = create_queue();
    biNode newNode, currentNode, parentNode, newChild;
    int nextc;
    while (fgetc(fp)==':'){
        printf("scanning:\n");
        fscanf(fp,"%d:",&nodeNum);
        printf("scanned %d",nodeNum);
        queueContents=strdup(getLine(fp));
        printf(" contents: %s\n",queueContents);
        newNode=makeLeafNode(queueContents,nodeNum);
        
        queue_append(parentQueue ,newNode);
        queue_append(childQueue  ,newNode);
    }
    printf("Done scanning\n");
    biNode root=queue_pop(childQueue);
    int parentNum, childNum;
    biNode yesChild, noChild; 
    while (queue_size(childQueue)>0){
        printf("queue_size is %d\n",queue_size(childQueue));
        yesChild = NULL;
        noChild  = NULL;
        parentNode  = queue_peek(parentQueue);
        newChild    = queue_peek(childQueue);
        
        parentNum  =parentNode ->nodeNum;
        childNum   =newChild   ->nodeNum;
        printf("Considering parent %d child %d\n",parentNum,childNum);
        
        //if (parentNum*2+2 > childNum) { //this shouldn't happen
        //    fprintf(stderr,"Something went wrong: parent %d child %d\n", parentNum, childNum);
        //    break;
        //    }

        if (parentNum*2+1 == childNum) {
        // Child node in buildQueue is the yesChild of current node.
        yesChild = newChild;
        queue_pop(childQueue);
        if (queue_size(childQueue)>0){
            newChild = queue_peek(childQueue);
            childNum = newChild -> nodeNum;
        }
        }
        
        if (parentNum*2+2 == childNum) {
        noChild = newChild;
        queue_pop(childQueue);
        if (queue_size(childQueue)>0){
            newChild = queue_peek(childQueue);
            childNum = newChild -> nodeNum;
        }
        }
        
        if (parentNum*2+1 < childNum) { 
        //current node's children would have a lower index than next child to add
        //pop the current node from the readQueue
        queue_pop(parentQueue);
        }
        
        linkChildren(parentNode,yesChild,noChild); 
        //yesChild and noChild initialized to NULL. linkChildren ignores NULL inputs.
    }
    
    //TODO: add queue_free
    return root;


}