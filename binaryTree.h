#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef struct binaryNode *biNode, biNode_store;

int isLeaf(biNode);
biNode makeRootNode(void *contents);
int shiftInsert(biNode, void *newContents, void *noContents);
void* getContents(biNode);
biNode getYesChild(biNode);
biNode getNoChild(biNode);
int addChildren(biNode parent, void* yesContents, void* noContents);
int saveTree(biNode root, FILE *fp, char *specifier);
biNode loadTree(FILE *fp, char *specifier);


#endif