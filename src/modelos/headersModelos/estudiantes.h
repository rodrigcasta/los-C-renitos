#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "../../estructuras/headersEstructuras/linkedList_n.h" // HP: NECESARIO para LinkedNode
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Estudiante {
    char nombre[15];
    char apellido[15];
    char nacimiento[11];
    int edad;
    int sexo; // 0 = hombre ;1 = mujer
    int ID;
    // --- CAMPOS NUEVOS ---
    LinkedNode *materiasAprobadas; // Lista de punteros a INT (IDs de materias)
    int esGraduado;                // 0 = No, 1 = Sí
} Estudiante;

Estudiante *NewEstudiante(const char *nombre, const char *apellido, const char *nacimiento, int sexo);

int ObtenerID(const Estudiante *e);
const char *ObtenerNombre(const Estudiante *e);
void CambiarNombre(Estudiante *e, const char *nombre);
const char *ObtenerApellido(const Estudiante *e);
void CambiarApellido(Estudiante *e, const char *apellido);
const char *ObtenerNacimiento(const Estudiante *e);
void CambiarNacimiento(Estudiante *e, const char *nacimiento);
int ObtenerEdad(const Estudiante *e);
const char *ObtenerSexo(const Estudiante *e);
void CambiarSexo(Estudiante *e, int sexo);
void freeEstudiante(Estudiante *est);
int calcularEdad(const char *fechaNacimiento);
#endif