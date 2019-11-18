#ifndef ESTADO_H
#define ESTADO_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define INICIAL 0
#define FINAL   1
#define INICIAL_Y_FINAL 2
#define NORMAL 3

/*typedef struct _estado{
  char* nombre;
  int tipo; //puede ser INICIAL, FINAL, INICIAL_Y_FINAL O NORMAL
  int** transiciones; // array de arrasys con los estados a los quue se puede ir y con que simbolos
  int num_simbolos;
  int num_estados;
}estado;*/
typedef struct _estado estado;
estado* ini_estado(int num_estados, int num_simbolos);
estado* crear_estado(char* nombre, int tipo, int num_simbolos, int num_estados);
char* get_nombre(estado* estado);
int get_tipo(estado* estado);
int** get_transciones(estado* estado);
int* get_transicion_simbolo(estado* estado, int pos_estado); //devuelve con que simbolos se puede llegar a un estado (no sabia que devolver si no)
void annadir_trans(estado* estado, int estado_pos, int simbolo);
void eliminar_estado(estado* est);


#endif
