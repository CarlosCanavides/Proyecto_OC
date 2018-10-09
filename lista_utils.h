#ifndef LISTA_UTILS
#define LISTA_UTILS

#include "lista.h"
#include "colacp.h"

TLista ordenar_lista(TLista lista, int (*comparador)(TEntrada, TEntrada), void* (*pesador)(TElemento, void* optarg), void* optarg);

TLista duplicar_lista(TLista lista);

void limpiar_lista(TLista* lista);

void invertir_lista(TLista* lista);

void eliminar_elemento(TLista * lista, TElemento elemento);

#endif
