#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "lista.h"
#include "colacp.h"
#include "lista_utils.h"
#include "comparadores.h"
#include "constantes.h"
#include "lector.h"
#include "pesadores.h"


void imprimir_valor_ciudades(TLista lista){
    TPosicion ini = l_primera(lista);
    while(ini != NULL){
        TCiudad ciudad = (TCiudad) l_recuperar(lista, ini);
        printf("%s : <%i ; %i> \n", ciudad->nombre, (int)(ciudad->pos_x), (int)(ciudad->pos_y));
        ini = l_siguiente(lista, ini);
    }
}

int main(){

    FILE* archivo = abrir_archivo("./Datos/viajes");
    TLista ciudades = obtener_ciudades(archivo);
    Viajante viajante = obtener_viajante(archivo);
    cerrar_archivo(archivo);
    imprimir_valor_ciudades(ciudades);
    TLista ciudad_ordenadas = ordenar_lista(ciudades, ciudad_mas_cercana, pesar_por_distancia_con_viajante, viajante);
    printf("\n");
    imprimir_valor_ciudades(ciudad_ordenadas);

    return 0;
}
