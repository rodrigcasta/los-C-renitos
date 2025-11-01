#ifndef MATERIAS_H
#define MATERIAS_H

// Necesita la definición del nodo doble
#include "../../estructuras/headersEstructuras/doublelinkedlist.h" 

typedef struct Materia {
    int ID;
    char nombre[50];
    // Usamos la lista doble para la lista de estudiantes
    DoubleLinkedNode *listaEstudiantes; 
} Materia;

// Función constructora
Materia *NewMateria(const char *nombre);

#endif 