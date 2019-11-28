#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AFND * AFNDMinimiza(AFND * afd){
  int num_simbolos = AFNDNumSimbolos(afnd);
  int num_estados = AFNDNumEstados(afnd);
  int* vistos = (int*)malloc(num_estados*sizeof(int));
  int estado_ini = AFNDIndiceEstadoInicial(afd);
  int i;
  if(!afnd){
    printf("No hay autómata.\n");
    return NULL;
  }

  for (i = 0; i < num_estados; i++){
    vistos[i] = 0;
  }
  /*Buscamos los estados que necesitamos para el AFD mediante busqueda en anchura*/
  vistos = bfs(estado_ini, num_simbolos, num_estados, vistos, afnd);

  return NULL;
}

int* bfs(int estado, int num_simbolos, int num_estados, int* vistos, AFND* afd){
  int* trans;
  int i;
  trans = transiciones(estado, num_estados, num_simbolos, afd);
  vistos[estado] = 1;
  for(i = 0; i < num_estados; i++){
    if(trans[i]){
      estado = i;
      if(vistos[i] == 0){
        bfs(estado, num_simbolos, num_estados, vistos, afd);
      }
    }
  }
return vistos;
}

int* transiciones (int est, int num_estados, int num_simbolos, AFND* afd){
  int i, j;
  int* transiciones = (int*)malloc(num_estados*sizeof(int));
  for (i = 0; i<num_estados; i++){
    if (AFNDCierreLTransicionIJ(afd, est, i)){
      transiciones[i] = 1;
    }
    else{
      for (j = 0; j < num_simbolos; j++){
        if (AFNDTransicionIndicesEstadoiSimboloEstadof(afd, est, j, i)){
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
