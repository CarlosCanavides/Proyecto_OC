#include<stdlib.h>
#include<math.h>
#include "colacp.h"
#include "constantes.h"

#define LOG_2(a) (log10(a)/log10(2))


/**
* \brief Intercambia las entradas de dos
* nodos del arbol
*/
static void intercambiar_entradas(TNodo nodo_uno, TNodo nodo_dos){
    TEntrada temp = nodo_uno->entrada;
    nodo_uno->entrada = nodo_dos->entrada;
    nodo_dos->entrada = temp;
}

/**
* \brief Realiza un burbujeo hacia arriba de un
* nodo en particular.
*
* Los nodos en si no son desplazados,
* solo se intercambian las entradas de los nodos.
* Para esto se utiliza un comparador
* que determinara si las entradas deben ser intercambiadas o no
*/
static void burbujeo_hacia_arriba(TNodo nodo, int(*comparador)(TEntrada a, TEntrada b)){
    if(nodo->padre != POS_NULA){
        TEntrada entradaHijo = nodo->entrada;
        TEntrada entradaPadre = nodo->padre->entrada;
        int resultadoComparacion = comparador(entradaHijo, entradaPadre);
        if(resultadoComparacion > 0){
            intercambiar_entradas(nodo, nodo->padre);
            burbujeo_hacia_arriba(nodo->padre, comparador);
        }
    }
}

/**
* \brief Realiza un burbujeo hacia abajo de un
* nodo en particular.
*
* Los nodos en si no son desplazados,
* solo se intercambian las entradas de los nodos.
* Para esto se utiliza un comparador
* que determinara si las entradas deben ser intercambiadas o no
*/
static void burbujeo_hacia_abajo(TNodo nodo, int(*comparador)(TEntrada a, TEntrada b)){
    TNodo hijo_izquierdo = nodo->hijo_izquierdo;
    TNodo hijo_derecho = nodo->hijo_derecho;
    int comparacionConHijo;
    if(hijo_izquierdo != POS_NULA && hijo_derecho != POS_NULA){
        TNodo nodo_menor = comparador(hijo_izquierdo->entrada, hijo_derecho->entrada) >= 0 ? hijo_izquierdo : hijo_derecho;
        comparacionConHijo = comparador(nodo->entrada, nodo_menor->entrada);
        if(comparacionConHijo < 0){
            intercambiar_entradas(nodo, nodo_menor);
            burbujeo_hacia_abajo(nodo_menor, comparador);
        }
    }
    else if(hijo_izquierdo != POS_NULA){
        comparacionConHijo = comparador(nodo->entrada, hijo_izquierdo->entrada);
        if(comparacionConHijo < 0){
            intercambiar_entradas(nodo, hijo_izquierdo);
            burbujeo_hacia_abajo(hijo_izquierdo, comparador);
        }
    }
    else if(hijo_derecho != POS_NULA){
        comparacionConHijo = comparador(nodo->entrada, hijo_derecho->entrada);
        if(comparacionConHijo < 0){
            intercambiar_entradas(nodo, hijo_derecho);
            burbujeo_hacia_abajo(hijo_derecho, comparador);
        }
    }
}

/**
* \brief Retorna la referencia al TNodo ubicado en la posicion
* indicada. Esta referencia apunta al TNodo almacenado en el padre.
* Ademas modifica el puntero padre recibido por parametro de manera
* que apunte al padre del TNodo deseado
*
* La busqueda del TNodo deseado se realiza de manera recursiva, calculando
* la direccion en la que se debe bajar en el arbol.
*
* A cada nodo del arbol se le asigna un entero representando su posicion,
* el cual crece de arriba hacia abajo y de izquierda a derecha.
* Los enteros piso y techo indican la menor y mayor posicion del
* nivel en el cual se encuentra la posicion deseada, a las cuales puedo
* llegar desde el nodo referencia sobre el cual estoy ubicado.
*/
static TNodo* buscar_posicion_aux(TNodo ref, int posicion_deseada, int piso, int techo, TNodo* padre){
    float mitad = (float)(piso+techo) / 2;
    if(posicion_deseada < mitad){
        if(floor(mitad) == piso){
            *padre = ref;
            return &(ref->hijo_izquierdo);
        }
        else if(ref->hijo_izquierdo != POS_NULA){
            return buscar_posicion_aux(ref->hijo_izquierdo, posicion_deseada, piso, floor(mitad), padre);
        }
        else{
            return POS_NULA;
        }
    }
    else{
        if(ceil(mitad) == techo){
            *padre = ref;
            return &(ref->hijo_derecho);
        }
        else if(ref->hijo_derecho != POS_NULA){
            return buscar_posicion_aux(ref->hijo_derecho, posicion_deseada, ceil(mitad), techo, padre);
        }
        else{
            return POS_NULA;
        }
    }
}


