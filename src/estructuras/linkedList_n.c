#include <stdio.h>
#include <stdlib.h>

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

/**
 * Inicializa una nueva lista con un nodo y el dato enviado por parámetro.
 */
LinkedNode* newLinkedNodeData(void* dato) {
  LinkedNode* nodo = (LinkedNode*)malloc(sizeof(LinkedNode));
  nodo->data = dato;
  nodo->next = NULL;
  return nodo;
}

/**
 * Inicializa una nueva lista vacía.
 */
LinkedNode* newLinkedNode() {
  LinkedNode* nodo = (LinkedNode*)malloc(sizeof(LinkedNode));
  nodo->data = NULL;
  nodo->next = NULL;
  return nodo;
}

/**
 * Agrega un nodo al principio de la lista.
 */
LinkedNode* prependNode(LinkedNode* headLista, int dato) {
  LinkedNode* nodo = newLinkedNode(dato);
  nodo->next = headLista;
  return nodo;
}

/**
 * Agrega un nodo para que quede colocado en la posicion indicada.
 * (Ej: posición 1 significa añadir al principio de la lista)
 */
LinkedNode* insertPos(LinkedNode* headLista, int dato, int pos) {
  if (pos <= 0) {
    printf("Error: posición fuera de rango.\n");
    return headLista;
  }
  if (headLista == NULL && pos > 1) {
    printf(
        "Error: no se puede insertar más allá del inicio en una lista "
        "vacía.\n");
    return headLista;
  }
  if (pos == 1) {
    return prependNode(headLista, dato);
  }
  LinkedNode* cursor = headLista;
  int i = 1;
  while (cursor != NULL && i < pos - 1) {
    cursor = cursor->next;
    i++;
  }
  if (cursor == NULL) {
    printf("Error: posición fuera de rango.\n");
    return headLista;
  }
  LinkedNode* nodo = newLinkedNode(dato);
  nodo->next = cursor->next;
  cursor->next = nodo;
  return headLista;
}

/**
 * Agrega un nodo al final de la lista.
 */
LinkedNode* appendNode(LinkedNode* headLista, int dato) {
  LinkedNode* nodo = newLinkedNode(dato);
  if (headLista == NULL) {
    return nodo; // la lista estaba vacía, el nuevo nodo es la cabeza
  }
  LinkedNode* cola = getTail(headLista);
  cola->next = nodo;
  return headLista;
}

/**
 * Elimina el primer nodo de la lista.
 */
LinkedNode* removeHead(LinkedNode* headLista) {
  if (headLista == NULL) {
    return NULL;
  }
  LinkedNode* nuevoHead = headLista->next;
  free(headLista);
  return nuevoHead;
}

/**
 * Elimina el primer nodo que encuentre que su contenido coincida con el dato
 * dado.
 */
LinkedNode* removeData(LinkedNode* headLista, int data) {
  if (headLista == NULL) {
    return NULL;
  }

  if (headLista->data == data) {
    LinkedNode* temp = headLista;
    headLista = headLista->next;
    free(temp);
    return headLista;
  }

  LinkedNode* cursor = headLista;
  while (cursor->next != NULL && cursor->next->data != data) {
    cursor = cursor->next;
  }

  if (cursor->next == NULL) {
    printf("Dato no encontrado.\n");
    return headLista;
  }

  LinkedNode* temp = cursor->next;
  cursor->next = temp->next;
  free(temp);

  return headLista;
}

/**
 * Elimina el nodo en la posición indicada.
 * (Ej: La posición 1 elimina el primer nodo de la lista.)
 */
LinkedNode* removePos(LinkedNode* headLista, int pos) {
  if (pos <= 0) {
    printf("Error: posición fuera de rango.\n");
    return headLista;
  }
  if (headLista == NULL && pos > 1) {
    printf(
        "Error: no se puede eliminar más allá del inicio en una lista "
        "vacía.\n");
    return headLista;
  }
  if (pos == 1) {
    return removeHead(headLista);
  }
  LinkedNode* cursor = headLista;
  int i = 1;
  while (cursor != NULL && i < pos - 1) {
    cursor = cursor->next;
    i++;
  }
  if (cursor == NULL) {
    printf("Error: posición fuera de rango.\n");
    return headLista;
  }
  LinkedNode* temp = cursor->next;
  cursor->next = temp->next;
  free(temp);
  return headLista;
}

/**
 * Elimina el último nodo de la lista.
 */
LinkedNode* removeTail(LinkedNode* headLista) {
  if (headLista == NULL) {
    return NULL;
  }
  if (headLista->next == NULL) {
    // Un solo nodo
    free(headLista);
    return NULL;
  }
  LinkedNode* cursor = headLista;
  while (cursor->next->next != NULL) {
    cursor = cursor->next;
  }
  free(cursor->next);
  cursor->next = NULL;
  return headLista;
}

/**
 * Función privada que obtiene el último elemento de la lista.
 */
static LinkedNode* getTail(LinkedNode* headLista) {
  LinkedNode* cursor = headLista;
  while (cursor->next != NULL) {
    cursor = cursor->next;
  }
  return cursor;
}

/**
 * Calcula y devuelve el tamaño de la lista.
 */
int getSize(LinkedNode* headLista) {
  LinkedNode* cursor = headLista;
  int cont = 0;
  while (cursor != NULL) {
    cursor = cursor->next;
    cont++;
  }
  return cont;
}

/**
 * Devuelve un print con todos los elementos de la lista.
 */
void printLinkedList(LinkedNode* headLista) {
  LinkedNode* cursor = headLista;
  printf("[ ");
  while (cursor != NULL) {
    printf("%d", cursor->data);
    if (cursor->next != NULL) printf(", ");
    cursor = cursor->next;
  }
  printf(" ]\n");
}

/**
 * Elimina la lista, limpiando todos los nodos de la memoria.
 */
void freeList(LinkedNode* headLista) {
  LinkedNode* cursor = headLista;
  while (cursor != NULL) {
    LinkedNode* temp = cursor;
    cursor = cursor->next;
    free(temp);
  }
}