#include <stdio.h>

typedef void * TElemento;

struct celda {
    TElemento elemento;
    struct celda * celda_anterior;
    struct celda * celda_siguiente;
};

typedef struct celda * TPosicion;

typedef struct celda * TLista;


TLista crear_lista();
int l_insertar(TLista * lista, TPosicion pos, TElemento elem);
int l_eliminar(TLista * lista, TPosicion pos);
TPosicion l_primera(TLista lista);
TPosicion l_ultima (TLista lista);
TPosicion l_anterior (TLista lista, TPosicion posicion);
TPosicion l_siguiente(TLista lista, TPosicion posicion);
TElemento recuperar  (TLista lista, TPosicion posicion);
int l_size(TLista lista);
int l_destruir(TLista * lista);


int main_AUX(){

    /*TLista * ln;
    struct celda * pc;

    int h = 112;
    int * p1 = &h;

    pc = ln;
    pc->elemento = p1;
    int * puntero = pc->elemento;
    printf("resultado1 : %d \n",*puntero);
    printf("dir pc %d \n",*pc);

    int * resultado = (*ln)->elemento;
    printf("resultado2 : %d \n",resultado);
    printf("dir ln %d \n",*ln);


    TLista nueva = crear_lista();
    int numero = 9;
    int * elemento = &numero;
    int ejecutar = l_insertar(&nueva,NULL,elemento);
    printf("Se ejecuto? : %i \n",ejecutar);
    printf("Número del elemento : %i \n",numero);*/


    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    TElemento pa = &a;
    TElemento pb = &b;
    TElemento pc = &c;
    TElemento pd = &d;

    TLista listC = crear_lista();

    TPosicion posA = l_primera(listC);
    TPosicion posB = l_ultima(listC);
    TPosicion posC = l_siguiente(listC,posB);
    TPosicion posD = l_anterior(listC,posA);

    int resultadoA = l_insertar(&listC,posA,pa);
    int resultadoB = l_insertar(&listC,posB,pb);
    int resultadoC = l_insertar(&listC,posC,pc);
    int resultadoD = l_insertar(&listC,posD,pd);

    printf("Exito 1ra insercción : %i \n",resultadoA);
    printf("Exito 2da insercción : %i \n",resultadoB);
    printf("Exito 3ra insercción : %i \n",resultadoC);
    printf("Exito 4ta insercción : %i \n",resultadoD);

    TElemento recA = recuperar(listC,posA);
    TElemento recB = recuperar(listC,posB);
    TElemento recC = recuperar(listC,posC);
    TElemento recD = recuperar(listC,posD);

    int * auxA = recA;
    int * auxB = recB;
    int * auxC = recC;
    int * auxD = recD;

    printf("1ra insercción : %i \n",*auxA);
    printf("2da insercción : %i \n",*auxB);
    printf("3ra insercción : %i \n",*auxC);
    printf("4ta insercción : %i \n",*auxD);

    int size = l_size(listC);
    printf("Size = %i \n",size);

    l_eliminar(&listC,posA);
    l_eliminar(&listC,posB);

    printf("Eliminar un elemento, Size = %i \n",l_size(listC));

    int ejecucion = l_destruir(&listC);
    printf("LISTA VACIA , Ejecución : %i, SIZE = %i \n",ejecucion,l_size(listC));

    int * p1 = recuperar(listC,posC);
    int * p2 = recuperar(listC,posD);
    printf("posC : %i \n",*p1);
    printf("posD : %i \n",*p2);

    return 0;
}

struct celda * crearCelda() {
    struct celda * nueva = (struct celda *) malloc(sizeof(struct celda));
    nueva->celda_anterior  = NULL;
    nueva->celda_siguiente = NULL;
    nueva->elemento = NULL;
    return nueva;
}

TLista crear_lista() {
    TLista newList = NULL;
    return newList;
}

int l_insertar(TLista * lista, TPosicion pos, TElemento elem) {
    int resultado = 0;
    if(pos != NULL && (*lista)!=NULL){
        struct celda * head = *lista;
        while(head!=pos && head->celda_siguiente!=NULL){
            head = head->celda_siguiente;
        }
        if(head==pos){
            resultado = 1;
            head->elemento = elem;
        }
        // ¿Qué pasa si la posicion no pertenece a la lista?
    }
    else{
        if((*lista)==NULL){
            *lista = crearCelda();
            (*lista)->elemento = elem;
            resultado = 1;
        }
        else{
            struct celda * nueva = crearCelda();
            nueva->celda_siguiente = *lista;
            nueva->elemento = elem;
            (*lista)->celda_anterior = nueva;
            *lista = nueva;
        }
        resultado = 1;
    }
    return resultado;
}

