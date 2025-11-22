#include "headersInterfaz/interfaz.h"
#include "../utils/headersUtils/generadorAleatorio.h"
#include "../utils/headersUtils/utilidades.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// **********************************************
// Funciones de Impresión
// **********************************************

/**
 * Muestra la información básica de un estudiante.
 */
void MostrarEstudianteSimple(const Estudiante *e)
{
    if (e == NULL)
    {
        return;
    }
    printf("ID: %d | Nombre: %s %s | Edad: %d | Sexo: %s | Nacimiento: %s\n", ObtenerID(e), ObtenerNombre(e),
           ObtenerApellido(e), ObtenerEdad(e), ObtenerSexo(e), ObtenerNacimiento(e));
}

/**
 * Muestra la lista completa de estudiantes.
 */
void MostrarEstudiantesLista(GestorEstudiantes *ge)
{
    if (ge == NULL || ge->estudiantes == NULL)
    {
        printf("\n[ No hay estudiantes registrados. ]\n");
        return;
    }

    printf("\n--- LISTA DE ESTUDIANTES REGISTRADOS ---\n");
    LinkedNode *cursor = ge->estudiantes;
    while (cursor != NULL)
    {
        MostrarEstudianteSimple((Estudiante *)cursor->data);
        cursor = cursor->next;
    }
    printf("------------------------------------------\n");
}

/**
 * Muestra las materias disponibles para anotarse.
 */
void MostrarMateriasDisponibles(GestorMaterias *gm)
{
    if (gm == NULL || gm->head_materias == NULL)
    {
        printf("\n[ No hay materias disponibles. ]\n");
        return;
    }
    printf("\n--- MATERIAS DISPONIBLES ---\n");
    DoubleLinkedNode *cursor = gm->head_materias;
    while (cursor != NULL)
    {
        Materia *m = (Materia *)cursor->data;
        printf("ID: %d | Nombre: %s\n", m->ID, m->nombre);
        cursor = cursor->next;
    }
    printf("--------------------------------\n");
}

/**
 * Muestra las materias aprobadas por un estudiante.
 */
void MostrarMateriasAprobadasEstudiante(const Estudiante *e, GestorMaterias *gm)
{
    if (e == NULL || e->materiasAprobadas == NULL)
    {
        printf("\n[ El estudiante no tiene materias aprobadas. ]\n");
        return;
    }
    printf("\n--- MATERIAS APROBADAS ---\n");
    LinkedNode *cursor = e->materiasAprobadas;
    int cont = 0;
    while (cursor != NULL)
    {
        int *ID_aprobado = (int *)cursor->data;
        Materia *materia = BuscarMateriaPorID(gm, *ID_aprobado);
        if (materia != NULL)
        {
            printf("%d. ID: %d | Nombre: %s\n", ++cont, *ID_aprobado, materia->nombre);
        }
        else
        {
            printf("%d. ID: %d | Nombre: [Materia Eliminada]\n", ++cont, *ID_aprobado);
        }
        cursor = cursor->next;
    }
    printf("------------------------------\n");
}

/**
 * Muestra una lista temporal de estudiantes (ej. resultados de una búsqueda).
 */
void MostrarEstudiantesBusqueda(LinkedNode *listaResultados)
{
    if (listaResultados == NULL)
    {
        printf("\n[ No se encontraron estudiantes con ese criterio. ]\n");
        return;
    }
    printf("\n--- RESULTADOS DE LA BUSQUEDA ---\n");
    LinkedNode *cursor = listaResultados;
    while (cursor != NULL)
    {
        MostrarEstudianteSimple((Estudiante *)cursor->data);
        cursor = cursor->next;
    }
    printf("--------------------------------------\n");
}

// **********************************************
// Funciones de Lógica de Estudiante
// **********************************************

/**
 * Implementa la opción 2: Dar de alta estudiante.
 */
