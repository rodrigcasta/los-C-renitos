#include "los-c-renitos/src/estructuras/linkedList_n.c"
#include "los-c-renitos/src/modelos/estudiantes.c"

typedef struct GestorEstudiantes {
    LinkedNode *estudiantes
} GestorEstudiantes;

/*
listar estudiantes

-Buscar estudiantes por nombre

-Buscar estudiantes por rango de edad
*/

GestorEstudiantes *NewGestorEstudiantes() {
    GestorEstudiantes *gestor = malloc(sizeof(GestorEstudiantes));
    gestor->estudiantes = newLinkedNode();
    return gestor;
}

void ListarEstudiante(GestorEstudiantes *gestor, Estudiante *estudiante) {
    gestor->estudiantes = appendNode(gestor->estudiantes, estudiante);
}

void DeslistarEstudiante(GestorEstudiantes *gestor, Estudiante *nombre) {
    gestor->estudiantes = removeTail(gestor->estudiantes);
}

/**
 * replantear como hacerlo devolviendo una nueva linked list con mas
 *  de un resultado (para hacer la edad).
 */
Estudiante *BuscarEstudiante(GestorEstudiantes *gestor, const char *nombre) {
    Estudiante *busqueda;
    LinkedNode *cursor = gestor->estudiantes;
    while (cursor != NULL || ObtenerNombre(cursor->data) != nombre) {
        cursor = cursor->next;
    }
    busqueda = cursor->data;
    return busqueda;
}
