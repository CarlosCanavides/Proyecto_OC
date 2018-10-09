#define VIAJERO_NULO 1

#include <math.h>
#include "planificador.h"
#include "utils.h"

static float obtener_distancia(float pos_x1, float pos_y1, float pos_x2, float pos_y2){
    float dist_x = fabs(pos_x1 - pos_x2);
    float dist_y = fabs(pos_y1 - pos_y2);
    return (dist_x + dist_y);
}

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


void* pesar_por_distancia_con_viajante(TElemento elemento, void* viajante){
    if(viajante == NULL){
        exit(VIAJERO_NULO);
    }
    TCiudad ciudad = (TCiudad) elemento;
    Viajante viaj = (Viajante) viajante;
    float* distancia = (float*) malloc(sizeof(float));
    *distancia = obtener_distancia(viaj->pos_x, viaj->pos_y, ciudad->pos_x, ciudad->pos_y);
    return distancia;
}