/**
* \brief Retorna la referencia al TNodo ubicado en la posicion
* indicada. Esta referencia apunta al TNodo almacenado en el padre.
* Ademas modifica el puntero padre recibido por parametro de manera
* que apunte al padre del TNodo deseado
*
* Se utilizan funciones matematicas para encontrar el nodo deseado.
* Esta funcion delega la busqueda a ::buscar_posicion_aux la cual de manera
* recursiva busca el nodo en la posicion deseada.
*/
static TNodo* buscar_posicion(TColaCP cola, int posicion_deseada, TNodo* padre){
    if(posicion_deseada == 1){
        *padre = POS_NULA;
        return &(cola->raiz);
    }
    int nivel_de_heap = floor(LOG_2(posicion_deseada));
    int cant_min_nodos_en_nivel = pow(2, nivel_de_heap);
    int cant_max_nodos_en_nivel = pow(2, nivel_de_heap+1) - 1;
    return buscar_posicion_aux(cola->raiz, posicion_deseada, cant_min_nodos_en_nivel, cant_max_nodos_en_nivel, padre);
}

/**
* \brief Crea un nuevo nodo en la proxima
* posicion vacia del arbol, de manera tal que
* se cumpla la propiedad de arbol binario completo.
* Retorna el nuevo nodo
*
* Para hallar la proxima posicion vacia utiliza la cantidad
* de nodos del arbol y el metodo ::buscar_posicion
*/
static TNodo crear_proximo_nodo_vacio(TColaCP cola){
    TNodo padre_nuevo_nodo;
    TNodo nuevo_nodo = (TNodo) malloc(sizeof(struct nodo));
    if(cola->raiz == POS_NULA){
        padre_nuevo_nodo = POS_NULA;
        cola->raiz = nuevo_nodo;
    }
    else{
        int posicion_deseada = cola->cantidad_elementos + 1;
        // La funcion retorna tambien el padre del nodo libre, alterando el pasado por parametro
        TNodo* nodo_libre = buscar_posicion(cola, posicion_deseada, &padre_nuevo_nodo);
        *nodo_libre = nuevo_nodo;
    }
    nuevo_nodo->padre = padre_nuevo_nodo;
    nuevo_nodo->hijo_izquierdo = POS_NULA;
    nuevo_nodo->hijo_derecho = POS_NULA;
    cola->cantidad_elementos++;
    return nuevo_nodo;
}

static int eliminar_hoja(TNodo* pnodo, TNodo* ppadre){
    TNodo nodo = *pnodo;
    TNodo padre = *ppadre;
    if(nodo->padre != padre || nodo->hijo_izquierdo != POS_NULA || nodo->hijo_derecho != POS_NULA){
        return FALSE;
    }
    if(padre != POS_NULA){
        if(padre->hijo_izquierdo == nodo){
            padre->hijo_izquierdo = POS_NULA;
        }
        else{
            padre->hijo_derecho = POS_NULA;
        }
    }
    nodo->entrada = NULL;
    nodo->padre = POS_NULA;
    free(nodo);
    return TRUE;
}

TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)){
    TColaCP nuevaCola = (TColaCP) malloc(sizeof(struct cola_con_prioridad));
    nuevaCola->cantidad_elementos = 0;
    nuevaCola->raiz = POS_NULA;
    nuevaCola->comparador = f;
    return nuevaCola;
}

int cp_insertar(TColaCP cola, TEntrada entr){
    if(cola == NULL){
        exit(CCP_NO_INI);
    }
    TNodo nuevo_nodo = crear_proximo_nodo_vacio(cola);
    nuevo_nodo->entrada = entr;
    burbujeo_hacia_arriba(nuevo_nodo, cola->comparador);
    return TRUE;
}

TEntrada cp_eliminar(TColaCP cola){
    if(cola == NULL){
        exit(CCP_NO_INI);
    }
    if(cola->raiz == POS_NULA){
        return ELE_NULO;
    }
    TEntrada entrada_almacenada = cola->raiz->entrada;

    TNodo padre_ultimo_nodo;
    TNodo* ultimo_nodo = buscar_posicion(cola, cola->cantidad_elementos, &padre_ultimo_nodo);
    intercambiar_entradas(cola->raiz, *ultimo_nodo);
    eliminar_hoja(ultimo_nodo, &padre_ultimo_nodo);
    burbujeo_hacia_abajo(cola->raiz, cola->comparador);
    cola->cantidad_elementos--;
    if(cola->cantidad_elementos == 0){
        cola->raiz = POS_NULA;
    }
    return entrada_almacenada;
}

int cp_size(TColaCP cola){
    if(cola == NULL){
        exit(CCP_NO_INI);
    }
    return cola->cantidad_elementos;
}

int cp_destruir(TColaCP cola){
    if(cola == NULL){
        exit(CCP_NO_INI);
    }
    TNodo* padre_ultimo_nodo = NULL;
    TNodo* ultimo_nodo = NULL;
    while(cola->cantidad_elementos > 0){
        ultimo_nodo = buscar_posicion(cola, cola->cantidad_elementos, padre_ultimo_nodo);
        eliminar_hoja(ultimo_nodo, padre_ultimo_nodo);
        cola->cantidad_elementos--;
    }
    cola->raiz = POS_NULA;
    cola->comparador = NULL;
    free(cola);
    cola = NULL;
    return TRUE;
}
