#ifndef COLA_CON_PRIORIDAD
#define COLA_CON_PRIORIDAD

/**
* \brief Representacion de la clave de una entrada.
*
* Toda entrada perteneciente a una cola con prioridad posee una clave y un valor.
* El tipo TClave define un puntero void que debe apuntar al dato que se desea
* almacenar como clave.
*/
typedef void * TClave;

/**
* \brief Representacion del valor de una entrada.
*
* Toda entrada perteneciente a una cola con prioridad posee un valor.
* El tipo TValor define un puntero void que debe apuntar al dato que se
* desea almacenar como valor.
*/
typedef void * TValor;

/**
* \brief Entrada almacenada en una cola con prioridad.
*
* Una cola con prioridad utiliza entradas para almacenar datos
* y poder ordenarlos segun su prioridad.
*/
typedef struct entrada {
    TClave clave;
    TValor valor;
} * TEntrada;

/**
* \brief Nodo del arbol binario de la cola con prioridad.
*
* La cola con prioridad utiliza nodos para representar un
* arbol binario. El tipo TNodo es un puntero a un struct nodo
* donde se almacena las entradas.
*/
typedef struct nodo {
    TEntrada entrada;
    struct nodo * padre;
    struct nodo * hijo_izquierdo;
    struct nodo * hijo_derecho;
} * TNodo;

/**
* \brief Cola con prioridad.
*
* Una cola con prioridad permite almacenar datos, y retirarlos
* secuencialmente segun su prioridad.
* La prioridad de cada dato sera la clave de la entrada que recibe
* la cola al momento de almacenarla.
*
*/
typedef struct cola_con_prioridad {
    unsigned int cantidad_elementos;
    TNodo raiz;
    int (*comparador)(TEntrada a, TEntrada b);
} * TColaCP;


/**
* \brief Crea un nueva cola con prioridad.
*
* \param int(*f)(TEntrada, TEntrada) Funcion que permite
* comparar la prioridad de dos entradas.
*/
TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada));


/**
* \brief Inserta una nueva entrada en la cola dada.
*
* \param cola Cola con prioridad donde se insertara la entrada.
* \param entr Entrada que se desea insertar en la cola con prioridad.
*/
int cp_insertar(TColaCP cola, TEntrada entr);

/**
* \brief Elimina y retorna la entrada de mayor prioridad
* de la cola con prioridad.
*
* \param cola Cola con prioridad de la cual se obtiene la entrada.
*/
TEntrada cp_eliminar(TColaCP cola);

/**
* \brief Retorna un entero representando la cantidad de entradas
* de la cola con prioridad recibida.
*
* \param cola Cola con prioridad de la cual se obtiene la cantidad de entradas.
*/
int cp_size(TColaCP cola);

/**
* \brief Destruye la cola con prioridad, eliminando todas sus entradas.
*
* \param cola Cola con prioridad que se desea destruir.
*/
int cp_destruir(TColaCP cola);

#endif

