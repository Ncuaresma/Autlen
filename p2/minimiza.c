
#include "minimiza.h"

AFND * AFNDMinimiza(AFND* afd){
  int num_simbolos = AFNDNumSimbolos(afd);
  int num_estados = AFNDNumEstados(afd);
  int* vistos = (int*)malloc(num_estados*sizeof(int));
  int* visitados = NULL;
  int estado_ini = AFNDIndiceEstadoInicial(afd);
  int i;
  int num_accesibles = 0;
  estru* estru_nueva;
  AFND * p_afnd_min;
  if(!afd){
    printf("No hay autómata.\n");
    return NULL;
  }

  for (i = 0; i < num_estados; i++){
    vistos[i] = 0;
  }
  /*Buscamos los estados que necesitamos para el AFD mediante busqueda en anchura*/
  vistos = bfs(estado_ini, num_simbolos, num_estados, vistos, afd);
  for (i = 0; i < num_estados; i++){
    if (vistos[i] == 1){
      num_accesibles++;
      visitados = realloc(visitados, num_accesibles*sizeof(int));
      visitados[num_accesibles-1] = i;
    }
  }
  printf("\nHay %d estados accesibles de %d\n", num_accesibles, num_estados);
  for (i = 0; i < num_accesibles; i++){
    printf("%d ", visitados[i]);
  }
  printf("\n");

  /*Inicializamos la lista de estados, la matriz con todos los valores a cero (solo con estados accesibles)*/
  estru_nueva = ini_estru(num_accesibles);

  /*Cargamos la matriz con el algoritmo propuesto en clase*/
  estru_nueva = estados_equivalentes(afd, visitados, estru_nueva);

  /*Crear el afd*/
  /*recorrer la matriz para sacar los estados equivalentes*/
  p_afnd_min = nuevos_estados(estru_nueva,afd, visitados);

  /*Liberamos memoria final*/
  free(vistos);
  free(visitados);
  eliminar_estru(estru_nueva);
  return p_afnd_min;
}

/*Busqueda en anchura para obtener todos los estados accesibles*/
int* bfs(int estado, int num_simbolos, int num_estados, int* vistos, AFND* afd){
  int* trans;
  int i;
  trans = transiciones(estado, num_estados, num_simbolos, afd);
  vistos[estado] = 1;
  for(i = 0; i < num_estados; i++){
    if(trans[i]){
      estado = i;
      if(vistos[estado] == 0){
        vistos = bfs(estado, num_simbolos, num_estados, vistos, afd);
      }
    }
  }
  free(trans);
  return vistos;
}

int* transiciones (int est, int num_estados, int num_simbolos, AFND* afd){
  int i, j;
  int* transiciones = (int*)malloc(num_estados*sizeof(int));
  for (i = 0; i < num_estados; i++){
    transiciones[i] = 0;
    if (AFNDCierreLTransicionIJ(afd, est, i)){
      transiciones[i] = 1;
    }
    else{
      for (j = 0; j < num_simbolos; j++){
        if (AFNDTransicionIndicesEstadoiSimboloEstadof(afd, est, j, i)){
          transiciones[i] = 1;
        }
      }
    }
  }
  return transiciones;
}

/*Marca el resto de estados distinguiendo en clases -- recursiva*/
estru* estados_equivalentes(AFND* afd, int* visitados, estru* estru_nueva){
  int i;
  int estado;
  int num_accesibles = get_num_accesibles(estru_nueva);

  /*Para cada estado comprobamos con pares si es equivalente con los siguientes a el*/
  for(i = 0; i < num_accesibles; i++){
    estado = visitados[i];
    estru_nueva = equivalentes(afd, estru_nueva, estado, i, visitados);
  }
  return estru_nueva;
}

