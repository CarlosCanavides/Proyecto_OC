#include <stdio.h>
#include <stdlib.h>
#include "planificador.h"
#include "constantes.h"
#include "lista.h"
#include "lista_utils.h"
#include "panel.h"
#include "lector.h"
#include "comparadores.h"
#include "pesadores.h"


int main_principal() {

    // Falta la parte de solicitar al usuario el archivo correspondiente

    FILE * archivo_ciudades = abrir_archivo("./Data/viajes");
    TLista ciudades = obtener_ciudades(archivo_ciudades);
    Viajante viajante = obtener_viajante(archivo_ciudades);
    cerrar_archivo(archivo_ciudades);

    mostrar_menu();
    int inicializacion_por_defecto = 4;
    int * eleccion = &inicializacion_por_defecto;
    scanf("%i",eleccion);
    while((*eleccion)!=0){
        elegir_opcion(*eleccion,ciudades,viajante);
    }

    return 0;
}

TLista mostrar_ciudades_ascendentes(TLista ciudades, Viajante viajante) {
    return ordenar_lista(ciudades, ciudad_mas_cercana);
}

TLista mostrar_ciudades_descendentes(TLista ciudades, Viajante viajante) {
    return ordenar_lista(ciudades, ciudad_mas_lejana);
}

TLista reducir_horas_manejo(TLista ciudades, Viajante viajante) {
    if(ciudades == NULL){
        return NULL;
    }
    int cantidad_ciudades = l_size(ciudades);
    TLista lista = duplicar_lista(ciudades);
    TLista ciudades_ordenadas = crear_lista();
    int i;
    for(i=0; i<cantidad_ciudades; i++) {
        TColaCP cola = crear_cola_cp(ciudad_mas_cercana);
        TPosicion ini = l_primera(lista);
        while(ini != POS_NULA){
            TCiudad elem = l_recuperar(lista, ini);
            TEntrada nueva_entrada = (TEntrada) malloc(sizeof(TEntrada));
            nueva_entrada->clave = pesar_por_distancia_con_viajante(elem,viajante);
            nueva_entrada->valor = elem;
            cp_insertar(cola, nueva_entrada);
            ini = l_siguiente(lista, ini);
        }
        TCiudad ciudad = (cp_eliminar(cola))->valor;
        viajante->pos_x = ciudad->pos_x;
        viajante->pos_y = ciudad->pos_y;
        l_eliminar(&lista,ciudad);
        l_insertar(&ciudades_ordenadas, POS_NULA, ciudad);
        cp_destruir(&cola);
    }
    invertir_lista(&ciudades_ordenadas);
    return ciudades_ordenadas;
}
