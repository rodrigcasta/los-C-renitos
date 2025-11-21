#ifndef GESTORESTUDIANTES_H
#define GESTORESTUDIANTES_H

#include "../../estructuras/headersEstructuras/linkedList_n.h"
#include "../../modelos/headersModelos/estudiantes.h"

typedef struct GestorEstudiantes {
    LinkedNode *estudiantes;
    int next_ID;
} GestorEstudiantes;

GestorEstudiantes *NewGestorEstudiantes();

void ListarEstudiante(GestorEstudiantes *gestor, Estudiante *estudiante);

void DeslistarEstudianteID(GestorEstudiantes *gestor, int id);

Estudiante *BuscarEstudianteID(GestorEstudiantes *gestor, int id);
Estudiante *BuscarEstudianteNombre(GestorEstudiantes *gestor, const char *nombre);
Estudiante *BuscarRangoEdad(GestorEstudiantes *gestor, int v1, int v2);
void freeGestorEstudiantes(GestorEstudiantes *gestor);
#endif
