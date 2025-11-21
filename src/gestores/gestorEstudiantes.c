#include "headersGestores/gestorEstudiantes.h"
#include <stdio.h> // Para printf
/**
 * Crea un nuevo gestor inicializando su linked list.
 */
GestorEstudiantes *NewGestorEstudiantes()
{
    GestorEstudiantes *gestor = malloc(sizeof(GestorEstudiantes));
    gestor->estudiantes = NULL;
    gestor->next_ID = 1;
    return gestor;
}

/**
 * Actualiza la id del estudiante enviado y lo añade a la linked list de la estructura del gestor.
 */
void ListarEstudiante(GestorEstudiantes *gestor, Estudiante *estudiante)
{
    if (gestor == NULL)
    {
        return;
    }
    if (estudiante == NULL)
    {
        return;
    }
    estudiante->ID = gestor->next_ID;
    gestor->next_ID++;
    gestor->estudiantes = appendNode(gestor->estudiantes, estudiante);
}

/**
 * Elimina un estudiante segun la id enviada
 */
void DeslistarEstudianteID(GestorEstudiantes *gestor, int id)
{
    if (gestor == NULL)
    {
        return;
    }
    Estudiante *busqueda = BuscarEstudianteID(gestor, id);
    if (busqueda == NULL)
    {
        return;
    }
    gestor->estudiantes = removeData(gestor->estudiantes, busqueda);
}

/**
 * Devuelve un estudiante buscado por su id.
 */
Estudiante *BuscarEstudianteID(GestorEstudiantes *gestor, int id)
{
    LinkedNode *cursor = gestor->estudiantes;
    while (cursor != NULL)
    {
        if (ObtenerID(cursor->data) == id)
        {
            return cursor->data;
        }
        cursor = cursor->next;
    }
    return NULL;
}

/**
 * Devuelve un estudiante buscado por su nombre.
 */
Estudiante *BuscarEstudianteNombre(GestorEstudiantes *gestor, const char *nombre)
{
    LinkedNode *cursor = gestor->estudiantes;
    while (cursor != NULL)
    {
        if (strcmp(ObtenerNombre(cursor->data), nombre) == 0)
        {
            return cursor->data;
        }
        cursor = cursor->next;
    }
    return NULL;
}

/**
 * Devuelve los estudiantes que cumplan el rango de edad enviado como parametros.
 * La busqueda verifica edades entre "v1" y "v2" incluyendo los mismos valores.
 */
LinkedNode *BuscarRangoEdad(GestorEstudiantes *gestor, int v1, int v2)
{
    LinkedNode *resultados = NULL;
    LinkedNode *cursor = gestor->estudiantes;

    while (cursor != NULL)
    {
        if (ObtenerEdad(cursor->data) >= v1 && ObtenerEdad(cursor->data) <= v2)
        {
            resultados = appendNode(resultados, cursor->data);
        }
        cursor = cursor->next;
    }
    return resultados;
}

void freeGestorEstudiantes(GestorEstudiantes *gestor)
{
    if (gestor == NULL)
        return;
    freeList(gestor->estudiantes);
    free(gestor);
}

// *******************************************************
// FUNCIONES DE GESTIÓN DEL HISTORIAL
// *******************************************************

int HaAprobadoMateriaGestor(const Estudiante *e, int ID_materia)
{
    if (e == NULL || e->materiasAprobadas == NULL)
    {
        return 0;
    }

    LinkedNode *cursor = e->materiasAprobadas;
    while (cursor != NULL)
    {
        int *ID_aprobado = (int *)cursor->data;

        if (ID_aprobado != NULL && *ID_aprobado == ID_materia)
        {
            return 1;
        }
        cursor = cursor->next;
    }
    return 0;
}

void AprobarMateriaGestor(Estudiante *e, int ID_materia)
{
    if (e == NULL)
        return;

    if (HaAprobadoMateriaGestor(e, ID_materia))
    {
        printf("Advertencia: Materia %d ya aprobada.\n", ID_materia);
        return;
    }

    int *nuevoID = (int *)malloc(sizeof(int));
    if (nuevoID == NULL)
    {
        return;
    }
    *nuevoID = ID_materia;

    // Usamos la función appendNode de tu linkedList_n.c
    e->materiasAprobadas = appendNode(e->materiasAprobadas, nuevoID);
}

void CambiarEstadoGraduadoGestor(Estudiante *e, int estado)
{
    if (e != NULL)
    {
        e->esGraduado = estado;
    }
}