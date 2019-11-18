#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "estructura.h"
#include "estado.h"

AFND * AFNDTransforma(AFND * afnd){

  char* nombre_sim;

  if(!afnd){
    printf("No hay autómata.\n");
    return NULL;
  }
  int num_estados = AFNDNumEstados(afnd);
  int num_simbolos = AFNDNumSimbolos(afnd);

  estructura* estru = crear_estructura(num_estados, num_simbolos);
  //inicializa los estados y crea el array de todos los estados existentes
  introdudir_estados(num_estados, num_simbolos, afnd, estru);
  //crea el array de simbolos existentes
  introdudir_simbolos(num_simbolos, afnd);
  /*Transformar a un autómata determinista*/
  //Ver de cada estado a cual de los siguientes va y con que símbolo
  for(int i = 0; i < num_estados; i++){
    //crea la matriz de transiciones de estados
    estados_contiguos(i, num_estados, afnd);
  }
  //para terminar hay que crear un un automata nuevo con todo
  actualizar_automata(estru);
}

/*Saca los estados del autómata y los introduce en la estductura creada
Obteniendo tambien el estado inicial y el final*/
void introdudir_estados(int num_estados, int num_simbolos, AFND * afnd){
  char* nombre_est;
  int tipo_est;
  //Obtener el estado INICIAL
  int ini = AFNDIndiceEstadoInicial(afnd);
  nombre_est = AFNDNombreEstadoEn(afnd, ini);
  strcpy(estru->estado_inicio, nombre_est);
  //Obtener el estado FINAL
  //no se por que pone primer, lo mismo es por que hay mas, en este caso usamos el if del bucle
  int fin = AFNDIndicePrimerEstadoFinal(afnd);
  nombre_est = AFNDNombreEstadoEn(afnd, fin);
  strcpy(estru->estado_fin, nombre_est);

  for (int i = 0; i < num_estados; i++){
    nombre_est = AFNDNombreEstadoEn(afnd, i);
    tipo_est = AFNDTipoEstadoEn(afnd, i);
    /*if (tipo_est == INICIAL){
      strcpy(estru->estado_inicio, nombre_est);
    }
    else if (tipo_est == FINAL){
      strcpy(estru->estado_fin, nombre_est);
    }*/
    strcpy(estru->estados[i], nombre_est);
    estado* est = crear_estado(nombre_est, tipo_est, num_simbolos, num_estados);
  }
}

/*Saca mediante las funciones los símbolos admitidos por el autómata
 y lo introduce en la estructura*/
void introdudir_simbolos(int num_simbolos, AFND * afnd){
  for (int i = 0; i < num_simbolos; i++){
    nombre_sim = AFNDSimboloEn(afnd, i);
    strcpy(estru->simbolos[i], nombre_sim); //Funcion set
  }
}

/**/
void estados_contiguos(int estado, int num_estados, int num_simbolos, AFND * afnd){
  //metemos en casa struct de cada estado sus transiciones, dependiendo del simbolo
  for (int i = 0; i < num_estados; i++){
    //en caso de que exista transición
    if (AFNDLTransicionIJ(afnd, estado, i)){
      buscar_simbolo(afnd, estado, i, num_simbolos, num_estados);
    }
  }
}

//introducir en el estado las transiciones con sus simbolos y estados siguientes
//cuidado no he mirado que desde el propio estado tenfa transicion lambda a alguno...xq no sabria como meterlo en el array
void buscar_simbolo(AFND * afnd, int estado, int estado2, int num_simbolos, int num_estados){
  for(int i = 0; i < num_simbolos; i++){
    if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, estado, i, estado2)){
      //ponemos un 1 en el estado al que va con el simbolo indicado
      estado->transiciones[i][estado2]=1;
      //en caso de que del segundo estado vaya a otro con lambda este tambien se incluiria
      for(int j = 0; j < num_estados; j++){
        if(AFNDCierreLTransicionIJ(afnd, estado2, j)){
          estado->transiciones[i][j]=1;
        }
      }
    }
  }
}
