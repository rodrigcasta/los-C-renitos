# include <stdio.h>

#include  <stdlib.h>

typedef struct Materia {
    int ID;
    char nombre[50];
    //puntero a la head de mi doublelinkedlist
    DoubleLinkedNode *listaEstudiante;
}Materia;

    