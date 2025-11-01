#ifndef GESTORMATERIAS_H
#define GESTORMATERIAS_H

#include "../../modelos/headersModelos/materias.h" 
#include "../../estructuras/headersEstructuras/doublelinkedlist.h" 
#include "../../modelos/headersModelos/estudiantes.h" 

typedef struct GestorMaterias {
    DoubleLinkedNode *head_materias; 
    int next_ID;                     
} GestorMaterias;

GestorMaterias *NewGestorMaterias();
void AgregarMateria(GestorMaterias *gestor, const char *nombre);

Materia *BuscarMateriaPorID(GestorMaterias *gestor, int ID);
void EliminarMateria(GestorMaterias *gestor, int ID);
void MatricularEstudiante(GestorMaterias *gestor, int ID_materia, Estudiante *estudiante);
void FreeGestorMaterias(GestorMaterias *gestor);

#endif