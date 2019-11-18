#include "estructura.h"

// estructura general
typedef struct _estructura{
  char** simbolos; //alfabeti
  char** estados_nombres;
  estado* estados;
  char* estado_inicio;
  char** estados_fin;
  int num_estados;
  int num_simbolos;
}estructura;

estructura* crear_estructura(int num_estados, int num_simbolos){
  if (num_estado < 0 || num_simbolos < 0) return null;

  estructura* estru = malloc(sizeof(estado));
  if (!estru) return NULL;

  estru->num_estados = num_estados;
  estru->num_simbolos = num_simbolos;

  estru->simbolos = (char**)malloc(num_simbolos*sizeof(char*));
  if (! estru->simbolos){
    free(estru);
    return NULL;
  }
  for (int i = 0; i < num_simbolos; i++){
    estru->simbolos[i] = (char*)malloc(sizeof(char));
    if (! estru->simbolos[i]){
      free(estru->simbolos);
      free(estru);
      return NULL;
    }
  }

  estru->estados_nombres = (char**)malloc(num_estados*sizeof(char*));
  if (! estru->estados_nombres){
    for(int i = 0; i < num_simbolos; i++){
  		free(estru->simbolos[i]);
  	}
    free(estru->simbolos);
    free(estru);
    return NULL;
  }
  for (int i = 0; i < num_estados; i++){
    estru->estados_nombres[i] = (char*)malloc(sizeof(char));
    if (! estru->estados_nombres[i]){
      free(estru->estados_nombres);
      free(estru->simbolos);
      for(int i = 0; i < num_simbolos; i++){
    		free(estru->simbolos[i]);
    	}
      free(estru);
      return NULL;
    }
  }
  //NO HE ACABADOO
  /*
  char* estado_inicio;
  char** estados_fin;
  int num_estados;
  int num_simbolos;*/
  estru->estados=(estado*)malloc(sizeof(estado));
  if (! estru->estados){
    for(int i = 0; i < num_estados; i++){
      free(estru->estados_nombres[i]);
    }
    free(estru->estados_nombres);
    free(estru->simbolos);
    for(int i = 0; i < num_simbolos; i++){
      free(estru->simbolos[i]);
    }
    free(estru);
    return NULL;
  }

  estru->estado_inicio=(char*)malloc(sizeof(char));
  if (! estru->estado_inicio){
    free(estru->estados);
    for(int i = 0; i < num_estados; i++){
      free(estru->estados_nombres[i]);
    }
    free(estru->estados_nombres);
    free(estru->simbolos);
    for(int i = 0; i < num_simbolos; i++){
      free(estru->simbolos[i]);
    }
    free(estru);
    return NULL;
  }
  estru->estados_fin=(char**)malloc(sizeof(char*));
  if (! estru->estados){
    free(estru->estado_inicio);
    free(estru->estados);
    for(int i = 0; i < num_estados; i++){
      free(estru->estados_nombres[i]);
    }
    free(estru->estados_nombres);
    free(estru->simbolos);
    for(int i = 0; i < num_simbolos; i++){
      free(estru->simbolos[i]);
    }
    free(estru);
    return NULL;
  }

}

char** get_simbolos(estructura* estru){
  if (!estru) return NULL;
  return estru->simbolos[];
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

char** get_estados_nombres(estructura* estru){
  if (!estru) return NULL;
  return estru->estados_nombres;
}

estado get_estado_bynombre(estructura* estru, char* estado_nombre){
  if (!estru || !estado_nombre) return NULL;
  for (int i = 0; i < estru->num_estados; i++){
    if (strcmp(estru->estados[i]->nombre), nombre){
      return estru->estados[i];
    }
  }
}

char* get_estado_pos(estructura* estru, int pos){
  if (!estru) return NULL;
  return estru->estados[pos];
}

void add_estado(estructura* estru, estado* new_estado){
  if (!estru || !estado) return;
  strcpy(estru->estados[estru->num_estados], new_estado);
  estru->num_estados++;
}

char* get_estado_inicio(estructura* estru){
  if (!estru) return NULL;
  return estru->estado_inicio;
}

void cambiar_estado_inicio(estructura* estru, char* new_estado_inicio){
  if (!estru || !new_estado_inicio) return;
  strcpy(estru->estado_inicio, new_estado_inicio);
}

char* get_estados_fin(estructura* estru){
  if (!estru) return NULL;
  return estru->estados_fin;
}

int get_num_simbolos(estructura* estru){
  if (!estru) return -1;
  return estr->num_simbolos;
}

int get_num_estados(estructura* estru){
  if (!estru) return -1;
  return estr->num_estados;
}

void eliminar_estructura(estructura* estru){
  if (!estru) return;
  free(estru->estados_fin);
  free(estru->estado_inicio);
  free(estru->estados);
  for(int i = 0; i < num_estados; i++){
    free(estru->estados_nombres[i]);
  }
  free(estru->estados_nombres);
  free(estru->simbolos);
  for(int i = 0; i < num_simbolos; i++){
    free(estru->simbolos[i]);
  }
  free(estru);

}
