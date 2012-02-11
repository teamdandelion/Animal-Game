#include <assert.h>
#include <string.h>
#include "animalGame.h"
#include <stdlib.h>

//agNode : animal_game_Node
struct agNode {
    char *string;
    int nodeNum;
    struct agNode *yesNode;
    struct agNode *noNode;
};


int isLeaf(agNode);
agNode makeRootNode(void);
agNode makeLeafNode(char *, int);
int addNode(agNode, char *nextQuestion, char *animalName);
char* getString(agNode);
agNode getYesNode(agNode);
agNode getNoNode(agNode);

agNode makeRootNode(void){ //Creates the root node and returns a pointer to it
    agNode rootNode = (agNode) malloc(sizeof(agNode_store));
    rootNode->string = "Does your animal have four legs?";
    rootNode->nodeNum = 1;
    rootNode->yesNode = makeLeafNode("a rhinoceros",2);
    rootNode->noNode = makeLeafNode("a bottlenose dolphin",3);
    return rootNode;
}

char* getString(agNode currentNode){
    return currentNode->string;
}

agNode getYesNode(agNode currentNode){
    return currentNode->yesNode;
}

agNode getNoNode(agNode currentNode){
    return currentNode->noNode;
}

agNode makeLeafNode(char *name, int nodeNum){
    agNode leafNode = (agNode) malloc(sizeof(agNode_store));
    leafNode->string = strdup(name);
    leafNode->nodeNum = nodeNum;
    leafNode->yesNode = NULL;
    leafNode->noNode = NULL;
    assert (leafNode->string != NULL);
    return leafNode;
}

agNode moveToLeaf(char *animal, int nodeNum){
    agNode leafNode   = (agNode) malloc(sizeof(agNode_store));
    leafNode->string  = animal;
    leafNode->nodeNum = nodeNum;
    leafNode->yesNode = NULL;
    leafNode->noNode  = NULL;
    return leafNode;
}
    
    
    
int isLeaf(agNode currentNode){
if (currentNode->yesNode == NULL) {
    assert (currentNode->noNode == NULL);
    return 1;
    }
else {
    assert(currentNode->noNode != NULL);
    return 0;
    }
}

int addNode(agNode currentNode, char *nextQuestion, char *yesAnimal){
    char *noAnimal=currentNode->string;
    int nodeNum = currentNode->nodeNum;
    agNode yesNode=makeLeafNode(yesAnimal, nodeNum*2);
    agNode noNode=moveToLeaf(noAnimal, nodeNum*2+1); //Otherwise we would needlessly make a copy of the string and free the original
    currentNode->string = strdup(nextQuestion);
    currentNode->yesNode=yesNode;
    currentNode->noNode=noNode;
    assert (currentNode->yesNode != NULL && currentNode->noNode != NULL);
    //

}