int l_eliminar(TLista * lista, TPosicion posicion){
    int resultado = 0;
    if(*lista != NULL){
        struct celda * head = *lista;
        while(head!=posicion && head->celda_siguiente!=NULL){
              head = head->celda_siguiente;
        }
        if(head==posicion){
            resultado = 1;
            if(head->celda_anterior==NULL && head->celda_siguiente==NULL){
                *lista = NULL;
            }
            else{
                if(head->celda_anterior==NULL){
                  (head->celda_siguiente)->celda_anterior = NULL;
                  *lista = head->celda_siguiente;
                }
                else{
                    if(head->celda_siguiente==NULL){
                      (head->celda_anterior)->celda_siguiente = NULL;
                    }
                    else{
                        (head->celda_anterior)->celda_siguiente = head->celda_siguiente;
                        (head->celda_siguiente)->celda_anterior = head->celda_anterior;
                    }
                }
            }
            free(head);
        }
    }
    return resultado;
}

TPosicion l_primera(TLista lista) {
    TPosicion pos = NULL;
    if(lista == NULL){
       lista = crearCelda();
    }
    else{
        struct celda * nueva = crearCelda();
        nueva->celda_siguiente = lista;
        lista->celda_anterior = nueva;
        lista = nueva;
    }
    return lista;
}

TPosicion l_ultima(TLista lista) {
    TPosicion posicion;
    if(lista == NULL){
       lista = crearCelda();
       posicion = lista;
    }
    else{
        struct celda * ultima = lista;
        while(ultima->celda_siguiente != NULL){
            ultima = ultima->celda_siguiente;
        }
        struct celda * nueva = crearCelda();
        nueva->celda_anterior = ultima;
        ultima->celda_siguiente = nueva;
        posicion = nueva;
    }
    return posicion;
}

TPosicion l_anterior(TLista lista, TPosicion posicion) {
    TPosicion pos_nueva = NULL;
    if(lista != NULL){
        struct celda * head = lista;
        while(head!=posicion && head->celda_siguiente!=NULL){
            head = head->celda_siguiente;
        }
        if(head==posicion){
            struct celda * nueva = crearCelda();
            nueva->celda_siguiente = head;
            nueva->celda_anterior = (head->celda_anterior);
            if(head->celda_anterior != NULL){
              (head->celda_anterior)->celda_siguiente = nueva;
            }
            else{
                lista = nueva;
            }
            head->celda_anterior = nueva;
            pos_nueva = nueva;
        }
    }
    return pos_nueva;
}

TPosicion l_siguiente(TLista lista, TPosicion posicion){
    TPosicion pos_nueva = NULL;
    if(lista != NULL){
        struct celda * head = lista;
        while(head!=posicion && head->celda_siguiente!=NULL){
            head = head->celda_siguiente;
        }
        if(head==posicion){
            struct celda * nueva = crearCelda();
            nueva->celda_anterior = head;
            nueva->celda_siguiente = (head->celda_siguiente);
            if(head->celda_siguiente != NULL){
              (head->celda_siguiente)->celda_anterior = nueva;
            }
            head->celda_siguiente = nueva;
            pos_nueva = nueva;
        }
    }
    return pos_nueva;
}

TElemento recuperar(TLista lista, TPosicion posicion){
    TElemento elemento_recuperado = NULL;
    if(lista != NULL){
        struct celda * head = lista;
        while(head!=posicion && head->celda_siguiente!=NULL){
            head = head->celda_siguiente;
        }
        if(head==posicion){
            elemento_recuperado = head->elemento;
        }
    }
    return elemento_recuperado;
}

int l_size(TLista lista) {
    int cantidad = 0;
    if(lista != NULL){
        struct celda * recorrido = lista;
        while(recorrido->celda_siguiente != NULL){
            recorrido = recorrido->celda_siguiente;
            cantidad++;
        }
        cantidad++;
    }
    return cantidad;
}

int l_destruir(TLista * lista) {
    int resultado = 0;
    if(*lista != NULL){
        struct celda * head = *lista;
        struct celda * aux;
        while(head != NULL){
            aux = head;
            head = head->celda_siguiente;
            free(aux);
        }
        free(head);
        free(*lista);
        *lista = NULL;
        resultado = 1;
    }
    return resultado;
}
