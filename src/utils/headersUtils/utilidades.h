#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funciones de control de la interfaz
void limpiarPantalla();
void pausar(const char *mensaje);
int leerOpcion();

// Funciones de lectura de datos
void leerCadena(char *destino, int max_len);
int leerEntero();
int leerID(const char *mensaje);

#endif