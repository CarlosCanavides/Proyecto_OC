#include <stdio.h>
#include <stdlib.h>
#include "planificador.h"
#include "constantes.h"
#include "lista.h"
#include "lista_utils.h"
#include "panel.h"
#include "lector.h"
#include "utils.h"

int main(int argc, const char * arg[]){
    FILE* archivo = abrir_archivo("./Datos/viajes");
    /*if(argc==2){
        archivo = abrir_archivo(arg[1]);
    }
    else{
        exit(0);
    }*/
    TLista ciudades = obtener_ciudades(archivo);
    Viajante viajante = obtener_viajante(archivo);
    cerrar_archivo(archivo);

    while(1){
        mostrar_menu();
        int input;
        do{
            scanf("%i", &input);
        }while(input < 1 && input > 4);
        elegir_opcion(input, ciudades, viajante);
    }

    return 0;
}

TLista mostrar_ciudades_ascendentes(TLista ciudades, Viajante viajante) {
    return ordenar_lista(ciudades, ciudad_mas_cercana, pesar_por_distancia_con_viajante, viajante);
}

TLista mostrar_ciudades_descendentes(TLista ciudades, Viajante viajante) {
    return ordenar_lista(ciudades, ciudad_mas_lejana, pesar_por_distancia_con_viajante, viajante);
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
        l_insertar(&ciudades_ordenadas, POS_NULA, ciudad);
        eliminar_elemento(&lista,ciudad);
        cp_destruir(&cola);
    }
    l_destruir(&lista);
    invertir_lista(&ciudades_ordenadas);
    return ciudades_ordenadas;
}
