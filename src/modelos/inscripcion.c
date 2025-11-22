#include "headersModelos/inscripcion.h"

Inscripcion *NewInscripcion(Estudiante *e, int aprobado) {
    if (e == NULL) {
        return NULL;
    }

    Inscripcion *insc = (Inscripcion *)malloc(sizeof(Inscripcion));
    if (insc == NULL) {
        return NULL;
    }

    insc->estudiante = e;
    insc->estaAprobado = aprobado;

    return insc;
}

void FreeInscripcion(Inscripcion *i) {
    if (i != NULL) {
        free(i);
    }
}