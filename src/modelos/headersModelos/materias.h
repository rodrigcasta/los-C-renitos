#ifndef MATERIAS_H
#define MATERIAS_H

#include "../../estructuras/headersEstructuras/doublelinkedlist.h"
#include "../../estructuras/headersEstructuras/linkedList_n.h"
#include "inscripcion.h"

typedef struct Materia {
    int ID;
    char nombre[50];

    LinkedNode *correlativasID;

    DoubleLinkedNode *listaEstudiantes;

    DoubleLinkedNode *listaInscripciones;
} Materia;

Materia *NewMateria(const char *nombre);

void FreeMateria(Materia *materia);

#endif