#include "panel.h"

void mostrar_menu() {
    printf(" PLANIFICADOR DE VIAJES \n ");
    printf(" Seleccione la opción deseada introduciendo el número asociado \n");
    printf(" 1 _ Mostrar ascendente \n");
    printf(" 2 _ Mostrar descendente \n");
    printf(" 3 _ Reducir horas de manejo \n");
}

void mostrar_ciudades(TLista ciudades) {
    TPosicion posicion_actual = l_primera(ciudades);
    TPosicion ultima_posicion = l_ultima(ciudades);
    TCiudad ciudad;
    int orden = 0;
    do{
        ciudad = l_recuperar(ciudades, posicion_actual);
        printf(" %i NOMBRE DE LA CIUDAD \n ",orden);
        posicion_actual = l_siguiente(ciudades,posicion_actual);
        orden++;
    } while(posicion_actual!=ultima_posicion);

}

void elegir_opcion(int opcion, TLista ciudades, Viajante viajante){
    TLista ciudades_ordenadas;
    if(opcion==1){
       ciudades_ordenadas = mostrar_ciudades_ascendentes(ciudades,viajante);
    }
    else {
          if(opcion==2){
             ciudades_ordenadas = mostrar_ciudades_descendentes(ciudades,viajante);
          }
          else {
             ciudades_ordenadas = reducir_horas_manejo(ciudades,viajante);
          }
    }
    mostrar_ciudades(ciudades_ordenadas);
}
