#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "planificador.h"
#include "lector.h"

FILE * abrir_archivo(char * nombre_archivo) {
    FILE * archivo = fopen(nombre_archivo,"r");
    if(archivo == NULL){
        return NULL;
    }
    return archivo;
}

void cerrar_archivo(FILE * archivo){
    fclose(archivo);
}

static void leer_ciudad(char linea[], int size, char* nombre, float* pos_x, float* pos_y){
    char* nombre_obtenido = strtok(linea, ";");
    float pos_x_obtenido = strtof(strtok(NULL, ";"), NULL);
    float pos_y_obtenido = strtof(strtok(NULL, ";"), NULL);

    strcpy(nombre, nombre_obtenido);
    *pos_x = pos_x_obtenido;
    *pos_y = pos_y_obtenido;

}

TLista obtener_ciudades(FILE * archivo){
    rewind(archivo);
    TLista lista_ciudades = crear_lista();
    char linea[100];
    char* nombre_ciudad;
    float pos_x;
    float pos_y;
    fscanf(archivo,"%*[^\n]\n");  // Salteo la linea del viajante
    while(!feof(archivo)){
        fgets(linea, 100, archivo);
        nombre_ciudad = (char*) malloc(sizeof(char)*20);
        leer_ciudad(linea, 100, nombre_ciudad, &pos_x, &pos_y);

        TCiudad ciudad = (TCiudad) malloc(sizeof(struct ciudad));
        ciudad->nombre = nombre_ciudad;
        ciudad->pos_x = pos_x;
        ciudad->pos_y = pos_y;
        l_insertar(&lista_ciudades, NULL, ciudad);
    }
    rewind(archivo);
    return lista_ciudades;
}

Viajante obtener_viajante(FILE * archivo){
    rewind(archivo);
    Viajante viajante = (Viajante) malloc(sizeof(struct viajante));
    char linea[10];
    fgets(linea, 10, archivo);
    float pos_x = strtof(strtok(linea, ";"), NULL);
    float pos_y = strtof(strtok(NULL, ";"), NULL);
    viajante->pos_x = pos_x;
    viajante->pos_y = pos_y;
    rewind(archivo);
    return viajante;
}
