#ifndef PLANIFICADOR
#define PLANIFICADOR

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "comparadores.h"
typedef struct ciudad {
    char * nombre;
    float pos_x;
    float pos_y;
} * TCiudad;

typedef struct viajante {
    float pos_x;
    float pos_y;
} * Viajante;


int main_principal();

TLista mostrar_ciudades_ascendentes(TLista ciudades, Viajante viajante);

TLista mostrar_ciudades_descendentes(TLista ciudades, Viajante viajante);

TLista reducir_horas_manejo(TLista ciudades, Viajante viajante);

#endif
