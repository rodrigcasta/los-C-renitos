#ifndef GESTORMATERIAS_H
#define GESTORMATERIAS_H

#include "../../estructuras/headersEstructuras/doublelinkedlist.h"
#include "../../modelos/headersModelos/estudiantes.h"
#include "../../modelos/headersModelos/materias.h"
#include "gestorEstudiantes.h"

typedef struct GestorMaterias {
    DoubleLinkedNode *head_materias;
    int next_ID;
} GestorMaterias;

GestorMaterias *NewGestorMaterias();
void AgregarMateria(GestorMaterias *gestor, const char *nombre);

Materia *BuscarMateriaPorID(GestorMaterias *gestor, int ID);
void EliminarMateria(GestorMaterias *gestor, int ID);

// void MatricularEstudiante(GestorMaterias *gestor, int ID_materia, Estudiante *estudiante);

// --- DECLARACIONES DE FUNCIONES NUEVAS/MODIFICADAS ---

// Función para añadir requisitos a una materia
void AgregarCorrelativa(Materia *materia, int ID_correlativa);
// Función que verifica si un estudiante cumple los requisitos
int CumpleCorrelativas(Materia *materia, Estudiante *estudiante);
// Función modificada para verificar correlativas y usar Inscripcion
void MatricularEstudiante(GestorMaterias *gestor, int ID_materia, Estudiante *estudiante, int aprobado_inicial);

void FreeGestorMaterias(GestorMaterias *gestor);

#endif