#include "estructura.h"

/* estructura general */
struct _estructura{
  char** simbolos; /*alfabeti*/
  /*char** estados_nombres;*/
  estado** estados;
  char* estado_inicio;
  char** estados_fin;
  int num_estados;
  int num_simbolos;
  int num_finales;
};

estructura* crear_estructura(int num_simbolos){
  int i = 0;
  estructura* estru = (estructura*)malloc(sizeof(estructura));

  if (num_simbolos < 0) return NULL;
  if (!estru) return NULL;

  estru->num_estados = 0;
  estru->num_simbolos = num_simbolos;

  estru->simbolos = (char**)malloc(num_simbolos*sizeof(char*));
  if (! estru->simbolos){
    free(estru);
    return NULL;
  }
  for (i = 0; i < num_simbolos; i++){
    estru->simbolos[i] = (char*)malloc(sizeof(char)*MAX_CHAR);
    if (! estru->simbolos[i]){
      free(estru->simbolos);
      free(estru);
      return NULL;
    }
  }

  estru->estados = (estado**)malloc(sizeof(estado*));
  if (! estru->estados){
    free(estru->simbolos);
    for (i = 0; i < num_simbolos; i++){
      free(estru->simbolos[i]);
    }
    free(estru);
    return NULL;
  }

  estru->estado_inicio=(char*)malloc(sizeof(char)*MAX_CHAR);
  if (! estru->estado_inicio){
    for (i = 0; i < estru->num_estados; i++){
      free(estru->estados[i]);
    }
    free(estru->estados);
    free(estru->simbolos);
    for (i = 0; i < num_simbolos; i++){
      free(estru->simbolos[i]);
    }
    free(estru);
    return NULL;
  }
  estru->estados_fin=(char**)malloc(sizeof(char*)*MAX_CHAR);
  if (! estru->estados_fin){
    free(estru->estado_inicio);
    for (i = 0; i < estru->num_estados; i++){
      free(estru->estados[i]);
    }
    free(estru->estados);
    free(estru->simbolos);
    for (i = 0; i < num_simbolos; i++){
      free(estru->simbolos[i]);
    }
    free(estru);
    return NULL;
  }
  return estru;
}

char** get_simbolos(estructura* estru){
  if (!estru) return NULL;
  return estru->simbolos;
}

char* get_simbolo_pos(estructura* estru, int pos){
  if (!estru) return NULL;
  if (pos < 0 || pos >= estru->num_simbolos) return NULL;
  return estru->simbolos[pos];
}

void add_simbolo(estructura* estru, char* new_simbolo){
  if (!estru || !new_simbolo) return;
  strcpy(estru->simbolos[estru->num_simbolos], new_simbolo);
  estru->num_simbolos++;
}

estado* get_estado_bynombre(estructura* estru, char* estado_nombre){
  int i = 0;
  if (!estru || !estado_nombre) return NULL;
  for (i = 0; i < estru->num_estados; i++){
    estado* state_inter = ini_estado(estru->num_estados, estru->num_simbolos);
    state_inter = estru->estados[i];
    if (!state_inter) return NULL;
    if (strcmp( get_nombre(state_inter), estado_nombre) == 0){
      return estru->estados[i];
    }
  }
  return NULL;
}

estado* get_estado_pos(estructura* estru, int pos){
  if (!estru) return NULL;
  if (pos < 0 || pos >= estru->num_estados) return NULL;
  return estru->estados[pos];
}

void add_estado(estructura* estru, estado* new_estado){
  if (!estru || !new_estado || !get_nombre(new_estado)) return;
  estru->num_estados++;
  estru->estados = realloc(estru->estados, (estru->num_estados)*sizeof(estado*));
  estru->estados[estru->num_estados-1] = new_estado;
}

char* get_estado_inicio(estructura* estru){
  if (!estru) return NULL;
  return estru->estado_inicio;
}

void cambiar_estado_inicio(estructura* estru, char* new_estado_inicio){
  if (!estru || !new_estado_inicio) return;
  strcpy(estru->estado_inicio, new_estado_inicio);
}

char** get_estados_fin(estructura* estru){
  if (!estru) return NULL;
  return estru->estados_fin;
}

int get_num_simbolos(estructura* estru){
  if (!estru) return -1;
  return estru->num_simbolos;
}

int get_num_estados(estructura* estru){
  if (!estru) return -1;
  return estru->num_estados;
}

void eliminar_estructura(estructura* estru){
  int i = 0;
  if (!estru) return;
  free(estru->estados_fin);
  free(estru->estado_inicio);
  free(estru->estados);

  free(estru->simbolos);
  for (i = 0; i < estru->num_simbolos; i++){
    free(estru->simbolos[i]);
  }
  free(estru);

}
