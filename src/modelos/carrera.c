#include <stdio.h>
#include <string.h> // strcmp, strcpy

// ----- Definición de las estructuras -----
typedef struct {
    char nombre[50];
    int edad;
    char carrera[50];
} Estudiante;

typedef struct {
    char estudianteNombre[50];
    char materiaNombre[50];
    int nota;
} Inscripcion;

// ----- Tu función: filtrar estudiantes por materia y carrera -----
void filtrarEstudiantesPorMateriaYCarrera(
    char materiaBuscada[50],
    char carreraBuscada[50],
    Estudiante estudiantes[],
    int cantEst,
    Inscripcion inscripciones[],
    int cantIns
) {
    printf("\nEstudiantes de la materia '%s' en la carrera '%s':\n",
           materiaBuscada, carreraBuscada);

    // Recorremos todas las inscripciones
    for(int i = 0; i < cantIns; i++) {

        // Si la inscripción corresponde a la materia buscada
        if(strcmp(inscripciones[i].materiaNombre, materiaBuscada) == 0) {

            // Buscar el estudiante correspondiente a la inscripción
            for(int j = 0; j < cantEst; j++) {
                if(strcmp(estudiantes[j].nombre, inscripciones[i].estudianteNombre) == 0 &&
                   strcmp(estudiantes[j].carrera, carreraBuscada) == 0) {

                    // Si coincide nombre y carrera, lo mostramos
                    printf("- %s (edad: %d)\n", estudiantes[j].nombre, estudiantes[j].edad);
                }
            }
        }
    }
}

// ----- Ejemplo de uso -----
int main() {
    Estudiante estudiantes[3] = {
        {"Milena Arbo", 22, "Licenciatura en Sistemas"},
        {"Juan Perez", 21, "Ingenieria Informatica"},
        {"Ana Gomez", 23, "Licenciatura en Sistemas"}
    };

    Inscripcion inscripciones[4] = {
        {"Milena Arbo", "Algoritmos", 0},
        {"Juan Perez", "Algoritmos", 7},
        {"Ana Gomez", "Algoritmos", 9},
        {"Ana Gomez", "Sistemas Operativos", 0}
    };

    filtrarEstudiantesPorMateriaYCarrera("Algoritmos", "Licenciatura en Sistemas",
                                        estudiantes, 3, inscripciones, 4);

    return 0;
}
