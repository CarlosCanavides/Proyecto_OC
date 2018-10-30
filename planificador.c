#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planificador.h"
#include "constantes.h"
#include "lista.h"
#include "tda_utils.h"
#include "panel.h"
#include "lector.h"
#include "utils.h"

int main(int argc, char * arg[]){
    FILE* archivo;
    if(argc==2){
        archivo = abrir_archivo(arg[1]);
    }
    else{
        exit(0);
    }
    TLista ciudades = obtener_ciudades(archivo);  // las ciudades son cargadas a una lista.
    Viajante viajante = obtener_viajante(archivo);
    cerrar_archivo(archivo);

    while(TRUE){
        mostrar_menu();
        int input = 0;
        scanf("%i", &input);
        limpiar_buffer(); // Se limpia el buffer para detectar que no se ingresaron cosas invalidas.
        mostrar_espaciado();
        elegir_opcion(input, ciudades, viajante);  // Se interpreta la opción elegida.
        mostrar_espaciado();
    }

    return 0;
}

void mostrar_ciudades_ascendentes(TLista ciudades, Viajante viajante) {
    ordenar_lista(ciudades, ciudad_mas_cercana, pesar_por_distancia_con_viajante, viajante);
}

void mostrar_ciudades_descendentes(TLista ciudades, Viajante viajante) {
    ordenar_lista(ciudades, ciudad_mas_lejana, pesar_por_distancia_con_viajante, viajante);
}

void reducir_horas_manejo(TLista ciudades, Viajante viajante) {
    if(ciudades != NULL) {
        // Se necesitara una lista duplicada para poder ir descartando las ciudades que ya son visitadas.
        TLista lista = duplicar_lista(ciudades);
        float totalRecorrido = 0;
        int cantidad_ciudades = l_size(ciudades);
        int i;
        for(i=0; i<cantidad_ciudades; i++) {
            TColaCP cola = crear_cola_cp(ciudad_mas_cercana);
            TPosicion ini = l_primera(lista);
            while(ini != POS_NULA){
                TCiudad elem = l_recuperar(lista, ini);
                TEntrada nueva_entrada = (TEntrada) malloc(sizeof(struct entrada)); // Se reserva espacio de memoria para la nueva entrada.
                nueva_entrada->clave = pesar_por_distancia_con_viajante(elem,viajante);
                nueva_entrada->valor = elem;
                cp_insertar(cola, nueva_entrada);
                ini = l_siguiente(lista, ini);
            }
            // Una vez que ya la ccp está armada, debemos extraer la minima entrada.
            // Dado que ordenadamos la ccp con las ciudades más cercanas, obtendremos la más cercana al viajero.
            TEntrada primera_entrada = cp_eliminar(cola);
            TCiudad ciudad = primera_entrada->valor;
            float * clave = primera_entrada->clave;
            totalRecorrido += (*clave); // Se actualiza el totalRecorrido.
            free(primera_entrada->clave); // Debemos liberar el espacio de memoria de la entrada que ya no utilizamos.
            free(primera_entrada);
            // Se debe actualizar la posición del viajante.
            viajante->pos_x = ciudad->pos_x;
            viajante->pos_y = ciudad->pos_y;
            // Se procede a eliminar de la lista duplicada la ciudad que obtuvimos anteriormente.
            // Se elimina esta ciudad para que en la próxima iteración no se la tenga en cuenta, ya que el viajero
            // está ubicado en dicha ciudad.
            eliminar_elemento(&lista,ciudad);
            limpiar_ccp_ciudades(&cola);  // Se limpia la ccp creada en esta iteración (las entradas y sus claves).
            imprimir_ciudad(ciudad,i+1);  // Se muestra por consola la ciudad obtenida.
        }
        printf(" Total Recorrido : %.2f \n",totalRecorrido);
        l_destruir(&lista);
    }
}
