#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "estado.h"

#define INICIAL 0
#define FINAL   1
#define INICIAL_Y_FINAL 2
#define NORMAL 3

/*typedef struct _estructura{
  char** simbolos; //alfabeti
  char** estados_nombres;
  estado** estados;
  char* estado_inicio;
  char** estado_fin;
  int num_estados;
  int num_simbolos;
  int num_finales;
}estructura;*/
typedef struct _estructura estructura;
estructura* crear_estructura(int num_estados, int num_simbolos);
char** get_simbolos(estructura* estru);
char* get_simbolo_pos(estructura* estru, int pos);
void add_simbolo(estructura* estru, char* new_simbolo);
char** get_estados_nombres(estructura* estru);
estado* get_estado_bynombre(estructura* estru, char* estado_nombre);
estado* get_estado_pos(estructura* estru, int pos);
void add_estado(estructura* estru, estado* new_estado);
char* get_estado_inicio(estructura* estru);
void cambiar_estado_inicio(estructura* estru, char* new_estado_inicio);
char** get_estados_fin(estructura* estru);
int get_num_simbolos(estructura* estru);
int get_num_estados(estructura* estru);
void eliminar_estructura(estructura* estru);
//hacer los sets


#endif
