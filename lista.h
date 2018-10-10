#ifndef LISTA
#define LISTA

/**
* \brief Representacion de un elemento de la lista.
*/
typedef void * TElemento;

/**
* \brief Representacion de una celda de la lista.
*
* Toda celda perteneciente a la lista tiene un TElemento asociado.
* Se guarda una referencia a la celda_anterior y celda_siguiente.
*/
struct celda {
    TElemento elemento;
    struct celda * celda_anterior;
    struct celda * celda_siguiente;
};

/**
* \brief Representacion de una posicion de la lista.
*
* Se representa una posicion de la lista como un puntero a un struct celda.
*/
typedef struct celda * TPosicion;

/**
* \brief Representacion de una lista.
*
* Se representa una lista como un puntero a la primera celda.
*/
typedef struct celda * TLista;



/**
* \brief Crea y retorna una lista vacia.
*/
TLista crear_lista();

/**
* \brief Agrega el elemento elem a la posicion pos, dentro de la lista. Si pos es POS_NULA, inserta el elemento en la primera posicion de la lista.
*
* Retorna verdadero si procede con exito, falso en caso contrario.
* Se considera que la posición pasada como parametro sea una POS_NULA o bien pertenezca a la respectiva lista (se requiere esto para lograr un mejor desempeño del TDA_LISTA en cuanto a tiempo de ejecucion).
* \param TLista * lista, puntero a la lista donde se va a insertar el elemento.
* \param TPosicion pos posicion en la cual se va a insertar el elemento.
*/
int l_insertar(TLista * lista, TPosicion pos, TElemento elem);

/**
* \brief Elimina el elemento de la posicion pos. Reacomoda la lista adecuadamente. Retorna verdadero si procede con exito, falso en caso contrario.
*
* Se considera que la posición pasada como parametro sea una POS_NULA o bien pertenezca a la respectiva lista (se requiere esto para lograr un mejor desempeño del TDA_LISTA en cuanto a tiempo de ejecucion).
* \param TLista * lista, puntero a una lista donde se va a insertar el elemento.
* \param TPosicion pos posicion que se va a eliminar de la lista.
*/
int l_eliminar(TLista * lista, TPosicion pos);

/**
* \brief Retorna la primera posicion de la lista. Si la lista es vacia, retorna POS_NULA.
*
* \param TLista lista a la cual se le solicita su primera posicion.
*/
TPosicion l_primera(TLista lista);

/**
* \brief Retorna la ultima posicion de la lista. Si la lista es vacia, retorna POS_NULA.
*
* \param TLista lista a la cual se le solicita su ultima posicion.
*/
TPosicion l_ultima (TLista lista);

/**
* \brief Retorna la posicion anterior a pos en la lista. Si pos es la primera posicion de la lista, retorna POS_NULA.
*
* Se considera que la posición pasada como parametro sea una POS_NULA o bien pertenezca a la respectiva lista (se requiere esto para lograr un mejor desempeño del TDA_LISTA en cuanto a tiempo de ejecucion).
* \param TLista lista a la que se solicita la posicion anterior a pos.
* \param TPosicion pos posicion de referencia.
*/
TPosicion l_anterior (TLista lista, TPosicion pos);

/**
* \brief Retorna la posicion siguiente a pos en la lista. Si pos es la ultima posicion de la lista, retorna POS_NULA.
*
* Se considera que la posición pasada como parametro sea una POS_NULA o bien pertenezca a la respectiva lista (se requiere esto para lograr un mejor desempeño del TDA_LISTA en cuanto a tiempo de ejecucion).
* \param TLista lista a la que se solicita la posicion siguiente a pos.
* \param TPosicion pos posicion de referencia.
*/
TPosicion l_siguiente(TLista lista, TPosicion pos);

/**
* \brief Retorna el elemento correspondiente a la posicion pos. Si la posicion es POS_NULA, retorna ELE_NULO.
*
* Se considera que la posición pasada como parametro sea una POS_NULA o bien pertenezca a la respectiva lista (se requiere esto para lograr un mejor desempeño del TDA_LISTA en cuanto a tiempo de ejecucion).
* \param TLista lista de la cual se va a recuperar el elemento de la posicion pasada como parametro.
* \param TPosicion pos posicion de referencia.
*/
TElemento l_recuperar(TLista lista, TPosicion pos);

/**
* \brief Retorna la cantidad de elementos de la lista.
*
* \param TLista lista a la cual se le solicita la cantidad de elementos.
*/
int l_size(TLista lista);

/**
* \brief Elimina todos los elementos y libera toda la memoria utilizada por la lista. Retorna verdadero si procede con exito, falso en caso contrario
*
* Observación : no es responsabilidad del TDA_LISTA liberar el espacio de memoria correspondiente a los elementos almacenados en la lista (queda a cargo del cliente).
* \param TLista lista que sera destruida.
*/
int l_destruir(TLista * lista);


#endif