/*Para cada estado comprobamos con que estados se combinan para crear los pares y si es equivalente con ellos*/
estru* equivalentes(AFND* afd, estru* estru_nueva, int estado, int pos, int* visitados){
  int i, simbol, k;
  int estado1;
  int estado2;
  int num_simbolos = AFNDNumSimbolos(afd);
  int num_accesibles = get_num_accesibles(estru_nueva);
  par* par_nuevo = NULL;

  /* Combinaciones de pares con los que cada estado se comprueba*/
  for(i = pos+1; i < num_accesibles; i++){
    par_nuevo = buscar_par(estado, visitados[i], estru_nueva);
    if (par_nuevo == NULL){
      par_nuevo = ini_par(estado, visitados[i]);
      aniadir_par(estru_nueva, par_nuevo);
    }
    /*Comprobamos si alguno de los dos es final y el otro no*/
    if(AFNDTipoEstadoEn(afd, estado) == FINAL || AFNDTipoEstadoEn(afd, estado) == INICIAL_Y_FINAL){
      if (AFNDTipoEstadoEn(afd, visitados[i]) != FINAL && AFNDTipoEstadoEn(afd, visitados[i]) != INICIAL_Y_FINAL){
          marcar(par_nuevo, estru_nueva, pos, i, visitados);
      }
    }
    else if(AFNDTipoEstadoEn(afd, visitados[i]) == FINAL || AFNDTipoEstadoEn(afd, visitados[i]) == INICIAL_Y_FINAL){
      if (AFNDTipoEstadoEn(afd, estado) != FINAL && AFNDTipoEstadoEn(afd, estado) != INICIAL_Y_FINAL){
          marcar(par_nuevo, estru_nueva, pos, i, visitados);
      }
    }else{
      /*si no lo he marcado compruebo sus transiciones*/
      /* Con cada simbolo a que estado voy*/
      for(simbol = 0; simbol < num_simbolos; simbol++){
        estado1 = -1;
        estado2 = -1;
        /* Vemos a donde van cada uno de los estados de par con cada simbolo*/
        for (k = 0; k < num_accesibles; k++){
          if(AFNDTransicionIndicesEstadoiSimboloEstadof(afd, estado, simbol, visitados[k])){
            estado1 = visitados[k];
          }
          if(AFNDTransicionIndicesEstadoiSimboloEstadof(afd, visitados[i], simbol, visitados[k])){
            estado2 = visitados[k];
          }
        }
        if(estado1 < estado2){
          pares_asociados(estru_nueva, par_nuevo, estado1, estado2, pos, i, visitados);
        }else{
          pares_asociados(estru_nueva, par_nuevo, estado2, estado1, pos, i, visitados);
        }
      }
    }
  }
  return estru_nueva;
}


void pares_asociados(estru* estru_nueva, par* par_nuevo, int estado1, int estado2, int pos, int i, int* visitados){
  par* par_asoc;

  if (!estru_nueva || !par_nuevo || !visitados) return;
  /* Si uno no tiene transicion y otro si*/
  if((estado1 == -1 && estado2 != -1) || (estado1 != -1 && estado2 == -1)){
    marcar(par_nuevo, estru_nueva, pos, i, visitados);
  }

  /* Si el par asociado existe y no equivalente*/
  par_asoc = buscar_par(estado1, estado2, estru_nueva);
  if (par_asoc != NULL){
    /* Si el par asociado no es equivalente entonces tampoco el que llega a ellos*/
    if(get_equivalente(par_asoc) == 1){
        marcar(par_nuevo, estru_nueva, pos, i, visitados);
    }else{
      /* si son equivalentes el que llega a ellos tambien, pero se une a su lista de dependencia, por si cambia la equivalencia*/
      /*buscar si ya se ha añadido*/
      if(!buscar_asociado(estru_nueva, par_asoc, par_nuevo)){
        aniadir_par_asociado(estru_nueva, par_asoc, par_nuevo);
      }
    }
  }else{
    /*Si no existe el par lo creo y añado a su lista de asociacion el par*/
    par_asoc = ini_par(estado1, estado2);
    aniadir_par(estru_nueva, par_asoc);
    aniadir_par_asociado(estru_nueva, par_asoc, par_nuevo);
  }
}

/***Recursiva***/
/*Marcamos si no son equivalentes los pares, tanto en la matriz como en la estructura*/
void marcar(par* par_nuevo, estru* estru_nueva, int pos1, int pos2, int* visitados){
  int i,j, id1, id2, pos1_asoc, pos2_asoc;
  int num_accesibles = get_num_accesibles(estru_nueva);
  int num_asoc = get_n_asoc(par_nuevo);
  par* asociado = NULL;

  set_par_equivalente(estru_nueva, par_nuevo, 1);
  marcar_matriz(estru_nueva, pos1, pos2);
  for(i = 0; i < num_asoc; i++){
    asociado = get_asociados(par_nuevo)[i];
    if (asociado != NULL && get_equivalente(asociado) == 0){
      id1 = get_id1(asociado);
      id2 = get_id2(asociado);

      for(j = 0; j < num_accesibles; j++){
        if(visitados[j] == id1){
          pos1_asoc = j;
        }else if(visitados[j] == id2){
          pos2_asoc = j;
        }
      }
      marcar(asociado, estru_nueva, pos1_asoc, pos2_asoc, visitados);
    }
  }
}

