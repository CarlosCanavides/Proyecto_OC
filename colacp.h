typedef void * TClave;
typedef void * TValor;
typedef struct entrada * TEntrada;
typedef struct nodo * TNodo;
typedef struct cola_con_prioridad * TColaCP;

TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada));

int cp_insertar(TColaCP cola, TEntrada entr);

TEntrada cp_eliminar(TColaCP cola);

int cp_size(TColaCP);

int cp_destruir(TColaCP* cola);
