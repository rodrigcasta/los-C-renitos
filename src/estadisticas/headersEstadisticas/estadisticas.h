#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include "../../gestores/headersGestores/gestorEstudiantes.h"
#include "../../gestores/headersGestores/gestorMaterias.h"
#include "../../modelos/headersModelos/inscripcion.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct EstadisticasGenerales {
    int totalAlumnos;
    int totalMaterias;
    int totalGraduados;
} EstadisticasGenerales;

EstadisticasGenerales *CalcularEstadisticasGenerales(GestorEstudiantes *ge, GestorMaterias *gm);
void MostrarEstadisticasGenerales(EstadisticasGenerales *stats);

float CalcularPromedioAprobadosMateria(Materia *materia);
void MostrarPromedioAprobadosPorMateria(GestorMaterias *gm);

#endif