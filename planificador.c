#include <stdio.h>
#include <stdlib.h>
#include "planificador.h"
#include "lista.h"
#include "panel.h"
#include "comparadores.h"


int main_principal() {

    // Falta la parte de solicitar al usuario el archivo correspondiente

    FILE * archivo_ciudades = abrirArchivo(NULL);
    TLista ciudades = leer_archivo(archivo_ciudades);

    mostrar_menu();
    int * eleccion;
    scanf("%i",eleccion);
    Viajante e;
    while((*eleccion)!=0){
        elegir_opcion(eleccion,ciudades,e);
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
    return lista_ciudades;
}

TLista mostrar_ciudades_ascendentes(TLista ciudades, Viajante viajante) {
    // Agregar el comparador
    ordenar_lista(ciudades, ciudad_mas_cercana);
}

TLista mostrar_ciudades_descendentes(TLista ciudades, Viajante viajante) {
    // Agregar el comparador
    ordenar_lista(ciudades, ciudad_mas_lejana);
}

TLista reducir_horas_manejo(TLista ciudades, Viajante viajante) {

}
