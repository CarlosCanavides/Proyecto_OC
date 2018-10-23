#ifndef PLANIFICADOR
#define PLANIFICADOR

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "utils.h"

/**
* \brief Representacion de una ciudad.
*
* Almacena la informacion que corresponde a una ciudad en el sistema.
*/
typedef struct ciudad {
    char * nombre;
    float pos_x;
    float pos_y;
} * TCiudad;

/**
* \brief Representacion del viajante o usuario.
*
* Alamacena la posicion actual del usuario
*/
typedef struct viajante {
    float pos_x;
    float pos_y;
} * Viajante;


int main(int argc, char* arg[]);


/**
* \brief
*
* \param TLista ciudades, lista de ciudades
* \param Viajante viajante
*/
TLista mostrar_ciudades_ascendentes(TLista ciudades, Viajante viajante);


/**
* \brief
*
* \param TLista ciudades
* \param Viajante viajante
*/
TLista mostrar_ciudades_descendentes(TLista ciudades, Viajante viajante);


/**
* \brief
*
* \param TLista ciudades
* \param Viajante viajante
*/
TLista reducir_horas_manejo(TLista ciudades, Viajante viajante);

#endif
