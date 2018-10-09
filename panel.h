#ifndef PANEL
#define PANEL

#include "lista.h"
#include "planificador.h"

/**
* \brief Muestra por consola el menu de opciones para el usuario.
* Se asocia un numero a cada opcion mostrada por consola.
*/
void mostrar_menu();

/**
* \brief Recibe una lista de ciudades, que luego seran mostradas por pantalla.
* Se muestra el nombre de la ciudad, junto con un numero que identifica el orden correspondiente.
*/
void mostrar_ciudades(TLista ciudades);

/**
* \brief Interpreta la opcion elegida por el usuario y la ejecuta con la informacion recibida como parametro.
*
* Recibe un numero que indica la opcion elegida por el usuario, una lista de ciudades y un viajante
*/
void elegir_opcion(int opcion, TLista ciudades, Viajante viajante);

#endif
