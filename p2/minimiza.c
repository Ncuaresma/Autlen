
#include "minimiza.h"

AFND * AFNDMinimiza(AFND * afnd){
  int num_simbolos = AFNDNumSimbolos(afnd);
  int num_estados = AFNDNumEstados(afnd);
  int* vistos = (int*)malloc(num_estados*sizeof(int));
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
    }
  }
  printf("\nHay %d estados accesibles de %d\n", n, num_estados);

  /*Inicializamos la matriz con todos los valores a cero (solo con estados accesibles)*/
  matriz = ini_matriz(n);

  /*Cargamos la matriz con el algoritmo propuesto en clase*/

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
      if(vistos[i] == 0){
        bfs(estado, num_simbolos, num_estados, vistos, afnd);
      }
    }
  }
return vistos;
}

int* transiciones (int est, int num_estados, int num_simbolos, AFND* afnd){
  int i, j;
  int* transiciones = (int*)malloc(num_estados*sizeof(int));
  for (i = 0; i<num_estados; i++){
    if (AFNDCierreLTransicionIJ(afnd, est, i)){
      transiciones[i] = 1;
    }
    else{
      for (j = 0; j < num_simbolos; j++){
        if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, est, j, i)){
          transiciones[i] = 1;
        }
        else{
          transiciones[i] = 0;
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
    matriz[i] = (int *)malloc(n*sizeof(int));
    for (j = 0; j < n; j++){
      matriz[i][j] = 0;
    }
  }
  return matriz;
}
