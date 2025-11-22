#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "../../estadisticas/headersEstadisticas/estadisticas.h"
#include "../../gestores/headersGestores/gestorEstudiantes.h"
#include "../../gestores/headersGestores/gestorMaterias.h"
#include "../../utils/headersUtils/utilidades.h"
#include <stdio.h>

void MostrarEstudianteSimple(const Estudiante *e);
void MostrarMateriasDisponibles(GestorMaterias *gm);
void MostrarMateriasAprobadasEstudiante(const Estudiante *e, GestorMaterias *gm);
void MostrarEstudiantesBusqueda(LinkedNode *listaResultados);
void MostrarEstudiantesLista(GestorEstudiantes *ge);

void AltaEstudiante(GestorEstudiantes *ge);
void EliminarEstudiante(GestorEstudiantes *ge);
void BuscarEstudiante(GestorEstudiantes *ge);
void MenuAccederEstudiante(Estudiante *e, GestorMaterias *gm, GestorEstudiantes *ge);
void MenuModificarEstudiante(Estudiante *e);
void RendirMateria(Estudiante *e, Materia *materia);
void DarDeBajaInscripcion(Estudiante *e, Materia *materia);

void AltaMateria(GestorMaterias *gm);
void ModificarNombreMateria(GestorMaterias *gm);
void EliminarMateriaCLI(GestorMaterias *gm);

void MenuPrincipal(GestorEstudiantes *ge, GestorMaterias *gm);
void MenuGestorEstudiantes(GestorEstudiantes *ge, GestorMaterias *gm);
void MenuGestorMaterias(GestorMaterias *gm);
void MenuEstadisticas(GestorEstudiantes *ge, GestorMaterias *gm);

#endif