#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "binaryTree.h" //for typedef

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

/*
static biNode moveToLeaf(void *contents, int nodeNum){
    biNode leafNode   = (biNode) malloc(sizeof(biNode_store));
    leafNode->contents= contents;
    leafNode->nodeNum = nodeNum;
    leafNode->yesChild = NULL;
    leafNode->noChild  = NULL;
    return leafNode;
}*/
    
    
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

