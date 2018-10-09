#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "constantes.h"

struct celda * crear_celda() {
    struct celda * nueva = (struct celda *)malloc(sizeof(struct celda));
    nueva->celda_anterior  = NULL;
    nueva->celda_siguiente = NULL;
    nueva->elemento = NULL;
    return nueva;
}

TLista crear_lista() {
    TLista nueva_lista = NULL;
    return nueva_lista;
}

int l_insertar(TLista * lista, TPosicion pos, TElemento elem) {
    int resultado = 0;
    if(lista!=NULL){
        if(*lista!=NULL) {
            if(pos!=NULL){
                struct celda * recorrido = *lista;
                while(recorrido!=pos && recorrido->celda_siguiente!=NULL){
                      recorrido = recorrido->celda_siguiente;
                }
                if(recorrido==pos){
                   recorrido->elemento = elem;
                   resultado = 1;
                }
            }
            else{
                struct celda * nueva = crear_celda();
                nueva->celda_siguiente = *lista;
                nueva->elemento = elem;
                (*lista)->celda_anterior = nueva;
                *lista = nueva;
                resultado = 1;
            }
        }
        else {
            struct celda * nueva = crear_celda();
            nueva->elemento = elem;
            *lista = nueva;
            resultado = 1;
        }
    }
    else{ exit(LST_NO_INI); }
    return resultado;
}

int l_eliminar(TLista * lista, TPosicion pos) {
    int resultado = 0;
    if(lista != NULL){
        if(*lista!=NULL) {
            struct celda * recorrido = *lista;
            while(recorrido!=pos && recorrido->celda_siguiente!=NULL){
                  recorrido = recorrido->celda_siguiente;
            }
            if(recorrido==pos){
                resultado = 1;
                if(recorrido->celda_anterior==NULL && recorrido->celda_siguiente==NULL){
                    *lista = NULL;
                }
                else{
                    if(recorrido->celda_anterior==NULL){
                      (recorrido->celda_siguiente)->celda_anterior = NULL;
                      *lista = recorrido->celda_siguiente;
                    }
                    else{
                        if(recorrido->celda_siguiente==NULL){
                          (recorrido->celda_anterior)->celda_siguiente = NULL;
                        }
                        else{
                            (recorrido->celda_anterior)->celda_siguiente = recorrido->celda_siguiente;
                            (recorrido->celda_siguiente)->celda_anterior = recorrido->celda_anterior;
                        }
                    }
                }
                free(recorrido);
            }
        }
    }
    else { exit(LST_NO_INI); }
    return resultado;
}

TPosicion l_primera(TLista lista) {
    TPosicion pos = NULL;
    if(lista!=NULL){
        pos = lista;
    }
    return pos;
}

TPosicion l_ultima(TLista lista) {
    TPosicion pos = NULL;
    if(lista!=NULL){
        struct celda * recorrido = lista;
        while(recorrido->celda_siguiente!=NULL){
              recorrido = recorrido->celda_siguiente;
        }
        pos = recorrido;
    }
    return pos;
}

TPosicion l_anterior(TLista lista, TPosicion pos) {
    TPosicion posicion = NULL;
    if(lista!=NULL){
        struct celda * recorrido = lista;
        while(recorrido!=pos && recorrido->celda_siguiente!=NULL){
              recorrido = recorrido->celda_siguiente;
        }
        if(recorrido==pos){
            posicion = recorrido->celda_anterior;
        }
    }
    return posicion;
}

TPosicion l_siguiente(TLista lista, TPosicion pos) {
    TPosicion posicion = NULL;
    if(lista!=NULL){
        struct celda * recorrido = lista;
        while(recorrido!=pos && recorrido->celda_siguiente!=NULL){
              recorrido = recorrido->celda_siguiente;
        }
        if(recorrido==pos){
           posicion = recorrido->celda_siguiente;
        }
    }
    return posicion;
}

TElemento l_recuperar(TLista lista ,TPosicion pos) {
    TElemento elemento = NULL;
    if(lista!=NULL){
        struct celda * recorrido = lista;
        while(recorrido!=pos && recorrido->celda_siguiente!=NULL){
              recorrido = recorrido->celda_siguiente;
        }
        if(recorrido==pos){
           elemento = recorrido->elemento;
        }
    }
    return elemento;
}

int l_size(TLista lista) {
    int cantidad = 0;
    if(lista!=NULL){
        struct celda * recorrido = lista;
        while(recorrido!=NULL){
              recorrido = recorrido->celda_siguiente;
              cantidad++;
        }
    }
    return cantidad;
}

int l_destruir(TLista * lista) {
    int resultado = 0;
    if(lista != NULL){
        if(*lista!=NULL) {
            struct celda * recorrido = *lista;
            struct celda * aux;
            while(recorrido != NULL){
                aux = recorrido;
                recorrido = recorrido->celda_siguiente;
                free(aux);
            }
            *lista = NULL;
            resultado = 1;
        }
    }
    else { exit(LST_NO_INI); }
    return resultado;
}
