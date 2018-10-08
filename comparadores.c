#include "comparadores.h"

int ciudad_mas_cercana(TEntrada ciudad_a, TEntrada ciudad_b){
    float distancia_a = *((float*)(ciudad_a->clave));
    float distancia_b = *((float*)(ciudad_b->clave));
    if(distancia_a < distancia_b){
        return 1;
    }
    else if(distancia_a == distancia_b){
        return 0;
    }
    else{
        return -1;
    }
}

int ciudad_mas_lejana(TEntrada ciudad_a, TEntrada ciudad_b){
    float distancia_a = *((float*) ciudad_a->clave);
    float distancia_b = *((float*) ciudad_b->clave);
    if(distancia_a > distancia_b){
        return 1;
    }
    else if(distancia_a == distancia_b){
        return 0;
    }
    else{
        return -1;
    }
}
