#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "estructura.h"
#include "estado.h"

AFND * AFNDTransforma(AFND * afnd){
  char* nombre_est;
  int tipo_est;
  char* nombre_sim;

  if(!afnd){
    printf("No hay autómata.");
    return NULL;
  }
  int num_estados = AFNDNumEstados(afnd);
  int num_simbolos = AFNDNumSimbolos(afnd);

  estructura* estru = crear_estructura(num_estados, num_simbolos);
  //si queda muy feo hacemos un funcion
  //inicializa los estados y crea el array de todos los estados existentes
  for (int i = 0; i < num_estados; i++){
    nombre_est = AFNDNombreEstadoEn(afnd, i);
    tipo_est = AFNDTipoEstadoEn(AFND * p_afnd, i);
    if (tipo_est == INICIAL){
      strcpy(estru->estado_inicio, nombre_est);
    }
    else if (tipo_est == FINAL){
      strcpy(estru->estado_fin, nombre_est);
    }
    strcpy(estru->estados[i], nombre_est);
    estado* est = crear_estado(nombre_est, tipo_est, num_simbolos, num_estados);
  }
  //obtiene el array de simbolos existentes
  for (int i = 0; i < num_simbolos; i++){
    nombre_sim = AFNDSimboloEn(afnd, i);
    strcpy(estru->simbolos[i], nombre_sim);
  }

  char* estado_ini = AFNDNombreEstadoEn(afnd, 0);


  /*Trnasformar a un autómata determinista*/
}
