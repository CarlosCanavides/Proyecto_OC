#ifndef LISTA_UTILS
#define LISTA_UTILS

#include "lista.h"
#include "colacp.h"

TLista ordenar_lista(TLista lista, int (*comparador)(TEntrada, TEntrada));

TLista duplicar_lista(TLista lista);

void limpiar_lista(TLista* lista);

void invertir_lista(TLista* lista);

#endif
