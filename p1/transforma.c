#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transforma.h"

AFND * AFNDTransforma(AFND * afnd){
  int num_estados;
  int num_simbolos;
  estructura* estru;

  if(!afnd){
    printf("No hay autómata.\n");
    return NULL;
  }

  num_simbolos = AFNDNumSimbolos(afnd);
  num_estados = AFNDNumEstados(afnd);

   estru = crear_estructura(num_simbolos);
  /*inicializa los estados y crea el array de todos los estados existentes*/
  introducir_estados(num_estados, num_simbolos, afnd, estru);
  /*crea el array de simbolos existentes*/
  introducir_simbolos(num_simbolos, afnd, estru);
  /*Transformar a un autómata determinista*/

  /*para terminar hay que crear un un automata nuevo con todo*/
  /*actualizar_automata(estru);*/
  /*MIERDA QUE HAY QUE BORRAR*/
  funcion_probar(num_estados, num_simbolos, afnd, estru);
  /*Devuelvo esto para probar lo de imprimir matriz, luego habra que devolver el afnd resultante*/
  return afnd;
}

/*Saca los estados del autómata y los introduce en la estductura creada
Obteniendo tambien el estado inicial y el final*/
void introducir_estados(int num_estados, int num_simbolos, AFND * afnd, estructura* estru){
  int i = 0;
  char* nombre_est;
  int tipo_est;
  int n_finales = 0;
  estado* est;
  /*Obtener el estado INICIAL*/
  int ini = AFNDIndiceEstadoInicial(afnd);
  nombre_est = AFNDNombreEstadoEn(afnd, ini);
  strcpy(get_estado_inicio(estru), nombre_est);
  /*Obtener el estado FINAL*/
  /*no se por que pone primer, lo mismo es por que hay mas, en este caso usamos el if del bucle*/
  /*int fin = AFNDIndicePrimerEstadoFinal(afnd);
  nombre_est = AFNDNombreEstadoEn(afnd, fin);
  strcpy(get_estados_fin(estru)[0], nombre_est);*/

  for (i = 0; i < num_estados; i++){
    nombre_est = AFNDNombreEstadoEn(afnd, i);
    tipo_est = AFNDTipoEstadoEn(afnd, i);
    /*if (tipo_est == INICIAL){
      strcpy(estru->estado_inicio, nombre_est);
    }
    else*/
    /*Introducimos en la estructura todos los estados finales existentes*/
    if (tipo_est == FINAL){
      strcpy(get_estados_fin(estru)[n_finales], nombre_est);
      n_finales++;
    }
    est = crear_estado(nombre_est, tipo_est, num_simbolos, num_estados, i);
    /*Ver de cada estado a cual de los siguientes va y con que símbolo*/
    /*crea la matriz de transiciones de estados*/
    estados_contiguos(est, num_estados, num_simbolos, afnd); /*---> no se si hacerlo antes o despues de añadir el estado*/
    /*Añadimos el nuevo estado a la estructura.*/
    add_estado(estru, est);
    /*TOCHACO ASQUEROSO QUE HAY QUE BORRAR*/
    eliminar_estado(est);
  }
  /*no se si aqui o en la de transformar (arriba)*/
  /*ver que el estado inicial tenga lambda y añadimos a la matriz el nuevo estado*/
  /*Recorrer la matriz transicion y generar los estados nuevos combinados que hay*/
  /*meterlos en la matriz estos estados nuevos.*/
  /*y hacer esto hasta que todos los estados nuevos que se vayan generando esten creados(bucle de lo que ya hay)*/
  /*desde el nuevo estado inicial ir recorriendo la matriz y hacer transiciones indicadas a estados indicados*/
  /*si desde un estado vas a dos vas metiendo en una pila los estado que has descubiertop y luego los exploras ((EDYL))jeje*/
  /*se genera finalmee el automata nuevo*/
}

/*Saca mediante las funciones los símbolos admitidos por el autómata
 y lo introduce en la estructura*/
void introducir_simbolos(int num_simbolos, AFND * afnd, estructura* estru){
  int i = 0;
  char* nombre_sim;
  for (i = 0; i < num_simbolos; i++){
    nombre_sim = AFNDSimboloEn(afnd, i);
    add_simbolo(estru, nombre_sim);
  }
}

/**/
void estados_contiguos(estado* estado, int num_estados, int num_simbolos, AFND * afnd){
  int i = 0;
  /*metemos en casa struct de cada estado sus transiciones, dependiendo del simbolo*/
  for (i = 0; i < num_estados; i++){
    /*en caso de que exista transición*/
    if (AFNDLTransicionIJ(afnd, get_id(estado), i)){
      buscar_simbolo(afnd, estado, i, num_simbolos, num_estados);
    }
  }
}

/*introducir en el estado las transiciones con sus simbolos y estados siguientes*/
/*cuidado no he mirado que desde el propio estado tenfa transicion lambda a alguno...xq no sabria como meterlo en el array*/
void buscar_simbolo(AFND * afnd, estado* estado, int n_estado2, int num_simbolos, int num_estados){
  int i,j = 0;
  int id_e = get_id(estado);
  for (i = 0; i < num_simbolos; i++){
    if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, id_e, i, n_estado2)){
      /*añadimos la transicion indicada.*/
      annadir_trans(estado, n_estado2, i);
      /*en caso de que del segundo estado vaya a otro con lambda este tambien se incluiria*/
      /*no cubrimos el caso de que se vaya a dos encadenados con lambda*/
      for (j = 0; j < num_estados; j++){
        if(AFNDCierreLTransicionIJ(afnd, n_estado2, j)){
          annadir_trans(estado, j, i);
        }
      }
    }
  }
}

void funcion_probar(int num_estados, int num_simbolos, AFND* afnd, estructura* estru){
  int i,j,k = 0;
  for (i = 0; i < num_estados; i++){
    estado* estadito = get_estado_pos(estru, i);
    printf("%s:\n", get_nombre(estadito));
    for (j = 0; j < num_simbolos; j++){
      int* ag = get_transicion_simbolo(estadito, j);
      for (k = 0; k < num_estados; k++){
        printf("%d\n", ag[k]);
      }
      printf("\n");
    }
  }
}
