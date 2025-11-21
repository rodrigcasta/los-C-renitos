#include "headersGestores/gestorMaterias.h"
#include <stdlib.h>
#include <string.h>

// Materia *NewMateria(const char *nombre)
// {
//     Materia *m = malloc(sizeof(Materia));
//     if (m == NULL)
//         return NULL;

//     // El ID será asignado por el gestor
//     m->ID = 0;
//     strcpy(m->nombre, nombre);
//     m->listaEstudiantes = NULL;
//     return m;
// }

Materia *NewMateria(const char *nombre)
{
    Materia *m = malloc(sizeof(Materia));
    if (m == NULL)
        return NULL;

    m->ID = 0;
    strcpy(m->nombre, nombre);

    m->listaEstudiantes = NULL;
    m->listaInscripciones = NULL;
    m->correlativasID = NULL;

    return m;
}

GestorMaterias *NewGestorMaterias()
{
    GestorMaterias *gestor = malloc(sizeof(GestorMaterias));
    if (gestor == NULL)
        return NULL;
    gestor->head_materias = newDoublyLinkedList();
    gestor->next_ID = 1;
    return gestor;
}

void AgregarMateria(GestorMaterias *gestor, const char *nombre)
{
    if (gestor == NULL)
        return;

    Materia *nuevaMateria = NewMateria(nombre);
    if (nuevaMateria == NULL)
        return;

    nuevaMateria->ID = gestor->next_ID;
    gestor->next_ID++;

    gestor->head_materias = addElement(gestor->head_materias, nuevaMateria);
}

Materia *BuscarMateriaPorID(GestorMaterias *gestor, int ID)
{
    if (gestor == NULL || gestor->head_materias == NULL)
    {
        return NULL;
    }

    DoubleLinkedNode *current = gestor->head_materias;
    while (current != NULL)
    {
        Materia *materia = (Materia *)current->data;
        if (materia->ID == ID)
        {
            return materia;
        }
        current = current->next;
    }
    return NULL;
}

void EliminarMateria(GestorMaterias *gestor, int ID)
{
    if (gestor == NULL || gestor->head_materias == NULL)
    {
        return;
    }

    DoubleLinkedNode *current = gestor->head_materias;
    int posicion = 0;

    while (current != NULL)
    {
        Materia *materia = (Materia *)current->data;
        if (materia->ID == ID)
        {
            // 1. Llamar a la función que devuelve los datos
            Materia *materia_a_liberar = (Materia *)RemoveElement(&gestor->head_materias, posicion);

            // 2. Liberar la estructura Materia y su lista anidada
            if (materia_a_liberar != NULL)
            {
                FreeMateria(materia_a_liberar);
            }
            return;
        }
        current = current->next;
        posicion++;
    }
}

void MatricularEstudiante(GestorMaterias *gestor, int ID_materia, Estudiante *estudiante, int aprobado_inicial)
{
    Materia *materia = BuscarMateriaPorID(gestor, ID_materia);

    if (materia == NULL || estudiante == NULL)
    {
        printf("Error: Materia o Estudiante no encontrados.\n");
        return;
    }

    // --- 1. VERIFICACIÓN DE DUPLICADOS (NUEVA LÓGICA) ---
    DoubleLinkedNode *cursor = materia->listaInscripciones;
    while (cursor != NULL)
    {
        Inscripcion *insc = (Inscripcion *)cursor->data;
        // Comprobar si la dirección de memoria del estudiante es la misma
        if (insc->estudiante == estudiante)
        {
            printf("⚠️ INSCRIPCIÓN FALLIDA: El estudiante ya está matriculado en esta materia.\n");
            return;
        }
        cursor = cursor->next;
    }
    // ----------------------------------------------------

    // 2. VERIFICACIÓN DE CORRELATIVIDAD (Mueve el paso original)
    if (CumpleCorrelativas(materia, estudiante) == 0)
    {
        printf("⚠️ INSCRIPCIÓN FALLIDA: No cumple con las correlativas.\n");
        return;
    }

    // 3. CREAR INSCRIPCIÓN
    Inscripcion *nuevaInscripcion = NewInscripcion(estudiante, aprobado_inicial);
    if (nuevaInscripcion == NULL)
        return;

    // 4. AÑADIR A LA LISTA DE INSCRIPCIONES
    materia->listaInscripciones = addElement(materia->listaInscripciones, nuevaInscripcion);
    printf("✅ INSCRIPCIÓN EXITOSA.\n");
}
// void FreeMateria(Materia *materia)
// {
//     if (materia == NULL)
//         return;
//     FreeDoubleLinkedListNodes(materia->listaEstudiantes);
//     free(materia);
// }

void FreeMateria(Materia *materia)
{
    if (materia == NULL)
        return;

    // 1. Liberar la lista de inscripciones (donde se guardan las Inscripcion*)
    FreeDoubleLinkedListNodes(materia->listaInscripciones);

    // 2. Liberar la lista de estudiantes (si es que se usa en otra parte)
    // Es posible que listaEstudiantes y listaInscripciones sean lo mismo o solo uses uno.
    // Si usas ambos, asegúrate de no liberar dos veces la misma lista.
    // Dejo la liberación de listaEstudiantes por si fuera otra lista diferente.
    FreeDoubleLinkedListNodes(materia->listaEstudiantes);

    // 3. Liberar la lista de correlativas (si FreeLinkedListNodes libera el data (int*))
    // NOTA: Asume que tienes una función para la lista simple.
    // FreeLinkedListNodes(materia->correlativasID);

    free(materia);
}

// **********************************************
// FUNCIONES DE CORRELATIVIDAD
// **********************************************

void AgregarCorrelativa(Materia *materia, int ID_correlativa)
{
    if (materia == NULL)
        return;

    int *nuevoID = (int *)malloc(sizeof(int));
    if (nuevoID == NULL)
        return;
    *nuevoID = ID_correlativa;

    // Usamos appendNode de tu linkedList_n.c en el campo correlativasID
    materia->correlativasID = appendNode(materia->correlativasID, nuevoID);
}

int CumpleCorrelativas(Materia *materia, Estudiante *estudiante)
{
    if (materia == NULL || estudiante == NULL || materia->correlativasID == NULL)
    {
        return 1; // Si no hay correlativas, se asume que cumple.
    }

    LinkedNode *cursor = materia->correlativasID;

    while (cursor != NULL)
    {
        int *ID_correlativa_ptr = (int *)cursor->data;
        if (ID_correlativa_ptr == NULL)
            continue;

        int ID_correlativa = *ID_correlativa_ptr;

        // Usamos la función del GestorEstudiantes para verificar
        if (HaAprobadoMateriaGestor(estudiante, ID_correlativa) == 0)
        {
            return 0; // Falla: Le falta una correlativa
        }

        cursor = cursor->next;
    }

    return 1; // Cumple con todas
}

void FreeGestorMaterias(GestorMaterias *gestor)
{
    if (gestor == NULL)
        return;

    DoubleLinkedNode *current = gestor->head_materias;
    DoubleLinkedNode *next;

    while (current != NULL)
    {
        next = current->next;
        Materia *materia = (Materia *)current->data;

        FreeMateria(materia);

        free(current);

        current = next;
    }

    free(gestor);
}