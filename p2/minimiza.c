
#include "minimiza.h"

AFND * AFNDMinimiza(AFND* afnd){
  int num_simbolos = AFNDNumSimbolos(afnd);
  int num_estados = AFNDNumEstados(afnd);
  int* vistos = (int*)malloc(num_estados*sizeof(int));
  int* visitados = NULL;
  int estado_ini = AFNDIndiceEstadoInicial(afnd);
  int i;
  int n = 0;
  int** matriz;
  if(!afnd){
    printf("No hay autómata.\n");
    return NULL;
  }

  for (i = 0; i < num_estados; i++){
    vistos[i] = 0;
  }

  /*Buscamos los estados que necesitamos para el AFD mediante busqueda en anchura*/
  vistos = bfs(estado_ini, num_simbolos, num_estados, vistos, afnd);
  printf("\nVistosss\n");
  for (i = 0; i < num_estados; i++){
    printf("%d ", vistos[i]);
    if (vistos[i] == 1){
      n++;
      visitados = realloc(visitados, n*sizeof(int));
      visitados[n-1] = i;
    }
  }
  printf("\nHay %d estados accesibles de %d\n", n, num_estados);

  /*Inicializamos la matriz con todos los valores a cero (solo con estados accesibles)*/
  matriz = ini_matriz(n);

  /*Cargamos la matriz con el algoritmo propuesto en clase*/
  matriz = estados_equivalentes(visitados, afnd, matriz, n);

  /*Liberamos memoria final*/
  free(vistos);
  free(visitados);
  for (i = 0; i < (n-1); i++){
    free(matriz[i]);
  }
  free(matriz);
  return NULL;
}

int* bfs(int estado, int num_simbolos, int num_estados, int* vistos, AFND* afnd){
  int* trans;
  int i;
  trans = transiciones(estado, num_estados, num_simbolos, afnd);
  vistos[estado] = 1;
  for(i = 0; i < num_estados; i++){
    if(trans[i]){
      estado = i;
      if(vistos[estado] == 0){
        vistos = bfs(estado, num_simbolos, num_estados, vistos, afnd);
      }
    }
  }
  free(trans);
  return vistos;
}

int* transiciones (int est, int num_estados, int num_simbolos, AFND* afnd){
  int i, j;
  int* transiciones = (int*)malloc(num_estados*sizeof(int));
  for (i = 0; i < num_estados; i++){
    transiciones[i] = 0;
    if (AFNDCierreLTransicionIJ(afnd, est, i)){
      transiciones[i] = 1;
    }
    else{
      for (j = 0; j < num_simbolos; j++){
        if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, est, j, i)){
          transiciones[i] = 1;
        }
      }
    }
  }
  return transiciones;
}

int** ini_matriz(int n){
  int i,j;
  int** matriz = (int **)malloc((n-1)*sizeof(int*));
  for (i = 0; i < (n-1); i++){
    matriz[i] = (int *)malloc((n-1)*sizeof(int));
    for (j = 0; j < n-1; j++){
      matriz[i][j] = 0;
    }
  }
  return matriz;
}

/* Marca los estados no equivalentes en la matriz*/
int** estados_equivalentes(int* visitados, AFND* afnd, int** matriz, int n){
  int* finales = NULL;
  int i, estado;
  int estados_fin = 0;

  printf("Estados finaless\n");
  for (i = 0; i < n; i++){
    estado = visitados[i];
    if (AFNDTipoEstadoEn(afnd, estado) == FINAL || AFNDTipoEstadoEn(afnd, estado) == INICIAL_Y_FINAL){
      estados_fin ++;
      finales = realloc(finales, estados_fin*sizeof(int));
      finales[estados_fin-1] = estado;
    }
  }
  /*Distinguimos los estados finales*/
  matriz = marcar_finales(visitados, matriz, finales, n-1, estados_fin);

  /*Busqueda de equivalentes por transiciones*/
  for (i = 0; i < estados_fin; i++){
    matriz = marcar(visitados, matriz, n, i);
  }

  free(finales);
  return matriz;
}

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
int** marcar(int* visitados, int** matriz, int n){

}