void AltaEstudiante(GestorEstudiantes *ge)
{
    char nombre[15];
    char apellido[15];
    char nacimiento[11];
    int sexo;
    int nombreValido;
    int apellidoValido;
    int fechaValida;

    printf("\n--- DAR DE ALTA ESTUDIANTE ---\n");

    do
    {
        printf("Ingrese nombre (solo letras): ");
        leerCadena(nombre, 15);
        nombreValido = 1;

        if (nombre[0] == '\0')
        {
            nombreValido = 0;
        }
        else
        {
            for (int i = 0; nombre[i] != '\0'; i++)
            {
                if (!isalpha((unsigned char)nombre[i]) && !isspace((unsigned char)nombre[i]))
                {
                    nombreValido = 0;
                    break;
                }
            }
        }

        if (!nombreValido)
        {
            printf(" ERROR: El nombre solo debe contener letras y espacios.\n");
        }
    } while (!nombreValido);

    do
    {
        printf("Ingrese apellido (solo letras): ");
        leerCadena(apellido, 15);
        apellidoValido = 1;

        if (apellido[0] == '\0')
        {
            apellidoValido = 0;
        }
        else
        {
            for (int i = 0; apellido[i] != '\0'; i++)
            {
                if (!isalpha((unsigned char)apellido[i]) && !isspace((unsigned char)apellido[i]))
                {
                    apellidoValido = 0;
                    break;
                }
            }
        }

        if (!apellidoValido)
        {
            printf(" ERROR: El apellido solo debe contener letras y espacios.\n");
        }
    } while (!apellidoValido);

    do
    {
        printf("Ingrese fecha de nacimiento en formato dd/mm/yyyy (con las barras incluidas): ");
        leerCadena(nacimiento, 11);
        fechaValida = 1;

        int dia, mes, anio;
        int chars_leidos = 0;
        int resultado = sscanf(nacimiento, "%d/%d/%d%n", &dia, &mes, &anio, &chars_leidos);

        if (resultado != 3 || chars_leidos != 10 || nacimiento[10] != '\0')
        {
            fechaValida = 0;
        }
        else
        {
            int esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);

            if (mes < 1 || mes > 12 || anio < 1900 || anio > ObtenerAnioActual())
            {
                fechaValida = 0;
            }
            else
            {
                int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                int maxDias = diasEnMes[mes];

                if (mes == 2 && esBisiesto)
                {
                    maxDias = 29;
                }

                if (dia < 1 || dia > maxDias)
                {
                    fechaValida = 0;
                }
                else
                {
                    if (anio == ObtenerAnioActual())
                    {
                        int mesActual = ObtenerMesActual();
                        if (mes > mesActual)
                        {
                            fechaValida = 0;
                        }
                        else if (mes == mesActual)
                        {
                            int diaActual = ObtenerDiaActual();
                            if (dia > diaActual)
                            {
                                fechaValida = 0;
                            }
                        }
                    }
                }
            }
        }

        if (!fechaValida)
        {
            printf(" ERROR: Fecha invalida. Verifique el formato (dd/mm/yyyy) y la validez logica (ej. no puede ser "
                   "futura).\n");
        }
    } while (!fechaValida);

    do
    {
        printf("Ingrese su sexo (0 = Hombre, 1 = Mujer): ");
        sexo = leerEntero();
        if (sexo != 0 && sexo != 1)
        {
            printf(" ERROR: Opcion de sexo invalida. Debe ser 0 o 1.\n");
        }
    } while (sexo != 0 && sexo != 1);

    Estudiante *nuevoEstudiante = NewEstudiante(nombre, apellido, nacimiento, sexo);

    ListarEstudiante(ge, nuevoEstudiante);

    printf("\n El estudiante se dio de alta correctamente con los siguientes datos:\n");
    MostrarEstudianteSimple(nuevoEstudiante);
    printf("----------------------------------------\n");
    pausar(NULL);
}

/**
 * Implementa la opción 4: Eliminar estudiante.
 */
void EliminarEstudiante(GestorEstudiantes *ge)
{
    int id;
    char confirmacion[5];
    Estudiante *e;

    printf("\n--- ELIMINAR ESTUDIANTE ---\n");
    id = leerID("Ingrese su ID: ");

    e = BuscarEstudianteID(ge, id);

    if (e == NULL)
    {
        printf("ERROR: Estudiante con ID %d no encontrado.\n", id);
        pausar(NULL);
        return;
    }

    printf("Estudiante a eliminar: ");
    MostrarEstudianteSimple(e);

    printf("Confirma que elimina el estudiante (s/n): ");
    leerCadena(confirmacion, 5);

    if (strcmp(confirmacion, "s") == 0 || strcmp(confirmacion, "S") == 0)
    {
        DeslistarEstudianteID(ge, id);
        printf("\n Estudiante eliminado correctamente.\n");
    }
    else
    {
        printf("\n Operacion cancelada.\n");
    }
    pausar(NULL);
}

