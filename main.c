#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <ncurses.h>
#include "lista.h"
#include "colacp.h"
#include "lista_utils.h"
#include "comparadores.h"
#include "constantes.h"
#include "lector.h"
#include "pesadores.h"
#include "panel.h"
#include "panel_ui.h"


int main(){

    initscr();
    cbreak();
    noecho();
    refresh();

    //FILE* archivo = abrir_archivo("./Datos/viajes");
    char* nombre_archivo = pedir_archivo_inicial();
    FILE* archivo = abrir_archivo(nombre_archivo);
    TLista ciudades;
    Viajante viajante;
    if(!archivo == NULL){
        ciudades = obtener_ciudades(archivo);
        viajante = obtener_viajante(archivo);
        cerrar_archivo(archivo);
    }
    mostrar_panel_opciones(ciudades, viajante);
    return 0;
}
