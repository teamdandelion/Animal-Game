#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "binaryTree.h" //for typedef


//ynNode :: a binary node, consisting of a string 
struct binaryNode {
    void *contents;
    int nodeNum;
    struct binaryNode *yesNode;
    struct binaryNode *noNode;
};



int isLeaf(biNode); //1 if is leaf, 0 otherwise

biNode makeRootNode(void*, void*, void*); //Makes root node with 2 children

static biNode makeLeafNode(void*, int); //Makes a leaf - internal only. Consider changing to get node # from parent instead of manual input

int shiftInsert(biNode, void *newContents, void *yesContents); //Update current node to new contents, and make parent. Subnode A (i.e. 'yesNode' gets new yesContent; previous contents of current node are shifted to noNode 
void* getContents(biNode);
biNode getYesNode(biNode);
biNode getNoNode(biNode);

biNode makeRootNode(void* contents, void* yesChild, void* noChild){ //Creates the root node and returns a pointer to it
    biNode rootNode = (biNode) malloc(sizeof(biNode_store));
    rootNode->contents = contents;
    rootNode->nodeNum = 0;
    rootNode->yesNode = makeLeafNode(yesChild,1);
    rootNode->noNode = makeLeafNode(noChild,2);
    return rootNode;
}

void* getContents(biNode currentNode){
    return currentNode->contents;
}

biNode getYesNode(biNode currentNode){
    return currentNode->yesNode;
}

biNode getNoNode(biNode currentNode){
    return currentNode->noNode;
}

static biNode makeLeafNode(void *contents, int nodeNum){
    biNode leafNode = (biNode) malloc(sizeof(biNode_store));
    leafNode->contents = contents;
    leafNode->nodeNum = nodeNum;
    leafNode->yesNode = NULL;
    leafNode->noNode = NULL;
//TODO: account for alloc-err
    return leafNode;
}

/*
static biNode moveToLeaf(void *contents, int nodeNum){
    biNode leafNode   = (biNode) malloc(sizeof(biNode_store));
    leafNode->contents= contents;
    leafNode->nodeNum = nodeNum;
    leafNode->yesNode = NULL;
    leafNode->noNode  = NULL;
    return leafNode;
}*/
    
    
int isLeaf(biNode currentNode){
if (currentNode->yesNode == NULL && currentNode->noNode == NULL)
    return 1;
else 
    return 0;
}

int shiftInsert(biNode currentNode, void *newContents, void *yesContents){
    void *noContents=currentNode->contents;
    int nodeNum = currentNode->nodeNum;
    biNode yesNode=makeLeafNode(yesContents, nodeNum*2+1);
    biNode noNode =makeLeafNode(noContents,  nodeNum*2+2);
    currentNode->contents=newContents;
    currentNode->yesNode=yesNode;
    currentNode->noNode=noNode;
}

