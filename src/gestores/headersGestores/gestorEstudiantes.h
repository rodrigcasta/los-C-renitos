#ifndef GESTORESTUDIANTES_H
#define GESTORESTUDIANTES_H

#include "../../estructuras/headersEstructuras/linkedList_n.h"
#include "../../modelos/headersModelos/estudiantes.h"

// Definimos la cantidad total de materias que debe aprobar un estudiante para graduarse
// Asumimos 30 materias basándonos en generadorAleatorio.c
#define MATERIAS_PARA_GRADUACION 30

typedef struct GestorEstudiantes {
    LinkedNode *estudiantes;
    int next_ID;
} GestorEstudiantes;

GestorEstudiantes *NewGestorEstudiantes();

void ListarEstudiante(GestorEstudiantes *gestor, Estudiante *estudiante);

void DeslistarEstudianteID(GestorEstudiantes *gestor, int id);

Estudiante *BuscarEstudianteID(GestorEstudiantes *gestor, int id);
Estudiante *BuscarEstudianteNombre(GestorEstudiantes *gestor, const char *nombre);
LinkedNode *BuscarRangoEdad(GestorEstudiantes *gestor, int v1, int v2);

void AprobarMateriaGestor(Estudiante *e, int ID_materia);
int HaAprobadoMateriaGestor(const Estudiante *e, int ID_materia);
void CambiarEstadoGraduadoGestor(Estudiante *e, int estado);

void VerificarGraduacion(Estudiante *e);
void freeGestorEstudiantes(GestorEstudiantes *gestor);
#endif