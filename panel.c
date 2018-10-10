#include <stdio.h>
#include <string.h>
#include "panel.h"
#include "lista_utils.h"

void mostrar_menu() {
    printf(" PLANIFICADOR DE VIAJES \n ");
    printf(" Seleccione la opción deseada introduciendo el número asociado \n");
    printf(" 1 _ Mostrar ascendente \n");
    printf(" 2 _ Mostrar descendente \n");
    printf(" 3 _ Reducir horas de manejo \n");
    printf(" 4 _ Salir \n");
    printf(" Elección : ");
}

void mostrar_ciudades(TLista ciudades) {
    if(ciudades!=NULL){
        TPosicion posicion_actual = l_primera(ciudades);
        int cantidad_ciudades = l_size(ciudades);
        TCiudad ciudad;
        int orden = 0;
        printf("\n \n");
        for(orden = 0; orden < cantidad_ciudades; orden++){
            ciudad = l_recuperar(ciudades, posicion_actual);
            char nombre[30];
            strcpy(nombre,ciudad->nombre);
            printf(" %i %s \n",orden+1,nombre);
            posicion_actual = l_siguiente(ciudades,posicion_actual);
        }
        printf("\n \n");
        l_destruir(&ciudades);
    }
}

void elegir_opcion(int opcion, TLista ciudades, Viajante viajante){
    TLista ciudades_ordenadas = NULL;
    if(opcion==1){
       ciudades_ordenadas = mostrar_ciudades_ascendentes(ciudades,viajante);
    }
    else {
          if(opcion==2){
             ciudades_ordenadas = mostrar_ciudades_descendentes(ciudades,viajante);
          }
          else {
                if(opcion==3){
                   Viajante viajante_temp = (Viajante) malloc(sizeof(struct viajante));
                   viajante_temp->pos_x = viajante->pos_x;
                   viajante_temp->pos_y = viajante->pos_y;
                   ciudades_ordenadas = reducir_horas_manejo(ciudades,viajante_temp);
                   free(viajante_temp);
                }
                else {
                      if(opcion==4){
                         free(viajante);
                         limpiar_lista(&ciudades);
                         exit(0);
                      }
                      else{
                           printf("\n");
                           printf("\n LEA LAS INSTRUCCIONES Y SELECCIONE UNA OPCION VALIDA \n");
                           printf("\n");
                      }
                }
          }
    }
    mostrar_ciudades(ciudades_ordenadas);
}
