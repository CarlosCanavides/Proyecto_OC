#ifndef COLA_CON_PRIORIDAD
#define COLA_CON_PRIORIDAD

typedef void * TClave;
typedef void * TValor;
typedef struct entrada {
    TClave clave;
    TValor valor;
} * TEntrada;
typedef struct nodo {
    TEntrada entrada;
    struct nodo * padre;
    struct nodo * hijo_izquierdo;
    struct nodo * hijo_derecho;
} * TNodo;
typedef struct cola_con_prioridad {
    unsigned int cantidad_elementos;
    TNodo raiz;
    int (*comparador)(TEntrada a, TEntrada b);
} * TColaCP;

void test_cola_con_prioridad();

TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada));

int cp_insertar(TColaCP cola, TEntrada entr);

TEntrada cp_eliminar(TColaCP cola);

int cp_size(TColaCP);

int cp_destruir(TColaCP* cola);

#endif 

