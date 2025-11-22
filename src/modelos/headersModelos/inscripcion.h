#ifndef INSCRIPCION_H
#define INSCRIPCION_H

#include "estudiantes.h"
#include <stdlib.h>

typedef struct Inscripcion {
    Estudiante *estudiante;
    int estaAprobado;
} Inscripcion;

Inscripcion *NewInscripcion(Estudiante *e, int aprobado);
void FreeInscripcion(Inscripcion *i);

#endif