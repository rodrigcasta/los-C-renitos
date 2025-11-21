#include "headersUtils/utilidades.h"
#include <time.h>

// **********************************************
// Funciones de Control de Consola
// **********************************************

/**
 * Limpia la pantalla de la consola.
 */
void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * Pausa la ejecución hasta que el usuario presione una tecla.
 */
void pausar(const char *mensaje)
{
    if (mensaje != NULL)
    {
        printf("%s", mensaje);
    }
    printf("\nPresione ENTER para continuar...");
    // Limpia el buffer antes de leer el caracter
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    if (c != EOF)
    {
        // Espera por el ENTER
        getchar();
    }
}

/**
 * Lee la opción de menú ingresada por el usuario, limpiando el buffer.
 */
int leerOpcion()
{
    int opcion;
    if (scanf("%d", &opcion) != 1)
    {
        opcion = -1; // Indica lectura fallida
    }
    // Limpia el buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    return opcion;
}

// **********************************************
// Funciones de Lectura de Datos
// **********************************************

/**
 * Lee una cadena de caracteres del usuario, con limpieza de buffer.
 */
// void leerCadena(char *destino, int max_len)
// {
//     // Primero, consume cualquier caracter de nueva línea o basura pendiente
//     int c;
//     while ((c = getchar()) != '\n' && c != EOF)
//         ;

//     // Lee la línea de entrada
//     if (fgets(destino, max_len, stdin) != NULL)
//     {
//         // Elimina el caracter de nueva línea si existe
//         size_t len = strlen(destino);
//         if (len > 0 && destino[len - 1] == '\n')
//         {
//             destino[len - 1] = '\0';
//         }
//     }
//     else
//     {
//         // En caso de error o EOF, limpia la cadena
//         destino[0] = '\0';
//     }
// }

void leerCadena(char *cadena, int max_len)
{
    if (fgets(cadena, max_len, stdin) != NULL)
    {
        // 1. Busca el caracter de nueva línea '\n' que fgets incluye
        size_t len = strlen(cadena);

        // 2. Si el último caracter es '\n' (entrada normal):
        if (len > 0 && cadena[len - 1] == '\n')
        {
            // Reemplázalo con el caracter nulo '\0' para terminar la cadena.
            cadena[len - 1] = '\0';
        }
        else
        {
            // 3. Si no encontró '\n', significa que la entrada excedió max_len.
            // Hay que limpiar los caracteres restantes en el búfer (stdin).
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
                // Leer y descartar caracteres
            }
        }
    }
}

/**
 * Lee un entero del usuario, limpiando el buffer.
 */
int leerEntero()
{
    printf("> ");
    int num;
    if (scanf("%d", &num) != 1)
    {
        num = -1; // Valor inválido
    }
    // Limpia el buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    return num;
}

/**
 * Lee un ID con un mensaje específico.
 */
int leerID(const char *mensaje)
{
    printf("%s", mensaje);
    return leerEntero();
}

/**
 * Retorna el año actual del sistema.
 */
int ObtenerAnioActual()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

/**
 * Retorna el mes actual del sistema (1-12).
 */
int ObtenerMesActual()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // tm_mon es 0-11, sumamos 1 para obtener 1-12
    return tm.tm_mon + 1;
}

/**
 * Retorna el día actual del sistema (1-31).
 */
int ObtenerDiaActual()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_mday;
}