/**
 * Implementa la opción 5: Buscar estudiante.
 */
void BuscarEstudiante(GestorEstudiantes *ge)
{
    int opcion;
    int id;
    char nombre[15];
    int v1, v2;
    Estudiante *est;
    LinkedNode *resultados = NULL;

    printf("\n--- BUSCAR ESTUDIANTE ---\n");
    printf("|| Elegir parametro de busqueda ||\n");
    printf("1. ID\n");
    printf("2. Nombre\n");
    printf("3. Rango de edad\n");
    printf("4. Volver\n");
    printf("--------------------------------\n");

    opcion = leerOpcion();
    limpiarPantalla();

    switch (opcion)
    {
    case 1:
        id = leerID("Ingrese ID a buscar: ");
        est = BuscarEstudianteID(ge, id);
        if (est != NULL)
        {
            printf("\n Estudiante encontrado:\n");
            MostrarEstudianteSimple(est);
        }
        else
        {
            printf("\n[ Estudiante con ID %d no encontrado. ]\n", id);
        }
        break;
    case 2:
        printf("Ingrese Nombre a buscar: ");
        leerCadena(nombre, 15);
        est = BuscarEstudianteNombre(ge, nombre);
        if (est != NULL)
        {
            printf("\n Estudiante encontrado:\n");
            MostrarEstudianteSimple(est);
        }
        else
        {
            printf("\n[ Estudiante con nombre '%s' no encontrado. ]\n", nombre);
        }
        break;
    case 3:
        printf("Ingrese edad minima (v1): ");
        v1 = leerEntero();
        printf("Ingrese edad maxima (v2): ");
        v2 = leerEntero();
        if (v1 > v2)
        {
            int temp = v1;
            v1 = v2;
            v2 = temp;
        }
        resultados = BuscarRangoEdad(ge, v1, v2);
        MostrarEstudiantesBusqueda(resultados);
        freeList(resultados);
        break;
    case 4:
        return;
    default:
        printf(" Opcion invalida.\n");
    }
    pausar(NULL);
}

