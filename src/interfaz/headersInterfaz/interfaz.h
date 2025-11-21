#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "../../estadisticas/headersEstadisticas/estadisticas.h"
#include "../../gestores/headersGestores/gestorEstudiantes.h"
#include "../../gestores/headersGestores/gestorMaterias.h"
#include "../../utils/headersUtils/utilidades.h"
#include <stdio.h>

// Definiciones de funciones de impresión
void MostrarEstudianteSimple(const Estudiante *e);
void MostrarMateriasDisponibles(GestorMaterias *gm);
void MostrarMateriasAprobadasEstudiante(const Estudiante *e, GestorMaterias *gm);
void MostrarEstudiantesBusqueda(LinkedNode *listaResultados);
void MostrarEstudiantesLista(GestorEstudiantes *ge);

// Definiciones de funciones de gestión de estudiante
void AltaEstudiante(GestorEstudiantes *ge);
void EliminarEstudiante(GestorEstudiantes *ge);
void BuscarEstudiante(GestorEstudiantes *ge);
void MenuAccederEstudiante(Estudiante *e, GestorMaterias *gm, GestorEstudiantes *ge);
void MenuModificarEstudiante(Estudiante *e);
void RendirMateria(Estudiante *e, Materia *materia);
void DarDeBajaInscripcion(Estudiante *e, Materia *materia);

// Definiciones de funciones de gestión de materia
void AltaMateria(GestorMaterias *gm);
void ModificarNombreMateria(GestorMaterias *gm);
void EliminarMateriaCLI(GestorMaterias *gm); // Renombrada para evitar conflicto con la función de gestorMaterias.c

// Menús principales
void MenuPrincipal(GestorEstudiantes *ge, GestorMaterias *gm);
void MenuGestorEstudiantes(GestorEstudiantes *ge, GestorMaterias *gm);
void MenuGestorMaterias(GestorMaterias *gm);
void MenuEstadisticas(GestorEstudiantes *ge, GestorMaterias *gm);

#endif