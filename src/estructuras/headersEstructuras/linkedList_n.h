#ifndef LINKEDLIST_N_H
#define LINKEDLIST_N_H

#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode {
    void *data;
    struct LinkedNode *next;
} LinkedNode;

LinkedNode *newLinkedNodeData(void *dato);
LinkedNode *newLinkedNode();
LinkedNode *prependNode(LinkedNode *headLista, void *dato);
LinkedNode *insertPos(LinkedNode *headLista, void *dato, int pos);
LinkedNode *appendNode(LinkedNode *headLista, void *dato);
LinkedNode *removeData(LinkedNode *headLista, void *dato);
LinkedNode *removeHead(LinkedNode *headLista);
LinkedNode *removePos(LinkedNode *headLista, int pos);
LinkedNode *removeTail(LinkedNode *headLista);
int getSize(LinkedNode *headLista);
void printLinkedList(LinkedNode *headLista);
void freeList(LinkedNode *headLista);
void freeListAndData(LinkedNode *headLista);

#endif