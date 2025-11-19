#ifndef CARRERA_H
#define CARRERA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../estructuras/headersEstructuras/doublelinkedlist.h"
#include "materias.h"
#include "estudiantes.h"
#include "../../gestores/headersGestores/gestorMaterias.h"

typedef struct Carrera {
    int ID; // asignado por el gestor
    char nombre[50];
    // Lista de materias asociadas a la carrera (punteros a Materia)
    DoubleLinkedNode *listaMaterias;
    // Lista de estudiantes que pertenecen a la carrera (punteros a Estudiante)
    DoubleLinkedNode *listaEstudiantes;
} Carrera;

// Constructor / Destructor
Carrera *NewCarrera(const char *nombre);
void freeCarrera(Carrera *c);

// Getters / Setters
const char *ObtenerNombreCarrera(const Carrera *c);
void CambiarNombreCarrera(Carrera *c, const char *nombre);
// ID
int ObtenerIDCarrera(const Carrera *c);
void CambiarIDCarrera(Carrera *c, int id);

// Acceso a las listas internas
DoubleLinkedNode *ObtenerListaMaterias(const Carrera *c);
DoubleLinkedNode *ObtenerListaEstudiantes(const Carrera *c);

// Agregar elementos
// Añade una materia (puntero) a la lista de materias de la carrera
void AgregarMateriaALaCarrera(Carrera *c, Materia *materia);
// Busca la materia en el gestor por ID y, si existe, la añade a la carrera
int AgregarMateriaALaCarreraPorID(Carrera *c, GestorMaterias *gestor, int idMateria);

// Añade un estudiante a la carrera
void AgregarEstudianteALaCarrera(Carrera *c, Estudiante *est);

// Cantidades
int ObtenerCantidadDeMaterias(const Carrera *c);
int ObtenerCantidadDeEstudiantes(const Carrera *c);

// Filtrado / utilidades específicas (definida en carrera.c)
void FiltrarEstudiantesPorMateriaYSexo(GestorMaterias *gestor, int idMateria, int sexoBuscado);

#endif 