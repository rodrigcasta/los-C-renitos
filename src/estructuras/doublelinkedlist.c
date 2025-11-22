#include "../estructuras/headersEstructuras/doublelinkedlist.h"
#include <stdio.h>
#include <stdlib.h>

DoubleLinkedNode *newDoublyLinkedList() {
    return NULL;
}

DoubleLinkedNode *addElement(DoubleLinkedNode *head, void *data) {
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
}

int SizeList(DoubleLinkedNode *head) {
    int count = 0;
    DoubleLinkedNode *current = head;

    while (current != NULL) {
        current = current->next;
        count++;
    }
    return count;
}

DoubleLinkedNode *FindElement(DoubleLinkedNode *head, int posicion) {
    if (head == NULL || posicion < 0) {
        return NULL;
    }

    DoubleLinkedNode *current = head;

    for (int i = 0; current != NULL && i < posicion; i++) {
        current = current->next;
    }

    return current;
}

void *RemoveElement(DoubleLinkedNode **head, int posicion) {

    DoubleLinkedNode *current = *head;
    if (current == NULL || posicion < 0) {
        return NULL;
    }

    for (int i = 0; current != NULL && i < posicion; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return NULL;

        if (current->prev != NULL) {
            current->prev->next = current->next;
        } else {
            *head = current->next;
        }

        if (current->next != NULL) {
            current->next->prev = current->prev;
        }

        void *data_to_return = current->data;
        free(current);

        return data_to_return;
    }
}

void printList(DoubleLinkedNode *head) {
    DoubleLinkedNode *current = head;
    while (current != NULL) {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
void FreeDoubleLinkedListNodes(DoubleLinkedNode *head) {
    DoubleLinkedNode *current = head;
    DoubleLinkedNode *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}