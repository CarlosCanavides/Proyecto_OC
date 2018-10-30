#ifndef PANEL
#define PANEL

#include "lista.h"
#include "planificador.h"

/**
* \brief Muestra por consola la ciudad pasada como paámetro.
* Se asocia un numero a cada ciudad mostrada por consola, dicho número corresponde con su orden.
*/
void imprimir_ciudad(TCiudad ciudad, int orden);

/**
* \brief Muestra por consola una separación (espacio).
*/
void mostrar_espaciado();

/**
* \brief Muestra por consola el menu de opciones para el usuario.
* Se asocia un numero a cada opcion mostrada por consola.
*/
void mostrar_menu();

/**
* \brief Interpreta la opcion elegida por el usuario y la ejecuta con la informacion recibida como parametro.
*
* Recibe un numero que indica la opcion elegida por el usuario, una lista de ciudades y un viajante
*/
void elegir_opcion(int opcion, TLista ciudades, Viajante viajante);

#endif
