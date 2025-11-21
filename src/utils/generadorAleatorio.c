#include "generadorAleatorio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *NOMBRES_MATERIAS[] = {"Introducción a la Ingeniería en Computación",
                                  "Algoritmos y Programación II",
                                  "Algebra I",
                                  "Matemática Discreta",
                                  "Algoritmos y Programación II",
                                  "Programación de bajo nivel",
                                  "Algebra II",
                                  "Diseño Lógico",
                                  "Inglés",
                                  "Sistemas Operativos"};

const int NUM_NOMBRES = sizeof(NOMBRES_MATERIAS) / sizeof(NOMBRES_MATERIAS[0]);

void GenerarMateriasAleatorias(GestorMaterias *gestor, int cantidad) {
    if (gestor == NULL || cantidad <= 0) {
        return;
    }

    srand(time(NULL));

    for (int i = 0; i < cantidad; i++) {
        int indiceNombre = rand() % NUM_NOMBRES;
        const char *nombre = NOMBRES_MATERIAS[indiceNombre];

        int notaEntera = (rand() % 31) + 40;
        double notaMinima = (double)notaEntera / 10.0;

        // Se llama a la función AgregarMateria definida en gestorMaterias.c
        AgregarMateria(gestor, nombre);
    }
}

void ImprimirMaterias(GestorMaterias *gestor) {
    if (gestor == NULL || gestor->head_materias == NULL) {
        printf("No hay materias en el gestor.\n");
        return;
    }

    DoubleLinkedNode *current = gestor->head_materias;

    while (current != NULL) {
        Materia *m = (Materia *)current->data;

        printf("ID: %d | Nombre: %s\n", m->ID, m->nombre);

        current = current->next;
    }
}