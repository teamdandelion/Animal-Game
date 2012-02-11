#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "basicIO.h"
#include "binaryTree.h"

void playGame(biNode);
void gameOver(void);

biNode root=NULL;

int main(){
    char *root_question, *yes_answer, *no_answer;
    root_question="Does your animal have four legs?";
    yes_answer="a rhinoceros";
    no_answer ="a velociraptor";
    root=makeRootNode((void*) root_question);
    addChildren(root, (void*) yes_answer, (void*) no_answer);
    playGame(root);
}


void playGame(biNode currentNode){
    char *question, *animal;
    while(! isLeaf(currentNode)){
        question=(char*) getContents(currentNode);
        printf("%s",question);
        if ( getYesNo() )
        currentNode=getYesChild(currentNode);
        else
        currentNode=getNoChild(currentNode);
    }
    animal=(char*) getContents(currentNode);
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
        newQuestion=strdup(getLine(stdin));
        shiftInsert(currentNode, (void*) newQuestion, (void*) newAnimal);
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