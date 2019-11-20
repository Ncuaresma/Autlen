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
#define MAX_CHAR 300

/*typedef struct _estado{
  char* nombre;
  int tipo; //puede ser INICIAL, FINAL, INICIAL_Y_FINAL O NORMAL
  int** transiciones; // array de arrasys con los estados a los quue se puede ir y con que simbolos
  int num_simbolos;
  int num_estados_base;
}estado;*/
typedef struct _estado estado;
estado* ini_estado(int num_estados_base, int num_simbolos);
estado* crear_estado(char* nombre, int tipo, int num_simbolos, int num_estados_base, int id);
estado* crear_estado_combinado(char* nombre, int tipo, int num_simbolos, int num_estados_base, int id, int* codificacion);
char* get_nombre(estado* estado);
int get_id(estado* estado);
int* get_codificacion(estado* estado);
int get_tipo(estado* estado);
int** get_transciones(estado* estado);
int* get_transicion_simbolo(estado* estado, int pos_estado);
void annadir_trans(estado* estado, int estado_pos, int simbolo);
void annadir_trans_comb(estado* estado, int* trans, int simbolo);
void eliminar_estado(estado* est);


#endif
