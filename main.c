#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "colacp.h"
#include "lista_utils.h"
#include "comparadores.h"
#include "constantes.h"

void imprimir_valor_lista(TLista lista, int pos){
    TPosicion posicion = l_primera(lista);
    int actual_pos = 1;
    while(actual_pos != pos){
        posicion = l_siguiente(lista, posicion);
        actual_pos++;
    }
    TEntrada entr = ((TEntrada) l_recuperar(lista, posicion));
    float clave = *((float *) (entr->clave));
    printf("%f \n", clave);
}

int main(){
    //lista_test();
    //test_cola_con_prioridad();

    TEntrada e1 = (TEntrada) malloc(sizeof(struct entrada));
    float c1 = 2.05;
    e1->clave = &c1;
    TEntrada e2 = (TEntrada) malloc(sizeof(struct entrada));
    float c2 = 4;
    e2->clave = &c2;
    TEntrada e3 = (TEntrada) malloc(sizeof(struct entrada));
    float c3 = 8.51;
    e3->clave = &c3;
    TEntrada e4 = (TEntrada) malloc(sizeof(struct entrada));
    float c4 = 8.24;
    e4->clave = &c4;

    TLista lista = crear_lista();
    l_insertar(&lista, POS_NULA, e1);
    l_insertar(&lista, POS_NULA, e2);
    l_insertar(&lista, POS_NULA, e3);
    l_insertar(&lista, POS_NULA, e4);


    int i;
    for(i = 1; i <= 4; i++){
        imprimir_valor_lista(lista, i);
    }

    TLista lista_ordenada = ordenar_lista(lista, &ciudad_mas_lejana);

    printf("\n");
    for(i = 1; i <= 4; i++){
        imprimir_valor_lista(lista_ordenada, i);
    }

    TLista lista_duplicada = duplicar_lista(lista_ordenada);
    limpiar_lista(&lista_ordenada);
    limpiar_lista(&lista);

    printf("\n");
    for(i = 1; i <= 4; i++){
        imprimir_valor_lista(lista_duplicada, i);
    }

    return 0;
}
