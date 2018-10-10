#include <stdlib.h>
#include "tda_utils.h"
#include "constantes.h"
#include "planificador.h"

TLista ordenar_lista(TLista lista, int(*comparador)(TEntrada, TEntrada), void*(*pesador)(TElemento, void* optarg), void*optarg){
    if(lista == POS_NULA){
        return POS_NULA;
    }
    TLista nuevaLista = crear_lista();
    TColaCP cola = crear_cola_cp(comparador);
    TPosicion ini = l_primera(lista);
    TEntrada entr_temp;
    TElemento elem_temp;
    while(ini != POS_NULA){
        entr_temp = (TEntrada) malloc(sizeof(struct entrada));
        elem_temp = l_recuperar(lista, ini);
        entr_temp->clave = pesador(elem_temp, optarg);
        entr_temp->valor = elem_temp;
        cp_insertar(cola, entr_temp);
        ini = l_siguiente(lista, ini);
    }

    while(cp_size(cola) > 0){
        entr_temp = cp_eliminar(cola);
        elem_temp = entr_temp->valor;
        free(entr_temp->clave);
        free(entr_temp);
        l_insertar(&nuevaLista, POS_NULA, elem_temp);
    }

    invertir_lista(&nuevaLista);
    cp_destruir(&cola);
    return nuevaLista;
}

TLista duplicar_lista(TLista lista){
    if(lista == POS_NULA){
        return POS_NULA;
    }
    TLista nuevaLista = crear_lista();
    TPosicion ultima = l_ultima(lista);
    while(ultima != POS_NULA){
        l_insertar(&nuevaLista, POS_NULA, l_recuperar(lista, ultima));
        ultima = l_anterior(lista, ultima);
    }
    return nuevaLista;
}

void limpiar_lista_ciudades(TLista * lista){
    if(lista != NULL){
        TPosicion pos = l_primera(*lista);
        while(pos != POS_NULA){
            TCiudad temporal = l_recuperar(*lista,pos);
            free(temporal->nombre);
            free(temporal);
            pos = l_siguiente(*lista, pos);
        }
        l_destruir(lista);
    }
}

void limpiar_ccp_ciudades(TColaCP * cola) {
    if(cola!=NULL) {
        int size = cp_size(*cola);
        while(size > 0){
            TEntrada entr_temp = cp_eliminar(*cola);
            free(entr_temp->clave);
            free(entr_temp);
            size--;
        }
        cp_destruir(cola);
    }
}

void invertir_lista(TLista* plista){
    if(plista != NULL && l_size(*plista)>1){
        TLista lista = *plista;
        TPosicion ini = l_primera(lista);
        TPosicion fin = l_ultima(lista);
        while(ini != fin && l_anterior(lista, ini) != fin){
            TElemento temp = l_recuperar(lista, ini);
            l_insertar(&lista, ini, l_recuperar(lista, fin));
            l_insertar(&lista, fin, temp);
            ini = l_siguiente(lista, ini);
            fin = l_anterior(lista, fin);
        }
    }
}

void eliminar_elemento(TLista * lista, TElemento elemento) {
    if(lista!=NULL && elemento!=ELE_NULO){
        TPosicion ini = l_primera(*lista);
        while((ini->elemento!=elemento) && (ini->celda_siguiente!=POS_NULA)){
            ini = ini->celda_siguiente;
        }
        if(ini->elemento==elemento){
            l_eliminar(lista,ini);
        }
    }
}
