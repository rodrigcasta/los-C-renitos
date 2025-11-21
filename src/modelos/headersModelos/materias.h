#ifndef MATERIAS_H
#define MATERIAS_H

// Necesita la definición del nodo doble
#include "../../estructuras/headersEstructuras/doublelinkedlist.h"
#include "../../estructuras/headersEstructuras/linkedList_n.h" // NECESARIO para requisitos de correlativas
#include "inscripcion.h"                                       // NECESARIO para listaInscripciones

typedef struct Materia {
    int ID;
    char nombre[50];

    LinkedNode *correlativasID; // Lista de IDs (int *) de materias que son requisito
                                // Usamos la lista doble para la lista de estudiantes
    // DoubleLinkedNode *listaEstudiantes;

    DoubleLinkedNode *listaInscripciones; // Lista de punteros a 'Inscripcion'
} Materia;

// Función constructora
Materia *NewMateria(const char *nombre);

void FreeMateria(Materia *materia);

#endif