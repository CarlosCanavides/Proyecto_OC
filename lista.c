#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "constantes.h"

TPosicion crear_celda() {
    // Se reserva espacio de memoria para una nueva celda de la lista.
    // Los campos de la celda se setean a NULL (inicialización por defecto).
    TPosicion nueva = (TPosicion)malloc(sizeof(struct celda));
    nueva->celda_anterior  = POS_NULA;
    nueva->celda_siguiente = POS_NULA;
    nueva->elemento = ELE_NULO;
    return nueva;
}

TLista crear_lista() {
    TLista nueva_lista = POS_NULA;  // Se representa una lista vacia como un puntero a POS_NULA.
    return nueva_lista;
}

int l_insertar(TLista * lista, TPosicion pos, TElemento elem) {
    int resultado = FALSE;
    if(lista!=NULL){            // Si el puntero al TLista que se recibe como parámetro no es nulo.
        resultado = TRUE;
        if(*lista!=POS_NULA) {  // Si la lista no está vacia.
            if(pos!=POS_NULA){  // Si la posición pasada como parámetro no es POS_NULA.
               TPosicion nueva = crear_celda();
               nueva->elemento = elem;
               nueva->celda_siguiente = pos;
               if(pos->celda_anterior==POS_NULA){ // Si la pos pasada como parámetro es la 1ra posicion de la lista.
                  *lista = nueva;
               }
               else {
                    (pos->celda_anterior)->celda_siguiente = nueva;
               }
               pos->celda_anterior = nueva;
            }
            else{  // Si la posición pasada como parámetro es POS_NULA.
                TPosicion nueva = crear_celda();
                nueva->celda_siguiente = *lista;
                nueva->elemento = elem;
                (*lista)->celda_anterior = nueva;
                *lista = nueva;
            }
        }
        else {  // Si la lista está vacia, creo una nueva celda con elemento y modifico el puntero de la lista.
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
    if(lista != NULL){  // Si el puntero al TLista que se recibe como parámetro no es nulo.
        if(*lista!=NULL && pos!=POS_NULA) {
            resultado = TRUE;
            if(pos->celda_anterior==POS_NULA && pos->celda_siguiente==POS_NULA){ // Si pos es la única posición de la lista.
               *lista = NULL;
            }
            else{  // Si pos no es la única posición de la lista.
                 if(pos->celda_anterior==POS_NULA){  // Si pos es la 1ra posición.
                   (pos->celda_siguiente)->celda_anterior = POS_NULA;
                    *lista = pos->celda_siguiente;
                 }
                 else{
                      if(pos->celda_siguiente==POS_NULA){ // Si pos es la última posición.
                        (pos->celda_anterior)->celda_siguiente = POS_NULA;
                      }
                      else{  // Si pos es una posición que esta en "medio" de la lista.
                          (pos->celda_anterior)->celda_siguiente = pos->celda_siguiente;
                          (pos->celda_siguiente)->celda_anterior = pos->celda_anterior;
                      }
                 }
            }
            // Una vez hechos los cambios necesarios en la lista, se procede a setear todo a NULL.
            // Y liberar el espacio de memoria correspondiente a la celda.
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
    TPosicion pos = POS_NULA;
    if(lista!=POS_NULA){  // Si la lista no está vacia.
        pos = lista;
    }
    return pos;
}

TPosicion l_ultima(TLista lista) {
    TPosicion pos = POS_NULA;
    if(lista!=POS_NULA){  // Si la lista no está vacia.
        TPosicion recorrido = lista;
        while(recorrido->celda_siguiente!=POS_NULA){
              recorrido = recorrido->celda_siguiente;
        }
        pos = recorrido;
    }
    return pos;
}

TPosicion l_anterior(TLista lista, TPosicion pos) {
    TPosicion posicion = POS_NULA;
    if(lista!=POS_NULA && pos!=POS_NULA){ // Si la lista no está vacia y la pos pasada como parámetro no es ṔOS_NULA.
        posicion = pos->celda_anterior;
    }
    return posicion;
}

TPosicion l_siguiente(TLista lista, TPosicion pos) {
    TPosicion posicion = POS_NULA;
    if(lista!=POS_NULA && pos!=POS_NULA){ // Si la lista no está vacia y la pos pasada como parámetro no es ṔOS_NULA.
        posicion = pos->celda_siguiente;
    }
    return posicion;
}

TElemento l_recuperar(TLista lista ,TPosicion pos) {
    TElemento elemento = ELE_NULO;
    if(lista!=POS_NULA && pos!=POS_NULA){ // Si la lista no está vacia y la pos pasada como parámetro no es ṔOS_NULA.
        elemento = pos->elemento;
    }
    return elemento;
}

int l_size(TLista lista) {
    int cantidad = 0;
    if(lista!=POS_NULA){  // Si la lista no está vacia.
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
    if(lista != POS_NULA){      // Si el puntero al TLista que se recibe como parámetro no es nulo.
        if(*lista!=POS_NULA) {  // Si la lista no está vacia.
            TPosicion recorrido = *lista;
            TPosicion aux;
            while(recorrido != POS_NULA){
                aux = recorrido;
                recorrido = recorrido->celda_siguiente;
                // Se debe liberar el espacio de memoria correspondiente y setear a NULL lo los campos de celda.
                aux->celda_anterior = NULL;
                aux->celda_siguiente = NULL;
                aux->elemento = NULL;
                free(aux);
                aux = POS_NULA;
            }
            *lista = POS_NULA;  // La lista ahora debe ser un puntero a POS_NULA, ya que no tiene elementos.
            resultado = TRUE;   // Se ha terminado con éxito.
        }
    }
    else { exit(LST_NO_INI); }
    return resultado;
}
