
#include "minimiza.h"

AFND * AFNDMinimiza(AFND* afd){
  int num_simbolos = AFNDNumSimbolos(afd);
  int num_estados = AFNDNumEstados(afd);
  int* vistos = (int*)malloc(num_estados*sizeof(int));
  int* visitados = NULL;
  int estado_ini = AFNDIndiceEstadoInicial(afd);
  int i;
  int num_accesibles = 0;
  estru* estru;
  if(!afd){
    printf("No hay autómata.\n");
    return NULL;
  }
  for (i = 0; i < num_estados; i++){
    vistos[i] = 0;
  }

  /*Buscamos los estados que necesitamos para el AFD mediante busqueda en anchura*/
  vistos = bfs(estado_ini, num_simbolos, num_estados, vistos, afd);
  printf("\nVistosss\n");
  for (i = 0; i < num_estados; i++){
    printf("%d ", vistos[i]);
    if (vistos[i] == 1){
      num_accesibles++;
      visitados = realloc(visitados, num_accesibles*sizeof(int));
      visitados[num_accesibles-1] = i;
    }
  }
  printf("\nHay %d estados accesibles de %d\n", num_accesibles, num_estados);

  /*Inicializamos la lista de estados, la matriz con todos los valores a cero (solo con estados accesibles)*/
  estru = ini_estru(num_accesibles);

  /*Cargamos la matriz con el algoritmo propuesto en clase*/
  estru = estados_equivalentes(afd, visitados, estru);


  /*Liberamos memoria final*/
  free(vistos);
  free(visitados);
  eliminar_estru(estru);
  return NULL;
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

/* Marca los estados no equivalentes en la matriz
int** estados_equivalentes(AFND* afd, int* visitados, estru* estru){
  int* finales = NULL;
  int i, estado;
  int num_simbolos = AFNDNumSimbolos(afd);

  printf("Estados finaless\n");
  for (i = 0; i < n; i++){
    estado = visitados[i];
    if (AFNDTipoEstadoEn(afd, estado) == FINAL || AFNDTipoEstadoEn(afd, estado) == INICIAL_Y_FINAL){
      estados_fin ++;
      finales = realloc(finales, estados_fin*sizeof(int));
      finales[estados_fin-1] = estado;
    }
  }
  Distinguimos los estados finales
  matriz = marcar_finales(visitados, matriz, finales, n-1, estados_fin);

  Busqueda de equivalentes por transiciones
  matriz = marcar(afd, visitados, estru, n);

  free(finales);
  return matriz;
}*/

/* Marcamos como distinguibles todas las relaciones con el final */
int** marcar_finales(int* visitados, int** matriz, int* finales, int tam_matriz, int estados_fin){
  int i, j, indice;
  for (i = 0; i < estados_fin; i++){
    indice = finales[i];
    for (j = 0; j <= tam_matriz; j ++){
      if (indice < j ){
        matriz[j-1][indice] = 1;
        printf("ponemos un 1 en j=%d  en indice=%d\n", j, indice);
      }
      else if (j < indice){
        matriz[indice-1][j] = 1;
        printf("ponemos un 1 en indice=%d  en j=%d\n",indice, j);
      }
    }
  }

  for (i = 0; i < tam_matriz; i++){
    printf("\n");
    for (j = 0; j < tam_matriz; j++){
      printf("%d", matriz[i][j]);
    }
  }
  printf("\n");

  return matriz;
}

/*Marca el resto de estados distinguiendo en clases -- recursiva*/
estru* estados_equivalentes(AFND* afd, int* visitados, estru* estru){
  int i;
  int estado;
  int num_accesibles = get_num_accesibles(estru);

  /*Para cada estado comprobamos con pares si es equivalente con los siguientes a el*/
  for(i = 0; i < num_accesibles; i++){
    estado = visitados[i];
    estru = equivalentes(afd, estru, estado, i, visitados);
  }
  return estru;
}

estru* equivalentes(AFND* afd, estru* estru, int estado, int pos, int* visitados){
  int i, simbol, k;
  int estado1 = -1;
  int estado2 = -1;
  int num_simbolos = AFNDNumSimbolos(afd);
  int num_accesibles = get_num_accesibles(estru);
  par* par;

  /* Combinaciones de pares con los que cada estado se comprueba*/
  for(i = pos+1; i < num_accesibles; i++){
    par = buscar_par(estado, visitados[i], estru);
    if (par == NULL){
      par = ini_par(estado, visitados[i]);
      aniadir_par(estru, par);
    }
    /*Comprobamos si alguno de los dos es final y el otro no*/
    if(AFNDTipoEstadoEn(afd, estado) == FINAL || AFNDTipoEstadoEn(afd, estado) == INICIAL_Y_FINAL){
      if (AFNDTipoEstadoEn(afd, visitados[i]) != FINAL && AFNDTipoEstadoEn(afd, visitados[i]) != INICIAL_Y_FINAL){
          marcar(par, estru, pos, i, visitados);
      }
    }
    if(AFNDTipoEstadoEn(afd, visitados[i]) == FINAL || AFNDTipoEstadoEn(afd, visitados[i]) == INICIAL_Y_FINAL){
      if (AFNDTipoEstadoEn(afd, estado) != FINAL && AFNDTipoEstadoEn(afd, estado) != INICIAL_Y_FINAL){
          marcar(par, estru, pos, i, visitados);
      }
    }
    /* Con cada simbolo a que estado voy*/
    for(simbol = 0; simbol < num_simbolos; simbol++){
      /* Vemos a donde van cada uno de los estados de par con cada simbolo*/
      for (k = 0; k < n; k++){
        if(AFNDTransicionIndicesEstadoiSimboloEstadof(afd, estado, simbol, visitados[k])){
          estado1 = visitados[k];
        }
        if(AFNDTransicionIndicesEstadoiSimboloEstadof(afd, visitados[i], simbol, visitados[k])){
          estado2 = visitados[k];
        }
      }
      if(estado1 < estado2){
        pares_asociados(estru, par, estado1, estado2, pos, i, visitados);
      }else{
        pares_asociados(estru, par, estado2, estado1, pos, i, visitados);
      }
    }
  }
  return estru;
}


pares_asociados(estru* estru, par* par, int estado1, int estado2, int pos, int i, int* visitados){
  int num_accesibles = get_num_accesibles(estru);

  /* Si uno no tiene transicion y otro si*/
  if((estado1 == -1 && estado2 != -1) || (estado1 != -1 && estado2 == -1)){
    marcar(par, estru, pos, i, visitados);
  }
  /* Si el par asociado existe y no equivalente*/
  par_asoc = buscar_par(estado1, estado2, estru);
  if (par_asoc != NULL){
    /* Si el par asociado no es equivalente entonces tampoco el que llega a ellos*/
    if(get_equivalente(par_asoc) == 1){
        marcar(par, estru, pos, i, visitados);
    }else{
      /* si son equivalentes el que llega a ellos tambien, pero se une a su lista de dependencia, por si cambia la equivalencia*/
      aniadir_par_asociado(estru, par_asoc, par);
    }
  }else{
    /*Si no existe el par lo creo y añado a su lista de asociacion el par*/
    par_asoc = ini_par(estado1, estado2);
    aniadir_par(estru, par_asoc);
    aniadir_par_asociado(estru, par_asoc, par);
  }
}

marcar(par* par, estru* estru, int pos1, int pos2, int* visitados){
  int i,j, id1, id2, pos1, pos2;
  int num_accesibles = get_num_accesibles(estru);
  int num_asoc = get_n_asoc(par);
  par* asociado = (par*)malloc(sizeof(par));

  set_par_equivalente(estru, par, 1);
  marcar_matriz(estru, pos1, pos2);
  for(i = 0; i < num_asoc; i++){
    for(j = 0; j < num_accesibles; j++){
      asociado = get_asociados(par)[i];
      id1 = get_id1(asociado);
      id2 = get_id2(asociado);
      if(visitados[j] == id1){
        pos1 = j;
      }else if(visitados[j] == id2){
        pos2 = j;
      }
      marcar(estru, pos1, pos2, num_accesibles, visitados);
    }
  }

}
