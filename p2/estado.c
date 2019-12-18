#include "estado.h"

/*estructura para estado*/
struct _estado{
  char nombre[MAX_CHAR];
  int* codificacion_mia;
  int tipo; /*puede ser INICIAL, FINAL, INICIAL_Y_FINAL O NORMAL*/
  int** transiciones; /*matriz de codificaciones con cada simbolo*/
  int num_simbolos;
  int num_estados; /*Todos, incluso lo s no accesibles*/
};

estado* crear_estado(int num_simbolos, int num_estados, char* nombre, int pos, int tipo){
  int i, j;
  estado* state = (estado*)malloc(sizeof(estado));
  state->num_simbolos = num_simbolos;
  state->num_estados = num_estados;
  state->tipo = tipo;
  memmove(state->nombre, nombre, MAX_CHAR);
  state->codificacion_mia = (int*)malloc(num_estados*sizeof(int));
  for (i = 0; i < num_estados; i++){
    if (i == pos){
      state->codificacion_mia[i] = 1;
    }
    else{
      state->codificacion_mia[i] = 0;
    }
  }
  state->transiciones = (int**)malloc(num_simbolos*sizeof(int*));

  for (i = 0; i < num_simbolos; i++){
    state->transiciones[i] = (int*)malloc(num_estados*sizeof(int));
    for(j = 0; j < num_estados; j++){
      state->transiciones[i][j] = 0;
    }
  }
  return state;
}

void add_estado(estado* state, char* nombre, int pos, int tipo){
  if (tipo != NORMAL && state->tipo == NORMAL){
    state->tipo = tipo;
  }
  if (tipo == INICIAL_Y_FINAL && (state->tipo == FINAL  || state->tipo == INICIAL)){
    state->tipo = tipo;
  }

  state->codificacion_mia[pos] = 1;
  strcat(state->nombre, nombre);
}

char* get_nombre_estado(estado* state){
  return state->nombre;
}

void set_transiciones_sim_est(estado* state, int sim, int est){
  state->transiciones[sim][est] = 1;
}

int** get_transiciones(estado* state){
  return state->transiciones;
}

int get_tipo_estado(estado* state){
  return state->tipo;
}

int* get_codificacion_mia(estado* state){
  return state->codificacion_mia;
}
