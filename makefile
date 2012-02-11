# Makefile

CFLAGS= -std=c99

animalGame: animalGame.o binaryTree.o basicIO.o

animalGame.o: binaryTree.h basicIO.h