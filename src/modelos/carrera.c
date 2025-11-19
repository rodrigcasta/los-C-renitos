#include "headersModelos/carrera.h"

// Constructor
Carrera *NewCarrera(const char *nombre) {
    Carrera *c = malloc(sizeof(Carrera));
    if (!c) return NULL;
    c->ID = 0; // será asignado por el gestor si corresponde
    strncpy(c->nombre, nombre ? nombre : "", sizeof(c->nombre)-1);
    c->nombre[sizeof(c->nombre)-1] = '\0';
    c->listaMaterias = NULL;
    c->listaEstudiantes = NULL;
    return c;
}

// Liberar solo la estructura de la carrera y los nodos de las listas (NO libera Materias ni Estudiantes)
void FreeCarrera(Carrera *c) {
    if (!c) return;
    FreeDoubleLinkedListNodes(c->listaMaterias);
    FreeDoubleLinkedListNodes(c->listaEstudiantes);
    free(c);
}

// Getters / Setters
const char *ObtenerNombreCarrera(const Carrera *c) {
    if (!c) return NULL;
    return c->nombre;
}

void CambiarNombreCarrera(Carrera *c, const char *nombre) {
    if (!c || !nombre) return;
    strncpy(c->nombre, nombre, sizeof(c->nombre)-1);
    c->nombre[sizeof(c->nombre)-1] = '\0';
}

// ID getters/setters
int ObtenerIDCarrera(const Carrera *c) {
    if (!c) return 0;
    return c->ID;
}

void CambiarIDCarrera(Carrera *c, int id) {
    if (!c) return;
    c->ID = id;
}

// Acceso a listas internas
DoubleLinkedNode *ObtenerListaMaterias(const Carrera *c) {
    if (!c) return NULL;
    return c->listaMaterias;
}

DoubleLinkedNode *ObtenerListaEstudiantes(const Carrera *c) {
    if (!c) return NULL;
    return c->listaEstudiantes;
}

// Agregar materias/estudiantes
void AgregarMateriaALaCarrera(Carrera *c, Materia *materia) {
    if (!c || !materia) return;
    c->listaMaterias = addElement(c->listaMaterias, materia);
}

int AgregarMateriaALaCarreraPorID(Carrera *c, GestorMaterias *gestor, int idMateria) {
    if (!c || !gestor) return 0;
    Materia *m = BuscarMateriaPorID(gestor, idMateria);
    if (!m) return 0;
    AgregarMateriaALaCarrera(c, m);
    return 1;
}

void AgregarEstudianteALaCarrera(Carrera *c, Estudiante *est) {
    if (!c || !est) return;
    c->listaEstudiantes = addElement(c->listaEstudiantes, est);
}

// Cantidades
int ObtenerCantidadDeMaterias(const Carrera *c) {
    if (!c) return 0;
    return SizeList(c->listaMaterias);
}

int ObtenerCantidadDeEstudiantes(const Carrera *c) {
    if (!c) return 0;
    return SizeList(c->listaEstudiantes);
}

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
