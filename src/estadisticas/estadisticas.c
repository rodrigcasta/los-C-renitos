// src/estadisticas/estadisticas.c

#include "headersEstadisticas/estadisticas.h"

// ****************************************************
// ESTADÍSTICAS GENERALES
// ****************************************************

EstadisticasGenerales *CalcularEstadisticasGenerales(GestorEstudiantes *ge, GestorMaterias *gm)
{
    if (ge == NULL || gm == NULL)
        return NULL;

    EstadisticasGenerales *stats = (EstadisticasGenerales *)malloc(sizeof(EstadisticasGenerales));
    if (stats == NULL)
        return NULL;

    stats->totalAlumnos = 0;
    stats->totalGraduados = 0;

    // Contar Alumnos y Graduados (depende de Estudiante->esGraduado)
    LinkedNode *cursorEstudiante = ge->estudiantes;
    while (cursorEstudiante != NULL)
    {
        stats->totalAlumnos++;
        Estudiante *est = (Estudiante *)cursorEstudiante->data;
        if (est->esGraduado == 1)
        {
            stats->totalGraduados++;
        }
        cursorEstudiante = cursorEstudiante->next;
    }

    // Contar Materias
    stats->totalMaterias = 0;
    DoubleLinkedNode *cursorMateria = gm->head_materias;
    while (cursorMateria != NULL)
    {
        stats->totalMaterias++;
        cursorMateria = cursorMateria->next;
    }

    return stats;
}

void MostrarEstadisticasGenerales(EstadisticasGenerales *stats)
{
    if (stats == NULL)
    {
        printf("\nNo hay estadisticas generales disponibles.\n");
        return;
    }

    printf("\n--- ESTADISTICAS GENERALES ---\n");
    printf("1. Cantidad total de alumnos en la carrera: %d\n", stats->totalAlumnos);
    printf("2. Cantidad total de materias ofrecidas: %d\n", stats->totalMaterias);
    printf("3. Cantidad de alumnos graduados: %d\n", stats->totalGraduados);
    printf("------------------------------------\n");
}

// ****************************************************
// ESTADÍSTICA DE PROMEDIO DE APROBADOS
// ****************************************************

float CalcularPromedioAprobadosMateria(Materia *materia)
{
    if (materia == NULL || materia->listaInscripciones == NULL)
    {
        return 0.0f;
    }

    int totalInscritos = 0;
    int totalAprobados = 0;

    // Recorre la lista de Inscripciones (depende de Inscripcion->estaAprobado)
    DoubleLinkedNode *current = materia->listaInscripciones;
    while (current != NULL)
    {
        totalInscritos++;

        Inscripcion *insc = (Inscripcion *)current->data;

        if (insc->estaAprobado == 1)
        {
            totalAprobados++;
        }

        current = current->next;
    }

    if (totalInscritos == 0)
    {
        return 0.0f;
    }

    return (float)totalAprobados / totalInscritos;
}

void MostrarPromedioAprobadosPorMateria(GestorMaterias *gm)
{
    if (gm == NULL || gm->head_materias == NULL)
    {
        printf("\nNo hay materias registradas.\n");
        return;
    }

    printf("\n--- PROMEDIO DE APROBADOS POR MATERIA ---\n");
    DoubleLinkedNode *cursorMateria = gm->head_materias;

    while (cursorMateria != NULL)
    {
        Materia *materia = (Materia *)cursorMateria->data;
        float promedio = CalcularPromedioAprobadosMateria(materia);

        printf("Materia ID %d (%s): %.2f%% de Aprobacion.\n", materia->ID, materia->nombre, promedio * 100.0f);

        cursorMateria = cursorMateria->next;
    }
    printf("------------------------------------------\n");
}