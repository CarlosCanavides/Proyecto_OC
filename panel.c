#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "panel.h"

char* pedir_archivo_inicial(){
    dibujar_panel_inicio();
    char* nombre_archivo = (char*) malloc(sizeof(char)*50);
    scanw("%s", nombre_archivo);
    noecho();
    cbreak();
    return nombre_archivo;
}

void elegir_opcion(int opcion, TLista ciudades, Viajante viajante){
    switch(opcion){
        case 0:{
            TLista ciudades_ascendente = mostrar_ciudades_ascendentes(ciudades, viajante);
            dibujar_panel_ciudades(ciudades_ascendente);
            break;
        }
        case 1:{
            TLista ciudades_descendente = mostrar_ciudades_descendentes(ciudades, viajante);
            dibujar_panel_ciudades(ciudades_descendente);
            break;
        }
        case 2:{
            TLista reducir_horas = reducir_horas_manejo(ciudades, viajante);
            dibujar_panel_ciudades(ciudades);
            break;
        }
    }
    char input;
    do{
        input = getch();
    }while(input != 10);
    mostrar_panel_opciones(ciudades, viajante);
}

void mostrar_panel_opciones(TLista ciudades, Viajante viajante){
    int opcion_actual = 0;
    dibujar_panel_opciones(opcion_actual);
    curs_set(0);
    char input;
    do{
        input = getch();
        if(input == 'w'){
            if(opcion_actual > 0) opcion_actual--;
        }
        else if(input == 's'){
            if(opcion_actual < 3) opcion_actual++;
        }
        dibujar_panel_opciones(opcion_actual);
    }while(input != 10 && input != 13); // Enter key
    elegir_opcion(opcion_actual, ciudades, viajante);
}
