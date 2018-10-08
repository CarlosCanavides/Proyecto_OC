#ifndef LECTOR
#define LECTOR

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "planificador.h"

FILE * abrir_archivo(char* nombre_archivo);

void cerrar_archivo(FILE* archivo);

TLista obtener_ciudades(FILE* archivo);

Viajante obtener_viajante(FILE* archivo);

#endif
