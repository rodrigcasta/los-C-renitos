#include "headersInterfaz/interfaz.h"

// **********************************************
// Funciones de Impresión
// **********************************************

/**
 * Muestra la información básica de un estudiante.
 */
void MostrarEstudianteSimple(const Estudiante *e) {
    if (e == NULL) {
        return;
    }
    printf("ID: %d | Nombre: %s %s | Edad: %d | Sexo: %s | Nacimiento: %s\n", ObtenerID(e), ObtenerNombre(e),
           ObtenerApellido(e), ObtenerEdad(e), ObtenerSexo(e), ObtenerNacimiento(e));
}

/**
 * Muestra la lista completa de estudiantes.
 */
void MostrarEstudiantesLista(GestorEstudiantes *ge) {
    if (ge == NULL || ge->estudiantes == NULL) {
        printf("\n[ No hay estudiantes registrados. ]\n");
        return;
    }

    printf("\n--- 🧑‍🎓 LISTA DE ESTUDIANTES REGISTRADOS ---\n");
    LinkedNode *cursor = ge->estudiantes;
    while (cursor != NULL) {
        MostrarEstudianteSimple((Estudiante *)cursor->data);
        cursor = cursor->next;
    }
    printf("------------------------------------------\n");
}

/**
 * Muestra las materias disponibles para anotarse.
 */
void MostrarMateriasDisponibles(GestorMaterias *gm) {
    if (gm == NULL || gm->head_materias == NULL) {
        printf("\n[ No hay materias disponibles. ]\n");
        return;
    }
    printf("\n--- 📚 MATERIAS DISPONIBLES ---\n");
    DoubleLinkedNode *cursor = gm->head_materias;
    while (cursor != NULL) {
        Materia *m = (Materia *)cursor->data;
        printf("ID: %d | Nombre: %s\n", m->ID, m->nombre);
        cursor = cursor->next;
    }
    printf("--------------------------------\n");
}

/**
 * Muestra las materias aprobadas por un estudiante.
 */
void MostrarMateriasAprobadasEstudiante(const Estudiante *e, GestorMaterias *gm) {
    if (e == NULL || e->materiasAprobadas == NULL) {
        printf("\n[ El estudiante no tiene materias aprobadas. ]\n");
        return;
    }
    printf("\n--- ✅ MATERIAS APROBADAS ---\n");
    LinkedNode *cursor = e->materiasAprobadas;
    int cont = 0;
    while (cursor != NULL) {
        int *ID_aprobado = (int *)cursor->data;
        Materia *materia = BuscarMateriaPorID(gm, *ID_aprobado);
        if (materia != NULL) {
            printf("%d. ID: %d | Nombre: %s\n", ++cont, *ID_aprobado, materia->nombre);
        } else {
            printf("%d. ID: %d | Nombre: [Materia Eliminada]\n", ++cont, *ID_aprobado);
        }
        cursor = cursor->next;
    }
    printf("------------------------------\n");
}

/**
 * Muestra una lista temporal de estudiantes (ej. resultados de una búsqueda).
 */
