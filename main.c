#include <stdio.h>
#include <stdlib.h>
#include "src/materias/headersMaterias/gestorMaterias.h"
#include "src/utils/headersUtils/generadorAleatorio.h"

// Prototipo de la función auxiliar (debe estar antes de main)
void ImprimirMaterias(GestorMaterias *gestor);

int main() {
    GestorMaterias *gm = NewGestorMaterias();

    GenerarMateriasAleatorias(gm, 7);
    
    printf("--- Materias Generadas Aleatoriamente ---\n");
    ImprimirMaterias(gm);
    printf("-----------------------------------------\n");

    return 0;
}