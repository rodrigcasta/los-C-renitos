#ifndef INSCRIPCION_H
#define INSCRIPCION_H

#include <stdlib.h>
// Necesitamos Estudiante para el puntero interno
#include "estudiantes.h"

typedef struct Inscripcion {
    Estudiante *estudiante; // Puntero al alumno matriculado
    int estaAprobado;       // 1 = Aprobado, 0 = Reprobado (para la estadística)
} Inscripcion;

Inscripcion *NewInscripcion(Estudiante *e, int aprobado);
void FreeInscripcion(Inscripcion *i);

#endif