/*Crea los nuevos estados combinados si son equivalentes y añade por cada estado que se combina la transicion al siguinete estado*/
AFND* nuevos_estados(estru* estru_nueva, AFND* afd, int* visitados){
  int i, j, k;
  int nom;
  int ya = 0;
  int creado = 0;
  char nombre_estado[MAX_CHAR];
  int estados = 0;
  int num_simbolos = AFNDNumSimbolos(afd);
  int num_estados = AFNDNumEstados(afd);
  estado** estados_nuevos = NULL; /*Array con los nuevos estados*/
  estado* state_nuevo = NULL;
  int tam_matriz = get_num_accesibles(estru_nueva);

  for (i = 0; i < tam_matriz; i++){
    for (j = 0; j < tam_matriz; j++){
      if (get_matriz(estru_nueva)[i][j] == 0){
        nom = sizeof(AFNDNombreEstadoEn(afd, visitados[j]));
        memmove(nombre_estado, AFNDNombreEstadoEn(afd, visitados[j]), nom);
        if(strcmp(nombre_estado, "") != 0){
          if (creado == 0){
            /*creamos estado*/
            state_nuevo = crear_estado(num_simbolos, num_estados, nombre_estado, visitados[j], AFNDTipoEstadoEn(afd, visitados[j]));
            creado = 1;
          }
          else{
            /*añadimos al creado*/
            add_estado(state_nuevo, nombre_estado, visitados[j], AFNDTipoEstadoEn(afd, visitados[j]));
          }
          aniadir_trasicion(state_nuevo, afd, visitados[j], num_estados, num_simbolos);
        }
        nom = sizeof("");
        memmove(nombre_estado, "", nom);
      }
    }
    if (state_nuevo != NULL){
      for (k = 0; k < estados; k++){
        /*Comprobamos nombre de los estados*/
        if (strcmp(get_nombre_estado(state_nuevo), get_nombre_estado(estados_nuevos[k])) == 0){
          ya = 1;
        }
      }
      if (ya == 0){
        /*Aqui añadimos codificacion*/
        estados ++;
        estados_nuevos = realloc(estados_nuevos, estados*sizeof(estado*));
        estados_nuevos[estados-1] = state_nuevo;
      }
    }
    ya = 0;
    creado = 0;
  }
  return automata_fin(afd,estados_nuevos, estados);
}

/*añade las transiciones entre estados*/
void aniadir_trasicion(estado* state_nuevo, AFND* afnd, int estado, int num_estados, int num_simbolos){
  int i, j;
  for(i = 0; i < num_estados; i++){
    for(j = 0; j < num_simbolos; j++){
      if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, estado, j, i)){
        set_transiciones_sim_est(state_nuevo, j, i);
      }
    }
  }
}

/*Crea el automata final*/
AFND* automata_fin(AFND* afnd, estado** estados_nuevos, int estados){
  int i, j, k, l;
  int mismo = 0;
  int num_simbolos = AFNDNumSimbolos(afnd);
  int estados_totales = AFNDNumEstados(afnd);
  AFND * p_afnd_min = AFNDNuevo("af1_min", estados, num_simbolos);
  for (i = 0; i < estados; i++){
    AFNDInsertaEstado(p_afnd_min, get_nombre_estado(estados_nuevos[i]), get_tipo_estado(estados_nuevos[i]));
  }
  for (i = 0; i < num_simbolos; i++){
    AFNDInsertaSimbolo(p_afnd_min,AFNDSimboloEn(afnd, i));
  }
  for (i = 0; i < estados; i++){
    for (j = 0; j < estados; j++){
      for (k = 0; k < num_simbolos; k++){
        mismo = 0;
        for (l = 0; l < estados_totales; l++){
          if (mismo == 0 && get_transiciones(estados_nuevos[i])[k][l] == 1 && get_codificacion_mia(estados_nuevos[j])[l] == 1){
            mismo = 1;
          }
        }
        if (mismo == 1){
          AFNDInsertaTransicion(p_afnd_min, get_nombre_estado(estados_nuevos[i]), AFNDSimboloEn(p_afnd_min,k), get_nombre_estado(estados_nuevos[j]));
        }
      }
    }
  }

  for(i = 0; i < estados; i++){
     eliminar_estado(estados_nuevos[i]);
   }
  free(estados_nuevos);
  return p_afnd_min;
}
