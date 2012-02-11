#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef struct binaryNode *biNode, biNode_store;

int isLeaf(biNode);
biNode makeRootNode(void *contents, void *yesChild, void *noChild);
int shiftInsert(biNode, void *newContents, void *noContents);
void* getContents(biNode);
biNode getYesNode(biNode);
biNode getNoNode(biNode);

#endif