#include <stdio.h>
#include <stdlib.h>
#include "planificador.h"
#include "lista.h"
#include "panel.h"
#include "lector.h"
#include "comparadores.h"


int main_principal() {

    // Falta la parte de solicitar al usuario el archivo correspondiente

    FILE * archivo_ciudades = abrir_archivo(NULL);
    TLista ciudades = obtener_ciudades(archivo_ciudades);

    mostrar_menu();
    int * eleccion;
    scanf("%i",eleccion);
    Viajante e;
    while((*eleccion)!=0){
        elegir_opcion(*eleccion,ciudades,e);
    }

    return 0;
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
