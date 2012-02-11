#ifndef BINARYTREE_H
#define BINARYTREE_H

int isLeaf(biNode);
biNode makeRootNode(void);
int addNode(biNode, void *newContents, void* noContents);
void* getContents(biNode);
biNode getYesNode(biNode);
biNode getNoNode(biNode);

#endif