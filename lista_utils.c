#include <stdlib.h>
#include "lista_utils.h"
#include "constantes.h"

TLista ordenar_lista(TLista lista, int(*comparador)(TEntrada, TEntrada), void*(*pesador)(TElemento, void* optarg), void*optarg){
    if(lista == NULL){
        return NULL;
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
    if(lista == NULL){
        return NULL;
    }
    TLista nuevaLista = crear_lista();
    TPosicion ultima = l_ultima(lista);
    while(ultima != POS_NULA){
        l_insertar(&nuevaLista, POS_NULA, l_recuperar(lista, ultima));
        ultima = l_anterior(lista, ultima);
    }
    return nuevaLista;
}

void limpiar_lista(TLista* lista){
    if(lista != NULL && l_size(*lista) > 0){
        while(l_size(*lista) > 0){
            TPosicion ultima = l_ultima(*lista);
            l_eliminar(lista, ultima);
        }
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
