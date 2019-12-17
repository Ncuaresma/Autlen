#ifndef _ESTADO_H
#define _ESTADO_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define INICIAL 1
#define FINAL   2
#define INICIAL_Y_FINAL 3
#define NORMAL 0
#define MAX_CHAR 300

typedef struct _estado estado;

estado* crear_estado(int num_simbolos, int num_estados, char* nombre, int pos, int tipo);
void add_estado(estado* state, char* nombre, int pos, int tipo);
char* get_nombre_estado(estado* state);
void set_transiciones_sim_est(estado* state, int sim, int est);
int** get_transiciones(estado* state);

#endif
