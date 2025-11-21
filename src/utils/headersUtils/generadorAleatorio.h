#ifndef GENERADORALEATORIO_H
#define GENERADORALEATORIO_H

#include "../../gestores/headersGestores/gestorMaterias.h"

void GenerarMateriasAleatorias(GestorMaterias *gestor);
void GenerarEstudiantesAleatorios(GestorEstudiantes *gestor, int cantidad);
void ImprimirMaterias(GestorMaterias *gestor);

#endif