void MenuModificarEstudiante(Estudiante *e)
{
    int opcion;
    char nuevoValor[20];
    int nuevoSexo;

    int nombreValido;
    int apellidoValido;
    int fechaValida;

    do
    {
        limpiarPantalla();
        printf("\n|| MODIFICAR PARAMETROS DE %s %s ||\n", ObtenerNombre(e), ObtenerApellido(e));
        printf("1. Nombre (Actual: %s)\n", ObtenerNombre(e));
        printf("2. Apellido (Actual: %s)\n", ObtenerApellido(e));
        printf("3. Fecha de nacimiento (Actual: %s, Edad: %d)\n", ObtenerNacimiento(e), ObtenerEdad(e));
        printf("4. Sexo (Actual: %s)\n", ObtenerSexo(e));
        printf("5. Volver\n");
        printf("--------------------------------\n");
        printf("|| Elegir opcion que desea modificar ||\n");

        opcion = leerOpcion();
        limpiarPantalla();

        switch (opcion)
        {
        case 1:
            do
            {
                printf("Ingrese nuevo nombre (solo letras): ");
                leerCadena(nuevoValor, 15);
                nombreValido = 1;

                if (nuevoValor[0] == '\0')
                {
                    nombreValido = 0;
                }
                else
                {
                    for (int i = 0; nuevoValor[i] != '\0'; i++)
                    {
                        if (!isalpha((unsigned char)nuevoValor[i]) && !isspace((unsigned char)nuevoValor[i]))
                        {
                            nombreValido = 0;
                            break;
                        }
                    }
                }

                if (!nombreValido)
                {
                    printf("ERROR: El nombre solo debe contener letras y espacios.\n");
                }
            } while (!nombreValido);

            CambiarNombre(e, nuevoValor);
            printf("Nombre modificado.\n");
            break;

        case 2:
            do
            {
                printf("Ingrese nuevo apellido (solo letras): ");
                leerCadena(nuevoValor, 15);
                apellidoValido = 1;

                if (nuevoValor[0] == '\0')
                {
                    apellidoValido = 0;
                }
                else
                {
                    for (int i = 0; nuevoValor[i] != '\0'; i++)
                    {
                        if (!isalpha((unsigned char)nuevoValor[i]) && !isspace((unsigned char)nuevoValor[i]))
                        {
                            apellidoValido = 0;
                            break;
                        }
                    }
                }

                if (!apellidoValido)
                {
                    printf("ERROR: El apellido solo debe contener letras y espacios.\n");
                }
            } while (!apellidoValido);

            CambiarApellido(e, nuevoValor);
            printf("Apellido modificado.\n");
            break;

        case 3:
            do
            {
                printf("Ingrese nueva fecha de nacimiento (dd/mm/yyyy): ");
                leerCadena(nuevoValor, 11);
                fechaValida = 1;

                int dia, mes, anio;
                int chars_leidos = 0;
                int resultado = sscanf(nuevoValor, "%d/%d/%d%n", &dia, &mes, &anio, &chars_leidos);

                if (resultado != 3 || chars_leidos != 10 || nuevoValor[10] != '\0')
                {
                    fechaValida = 0;
                }
                else
                {
                    int esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);

                    if (mes < 1 || mes > 12 || anio < 1900 || anio > ObtenerAnioActual())
                    {
                        fechaValida = 0;
                    }
                    else
                    {
                        int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                        int maxDias = diasEnMes[mes];

                        if (mes == 2 && esBisiesto)
                        {
                            maxDias = 29;
                        }

                        if (dia < 1 || dia > maxDias)
                        {
                            fechaValida = 0;
                        }
                        else
                        {
                            if (anio == ObtenerAnioActual())
                            {
                                int mesActual = ObtenerMesActual();
                                if (mes > mesActual)
                                {
                                    fechaValida = 0;
                                }
                                else if (mes == mesActual)
                                {
                                    int diaActual = ObtenerDiaActual();
                                    if (dia > diaActual)
                                    {
                                        fechaValida = 0;
                                    }
                                }
                            }
                        }
                    }
                }

                if (!fechaValida)
                {
                    printf("ERROR: Fecha invalida. Verifique el formato (dd/mm/yyyy) y la validez logica (ej. no puede "
                           "ser futura).\n");
                }
            } while (!fechaValida);

            CambiarNacimiento(e, nuevoValor);
            printf("Fecha de nacimiento modificada (Nueva edad: %d).\n", ObtenerEdad(e));
            break;

        case 4:
            do
            {
                printf("Ingrese nuevo sexo (0 = Hombre, 1 = Mujer): ");
                nuevoSexo = leerEntero();
                if (nuevoSexo != 0 && nuevoSexo != 1)
                {
                    printf("ERROR: Opcion de sexo invalida. Debe ser 0 o 1.\n");
                }
            } while (nuevoSexo != 0 && nuevoSexo != 1);
            CambiarSexo(e, nuevoSexo);
            printf("Sexo modificado.\n");
            break;

        case 5:
            return;
        default:
            printf("Opcion invalida.\n");
        }
        pausar(NULL);
    } while (opcion != 5);
}

/**
 * Implementa la opción 3: Rendir materia del menú de estudiante.
 * Asume que el estudiante ya está inscrito.
 */
void RendirMateria(Estudiante *e, Materia *materia)
{
    DoubleLinkedNode *cursor = materia->listaInscripciones;
    Inscripcion *inscripcion = NULL;
    while (cursor != NULL)
    {
        Inscripcion *i = (Inscripcion *)cursor->data;
        if (i->estudiante == e)
        {
            inscripcion = i;
            break;
        }
        cursor = cursor->next;
    }

    if (inscripcion == NULL)
    {
        printf("ERROR: El estudiante no esta inscrito en esta materia.\n");
        return;
    }

    if (HaAprobadoMateriaGestor(e, materia->ID))
    {
        printf("Advertencia: El estudiante ya aprobo esta materia.\n");
        return;
    }

    int aprobacion;
    do
    {
        printf("Ingrese resultado (1 = Aprobado, 0 = Reprobado): ");
        aprobacion = leerEntero();
    } while (aprobacion != 0 && aprobacion != 1);

    if (aprobacion == 1)
    {
        inscripcion->estaAprobado = 1;
        AprobarMateriaGestor(e, materia->ID);
        printf("Materia '%s' aprobada e historico actualizado.\n", materia->nombre);
    }
    else
    {
        inscripcion->estaAprobado = 0;
        printf("Materia '%s' reprobada. Inscripcion actualizada.\n", materia->nombre);
    }
}