void MostrarEstudiantesBusqueda(LinkedNode *listaResultados) {
    if (listaResultados == NULL) {
        printf("\n[ No se encontraron estudiantes con ese criterio. ]\n");
        return;
    }
    printf("\n--- 🔍 RESULTADOS DE LA BÚSQUEDA ---\n");
    LinkedNode *cursor = listaResultados;
    while (cursor != NULL) {
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
void AltaEstudiante(GestorEstudiantes *ge) {
    char nombre[15];
    char apellido[15];
    char nacimiento[11];
    int sexo;

    printf("\n--- ➕ DAR DE ALTA ESTUDIANTE ---\n");

    printf("Ingrese nombre: ");
    leerCadena(nombre, 15);

    printf("Ingrese apellido: ");
    leerCadena(apellido, 15);

    printf("Ingrese fecha de nacimiento en formato dd/mm/yyyy (con las barras incluidas): ");
    leerCadena(nacimiento, 11);

    do {
        printf("Ingrese su sexo (0 = Hombre, 1 = Mujer): ");
        sexo = leerEntero();
    } while (sexo != 0 && sexo != 1);

    Estudiante *nuevoEstudiante = NewEstudiante(nombre, apellido, nacimiento, sexo);
    // Inicializar campos nuevos
    nuevoEstudiante->materiasAprobadas = NULL;
    nuevoEstudiante->esGraduado = 0;

    ListarEstudiante(ge, nuevoEstudiante);

    printf("\n✅ El estudiante se dio de alta correctamente con los siguientes datos:\n");
    MostrarEstudianteSimple(nuevoEstudiante);
    printf("----------------------------------------\n");
    pausar(NULL);
}

/**
 * Implementa la opción 4: Eliminar estudiante.
 */
void EliminarEstudiante(GestorEstudiantes *ge) {
    int id;
    char confirmacion[5];
    Estudiante *e;

    printf("\n--- 🗑️ ELIMINAR ESTUDIANTE ---\n");
    id = leerID("Ingrese su ID: ");

    e = BuscarEstudianteID(ge, id);

    if (e == NULL) {
        printf("⚠️ ERROR: Estudiante con ID %d no encontrado.\n", id);
        pausar(NULL);
        return;
    }

    printf("Estudiante a eliminar: ");
    MostrarEstudianteSimple(e);

    printf("Confirma que elimina el estudiante (s/n): ");
    leerCadena(confirmacion, 5);

    if (strcmp(confirmacion, "s") == 0 || strcmp(confirmacion, "S") == 0) {
        DeslistarEstudianteID(ge, id);
        printf("\n✅ Estudiante eliminado correctamente.\n");
    } else {
        printf("\n❌ Operación cancelada.\n");
    }
    pausar(NULL);
}

/**
 * Implementa la opción 5: Buscar estudiante.
 */
void BuscarEstudiante(GestorEstudiantes *ge) {
    int opcion;
    int id;
    char nombre[15];
    int v1, v2;
    Estudiante *est;
    LinkedNode *resultados = NULL;

    printf("\n--- 🔍 BUSCAR ESTUDIANTE ---\n");
    printf("|| Elegir parámetro de búsqueda ||\n");
    printf("1. ID\n");
    printf("2. Nombre\n");
    printf("3. Rango de edad\n");
    printf("4. Volver\n");
    printf("--------------------------------\n");

    opcion = leerOpcion();
    limpiarPantalla();

    switch (opcion) {
    case 1:
        id = leerID("Ingrese ID a buscar: ");
        est = BuscarEstudianteID(ge, id);
        if (est != NULL) {
            printf("\n✅ Estudiante encontrado:\n");
            MostrarEstudianteSimple(est);
        } else {
            printf("\n[ Estudiante con ID %d no encontrado. ]\n", id);
        }
        break;
    case 2:
        printf("Ingrese Nombre a buscar: ");
        leerCadena(nombre, 15);
        est = BuscarEstudianteNombre(ge, nombre);
        if (est != NULL) {
            printf("\n✅ Estudiante encontrado:\n");
            MostrarEstudianteSimple(est);
        } else {
            printf("\n[ Estudiante con nombre '%s' no encontrado. ]\n", nombre);
        }
        break;
    case 3:
        printf("Ingrese edad mínima (v1): ");
        v1 = leerEntero();
        printf("Ingrese edad máxima (v2): ");
        v2 = leerEntero();
        if (v1 > v2) {
            int temp = v1;
            v1 = v2;
            v2 = temp;
        }
        resultados = BuscarRangoEdad(ge, v1, v2);
        MostrarEstudiantesBusqueda(resultados);
        // La función BuscarRangoEdad crea una nueva lista, hay que liberarla
        freeList(resultados);
        break;
    case 4:
        return;
    default:
        printf("⚠️ Opción inválida.\n");
    }
    pausar(NULL);
}

/**
 * Implementa la opción 1: Modificar parámetros del menú de estudiante.
 */
void MenuModificarEstudiante(Estudiante *e) {
    int opcion;
    char nuevoValor[20];
    int nuevoSexo;

    do {
        limpiarPantalla();
        printf("\n|| MODIFICAR PARÁMETROS DE %s %s ||\n", ObtenerNombre(e), ObtenerApellido(e));
        printf("1. Nombre (Actual: %s)\n", ObtenerNombre(e));
        printf("2. Apellido (Actual: %s)\n", ObtenerApellido(e));
        printf("3. Fecha de nacimiento (Actual: %s, Edad: %d)\n", ObtenerNacimiento(e), ObtenerEdad(e));
        printf("4. Sexo (Actual: %s)\n", ObtenerSexo(e));
        printf("5. Volver\n");
        printf("--------------------------------\n");
        printf("|| Elegir opción que desea modificar ||\n");

        opcion = leerOpcion();
        limpiarPantalla();

        switch (opcion) {
        case 1:
            printf("Ingrese nuevo nombre: ");
            leerCadena(nuevoValor, 15);
            CambiarNombre(e, nuevoValor);
            printf("✅ Nombre modificado.\n");
            break;
        case 2:
            printf("Ingrese nuevo apellido: ");
            leerCadena(nuevoValor, 15);
            CambiarApellido(e, nuevoValor);
            printf("✅ Apellido modificado.\n");
            break;
        case 3:
            printf("Ingrese nueva fecha de nacimiento (dd/mm/yyyy): ");
            leerCadena(nuevoValor, 11);
            CambiarNacimiento(e, nuevoValor);
            printf("✅ Fecha de nacimiento modificada (Nueva edad: %d).\n", ObtenerEdad(e));
            break;
        case 4:
            do {
                printf("Ingrese nuevo sexo (0 = Hombre, 1 = Mujer): ");
                nuevoSexo = leerEntero();
            } while (nuevoSexo != 0 && nuevoSexo != 1);
            CambiarSexo(e, nuevoSexo);
            printf("✅ Sexo modificado.\n");
            break;
        case 5:
            return;
        default:
            printf("⚠️ Opción inválida.\n");
        }
        pausar(NULL);
    } while (opcion != 5);
}

/**
 * Implementa la opción 3: Rendir materia del menú de estudiante.
 * Asume que el estudiante ya está inscrito.
 */
void RendirMateria(Estudiante *e, Materia *materia) {
    // Buscar la inscripción en la materia
    DoubleLinkedNode *cursor = materia->listaInscripciones;
    Inscripcion *inscripcion = NULL;
    while (cursor != NULL) {
        Inscripcion *i = (Inscripcion *)cursor->data;
        if (i->estudiante == e) {
            inscripcion = i;
            break;
        }
        cursor = cursor->next;
    }

    if (inscripcion == NULL) {
        printf("⚠️ ERROR: El estudiante no está inscrito en esta materia.\n");
        return;
    }

    if (HaAprobadoMateriaGestor(e, materia->ID)) {
        printf("⚠️ Advertencia: El estudiante ya aprobó esta materia.\n");
        return;
    }

    // Suponemos una nota aleatoria o una simple aprobación
    int aprobacion;
    do {
        printf("Ingrese resultado (1 = Aprobado, 0 = Reprobado): ");
        aprobacion = leerEntero();
    } while (aprobacion != 0 && aprobacion != 1);

    if (aprobacion == 1) {
        // 1. Actualizar la inscripción
        inscripcion->estaAprobado = 1;
        // 2. Añadir a la lista de materias aprobadas del estudiante
        AprobarMateriaGestor(e, materia->ID);
        printf("✅ Materia '%s' aprobada e historico actualizado.\n", materia->nombre);
    } else {
        inscripcion->estaAprobado = 0;
        printf("❌ Materia '%s' reprobada. Inscripción actualizada.\n", materia->nombre);
    }
}

/**
 * Implementa la opción 4: Dar de baja materia del menú de estudiante.
 */
void DarDeBajaInscripcion(Estudiante *e, Materia *materia) {
    DoubleLinkedNode *current = materia->listaInscripciones;
    int posicion = 0;

    while (current != NULL) {
        Inscripcion *insc = (Inscripcion *)current->data;
        if (insc->estudiante == e) {
            // Eliminar y liberar la inscripción
            Inscripcion *insc_a_liberar = (Inscripcion *)RemoveElement(&materia->listaInscripciones, posicion);
            if (insc_a_liberar != NULL) {
                // Si la inscripción existía, liberar la estructura Inscripcion
                // NOTA: FreeInscripcion ya NO libera al Estudiante*, solo la estructura Inscripcion.
                FreeInscripcion(insc_a_liberar);
                printf("✅ Inscripción eliminada para la materia '%s'.\n", materia->nombre);
            }
            return;
        }
        current = current->next;
        posicion++;
    }

    printf("⚠️ ERROR: El estudiante no está inscrito en la materia '%s'.\n", materia->nombre);
}

/**
 * Menú para interactuar con un estudiante específico (Opción 3 del gestor).
 */
void MenuAccederEstudiante(Estudiante *e, GestorMaterias *gm, GestorEstudiantes *ge) {
    int opcion;
    int idMateria;
    Materia *materia;
    char confirmacion[5];
    LinkedNode *materiasInscritas = NULL; // Usaremos una lista temporal para rendir/dar de baja

    do {
        limpiarPantalla();
        printf("\n|| Hola ID %d (%s %s) ||\n", ObtenerID(e), ObtenerNombre(e), ObtenerApellido(e));
        printf("1. Modificar parámetros\n");
        printf("2. Anotarse a materia\n");
        printf("3. Rendir materia\n");
        printf("4. Dar de baja materia (Inscripción)\n");
        printf("5. Ver mis materias aprobadas\n");
        printf("6. Volver\n");
        printf("--------------------------------\n");
        printf("|| Elegir opción que desee ||\n");

        opcion = leerOpcion();
        limpiarPantalla();

        switch (opcion) {
        case 1:
            MenuModificarEstudiante(e);
            break;
        case 2:
            // Anotarse a materia
            MostrarMateriasDisponibles(gm);
            idMateria = leerID("Ingrese ID de la materia a anotarse: ");
            materia = BuscarMateriaPorID(gm, idMateria);

            if (materia != NULL) {
                // El 0 indica que inicialmente está 'Reprobado' (simplemente inscrito)
                MatricularEstudiante(gm, idMateria, e, 0);
            } else {
                printf("⚠️ ERROR: Materia con ID %d no encontrada.\n", idMateria);
            }
            pausar(NULL);
            break;
        case 3:
            // Rendir materia: Necesita estar inscrito
            MostrarMateriasDisponibles(gm);
            idMateria = leerID("Ingrese ID de la materia a rendir: ");
            materia = BuscarMateriaPorID(gm, idMateria);

            if (materia != NULL) {
                RendirMateria(e, materia);
            } else {
                printf("⚠️ ERROR: Materia con ID %d no encontrada.\n", idMateria);
            }
            pausar(NULL);
            break;
        case 4:
            // Dar de baja materia: Solo elimina la inscripción
            MostrarMateriasDisponibles(gm);
            idMateria = leerID("Ingrese ID de la materia a darse de baja: ");
            materia = BuscarMateriaPorID(gm, idMateria);

            if (materia != NULL) {
                printf("Confirma dar de baja la inscripción de '%s' (s/n): ", materia->nombre);
                leerCadena(confirmacion, 5);
                if (strcmp(confirmacion, "s") == 0 || strcmp(confirmacion, "S") == 0) {
                    DarDeBajaInscripcion(e, materia);
                } else {
                    printf("\n❌ Operación cancelada.\n");
                }
            } else {
                printf("⚠️ ERROR: Materia con ID %d no encontrada.\n", idMateria);
            }
            pausar(NULL);
            break;
        case 5:
            // Ver materias aprobadas
            MostrarMateriasAprobadasEstudiante(e, gm);
            pausar(NULL);
            break;
        case 6:
            // Volver
            break;
        default:
            printf("⚠️ Opción inválida.\n");
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
void AltaMateria(GestorMaterias *gm) {
    char nombre[50];
    printf("\n--- ➕ DAR DE ALTA MATERIA ---\n");
    printf("Ingrese nombre de la materia: ");
    leerCadena(nombre, 50);

    AgregarMateria(gm, nombre);

    // Buscamos la materia recién agregada (no es eficiente pero es simple)
    // Se puede modificar AgregarMateria para que devuelva la Materia*
    printf("\n✅ Materia dada de alta correctamente. \n");
    // Podríamos mostrar la lista de nuevo, pero no es estrictamente necesario
    pausar(NULL);
}

/**
 * Implementa la opción 3: Modificar nombre de materia.
 */
void ModificarNombreMateria(GestorMaterias *gm) {
    int id;
    char nuevoNombre[50];
    Materia *materia;

    printf("\n--- ✏️ MODIFICAR NOMBRE DE MATERIA ---\n");
    MostrarMateriasDisponibles(gm);
    id = leerID("Ingrese ID de la materia a modificar: ");

    materia = BuscarMateriaPorID(gm, id);

    if (materia == NULL) {
        printf("⚠️ ERROR: Materia con ID %d no encontrada.\n", id);
        pausar(NULL);
        return;
    }

    printf("Materia seleccionada: %s\n", materia->nombre);
    printf("Ingrese nuevo nombre: ");
    leerCadena(nuevoNombre, 50);

    strcpy(materia->nombre, nuevoNombre);
    printf("\n✅ Nombre de materia modificado a '%s'.\n", materia->nombre);
    pausar(NULL);
}

/**
 * Implementa la opción 4: Eliminar materia.
 */
void EliminarMateriaCLI(GestorMaterias *gm) {
    int id;
    char confirmacion[5];

    printf("\n--- 🗑️ ELIMINAR MATERIA ---\n");
    MostrarMateriasDisponibles(gm);
    id = leerID("Ingrese ID de la materia a eliminar: ");

    Materia *materia = BuscarMateriaPorID(gm, id);

    if (materia == NULL) {
        printf("⚠️ ERROR: Materia con ID %d no encontrada.\n", id);
        pausar(NULL);
        return;
    }

    printf("Confirma eliminar la materia '%s' y todas sus inscripciones (s/n): ", materia->nombre);
    leerCadena(confirmacion, 5);

    if (strcmp(confirmacion, "s") == 0 || strcmp(confirmacion, "S") == 0) {
        EliminarMateria(gm, id);
        printf("\n✅ Materia eliminada correctamente.\n");
    } else {
        printf("\n❌ Operación cancelada.\n");
    }
    pausar(NULL);
}

// **********************************************
// Funciones de Menú
// **********************************************

/**
 * Menú de estadísticas (Opción 3 del menú principal).
 */
void MenuEstadisticas(GestorEstudiantes *ge, GestorMaterias *gm) {
    limpiarPantalla();
    printf("\n||              BIENVENIDO a las estadisticas             ||\n");

    // Estadísticas Generales
    EstadisticasGenerales *stats = CalcularEstadisticasGenerales(ge, gm);
    MostrarEstadisticasGenerales(stats);

    // Promedio de Aprobados por Materia
    MostrarPromedioAprobadosPorMateria(gm);

    // NOTA: stats fue creado con malloc, debe ser liberado
    if (stats != NULL) {
        free(stats);
    }

    pausar("presione una tecla para volver...");
}

/**
 * Menú de gestión de materias (Opción 2 del menú principal).
 */
void MenuGestorMaterias(GestorMaterias *gm) {
    int opcion;

    do {
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

        switch (opcion) {
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
            printf("⚠️ Opción inválida.\n");
            pausar(NULL);
        }
    } while (opcion != 5);
}

/**
 * Menú de gestión de estudiantes (Opción 1 del menú principal).
 */
void MenuGestorEstudiantes(GestorEstudiantes *ge, GestorMaterias *gm) {
    int opcion;
    int id;
    Estudiante *estudiante;

    do {
        limpiarPantalla();
        printf("\n||              BIENVENIDO al gestor de estudiantes             ||\n");
        printf("1. Ver Estudiantes (muestra info de estudiantes)\n");
        printf("2. Dar de alta estudiante\n");
        printf("3. Acceder a estudiante\n");
        printf("4. Eliminar estudiantes\n");
        printf("5. Buscar estudiante\n");
        printf("6. Volver\n");
        printf("------------------------------------------------------------------------\n");

        opcion = leerOpcion();
        limpiarPantalla();

        switch (opcion) {
        case 1:
            MostrarEstudiantesLista(ge);
            pausar(NULL);
            break;
        case 2:
            AltaEstudiante(ge);
            break;
        case 3:
            // Acceder a estudiante
            id = leerID("Ingrese ID de estudiante: ");
            estudiante = BuscarEstudianteID(ge, id);
            if (estudiante != NULL) {
                MenuAccederEstudiante(estudiante, gm, ge);
            } else {
                printf("⚠️ ERROR: Estudiante con ID %d no encontrado.\n", id);
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
            printf("⚠️ Opción inválida.\n");
            pausar(NULL);
        }
    } while (opcion != 6);
}

/**
 * Menú principal del sistema.
 */
void MenuPrincipal(GestorEstudiantes *ge, GestorMaterias *gm) {
    int opcion;

    do {
        limpiarPantalla();
        printf("\n// Sistema de estudiantes de ingenieria en computacion - Los C-Renitos //\n");
        printf("||              BIENVENIDO                ||\n");
        printf("1. gestionar estudiantes\n");
        printf("2. gestionar materias\n");
        printf("3. estadisticas generales\n");
        printf("4. salir\n");
        printf("=============================================\n");

        opcion = leerOpcion();

        switch (opcion) {
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
            printf("\n¡Gracias por usar Los C-Renitos! Cerrando sistema...\n");
            break;
        default:
            printf("⚠️ Opción inválida. Intente de nuevo.\n");
            pausar(NULL);
        }
    } while (opcion != 4);
}