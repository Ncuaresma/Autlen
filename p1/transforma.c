#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AFND * AFNDTransforma(AFND * afnd){
  if(!afnd){
    printf("No hay autómata.");
    return NULL;
  }
  int estados = AFNDNumEstados(afnd);
  int simbolos = AFNDNumSimbolos(afnd);

  
  /*Trnasformar a un autómata determinista*/
}
