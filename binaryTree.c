/*binaryTree.c 
the binaryTree interface
by Dan Mane*/

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

Memory: binaryTree does not implement any memory management for contents (since it doesn't know what type the contents point to, it can't duplicate them). 

Functions are provided for serialization, i.e. writing and reading binary trees from files, but this only works for strings.
*/

struct binaryNode {
    void *contents;              // void pointer to contents of the node
    //calling program is responsible for memory management
    int nodeNum;                 // the number of the node. 
    //zero based indexing, so root is 0, children of n are (2n+1), (2n+2)
    int numChildren;             // the number of children [0,2]
    struct binaryNode *yesChild; // the child on the left side
    struct binaryNode *noChild;  // the child on the right side 
};

int isLeaf(biNode); //1 if is leaf, 0 otherwise

biNode makeRootNode(void*); //Makes root node with 2 children

int addChildren(biNode, void*, void*);



static biNode makeLeafNode(void*, int); //Makes a leaf - internal only. Consider changing to get node # from parent instead of manual input

int shiftInsert(biNode, void *newContents, void *yesContents); //Update current node to new contents, and make parent. Subnode A (i.e. 'yesChild' gets new yesContent; previous contents of current node are shifted to noChild 
void* getContents(biNode);
biNode getyesChild(biNode);
biNode getnoChild(biNode);


biNode makeRootNode(void* contents){ 
//Creates the root node and returns a pointer to it
    biNode rootNode = (biNode) malloc(sizeof(biNode_store));
    rootNode->contents    = contents;
    rootNode->nodeNum     = 0;
    rootNode->numChildren = 0;
    rootNode->yesChild     = NULL;
    rootNode->noChild      = NULL;
    return rootNode;
}

//add children (between zero and two) to the root node. Pass pointers to contents for the yesChild and the noChild; if a NULL pointer is passed for either argument, then no child is added. Returns 0 on success, 1 if there was a problem with the yesChild, 2 if there was a problem with the noChild, or 3 if there were problems with both yesChild and noChild
int addChildren(biNode parent, void* yesContents, void* noContents){
    int nodeNum=parent->nodeNum;
    int returnNum=0;
    if (yesContents != NULL){
        if (parent->yesChild != NULL) {
            fprintf(stderr,"Warning: Tried to overwrite yesChild of node %d\n", nodeNum);
            returnNum+=1;
        } else {
            parent->yesChild = makeLeafNode(yesContents,nodeNum*2+1);
            parent->numChildren++;
        }
    }

    if (noContents != NULL){
        if (parent->noChild != NULL) {
            fprintf(stderr,"Warning: Tried to overwrite noChild of node %d\n", nodeNum);
            returnNum+=2;
        } else {
            parent->noChild = makeLeafNode(noContents,nodeNum*2+2);
            parent->numChildren++;
        }
    }
    return returnNum;
}

int linkChildren(biNode parent, biNode yesChild, biNode noChild){
    int returnNum=0;
    int parentNum=parent->nodeNum;
    if (yesChild != NULL){
        int yesNum=yesChild->nodeNum;
        if (parentNum*2+1 != yesNum){
            fprintf(stderr,"Warning: Tried to assign yesChild with bad nodeNum\n");
            fprintf(stderr,"Parent: %d Child: %d\n",parentNum, yesNum);
        } else
        if (parent->yesChild != NULL){
            fprintf(stderr,"Warning: Tried to overwrite yesChild of node %d\n", parentNum);
            returnNum+=1;
        } else {
            parent->yesChild=yesChild;
            parent->numChildren++;
        }
    }
    
    if (noChild != NULL){
        int noNum=noChild->nodeNum;
        if (parentNum*2+2 != noNum){
            fprintf(stderr,"Warning: Tried to assign yesChild with bad nodeNum\n");
            fprintf(stderr,"Parent: %d Child: %d\n",parentNum, noNum);
        } else
        if (parent->noChild != NULL){
            fprintf(stderr,"Warning: Tried to overwrite noChild of parent %d\n",parentNum);
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
    if (leafNode==NULL)
        goto alloc_err;
    leafNode -> contents    = contents;
    leafNode -> nodeNum     = nodeNum;
    leafNode -> numChildren = 0;
    leafNode -> yesChild    = NULL;
    leafNode -> noChild     = NULL;
    return leafNode;
    
alloc_err:
        fprintf(stderr,"fatal error -- buffer allocation failed\n");
        exit(1);
}

    
int isLeaf(biNode currentNode){
    return (currentNode->numChildren==0);
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
    queue q=create_queue();
    queue_append(q,root);
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
        
        fprintf(fp,":%d:%s\n",currentNode->nodeNum,(char*) currentNode->contents);
        queue_pop(q);
    }
}

biNode loadTree(FILE *fp, char *specifier){
    /*
    The strategy for loading a tree:
    Each line in the DB file will be of form
    :(int)nodeNum:string
    This program will create a biNode from each entry, with no children. It will add each entry to two queues: a parentQueue and a childQueue. Then it pops the root off the childQueue, and loops through the childQueue while it still has more nodes in queue. Each iteration of the loop, it compares the nodeNum of the top of the parentQueue with the nodeNum on top of the childQueue, and links the child to parent as appropriate. Each time it links a child, it pops the child off of the childQueue, and when it encounters a child indexed above the current parentNode, it pops the parentNode off the queue. This approach is memory efficient; it uses memory proportional to the size of the tree, unlike an array-based approach which would use memory proportional to the highest index of the tree.
    
    If program is given an empty database file, it will return NULL. Behavior on badly formed database files is undefined.
    
    Would like to improve this program to use void*s like the rest of the binaryTree implementation, but not sure how to do so.
    */
    char* queueContents;
    int nodeNum;
    queue parentQueue  = create_queue();
    queue childQueue   = create_queue();
    biNode newNode, currentNode, parentNode, newChild;
    int nextc;
    
    while (fgetc(fp)==':'){
        fscanf(fp,"%d:",&nodeNum);
        queueContents=strdup(getLine(fp));
        newNode=makeLeafNode(queueContents,nodeNum);
        
        queue_append(parentQueue , newNode);
        queue_append(childQueue  , newNode);
    }
    
    biNode root= queue_pop(childQueue);
    
    int parentNum, childNum;
    biNode yesChild, noChild; 
    while (queue_size(childQueue)>0){
        //initialize both children to NULL, so we can use one linkChildren command, and properly link only valid children
        yesChild    = NULL;
        noChild     = NULL;
        
        parentNode  = queue_peek(parentQueue);
        newChild    = queue_peek(childQueue);
        
        parentNum   = parentNode ->nodeNum;
        childNum    = newChild   ->nodeNum;
        
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
    
    queue_free(parentQueue);
    queue_free(childQueue);
    return root;
    

}

