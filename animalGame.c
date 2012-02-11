#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "animalGame.h"

void playGame(agNode);
void gameOver(void);

agNode root=NULL;

int main(){
    root=makeRootNode();
    playGame(root);
}


void playGame(agNode currentNode){
    char *question, *animal;
    while(! isLeaf(currentNode)){
        question=getString(currentNode);
        printf("%s",question);
        if ( getYesNo() )
        currentNode=getYesNode(currentNode);
        else
        currentNode=getNoNode(currentNode);
    }
    animal=getString(currentNode);
    printf("Is your animal %s",animal);
    if ( getYesNo() ){
        printf("Great! I win!\n");
        gameOver();
    }
    else {
        char *newAnimal, *newQuestion;
        printf("Great! I get to learn another animal.\n");
        printf("What animal were you thinking of? >");
        newAnimal=strdup(getLine(stdin));
        printf("What is true of %s but false of %s?\n>",newAnimal,animal);
        newQuestion=getLine(stdin);
        addNode(currentNode, newQuestion, newAnimal);
        free(newAnimal);
        gameOver();
    }
}
    
void gameOver(void){
    printf("Would you like to play again?");
    if (getYesNo() )
    playGame(root);
    else
    exit(0);
}