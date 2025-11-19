#ifndef GESTORCARRERAS_H
#define GESTORCARRERAS_H

#include "../../estructuras/headersEstructuras/doublelinkedlist.h"
#include "../../modelos/headersModelos/carrera.h"

typedef struct GestorCarreras {
    DoubleLinkedNode *head_carreras;
    int next_ID;
} GestorCarreras;

GestorCarreras *NewGestorCarreras(void);
void AgregarCarrera(GestorCarreras *gestor, const char *nombre);

Carrera *BuscarCarreraPorID(GestorCarreras *gestor, int ID);
Carrera *BuscarCarreraPorNombre(GestorCarreras *gestor, const char *nombre);
void EliminarCarrera(GestorCarreras *gestor, int ID);
void MatricularEstudianteEnCarrera(GestorCarreras *gestor, int ID_carrera, Estudiante *estudiante);
void FreeGestorCarreras(GestorCarreras *gestor);

#endif // GESTORCARRERAS_H
