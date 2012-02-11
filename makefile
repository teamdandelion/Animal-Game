# Makefile

CFLAGS= -std=c99

animalGame: animalGame.o binaryTree.o basicIO.o
queueTest: queue_test.o queue.o

animalGame.o: binaryTree.h basicIO.h