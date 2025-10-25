#include <stdio.h>

#include <stdlib.h>

typedef struct LinkedNode{
void *data; // para usar un tipo de dato generico podria usar (void *)
struct LinkedNode *next;
} LinkedNode;



LinkedNode *newLinkedList(){
    return NULL;
} // La complejidad de la funcion es O(1) ya que solo inicializa la lista vacia.


LinkedNode *addElement(LinkedNode *head,int data) {
    LinkedNode *newNode = malloc(sizeof(LinkedNode));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        LinkedNode *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return head;

} // Complejidad de la funcion es O(n) debido al recorrido hasta el final de la lista.


int SizeList(LinkedNode *head) {
    if (head == NULL) {
        return 0;
    } 

    int contador = 0;
    LinkedNode *current = head;
        
    while(current != NULL) {
        current = current->next;
        contador++;
    }
    return contador;
} // Complejidad de la funcion es O(n) debido al recorrido de toda la lista.

LinkedNode *FindElement(LinkedNode *head, int posicion) {
    if (head == NULL || SizeList(head)<= posicion) {
        return NULL;
    }

    LinkedNode *current = head;

    for (int i = 0; i< posicion;i++){
        current = current->next;
        }

   return current; 
} // La complejidad de la funcion es O(n) debido al recorrido hasta la posicion indicada.


void Remove(LinkedNode **head, int posicion){
    
    LinkedNode *currentHead = *head;
    if (currentHead == NULL || SizeList(currentHead)<= posicion) {
        return;
    }

    LinkedNode *to_delete;

    if (posicion == 0) {
        to_delete = currentHead;
        *head = currentHead->next;
        free(to_delete);
        return;
    }

    LinkedNode *current = currentHead;

    for (int i = 0; i < posicion-1; i++) {
        current = current->next;
    }

    to_delete = current->next;
    current->next = to_delete->next;
    free(to_delete);
    return;
} // La complejidad de la funcion es O(n) debido al recorrido hasta la posicion indicada.

void printList(LinkedNode *head) {
    LinkedNode *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
} // La complejidad de la funcion es O(n) debido al recorrido de toda la lista.


