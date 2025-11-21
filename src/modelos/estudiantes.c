#include "headersModelos/estudiantes.h"

/**
 * Crea un estudiante con nombre, apellido, fecha de nacimiento y sexo.
 */
Estudiante *NewEstudiante(const char *nombre, const char *apellido, const char *nacimiento, int sexo) {
    Estudiante *est = malloc(sizeof(Estudiante));
    strcpy(est->nombre, nombre);
    strcpy(est->apellido, apellido);
    strcpy(est->nacimiento, nacimiento);
    est->edad = calcularEdad(nacimiento);
    est->sexo = sexo;
    est->ID = 0;
    return est;
}

// Getters y Setters.

int ObtenerID(const Estudiante *e) {
    return e->ID;
}

const char *ObtenerNombre(const Estudiante *e) {
    return e->nombre;
}

void CambiarNombre(Estudiante *e, const char *nombre) {
    strcpy(e->nombre, nombre);
}

const char *ObtenerApellido(const Estudiante *e) {
    return e->apellido;
}

void CambiarApellido(Estudiante *e, const char *apellido) {
    strcpy(e->apellido, apellido);
}

const char *ObtenerNacimiento(const Estudiante *e) {
    return e->nacimiento;
}

void CambiarNacimiento(Estudiante *e, const char *nacimiento) {
    strcpy(e->nacimiento, nacimiento);
    e->edad = calcularEdad(nacimiento);
}

int ObtenerEdad(const Estudiante *e) {
    return e->edad;
}

const char *ObtenerSexo(const Estudiante *e) {
    if (e->sexo == 0) {
        return "Hombre";
    }
    if (e->sexo == 1) {
        return "Mujer";
    }
    return "Invalido";
}

void CambiarSexo(Estudiante *e, int sexo) {
    e->sexo = sexo;
}

/**
 * Libera estudiante.
 */
void freeEstudiante(Estudiante *est) {
    free(est);
}

/**
 * Calcula la edad a partir de la fecha de nacimiento dada por parámetro.
 */
int calcularEdad(const char *fechaNacimiento) {
    int dia, mes, anio;
    sscanf(fechaNacimiento, "%d/%d/%d", &dia, &mes, &anio);

    // Obtener la fecha actual
    time_t t = time(NULL);
    struct tm *fechaActual = localtime(&t);

    int anioActual = fechaActual->tm_year + 1900;
    int mesActual = fechaActual->tm_mon + 1;
    int diaActual = fechaActual->tm_mday;

    int edad = anioActual - anio;

    // Si todavía no cumplió años este año, restamos 1
    if (mesActual < mes || (mesActual == mes && diaActual < dia)) {
        edad--;
    }

    return edad;
}
