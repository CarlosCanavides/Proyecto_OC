#define VIAJERO_NULO 1

#include "planificador.h"
#include <math.h>


static float obtener_distancia(float pos_x1, float pos_y1, float pos_x2, float pos_y2){
    float dist_x = pow(pos_x1 - pos_x2, 2);
    float dist_y = pow(pos_y1 - pos_y2, 2);
    return sqrt(dist_x + dist_y);
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
