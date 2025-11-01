#include <stdio.h>
#include <stdlib.h>

typedef struct DoubleLinkedNode {
    void *data;
    struct DoubleLinkedNode *prev;
    struct DoubleLinkedNode *next;
} DoubleLinkedNode;

DoubleLinkedNode *newDoubleLinkedList(){
    return NULL;
}

DoubleLinkedNode *addElement(DoubleLinkedNode *head, int data) {
    DoubleLinkedNode *newNode = malloc(sizeof(DoubleLinkedNode));
    if (newNode == NULL) {
        return head; 
    }

    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        return newNode; 
    } else {
        DoubleLinkedNode *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        
        current->next = newNode;
        newNode->prev = current; 
        
        return head;
    }
} // La complejidad de la funcion es O(n) debido al recorrido hasta el final de la lista.

int SizeList(DoubleLinkedNode *head) {
    int count = 0;
    DoubleLinkedNode *current = head;
        
    while(current != NULL) {
        current = current->next;
        count++;
    }
    return count;
} // La complejidad de la funcion es O(n) debido al recorrido de toda la lista.


DoubleLinkedNode *FindElement(DoubleLinkedNode *head, int posicion) {
    if (head == NULL || posicion < 0) {
        return NULL;
    }

    DoubleLinkedNode *current = head;

    for (int i = 0; current != NULL && i < posicion; i++){
        current = current->next;
    }

    return current;
} // La complejidad de la funcion es O(n) debido al recorrido hasta la posicion indicada.


void Remove(DoubleLinkedNode **head, int posicion){
    
    DoubleLinkedNode *current = *head;
    if (current == NULL || posicion < 0) {
        return;
    }

    for (int i = 0; current != NULL && i < posicion; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return; 
    }
    
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);
} // la complejidad de la funcion es O(n) debido al recorrido hasta la posicion indicada.

void printList(DoubleLinkedNode *head) {
    DoubleLinkedNode *current = head;
    while (current != NULL) {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
} // La complejidad de la funcion es O(n) debido al recorrido de toda la lista.