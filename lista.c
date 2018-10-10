#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "constantes.h"

struct celda * crear_celda() {
    struct celda * nueva = (struct celda *)malloc(sizeof(struct celda));
    nueva->celda_anterior  = POS_NULA;
    nueva->celda_siguiente = POS_NULA;
    nueva->elemento = POS_NULA;
    return nueva;
}

TLista crear_lista() {
    TLista nueva_lista = POS_NULA;
    return nueva_lista;
}

int l_insertar(TLista * lista, TPosicion pos, TElemento elem) {
    int resultado = FALSE;
    if(lista!=POS_NULA){
        resultado = TRUE;
        if(*lista!=POS_NULA) {
            if(pos!=POS_NULA){
                pos->elemento = elem;
            }
            else{
                TPosicion nueva = crear_celda();
                nueva->celda_siguiente = *lista;
                nueva->elemento = elem;
                (*lista)->celda_anterior = nueva;
                *lista = nueva;
            }
        }
        else {
            TPosicion nueva = crear_celda();
            nueva->elemento = elem;
            *lista = nueva;
        }
    }
    else{ exit(LST_NO_INI); }
    return resultado;
}

int l_eliminar(TLista * lista, TPosicion pos) {
    int resultado = FALSE;
    if(lista != NULL){
        if(*lista!=NULL && pos!=POS_NULA) {
            resultado = TRUE;
            if(pos->celda_anterior==POS_NULA && pos->celda_siguiente==POS_NULA){
               *lista = NULL;
            }
            else{
                 if(pos->celda_anterior==POS_NULA){
                   (pos->celda_siguiente)->celda_anterior = POS_NULA;
                    *lista = pos->celda_siguiente;
                 }
                 else{
                      if(pos->celda_siguiente==POS_NULA){
                        (pos->celda_anterior)->celda_siguiente = POS_NULA;
                      }
                      else{
                          (pos->celda_anterior)->celda_siguiente = pos->celda_siguiente;
                          (pos->celda_siguiente)->celda_anterior = pos->celda_anterior;
                      }
                 }
            }
            pos->celda_anterior = POS_NULA;
            pos->celda_siguiente = POS_NULA;
            pos->elemento = ELE_NULO;
            free(pos);
            pos = POS_NULA;
        }
    }
    else { exit(LST_NO_INI); }
    return resultado;
}

TPosicion l_primera(TLista lista) {
    TPosicion pos = NULL;
    if(lista!=POS_NULA){
        pos = lista;
    }
    return pos;
}

TPosicion l_ultima(TLista lista) {
    TPosicion pos = POS_NULA;
    if(lista!=POS_NULA){
        TPosicion recorrido = lista;
        while(recorrido->celda_siguiente!=POS_NULA){
              recorrido = recorrido->celda_siguiente;
        }
        pos = recorrido;
    }
    return pos;
}

TPosicion l_anterior(TLista lista, TPosicion pos) {
    TPosicion posicion = NULL;
    if(lista!=NULL && pos!=POS_NULA){
        posicion = pos->celda_anterior;
    }
    return posicion;
}

TPosicion l_siguiente(TLista lista, TPosicion pos) {
    TPosicion posicion = POS_NULA;
    if(lista!=POS_NULA && pos!=POS_NULA){
        posicion = pos->celda_siguiente;
    }
    return posicion;
}

TElemento l_recuperar(TLista lista ,TPosicion pos) {
    TElemento elemento = ELE_NULO;
    if(lista!=POS_NULA && pos!=POS_NULA){
        elemento = pos->elemento;
    }
    return elemento;
}

int l_size(TLista lista) {
    int cantidad = 0;
    if(lista!=POS_NULA){
        TPosicion recorrido = lista;
        while(recorrido!=POS_NULA){
              recorrido = recorrido->celda_siguiente;
              cantidad++;
        }
    }
    return cantidad;
}

int l_destruir(TLista * lista) {
    int resultado = FALSE;
    if(lista != POS_NULA){
        if(*lista!=POS_NULA) {
            TPosicion recorrido = *lista;
            TPosicion aux;
            while(recorrido != POS_NULA){
                aux = recorrido;
                recorrido = recorrido->celda_siguiente;
                free(aux);
                aux = POS_NULA;
            }
            *lista = POS_NULA;
            resultado = TRUE;
        }
    }
    else { exit(LST_NO_INI); }
    return resultado;
}
