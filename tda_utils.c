#include <stdlib.h>
#include "tda_utils.h"
#include "constantes.h"
#include "planificador.h"
#include "panel.h"

void ordenar_lista(TLista lista, int(*comparador)(TEntrada, TEntrada), void*(*pesador)(TElemento, void* optarg), void*optarg){
    if(lista == POS_NULA){
        return;
    }
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

    // Una vez armada la ccp correspondiente se procede a mostrar por pantalla las ciudades con sus respectivos ordenes.
    // Además se libera el espacio de memoria reservado para cada entrada y su respectiva clave.
    int orden;
    int size = cp_size(cola);
    for(orden = 0; orden<size; orden++) {
        entr_temp = cp_eliminar(cola);
        elem_temp = entr_temp->valor;
        free(entr_temp->clave);
        free(entr_temp);
        imprimir_ciudad(elem_temp,orden+1); // Muestra las ciudades por pantalla.
    }
    cp_destruir(cola);
}

TLista duplicar_lista(TLista lista){
    // Se realiza una copia superficial de la lista pasada como parámetro.
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
            TCiudad temporal = l_recuperar(*lista,pos); // Se recupera la ciudad para poder liberar su espacio de memoria.
            pos = l_siguiente(*lista, pos); // Se actualiza la pos para luego poder seguir con el recorrido.
            free(temporal->nombre);        // Se libera el espacio de memoria reservado para su nombre.
            free(temporal);               // Se libera el espacio de memoria reservado para la ciudad.
        }
        l_destruir(lista);              // Finalmente se destruye la lista.
    }
}

void limpiar_ccp_ciudades(TColaCP * cola) {
    if(cola!=NULL) {
        int size = cp_size(*cola);
        while(size > 0){
            TEntrada entr_temp = cp_eliminar(*cola); // Obtengo la entrada mínima de la ccp.
            free(entr_temp->clave);  // Se libera el espacio de memoria reservado para la clave de la entrada.
            free(entr_temp);         // Se libera el espacio de memoria reservado para la entrada.
            size--;
        }
        cp_destruir(*cola);
    }
}

void eliminar_elemento(TLista * lista, TElemento elemento) {
    // Se procede a recorrer la lista hasta encontrar el elemento (puede no llegar a estar en la lista).
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
