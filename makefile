# Makefile

CFLAGS= -std=c99 -g

animalGame: animalGame.o binaryTree.o basicIO.o queue.o

animalGame.o: binaryTree.h basicIO.h
binaryTree.o: binaryTree.h queue.h