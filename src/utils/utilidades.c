#include "headersUtils/utilidades.h"
#include <time.h>

// **********************************************
// Funciones de Control de Consola
// **********************************************

/**
 * Limpia la pantalla de la consola.
 */
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * Pausa la ejecución hasta que el usuario presione una tecla.
 */
void pausar(const char *mensaje) {
    if (mensaje != NULL) {
        printf("%s", mensaje);
    }
    printf("\nPresione ENTER para continuar...");

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * Lee la opción de menú ingresada por el usuario, limpiando el buffer.
 */
int leerOpcion() {
    int opcion;
    if (scanf("%d", &opcion) != 1) {
        opcion = -1;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    return opcion;
}

void leerCadena(char *cadena, int max_len) {
    if (fgets(cadena, max_len, stdin) != NULL) {
        size_t len = strlen(cadena);

        if (len > 0 && cadena[len - 1] == '\n') {
            cadena[len - 1] = '\0';
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
    }
}

/**
 * Lee un entero del usuario, limpiando el buffer.
 */
int leerEntero() {
    printf("> ");
    int num;
    if (scanf("%d", &num) != 1) {
        num = -1;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    return num;
}

/**
 * Lee un ID con un mensaje específico.
 */
int leerID(const char *mensaje) {
    printf("%s", mensaje);
    return leerEntero();
}

/**
 * Retorna el año actual del sistema.
 */
int ObtenerAnioActual() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

/**
 * Retorna el mes actual del sistema (1-12).
 */
int ObtenerMesActual() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_mon + 1;
}

/**
 * Retorna el día actual del sistema (1-31).
 */
int ObtenerDiaActual() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_mday;
}