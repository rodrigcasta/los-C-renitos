#include "src/gestores/headersGestores/gestorEstudiantes.h"
#include "src/gestores/headersGestores/gestorMaterias.h"
#include "src/interfaz/headersInterfaz/interfaz.h"
#include "src/utils/headersUtils/generadorAleatorio.h"
#include <stdio.h>
#include <stdlib.h>

// NOTA: La función ImprimirMaterias ya está declarada en generadorAleatorio.h

int main() {
    // 1. Inicializar Gestores
    GestorEstudiantes *ge = NewGestorEstudiantes();
    GestorMaterias *gm = NewGestorMaterias();

    // 2. Generar Datos de Prueba (Opcional, pero útil para demostrar)
    // Descomentar para generar 7 materias aleatorias al inicio.
    GenerarMateriasAleatorias(gm, 7);

    // 3. Iniciar el Menú Principal
    MenuPrincipal(ge, gm);

    // 4. Liberar memoria al salir
    freeGestorEstudiantes(ge);
    FreeGestorMaterias(gm);

    return 0;
}