#ifndef LINKEDLIST_N_H
#define LINKEDLIST_N_H

#include <stdlib.h> // Para usar NULL

typedef struct LinkedNode {
  void* data;
  struct LinkedNode* next;
} LinkedNode;

LinkedNode* newLinkedNodeData(void* dato);
LinkedNode* newLinkedNode();
LinkedNode* prependNode(LinkedNode* headLista, int dato);
LinkedNode* insertPos(LinkedNode* headLista, int dato, int pos);
LinkedNode* appendNode(LinkedNode* headLista, int dato);
LinkedNode* removeData(LinkedNode* headLista, int data);
LinkedNode* removeHead(LinkedNode* headLista);
LinkedNode* removePos(LinkedNode* headLista, int pos);
LinkedNode* removeTail(LinkedNode* headLista);
int getSize(LinkedNode* headLista);
void printLinkedList(LinkedNode* headLista);
void freeList(LinkedNode* headLista);


#endif