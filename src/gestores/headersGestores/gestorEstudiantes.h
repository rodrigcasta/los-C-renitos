#ifndef GESTORESTUDIANTES_H
#define GESTORESTUDIANTES_H

#include "los-c-renitos/src/estructuras/headersEstructuras/linkedList_n.h"
#include "los-c-renitos/src/modelos/headersModelos/estudiantes.h"

typedef struct GestorEstudiantes {
    LinkedNode *estudiantes
} GestorEstudiantes;


GestorEstudiantes *NewGestorEstudiantes();

void ListarEstudiante(GestorEstudiantes *gestor, Estudiante *estudiante);

void DeslistarEstudiante(GestorEstudiantes *gestor, Estudiante *nombre);

Estudiante *BuscarEstudiante(GestorEstudiantes *gestor, const char *nombre);

#endif
