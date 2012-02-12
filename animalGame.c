#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "basicIO.h"
#include "binaryTree.h"

void playGame(biNode);
void gameOver(void);
void makeNewRoot();

biNode root=NULL;


int main(){

    FILE *readFile = fopen("DB_animalGame","r");
    if (readFile==NULL)
        makeNewRoot();
    else
        root=loadTree(readFile,"%s");
    fclose(readFile);
    playGame(root);
}

void makeNewRoot(){
    char *root_question, *yes_answer, *no_answer;
    root_question="Does your animal have four legs?";
    yes_answer="a rhinoceros";
    no_answer ="a velociraptor";
    root=makeRootNode((void*) root_question);
    addChildren(root, (void*) yes_answer, (void*) no_answer);
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
    //printf("root pointer:%p",root);
    printf("Would you like to play again?");
    if (getYesNo()){
        playGame(root);
    }
    else{
        printf("root pointer:%p",root);
        FILE *fp=fopen("DB_animalGame_temp","w");
        printf("opened file\n");
        saveTree(root,fp,"%s");
        printf("Saved tree to temp");
        remove("DB_animalGame");
        fclose(fp);
        rename("DB_animalGame_temp", "DB_animalGame");
        exit(0);
    }
}