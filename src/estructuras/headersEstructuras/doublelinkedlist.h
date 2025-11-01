#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <stdlib.h> // Para usar NULL

typedef struct DoubleLinkedNode {
    void *data;
    struct DoubleLinkedNode *prev;
    struct DoubleLinkedNode *next;
} DoubleLinkedNode;

// Funciones
DoubleLinkedNode *newDoublyLinkedList();
DoubleLinkedNode *addElement(DoubleLinkedNode *head, void *data); 
int SizeList(DoubleLinkedNode *head);
DoubleLinkedNode *FindElement(DoubleLinkedNode *head, int posicion);
void *RemoveElement(DoubleLinkedNode **head, int posicion);
void printList(DoubleLinkedNode *head);

#endif