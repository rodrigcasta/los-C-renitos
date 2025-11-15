#include <stdio.h>
#include <string.h>
#include "gestorMaterias.h"  // donde está definida Materia, GestorMaterias, etc.
#include "estudiantes.h"     // donde está Estudiante y sus funciones


// ---------------

// inicializar linkedList de estudiantes
// incializar linkedList de materias

// Constructor: Carrera *NewCarrera(char nombreCarrera[20])

// getters y setters

// AgregarMateriaALaCarrera(IDMateria) --> Añadir una materia mediante append a la linkedList incializada al principio
// AgregarEstudianteALaCarrera(IDMateria) --> Añadir una materia mediante append a la linkedList incializada al principio


// ObtenerCantidadDeMaterias() return total de carreras
// ObtenerCantidadDeEstudiantes() devuelvo cantidad de estudiantes dentro de la carrera

// ---------------




// Filtrar estudiantes por MATERIA y SEXO (0 = hombre, 1 = mujer)
void FiltrarEstudiantesPorMateriaYSexo(GestorMaterias *gestor, int idMateria, int sexoBuscado) {

    // 1. Buscar la materia por ID
    Materia *materia = BuscarMateriaPorID(gestor, idMateria);
    if (materia == NULL) {
        printf("No se encontró la materia con ID %d\n", idMateria);
        return;
    }

    printf("Estudiantes en la materia '%s' con sexo = %d:\n", materia->nombre, sexoBuscado);

    // 2. Recorrer la lista de estudiantes dentro de esa materia
    DoubleLinkedNode *current = materia->listaEstudiantes;
    while (current != NULL) {
        Estudiante *est = (Estudiante*) current->data;

        // 3. Comparar el sexo del estudiante con el que buscamos
        if (ObtenerSexo(est) == sexoBuscado) {
            printf("- %s %s | Edad: %d | Sexo: %d\n",
                   ObtenerNombre(est),
                   ObtenerApellido(est),
                   ObtenerEdad(est),
                   ObtenerSexo(est)
            );
        }

        current = current->next;
    }
}
