#include <stdio.h>
#include <string.h>
#include "panel.h"
#include "tda_utils.h"

void mostrar_menu() {
    printf(" PLANIFICADOR DE VIAJES \n ");
    printf(" Seleccione la opción deseada introduciendo el número asociado \n");
    printf(" 1 _ Mostrar ascendente \n");
    printf(" 2 _ Mostrar descendente \n");
    printf(" 3 _ Reducir horas de manejo \n");
    printf(" 4 _ Salir \n");
    printf(" Elección : ");
}

void imprimir_ciudad(TCiudad ciudad, int orden) {
    char nombre[30];
    strcpy(nombre,ciudad->nombre);
    printf(" %i %s \n",orden,nombre);
}

void mostrar_espaciado(){
    printf("\n");
    printf("/////////////////////////////////////////////////////////////// \n");
    printf("\n");
}

void elegir_opcion(int opcion, TLista ciudades, Viajante viajante){
    if(opcion==1){
       mostrar_ciudades_ascendentes(ciudades,viajante);
    }
    else {
          if(opcion==2){
             mostrar_ciudades_descendentes(ciudades,viajante);
          }
          else {
                if(opcion==3){
                   // Se realiza una copia del viajante, ya que el original no deberia ser modificado.
                   Viajante viajante_temp = (Viajante) malloc(sizeof(struct viajante));
                   viajante_temp->pos_x = viajante->pos_x;
                   viajante_temp->pos_y = viajante->pos_y;
                   reducir_horas_manejo(ciudades,viajante_temp);
                   free(viajante_temp); // Una vez terminada la ejecucción del método, se libera el espacio de memoria.
                }
                else {
                      if(opcion==4){  // Opción de salida.
                        // Se procede a liberar todo el espacio de memoria reservado para las ciudades y el viajante.
                         free(viajante);
                         limpiar_lista_ciudades(&ciudades);
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
}