/**
 * Implementa la opción 4: Dar de baja materia del menú de estudiante.
 */
void DarDeBajaInscripcion(Estudiante *e, Materia *materia)
{

    if (HaAprobadoMateriaGestor(e, materia->ID))
    {
        printf("\n ERROR: No puede darse de baja. La materia '%s' ya esta registrada como APROBADA en el historial del "
               "estudiante.\n",
               materia->nombre);
        return;
    }

    DoubleLinkedNode *current = materia->listaInscripciones;
    int posicion = 0;

    while (current != NULL)
    {
        Inscripcion *insc = (Inscripcion *)current->data;
        if (insc->estudiante == e)
        {
            Inscripcion *insc_a_liberar = (Inscripcion *)RemoveElement(&materia->listaInscripciones, posicion);
            if (insc_a_liberar != NULL)
            {
                FreeInscripcion(insc_a_liberar);
                printf("Inscripcion eliminada para la materia '%s'.\n", materia->nombre);
            }
            return;
        }
        current = current->next;
        posicion++;
    }

    printf("ERROR: El estudiante no esta inscrito en la materia '%s'.\n", materia->nombre);
}

/**
 * Menú para interactuar con un estudiante específico (Opción 3 del gestor).
 */
void MenuAccederEstudiante(Estudiante *e, GestorMaterias *gm, GestorEstudiantes *ge)
{
    int opcion;
    int idMateria;
    Materia *materia;
    char confirmacion[5];
    LinkedNode *materiasInscritas = NULL;

    do
    {
        limpiarPantalla();
        printf("\n|| Hola ID %d (%s %s) ||\n", ObtenerID(e), ObtenerNombre(e), ObtenerApellido(e));
        printf("1. Modificar parametros\n");
        printf("2. Anotarse a materia\n");
        printf("3. Rendir materia\n");
        printf("4. Dar de baja materia (Inscripcion)\n");
        printf("5. Ver mis materias aprobadas\n");
        printf("6. Volver\n");
        printf("--------------------------------\n");
        printf("|| Elegir opcion que desee ||\n");

        opcion = leerOpcion();
        limpiarPantalla();

        switch (opcion)
        {
        case 1:
            MenuModificarEstudiante(e);
            break;
        case 2:
            MostrarMateriasDisponibles(gm);
            idMateria = leerID("Ingrese ID de la materia a anotarse: ");
            materia = BuscarMateriaPorID(gm, idMateria);

            if (materia != NULL)
            {
                MatricularEstudiante(gm, idMateria, e, 0);
            }
            else
            {
                printf("ERROR: Materia con ID %d no encontrada.\n", idMateria);
            }
            pausar(NULL);
            break;
        case 3:
            MostrarMateriasDisponibles(gm);
            idMateria = leerID("Ingrese ID de la materia a rendir: ");
            materia = BuscarMateriaPorID(gm, idMateria);

            if (materia != NULL)
            {
                RendirMateria(e, materia);
            }
            else
            {
                printf("ERROR: Materia con ID %d no encontrada.\n", idMateria);
            }
            pausar(NULL);
            break;
        case 4:
            MostrarMateriasDisponibles(gm);
            idMateria = leerID("Ingrese ID de la materia a darse de baja: ");
            materia = BuscarMateriaPorID(gm, idMateria);

            if (materia != NULL)
            {
                printf("Confirma dar de baja la inscripcion de '%s' (s/n): ", materia->nombre);
                leerCadena(confirmacion, 5);
                if (strcmp(confirmacion, "s") == 0 || strcmp(confirmacion, "S") == 0)
                {
                    DarDeBajaInscripcion(e, materia);
                }
                else
                {
                    printf("\n Operacion cancelada.\n");
                }
            }
            else
            {
                printf("ERROR: Materia con ID %d no encontrada.\n", idMateria);
            }
            pausar(NULL);
            break;
        case 5:
            MostrarMateriasAprobadasEstudiante(e, gm);
            pausar(NULL);
            break;
        case 6:
            break;
        default:
            printf("Opcion invalida.\n");
            pausar(NULL);
        }
    } while (opcion != 6);
}

