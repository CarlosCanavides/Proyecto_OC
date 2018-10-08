#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "panel.h"
#include "comparadores.h"

typedef struct ciudad {
    char * nombre;
    float pos_x;
    float pos_y;
} * TCiudad;

typedef struct viajante {
    float pos_x;
    float pos_y;
} Viajante;


int main_principal() {

    // Falta la parte de solicitar al usuario el archivo correspondiente

    FILE * archivo_ciudades = abrirArchivo();
    TLista ciudades = leer_archivo(archivo_ciudades);

    mostrar_menu();
    int * eleccion;
    scanf("%i",eleccion);
    while((*eleccion)!=0){
        elegir_opcion(eleccion,ciudades,viajante);
    }

    return 0;
}


FILE * abrirArchivo(char * nombre_archivo) {
    FILE * archivo = fopen(nombre_archivo,"r");
    if(archivo == NULL){
        exit(0);
    }
    return archivo;
}

TLista leer_archivo(FILE * archivo){
    float * posX_viajante;
    float * posY_viajante;
    char  * separador;
    TLista lista_ciudades = crear_lista();
    fscanf(archivo,"%f %c %f",posX_viajante,separador,posY_viajante);
    while(!feof(archivo)){
        char nombre_ciudad[20];
        char * temp;
        fscanf(archivo,"%c",temp);
        int i = 0;
        for(i=0; (i<20)&&((*temp)!=';') ; i++){
            nombre_ciudad[i] = (*temp);
            fscanf(archivo,"%c",temp);
        }
        float * posX_ciudad;
        float * posY_ciudad;
        fscanf(archivo,"%f %c %f",posX_ciudad,separador,posY_ciudad);
        TCiudad ciudad = (TCiudad) malloc(sizeof(struct ciudad));
        ciudad->nombre = nombre_ciudad;
        ciudad->pos_x  = (*posX_ciudad);
        ciudad->pos_y  = (*posY_ciudad);
        l_insertar(&lista_ciudades,NULL,ciudad);
    }
    return TLista;
}

void mostrar_ciudades_ascendentes(TLista ciudades, Viajante viajante) {
    // Agregar el comparador
    ordenar_lista(ciudades,);
}

void mostrar_ciudades_descendentes(TLista ciudades, Viajante viajante) {
    // Agregar el comparador
    ordenar_lista(ciudades,);
}

void reducir_hojas_manejo(TLista ciudades, Viajante viajante) {

}
