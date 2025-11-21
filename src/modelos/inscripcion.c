#include "headersModelos/inscripcion.h" // Incluye la definición de Inscripcion

/**
 * @brief Crea una nueva estructura de Inscripción.
 * * @param e Puntero al estudiante que se inscribe.
 * @param aprobado Estado inicial de aprobación (1=Aprobado, 0=Reprobado/Cursando).
 * @return Inscripcion* Puntero a la nueva estructura Inscripcion o NULL si falla.
 */
Inscripcion *NewInscripcion(Estudiante *e, int aprobado) {
    if (e == NULL) {
        return NULL;
    }

    Inscripcion *insc = (Inscripcion *)malloc(sizeof(Inscripcion));
    if (insc == NULL) {
        // Manejo de error si malloc falla
        return NULL;
    }

    insc->estudiante = e;
    insc->estaAprobado = aprobado;

    return insc;
}

/**
 * @brief Libera la memoria ocupada por la estructura Inscripcion.
 * @note Esta función SOLO libera la estructura 'Inscripcion' en sí,
 * NO libera el puntero al estudiante, ya que este es gestionado
 * por el GestorEstudiantes.
 * * @param i Puntero a la estructura Inscripcion a liberar.
 */
void FreeInscripcion(Inscripcion *i) {
    if (i != NULL) {
        // Solo liberamos la estructura Inscripcion.
        // NO hacemos free(i->estudiante)
        free(i);
    }
}