// **********************************************
// Funciones de Lógica de Materia
// **********************************************

/**
 * Implementa la opción 2: Dar de alta una materia.
 */
void AltaMateria(GestorMaterias *gm)
{
    char nombre[50];
    printf("\n--- DAR DE ALTA MATERIA ---\n");
    printf("Ingrese nombre de la materia: ");
    leerCadena(nombre, 50);

    AgregarMateria(gm, nombre);

    printf("\n Materia dada de alta correctamente. \n");
    pausar(NULL);
}

/**
 * Implementa la opción 3: Modificar nombre de materia.
 */
void ModificarNombreMateria(GestorMaterias *gm)
{
    int id;
    char nuevoNombre[50];
    Materia *materia;

    printf("\n--- MODIFICAR NOMBRE DE MATERIA ---\n");
    MostrarMateriasDisponibles(gm);
    id = leerID("Ingrese ID de la materia a modificar: ");

    materia = BuscarMateriaPorID(gm, id);

    if (materia == NULL)
    {
        printf("ERROR: Materia con ID %d no encontrada.\n", id);
        pausar(NULL);
        return;
    }

    printf("Materia seleccionada: %s\n", materia->nombre);
    printf("Ingrese nuevo nombre: ");
    leerCadena(nuevoNombre, 50);

    strcpy(materia->nombre, nuevoNombre);
    printf("\nNombre de materia modificado a '%s'.\n", materia->nombre);
    pausar(NULL);
}

/**
 * Implementa la opción 4: Eliminar materia.
 */
void EliminarMateriaCLI(GestorMaterias *gm)
{
    int id;
    char confirmacion[5];

    printf("\n--- ELIMINAR MATERIA ---\n");
    MostrarMateriasDisponibles(gm);
    id = leerID("Ingrese ID de la materia a eliminar: ");

    Materia *materia = BuscarMateriaPorID(gm, id);

    if (materia == NULL)
    {
        printf("ERROR: Materia con ID %d no encontrada.\n", id);
        pausar(NULL);
        return;
    }

    printf("Confirma eliminar la materia '%s' y todas sus inscripciones (s/n): ", materia->nombre);
    leerCadena(confirmacion, 5);

    if (strcmp(confirmacion, "s") == 0 || strcmp(confirmacion, "S") == 0)
    {
        EliminarMateria(gm, id);
        printf("\nMateria eliminada correctamente.\n");
    }
    else
    {
        printf("\n Operacion cancelada.\n");
    }
    pausar(NULL);
}

// **********************************************
// Funciones de Menú
// **********************************************

/**
 * Menú de estadísticas (Opción 3 del menú principal).
 */
void MenuEstadisticas(GestorEstudiantes *ge, GestorMaterias *gm)
{
    limpiarPantalla();
    printf("\n||              BIENVENIDO a las estadisticas             ||\n");

    EstadisticasGenerales *stats = CalcularEstadisticasGenerales(ge, gm);
    MostrarEstadisticasGenerales(stats);

    MostrarPromedioAprobadosPorMateria(gm);

    if (stats != NULL)
    {
        free(stats);
    }

    pausar(NULL);
}

/**
 * Menú de gestión de materias (Opción 2 del menú principal).
 */
void MenuGestorMaterias(GestorMaterias *gm)
{
    int opcion;

    do
    {
        limpiarPantalla();
        printf("\n||              BIENVENIDO al gestor de materias             ||\n");
        printf("1. Ver materias disponibles\n");
        printf("2. Dar de alta una materia\n");
        printf("3. Modificar nombre de materia\n");
        printf("4. Eliminar materia\n");
        printf("5. Volver\n");
        printf("--------------------------------------------------------------------------\n");

        opcion = leerOpcion();
        limpiarPantalla();

        switch (opcion)
        {
        case 1:
            MostrarMateriasDisponibles(gm);
            pausar(NULL);
            break;
        case 2:
            AltaMateria(gm);
            break;
        case 3:
            ModificarNombreMateria(gm);
            break;
        case 4:
            EliminarMateriaCLI(gm);
            break;
        case 5:
            return;
        default:
            printf("Opcion invalida.\n");
            pausar(NULL);
        }
    } while (opcion != 5);
}

