# include <stdio.h>

#include  <stdlib.h>

typedef struct Materias {
    int ID;
    double nota;
    //puntero a la head de mi doublelinkedlist
    struct Estudiantes *listaDeEstudiantes;
    int size;
}Materias;

    