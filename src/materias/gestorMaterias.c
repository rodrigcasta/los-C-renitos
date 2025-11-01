#include "gestorMaterias.h"
#include <stdlib.h>
#include <string.h>



Materia *NewMateria(const char *nombre) {
    Materia *m = malloc(sizeof(Materia));
    if (m == NULL) return NULL;
    
    // El ID será asignado por el gestor
    m->ID = 0; 
    strcpy(m->nombre, nombre);
    m->listaEstudiantes = NULL; 
    return m;
}



GestorMaterias *NewGestorMaterias() {
    GestorMaterias *gestor = malloc(sizeof(GestorMaterias));
    if (gestor == NULL) return NULL;
    gestor->head_materias = newDoublyLinkedList();
    gestor->next_ID = 1; 
    return gestor;
}



void AgregarMateria(GestorMaterias *gestor, const char *nombre) {
    if (gestor == NULL) return;


    Materia *nuevaMateria = NewMateria(nombre); 
    if (nuevaMateria == NULL) return;

    nuevaMateria->ID = gestor->next_ID;
    gestor->next_ID++;

    gestor->head_materias = addElement(gestor->head_materias, nuevaMateria);
}
Materia *BuscarMateriaPorID(GestorMaterias *gestor, int ID) {
    if (gestor == NULL || gestor->head_materias == NULL) {
        return NULL;
    }

    DoubleLinkedNode *current = gestor->head_materias;
    while (current != NULL) {
        Materia *materia = (Materia *)current->data;
        if (materia->ID == ID) {
            return materia;
        }
        current = current->next;
    }
    return NULL;
}


void EliminarMateria(GestorMaterias *gestor, int ID) {
    if (gestor == NULL || gestor->head_materias == NULL) {
        return;
    }

    DoubleLinkedNode *current = gestor->head_materias;
    int posicion = 0;
    
    while (current != NULL) {
        Materia *materia = (Materia *)current->data;
        if (materia->ID == ID) {
            
            Remove(&gestor->head_materias, posicion);
            return;
        }
        current = current->next;
        posicion++;
    }
}


void MatricularEstudiante(GestorMaterias *gestor, int ID_materia, Estudiante *estudiante) {
    Materia *materia = BuscarMateriaPorID(gestor, ID_materia);
    if (materia == NULL || estudiante == NULL) {
        return;
    }

    materia->listaEstudiante = addElement(materia->listaEstudiante, estudiante);
}