/**
 * Menú de gestión de estudiantes (Opción 1 del menú principal).
 */
void MenuGestorEstudiantes(GestorEstudiantes *ge, GestorMaterias *gm)
{
    int opcion;
    int id;
    Estudiante *estudiante;

    do
    {
        limpiarPantalla();
        printf("\n||              BIENVENIDO al gestor de estudiantes             ||\n");
        printf("1. Ver Estudiantes\n");
        printf("2. Dar de alta estudiante\n");
        printf("3. Acceder a estudiante\n");
        printf("4. Eliminar estudiantes\n");
        printf("5. Buscar estudiante\n");
        printf("6. Volver\n");
        printf("------------------------------------------------------------------------\n");

        opcion = leerOpcion();
        limpiarPantalla();

        switch (opcion)
        {
        case 1:
            MostrarEstudiantesLista(ge);
            pausar(NULL);
            break;
        case 2:
            AltaEstudiante(ge);
            break;
        case 3:
            id = leerID("Ingrese ID de estudiante: ");
            estudiante = BuscarEstudianteID(ge, id);
            if (estudiante != NULL)
            {
                MenuAccederEstudiante(estudiante, gm, ge);
            }
            else
            {
                printf("ERROR: Estudiante con ID %d no encontrado.\n", id);
                pausar(NULL);
            }
            break;
        case 4:
            EliminarEstudiante(ge);
            break;
        case 5:
            BuscarEstudiante(ge);
            break;
        case 6:
            return;
        default:
            printf("Opcion invalida.\n");
            pausar(NULL);
        }
    } while (opcion != 6);
}

void MenuPrincipal(GestorEstudiantes *ge, GestorMaterias *gm)
{
    int opcion;
    int cantidad;

    do
    {
        limpiarPantalla();
        printf("\n// Sistema de estudiantes de ingenieria en computacion - Los C-Renitos //\n");
        printf("||              BIENVENIDO                ||\n");
        printf("1. Gestionar estudiantes\n");
        printf("2. Gestionar materias\n");
        printf("3. Estadisticas generales\n");
        printf("4. Generar estudiantes aleatorios\n");
        printf("5. Generar materias\n");
        printf("6. Ejecutar casos de prueba\n");
        printf("7. Salir del sistema\n");
        printf("=============================================\n");

        opcion = leerOpcion();
        limpiarPantalla();

        switch (opcion)
        {
        case 1:
            MenuGestorEstudiantes(ge, gm);
            break;
        case 2:
            MenuGestorMaterias(gm);
            break;
        case 3:
            MenuEstadisticas(ge, gm);
            break;
        case 4:
            printf("\n--- GENERAR ESTUDIANTES ALEATORIOS ---\n");
            printf("Ingrese la cantidad de estudiantes a generar: ");
            cantidad = leerEntero();

            if (cantidad > 0)
            {
                GenerarEstudiantesAleatorios(ge, gm, cantidad);
            }
            else
            {
                printf("La cantidad debe ser mayor a cero.\n");
            }
            pausar(NULL);
            break;
        case 5:
            printf("\n--- GENERAR MATERIAS ---\n");
            if (gm->head_materias != NULL)
            {
                printf("\n Ya existen materias en la plataforma.\n");
                pausar(NULL);
                break;
            }
            GenerarMateriasAleatorias(gm);
            printf("\n Se generaron %d materias.\n", 30);

            pausar(NULL);
            break;
        case 6:
            EjecutarCasosPrueba(ge, gm);
            pausar(NULL);
            break;
        case 7:
            printf("\nGracias por usar Los C-Renitos! Cerrando sistema...\n");
            break;
        default:
            printf(" Opcion invalida. Intente de nuevo.\n");
            pausar(NULL);
        }
    } while (opcion != 7);
}