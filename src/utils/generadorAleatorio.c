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
        const char *nombre = NOMBRES_MATERIAS[i];
        AgregarMateria(gestor, nombre);
    }
}

/**
 * Genera una cantidad específica de estudiantes con datos aleatorios
 * y los añade al GestorEstudiantes.
 */
void GenerarEstudiantesAleatorios(GestorEstudiantes *ge, GestorMaterias *gm, int cantidad) {
    if (ge == NULL || gm == NULL || cantidad <= 0) {
        return;
    }

    if (gm->head_materias == NULL) {
        printf("ADVERTENCIA: No hay materias registradas. Generando 30 materias por defecto...\n");
        GenerarMateriasAleatorias(gm);
    }

    int max_materia_id = gm->next_ID - 1;

    if (max_materia_id <= 0) {
        printf(
            "ERROR: No se pudo determinar el rango de IDs de materias. Cancelando asignacion aleatoria de materias.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        const char *nombre = NOMBRES_ESTUDIANTES[rand() % NUM_NOMBRES_E];
        const char *apellido = APELLIDOS_ESTUDIANTES[rand() % NUM_APELLIDOS_E];

        int anio = 1990 + (rand() % 16);
        int mes = 1 + (rand() % 12);
        int max_dias = (mes == 2) ? 28 : ((mes == 4 || mes == 6 || mes == 9 || mes == 11) ? 30 : 31);
        int dia = 1 + (rand() % max_dias);

        char nacimiento[11];
        sprintf(nacimiento, "%02d/%02d/%d", dia, mes, anio);

        int sexo = rand() % 2;

        Estudiante *nuevoEstudiante = NewEstudiante(nombre, apellido, nacimiento, sexo);
        if (nuevoEstudiante != NULL) {
            ListarEstudiante(ge, nuevoEstudiante);

            for (int id_materia = 1; id_materia <= max_materia_id; id_materia++) {

                if (rand() % 100 < 50) {
                    Materia *materia = BuscarMateriaPorID(gm, id_materia);

                    if (materia != NULL) {

                        if (HaAprobadoMateriaGestor(nuevoEstudiante, id_materia)) {
                            continue;
                        }

                        int aprobado = (rand() % 100 < 70) ? 1 : 0;

                        if (aprobado == 1) {
                            AprobarMateriaGestor(nuevoEstudiante, id_materia);

                            Inscripcion *inscripcionAprobada = NewInscripcion(nuevoEstudiante, 1);
                            if (inscripcionAprobada != NULL) {
                                materia->listaInscripciones =
                                    addElement(materia->listaInscripciones, inscripcionAprobada);
                            }
                        } else {

                            Inscripcion *inscripcionReprobada = NewInscripcion(nuevoEstudiante, 0);
                            if (inscripcionReprobada != NULL) {
                                materia->listaInscripciones =
                                    addElement(materia->listaInscripciones, inscripcionReprobada);
                            }
                        }
                    }
                }
            }
        }
    }
    printf("Se han generado y listado %d estudiantes aleatorios.\n", cantidad);
    printf("Se asignaron materias aleatorias a los estudiantes (aprobadas/reprobadas).\n");
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