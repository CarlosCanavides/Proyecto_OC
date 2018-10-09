#include<stdlib.h>
#include<math.h>
#include "colacp.h"
#include "constantes.h"

#define LOG_2(a) (log10(a)/log10(2))


// Metodos de arbol binario completo
static void intercambiar_entradas(TNodo nodo_uno, TNodo nodo_dos){
    TEntrada temp = nodo_uno->entrada;
    nodo_uno->entrada = nodo_dos->entrada;
    nodo_dos->entrada = temp;
}

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
    //free(nodo);
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
    return 1;
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

int cp_destruir(TColaCP* cola){
    if(cola == NULL || *cola == NULL){
        exit(CCP_NO_INI);
    }
    TNodo* padre_ultimo_nodo;
    TNodo* ultimo_nodo;
    while((*cola)->cantidad_elementos > 0){
        ultimo_nodo = buscar_posicion(*cola, (*cola)->cantidad_elementos, padre_ultimo_nodo);
        eliminar_hoja(ultimo_nodo, padre_ultimo_nodo);
        (*cola)->cantidad_elementos--;
    }
    (*cola)->raiz = POS_NULA;
    (*cola)->comparador = NULL;
    free(*cola);
    cola = NULL;
    return 1;
}

int comparador_prueba_int(TEntrada a, TEntrada b){
    int clave_a =  *((int*)(a->clave));
    int clave_b =  *((int*)(b->clave));
    if(clave_a > clave_b){
        return 1;
    }
    else if(clave_a == clave_b){
        return 0;
    }
    else{
        return -1;
    }
}

void test_cola_con_prioridad(){
    // Creo varias entradas
    TEntrada e1 = (TEntrada) malloc(sizeof(struct entrada));
    TEntrada e2 = (TEntrada) malloc(sizeof(struct entrada));
    TEntrada e3 = (TEntrada) malloc(sizeof(struct entrada));
    TEntrada e4 = (TEntrada) malloc(sizeof(struct entrada));
    TEntrada e5 = (TEntrada) malloc(sizeof(struct entrada));
    TEntrada e6 = (TEntrada) malloc(sizeof(struct entrada));
    TEntrada e7 = (TEntrada) malloc(sizeof(struct entrada));
    {
        int c1 = 2;
        int v1 = 86;
        e1->clave = &c1;
        e1->valor = &v1;
        int c2 = 6;
        int v2 = 43;
        e2->clave = &c2;
        e2->valor = &v2;
        int c3 = 9;
        int v3 = 65;
        e3->clave = &c3;
        e3->valor = &v3;
        int c4 = 5;
        int v4 = 45;
        e4->clave = &c4;
        e4->valor = &v4;
        int c5 = 1;
        int v5 = 76;
        e5->clave = &c5;
        e5->valor = &v5;
        int c6 = 10;
        int v6 = 98;
        e6->clave = &c6;
        e6->valor = &v6;
        int c7 = 3;
        int v7 = 22;
        e7->clave = &c7;
        e7->valor = &v7;
    }

    // Probamos insertar, anda bien
    TColaCP cola = crear_cola_cp(*comparador_prueba_int);
    int size = cp_size(cola);
    cp_insertar(cola, e1);
    size = cp_size(cola);
    cp_insertar(cola, e3);
    cp_insertar(cola, e4);
    cp_insertar(cola, e2);
    cp_insertar(cola, e5);
    cp_insertar(cola, e6);

    // Probamos eliminar todo(Unico problema es free)
    TNodo test = cola->raiz->hijo_izquierdo;

    size = cp_size(cola);
    int clave;
    clave = *((int*)cp_eliminar(cola)->clave);
    clave = *((int*)cp_eliminar(cola)->clave);
    clave = *((int*)cp_eliminar(cola)->clave);
    clave = *((int*)cp_eliminar(cola)->clave);
    clave = *((int*)cp_eliminar(cola)->clave);
    cp_insertar(cola, e1);
    clave = *((int*)cp_eliminar(cola)->clave);
    clave = *((int*)cp_eliminar(cola)->clave);

    // Probamos insertar y luego destruir
    cp_insertar(cola, e1);
    cp_insertar(cola, e2);
    cp_insertar(cola, e3);
    cp_insertar(cola, e4);
    cp_insertar(cola, e5);
    cp_insertar(cola, e6);
    cp_insertar(cola, e7);
    cp_destruir(&cola);
}
