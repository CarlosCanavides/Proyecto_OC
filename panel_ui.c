#include <ncurses.h>
#include "lista.h"
#include "planificador.h"

void insertar_linea_decorada(char* dest, char* contenido){
    char linea[52];
    sprintf(linea ,"*  %s", contenido);
    int espacio_restante = 50 - strlen(linea);
    int i;
    for(i = 0; i <= espacio_restante; i++){
        strcat(linea, " ");
    }
    strcat(linea, "*\n");
    strcat(dest, linea);
}

void dibujar_panel_inicio(){
    clear();
    printw("****************************************************\n\
*         Bienvenido al sistema de viajeros.       *\n\
*                                                  *\n\
****************************************************\n\
*                                                  *\n\
*    Por favor, inserte el nombre de su archivo:   *\n\
*                                                  *\n\
* Archivo:                                         *\n\
*                                                  *\n\
****************************************************");
    move(7,12);
    echo();
    nocbreak();
    refresh();
}

void dibujar_panel_opciones(int opcion){
    int ini_y = 4;
    int ini_x = 3;
    clear();
    printw("****************************************************\n\
*      Seleccione una de nuestras operaciones      *\n\
****************************************************\n\
*                                                  *\n\
* [ ] Mostrar ciudades ascendentemente             *\n\
*                                                  *\n\
* [ ] Mostrar ciudades descedentemente             *\n\
*                                                  *\n\
* [ ] Reducir horas de viaje                       *\n\
*                                                  *\n\
* [ ] Salir                                        *\n\
*                                                  *\n\
****************************************************\n\
      [W]:arriba   [S]:abajo   [ENTER]:aceptar");

    int x = ini_x;
    int y = ini_y + (2*opcion);
    mvaddstr(y,x, "#");
    refresh();
}

void dibujar_panel_ciudades(TLista ciudades){
    clear();
    char panel[2048] = "****************************************************\n\
*                                                  *\n";
    char panel_final[] = "* [#] Volver                                       *\n\
*                                                  *\n\
****************************************************\n\
      [W]:arriba   [S]:abajo   [ENTER]:aceptar";
    TPosicion pos_actual = l_primera(ciudades);
    TCiudad ciudad_actual;
    int pos = 1;
    while(pos_actual != NULL){
        ciudad_actual = (TCiudad)l_recuperar(ciudades, pos_actual);
        char contenido_linea[20];
        sprintf(contenido_linea, "%i. %s", pos++, ciudad_actual->nombre);
        insertar_linea_decorada(panel, contenido_linea);
        insertar_linea_decorada(panel, "");
        pos_actual = l_siguiente(ciudades, pos_actual);
    }
    strcat(panel, panel_final);
    printw(panel);
    refresh();
}
