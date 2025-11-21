#include "headersUtils/generadorAleatorio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *NOMBRES_ESTUDIANTES[] = {"Alejandro", "Sofia",   "Carlos", "Valentina", "Diego",  "Camila",
                                     "Javier",    "Mariana", "Pablo",  "Laura",     "Andres", "Valeria"};
const char *APELLIDOS_ESTUDIANTES[] = {"Gomez",  "Rodriguez", "Lopez",  "Martinez", "Diaz",   "Perez",
                                       "Garcia", "Sanchez",   "Romero", "Torres",   "Flores", "Ruiz"};
const int NUM_NOMBRES_E = sizeof(NOMBRES_ESTUDIANTES) / sizeof(NOMBRES_ESTUDIANTES[0]);
const int NUM_APELLIDOS_E = sizeof(APELLIDOS_ESTUDIANTES) / sizeof(APELLIDOS_ESTUDIANTES[0]);

const char *NOMBRES_MATERIAS[] = {
    "Introduccion a la Ingenieria en Computacion",
    "Algoritmos y Programacion I",
    "Algebra I",
    "Matematica Discreta",
    "Algoritmos y Programacion II",
    "Programacion de bajo nivel",
    "Algebra II",
    "Disenio Logico",
    "Ingles",
    "Sistemas Operativos",
    "Ingenieria en Software",
    "Fisica I",
    "Fisica II",
    "Redes de Computadoras",
    "Matematicas Especiales",
    "Probabilidad y Estadistica",
    "Redes de Computadoras",
    "Estructura de Datos",
    "Procesamiento de Seniales",
    "Control Automatico",
    "Sistemas Embebidos",
    "Sistemas Ciberfisicos",
    "Etica y Legislacion",
    "Arquitecturas de Computadoras I",
    "Arquitecturas de Computadoras II",
    "Metodologia de la investigacion",
    "Construccion de Sistemas de Computacion",
    "Ingles Tecnico",
    "Tesis",
    "Inteligencia Artificial",
};

const int NUM_NOMBRES = sizeof(NOMBRES_MATERIAS) / sizeof(NOMBRES_MATERIAS[0]);

void GenerarMateriasAleatorias(GestorMaterias *gestor) {
    if (gestor == NULL) {
        return;
    }

    srand(time(NULL));

    for (int i = 0; i < 30; i++) {
        // int indiceNombre = rand() % NUM_NOMBRES;
        const char *nombre = NOMBRES_MATERIAS[i];

        // int notaEntera = (rand() % 31) + 40;
        // double notaMinima = (double)notaEntera / 10.0;

        // Se llama a la función AgregarMateria definida en gestorMaterias.c
        AgregarMateria(gestor, nombre);
    }
}

/**
 * Genera una cantidad específica de estudiantes con datos aleatorios
 * y los añade al GestorEstudiantes.
 */
void GenerarEstudiantesAleatorios(GestorEstudiantes *gestor, int cantidad) {
    if (gestor == NULL || cantidad <= 0) {
        return;
    }

    // Inicializa la semilla del generador de números aleatorios
    srand(time(NULL));

    for (int i = 0; i < cantidad; i++) {
        // 1. Nombre y Apellido aleatorio
        const char *nombre = NOMBRES_ESTUDIANTES[rand() % NUM_NOMBRES_E];
        const char *apellido = APELLIDOS_ESTUDIANTES[rand() % NUM_APELLIDOS_E];

        // 2. Fecha de Nacimiento aleatoria (Ej: entre 1990 y 2005)
        int anio = 1990 + (rand() % 16);
        int mes = 1 + (rand() % 12);
        // Cálculo simplificado de días máximos del mes
        int max_dias = (mes == 2) ? 28 : ((mes == 4 || mes == 6 || mes == 9 || mes == 11) ? 30 : 31);
        int dia = 1 + (rand() % max_dias);

        char nacimiento[11]; // "dd/mm/yyyy\0"
        sprintf(nacimiento, "%02d/%02d/%d", dia, mes, anio);

        // 3. Sexo (0 = Hombre, 1 = Mujer)
        int sexo = rand() % 2;

        // 4. Crear y Listar el estudiante
        Estudiante *nuevoEstudiante = NewEstudiante(nombre, apellido, nacimiento, sexo);
        if (nuevoEstudiante != NULL) {
            // La inicialización de materiasAprobadas y esGraduado ahora es manejada por NewEstudiante.
            ListarEstudiante(gestor, nuevoEstudiante);
        }
    }
    printf("Se han generado y listado %d estudiantes aleatorios.\n", cantidad);
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