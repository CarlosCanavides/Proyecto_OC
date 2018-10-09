#ifndef LECTOR
#define LECTOR

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "planificador.h"

/**
* \brief Abre un archivo y retorna un puntero al mismo.
*
* \param nombre_archivo Direccion relativa del archivo que se desea abrir.
*/
FILE * abrir_archivo(char* nombre_archivo);

/**
* \brief Cierra un archivo que fue abierto previamente.
*
* \param archivo Archivo abierto.
*/
void cerrar_archivo(FILE* archivo);

/**
* \brief Intepreta un archivo recibido y retorna una lista
* con las ciudades que alli se encuentran descriptas
*
* \param archivo Archivo que contiene ciudades
*/
TLista obtener_ciudades(FILE* archivo);

/**
* \brief Interpreta un archivo recibido y retorna un tipo Viajante
* con la informacion proveida por el archivo.
*
* \param archivo Archivo que contiene informacion del viajante.
*/
Viajante obtener_viajante(FILE* archivo);

#endif
