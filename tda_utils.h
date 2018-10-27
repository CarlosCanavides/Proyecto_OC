#ifndef LISTA_UTILS
#define LISTA_UTILS

#include "lista.h"
#include "colacp.h"

/**
* \brief Recibe una lista, una funcion comparadora, una funcion pesadora
* y retorna una nueva lista con el orden resultante.
*
* Utiliza una cola con prioridad para insertar los elementos de la lista y formar
* la nueva lista ordenada. La prioridad de los elementos se obtiene a traves
* de la funcion pesadora.
*
* \param lista Lista original.
* \param comparador Funcion que compara dos entradas (clave-valor).
* \param pesador Funcion que dado un elemento y un argumento opcional retorna la prioridad o peso que tiene.
* \param optarg Puntero void a un argumento opcional para entregarselo a la funcion pesador.
*/
void ordenar_lista(TLista lista, int (*comparador)(TEntrada, TEntrada), void* (*pesador)(TElemento, void* optarg), void* optarg);


/**
* \brief Recibe una lista y retorna una lista duplicada con los mismos elementos.
*
* Los elementos de la nueva lista son los mismos que la lista original.
*
* \param lista Lista original
*/
TLista duplicar_lista(TLista lista);

/**
* \brief Recibe un puntero a una lista y elimina todos sus elementos, liberando tambien la memoria
* que puedan estar ocupando.
*
* \param lista Puntero a la lista a limpiar.
*/
void limpiar_lista_ciudades(TLista * lista);

/**
* \brief Recibe un puntero a una cola con prioridad y elimina todas sus entradas, liberando el espacio de memoria reservado.
*
* \param lista Puntero a la ccp a limpiar.
*/
void limpiar_ccp_ciudades(TColaCP * cola);

/**
* \brief Recibe un puntero a una lista y un elemento, si el elemento
* pertenece a la lista, este es eliminado de la misma.
*
* \param lista Lista donde se buscara el elemento.
* \param elemento Elemento que se desea eliminar de la lista.
*/
void eliminar_elemento(TLista * lista, TElemento elemento);

#endif
