#include "headersGestores/gestorEstudiantes.h"

/**
 * Crea un nuevo gestor inicializando su linked list.
 */
GestorEstudiantes *NewGestorEstudiantes() {
    GestorEstudiantes *gestor = malloc(sizeof(GestorEstudiantes));
    gestor->estudiantes = newLinkedNode();
    gestor->next_ID = 1;
    return gestor;
}

/**
 * Actualiza la id del estudiante enviado y lo añade a la linked list de la estructura del gestor.
 */
void ListarEstudiante(GestorEstudiantes *gestor, Estudiante *estudiante) {
    if (gestor == NULL) {
        return;
    }
    if (estudiante == NULL) {
        return;
    }
    estudiante->ID = gestor->next_ID;
    gestor->next_ID++;
    gestor->estudiantes = appendNode(gestor->estudiantes, estudiante);
}

/**
 * Elimina un estudiante segun la id enviada
 */
void DeslistarEstudianteID(GestorEstudiantes *gestor, int id) {
    if (gestor == NULL) {
        return;
    }
    Estudiante *busqueda = BuscarEstudianteID(gestor, id);
    if (busqueda == NULL) {
        return;
    }
    gestor->estudiantes = removeData(gestor->estudiantes, busqueda);
}

/**
 * Devuelve un estudiante buscado por su id.
 */
Estudiante *BuscarEstudianteID(GestorEstudiantes *gestor, int id) {
    LinkedNode *cursor = gestor->estudiantes;
    while (cursor != NULL) {
        if (ObtenerID(cursor->data) == id) {
            return cursor->data;
        }
    }
    return NULL;
}

/**
 * Devuelve un estudiante buscado por su nombre.
 */
Estudiante *BuscarEstudianteNombre(GestorEstudiantes *gestor, const char *nombre) {
    LinkedNode *cursor = gestor->estudiantes;
    while (cursor != NULL) {
        if (ObtenerNombre(cursor->data) == nombre) {
            return cursor->data;
        }
    }
    return NULL;
}

/**
 * Devuelve el primer estudiante que cumpla el rango de edad enviado como parametros.
 * La busqueda busca edades entre "v1" y "v2" incluyendo los mismos valores.
 */
Estudiante *BuscarRangoEdad(GestorEstudiantes *gestor, int v1, int v2) {
    LinkedNode *cursor = gestor->estudiantes;
    while (cursor != NULL) {
        if (ObtenerID(cursor->data) >= v1 && ObtenerID(cursor->data) <= v2) {
            return cursor->data;
        }
    }
    return NULL;
}
