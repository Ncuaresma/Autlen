#include "estado.h"

/*estructura para estado*/
struct _estado{
  char* nombre;
  int id;
  int* codificacion;
  int tipo; /*puede ser INICIAL, FINAL, INICIAL_Y_FINAL O NORMAL*/
  int** transiciones; /* array de arrasys con los estados a los quue se puede ir y con que simbolos*/
  int num_simbolos;
  int num_estados_base;
};

/*inicializando valores del estado*/
estado *ini_estado(int num_estados_base, int num_simbolos){
  int i,j = 0;
  estado* state;
  if (num_simbolos < 0 || num_estados_base < 0) return NULL;
  state = (estado*)malloc(sizeof(estado));
  state->num_estados_base=num_estados_base;
  state->num_simbolos=num_simbolos;
  if (!state) return NULL;
  state->nombre = (char*)malloc((sizeof(char))*MAX_CHAR);
  if(!state->nombre){
    free(state);
    return NULL;
  }
  state->transiciones = (int **)malloc(state->num_simbolos*sizeof(int*));
  if (!state->transiciones){
    free(state->nombre);
    free(state);
    return NULL;
  }
  for (i=0;i<num_simbolos;i++){
		state->transiciones[i] = (int*)malloc(state->num_estados_base*sizeof(int));
    for(j = 0; j < num_estados_base; j++){
      state->transiciones[i][j] = 0;
    }
    if (!state->transiciones[i]){
      free(state->transiciones);
      free(state->nombre);
      free(state);
      return NULL;
    }
  }
  state->codificacion = (int*)malloc((state->num_estados_base)*sizeof(int));
  for (i = 0; i < state->num_estados_base; i++){
    state->codificacion[i] = 0;
  }
  return state;
}

estado* crear_estado(char* nombre, int tipo, int num_simbolos, int num_estados_base, int id){
  estado* state;
  int nom = 0;
  if (!nombre) return NULL;
  if (tipo > 3 || tipo < 0) return NULL;
  if (num_simbolos < 0 || num_estados_base < 0) return NULL;

  state = ini_estado(num_estados_base, num_simbolos);

  state->id = id;
  state->codificacion[id] = 1;
  state->tipo = tipo;
  nom = sizeof(nombre);
  memmove(state->nombre, nombre, nom);
  return state;
}

estado* crear_estado_combinado(char* nombre, int tipo, int num_simbolos, int num_estados_base, int id, int* codificacion){
  estado* state;
  int nom;
  if (!nombre) return NULL;
  if (tipo > 3 || tipo < 0) return NULL;
  if (num_simbolos < 0 || num_estados_base < 0) return NULL;

  state = ini_estado(num_estados_base, num_simbolos);

  state->id = id;
  state->codificacion = codificacion;
  state->num_estados_base = num_estados_base;
  state->num_simbolos = num_simbolos;
  state->tipo = tipo;
  nom = sizeof(nombre);
  memmove(state->nombre, nombre, nom);
  return state;
}

char* get_nombre(estado* estado){
  if(!estado) return NULL;
  return estado->nombre;
}

void set_nombre_estado(estado * estado, char *nombre){
  int nom = sizeof(nombre);
  memmove(estado->nombre, nombre, nom);
}

int* get_codificacion(estado* estado){
  if(!estado) return NULL;
  return estado->codificacion;
}

int get_id(estado* estado){
  if(!estado) return -1;
  return estado->id;
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
    estado->transiciones[simbolo][estado_pos] = 1;
}

void annadir_trans_comb(estado* estado, int* trans, int simbolo){
    if(!estado) return;
    if(simbolo < 0 || simbolo >= estado->num_simbolos) return;
}

void eliminar_estado(estado* estado){
  int i;
  free(estado->codificacion);
  free(estado->nombre);
  for (i = 0; i < estado->num_simbolos; i++){
    free(estado->transiciones[i]);
  }
  free(estado->transiciones);
	free(estado);
}
