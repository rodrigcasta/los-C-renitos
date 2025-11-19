#include <stdlib.h>
#include <string.h>
#include "../headersGestores/gestorCarreras.h"

// Crear nueva carrera
Carrera *NewCarrera_local(const char *nombre) {
    return NewCarrera(nombre);
}

GestorCarreras *NewGestorCarreras() {
    GestorCarreras *gestor = malloc(sizeof(GestorCarreras));
    if (gestor == NULL) return NULL;
    gestor->head_carreras = newDoubleLinkedList();
    gestor->next_ID = 1;
    return gestor;
}

void AgregarCarrera(GestorCarreras *gestor, const char *nombre) {
    if (gestor == NULL) return;

    Carrera *c = NewCarrera_local(nombre);
    if (c == NULL) return;

    c->ID = gestor->next_ID;
    gestor->next_ID++;

    gestor->head_carreras = addElement(gestor->head_carreras, c);
}

Carrera *BuscarCarreraPorID(GestorCarreras *gestor, int ID) {
    if (gestor == NULL || gestor->head_carreras == NULL) return NULL;
    DoubleLinkedNode *current = gestor->head_carreras;
    while (current != NULL) {
        Carrera *c = (Carrera *)current->data;
        if (c->ID == ID) return c;
        current = current->next;
    }
    return NULL;
}

Carrera *BuscarCarreraPorNombre(GestorCarreras *gestor, const char *nombre) {
    if (gestor == NULL || gestor->head_carreras == NULL || nombre == NULL) return NULL;
    DoubleLinkedNode *current = gestor->head_carreras;
    while (current != NULL) {
        Carrera *c = (Carrera *)current->data;
        if (strcmp(c->nombre, nombre) == 0) return c;
        current = current->next;
    }
    return NULL;
}

void EliminarCarrera(GestorCarreras *gestor, int ID) {
    if (gestor == NULL || gestor->head_carreras == NULL) return;
    DoubleLinkedNode *current = gestor->head_carreras;
    int posicion = 0;
    while (current != NULL) {
        Carrera *c = (Carrera *)current->data;
        if (c->ID == ID) {
            Carrera *c_a_liberar = (Carrera *)RemoveElement(&gestor->head_carreras, posicion);
            if (c_a_liberar != NULL) {
                FreeCarrera(c_a_liberar);
            }
            return;
        }
        current = current->next;
        posicion++;
    }
}

void MatricularEstudianteEnCarrera(GestorCarreras *gestor, int ID_carrera, Estudiante *estudiante) {
    Carrera *c = BuscarCarreraPorID(gestor, ID_carrera);
    if (c == NULL || estudiante == NULL) return;
    c->listaEstudiantes = addElement(c->listaEstudiantes, estudiante);
}

void FreeGestorCarreras(GestorCarreras *gestor) {
    if (gestor == NULL) return;
    DoubleLinkedNode *current = gestor->head_carreras;
    DoubleLinkedNode *next;
    while (current != NULL) {
        next = current->next;
        Carrera *c = (Carrera *)current->data;
        FreeCarrera(c);
        free(current);
        current = next;
    }
    free(gestor);
}

// constructor de GestorDeCarreras()
// ObtenerCantidadDeCarreras() return total de carreras
// getters y setters
// añadir y eliminar carrera

// AnotarseALaCarrera >> llama al metodo AgregarEstudianteALaCarrera

// ObtenerCarreras() >> Te devuelve todas las carreras con su ID
// ObtenerCarrera (ID) devuelvo la carrera especifica