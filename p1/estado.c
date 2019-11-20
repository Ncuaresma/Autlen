#include "estado.h"

/*estructura para estado*/
struct _estado{
  char* nombre;
  int* id;
  int tipo; /*puede ser INICIAL, FINAL, INICIAL_Y_FINAL O NORMAL*/
  int** transiciones; /* array de arrasys con los estados a los quue se puede ir y con que simbolos*/
  int num_simbolos;
  int num_estados_base;
};

/*inicializando valores del estado*/
estado *ini_estado(int num_estados_base, int num_simbolos){
  int i = 0;
  estado* state;
  if (num_simbolos < 0 || num_estados_base < 0) return NULL;
  state = (estado*)malloc(sizeof(estado));
  if (!state) return NULL;
  state->nombre = (char*)malloc((sizeof(char))*MAX_CHAR);
  if(!state->nombre){
    free(state);
    return NULL;
  }
  state->transiciones = (int **)malloc(num_simbolos*sizeof(int*));
  if (!state->transiciones){
    free(state->nombre);
    free(state);
    return NULL;
  }
  for (i=0;i<num_simbolos;i++){
		state->transiciones[i] = (int*)malloc(num_estados_base*sizeof(int));
    if (!state->transiciones[i]){
      free(state->transiciones);
      free(state->nombre);
      free(state);
      return NULL;
    }
  }
  state->id = (int *)malloc(num_estados_base*sizeof(int));
  /*Ponemos por defecto todos los ids a 0*/
  if (!state->id){
    for (i = 0; i < num_simbolos; i++){
      free(state->transiciones[i]);
    }
    free(state->transiciones);
    free(state->nombre);
    free(state);
    return NULL;
  }
  for (i = 0; i < num_estados_base; i++){
    state->id[i] = 0;
  }
  return state;
}

estado* crear_estado(char* nombre, int tipo, int num_simbolos, int num_estados_base, int id){
  estado* state;
  if (!nombre) return NULL;
  if (tipo > 3 || tipo < 0) return NULL;
  if (num_simbolos < 0 || num_estados_base < 0) return NULL;

  state = ini_estado(num_estados_base, num_simbolos);

  state->id[id] = 1;
  state->num_estados_base = num_estados_base;
  state->num_simbolos = num_simbolos;
  state->tipo = tipo;
  strcpy(state->nombre, nombre);
  return state;
}

char* get_nombre(estado* estado){
  if(!estado) return NULL;
  return estado->nombre;
}

int get_id(estado* estado){
  int i;
  if(!estado) return -1;
  for (i = 0; i < estado->num_estados_base; i++){
    if(estado->id[i]){
      return i;
    }
  }
  return -1;
}

int get_tipo(estado* estado){
  if(!estado) return -1;
  return estado->tipo;
}

int** get_transciones(estado* estado){
  if(!estado) return NULL;
  return estado->transiciones;
}

int* get_transicion_simbolo(estado* estado, int pos_simbolo){
  if(!estado) return NULL;
  return estado->transiciones[pos_simbolo];
}

void annadir_trans(estado* estado, int estado_pos, int simbolo){
    if(!estado) return;
    if(estado_pos < 0 || estado_pos >= estado->num_estados_base || simbolo < 0 || simbolo >= estado->num_simbolos) return;
    estado->transiciones[estado_pos][simbolo] = 1;
}

void eliminar_estado(estado* estado){
  int i = 0;
  if(!estado) return;
	if(estado->nombre) free(estado->nombre);
	for (i = 0; i < estado->num_simbolos; i++){
		free(estado->transiciones[i]);
	}
	free(estado->transiciones);
	free(estado);
}
