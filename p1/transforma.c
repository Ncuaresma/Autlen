#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transforma.h"

AFND * AFNDTransforma(AFND * afnd){
  int num_estados_base;
  int num_simbolos;
  estructura* estru;

  if(!afnd){
    printf("No hay autómata.\n");
    return NULL;
  }

  num_simbolos = AFNDNumSimbolos(afnd);
  num_estados_base = AFNDNumEstados(afnd);

  estru = crear_estructura(num_simbolos, AFNDNumEstados(afnd));
  /*inicializa los estados y crea el array de todos los estados existentes*/
  introducir_estados(num_estados_base, num_simbolos, afnd, estru);
  /*crea el array de simbolos existentes*/
  introducir_simbolos(num_simbolos, afnd, estru);
  /*Transformar a un autómata determinista*/

  /*ver que el estado inicial tenga lambda y añadimos a la matriz el nuevo estado*/
  actualizar_ini(afnd, estru, num_simbolos, num_estados_base);

  /*Recorrer la matriz transicion y generar los estados nuevos combinados que hay*/
  /*meterlos en la matriz estos estados nuevos.*/

  /*estado_matriz(afnd, estru);*/
  
  /*y hacer esto hasta que todos los estados nuevos que se vayan generando esten creados(bucle de lo que ya hay)*/
  /*desde el nuevo estado inicial ir recorriendo la matriz y hacer transiciones indicadas a estados indicados*/
  /*si desde un estado vas a dos vas metiendo en una pila los estado que has descubiertop y luego los exploras ((EDYL))jeje*/
  /*se genera finalmee el automata nuevo*/

  /*para terminar hay que crear un un automata nuevo con todo*/
  /*actualizar_automata(estru);*/
  /*MIERDA QUE HAY QUE BORRAR*/
  funcion_probar(num_simbolos, afnd, estru);
  /*Devuelvo esto para probar lo de imprimir matriz, luego habra que devolver el afnd resultante*/
  return afnd;
}

/*Saca los estados del autómata y los introduce en la estductura creada
Obteniendo tambien el estado inicial y el final*/
void introducir_estados(int num_estados_base, int num_simbolos, AFND * afnd, estructura* estru){
  int i = 0;
  char* nombre_est;
  int tipo_est;
  estado* est;
  /*Obtener el estado INICIAL*/
  int ini;
  /*Obtener el estado FINAL*/
  /*no se por que pone primer, lo mismo es por que hay mas, en este caso usamos el if del bucle*/
  /*int fin = AFNDIndicePrimerEstadoFinal(afnd);
  nombre_est = AFNDNombreEstadoEn(afnd, fin);
  strcpy(get_estados_fin(estru)[0], nombre_est);*/


  for (i = 0; i < num_estados_base; i++){
    nombre_est = AFNDNombreEstadoEn(afnd, i);
    tipo_est = AFNDTipoEstadoEn(afnd, i);
    /*if (tipo_est == INICIAL){
      strcpy(estru->estado_inicio, nombre_est);
    }
    else*/
    /*Introducimos en la estructura todos los estados finales existentes*/
    est = crear_estado(nombre_est, tipo_est, num_simbolos, num_estados_base, i);
    if (tipo_est == FINAL){
      add_estado_fin(estru, est);
    }

    /*Ver de cada estado a cual de los siguientes va y con que símbolo*/
    /*crea la matriz de transiciones de estados*/
    estados_contiguos(est, num_estados_base, num_simbolos, afnd); /*---> no se si hacerlo antes o despues de añadir el estado*/
    /*Añadimos el nuevo estado a la estructura.*/
    add_estado(estru, est);


  }

  /*Obtenemos el estado inicial para meterlo en la struct*/
  ini = AFNDIndiceEstadoInicial(afnd);
  nombre_est = AFNDNombreEstadoEn(afnd, ini);
  est = get_estado_bynombre(estru, nombre_est);
  if(est){
    cambiar_estado_inicio(estru, est);
  }
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
void estados_contiguos(estado* estado, int num_estados_base, int num_simbolos, AFND * afnd){
  int i = 0;
  /*metemos en casa struct de cada estado sus transiciones, dependiendo del simbolo*/
  for (i = 0; i < num_estados_base; i++){
    /*en caso de que exista transición*/
    buscar_simbolo(afnd, estado, i, num_simbolos, num_estados_base);
  }
}

void estados_contiguos_generados(estructura* estru, estado* estado, int num_simbolos, AFND * afnd){
  int* cod;
  int** trans;
  int i, j, k;
  int num_estados_base = get_num_estados_base(estru);
  cod = (int*)malloc(num_estados_base*(sizeof(int)));
  trans = (int **)malloc(num_simbolos*sizeof(int*));
  if(!estado) return;
  cod = get_codificacion(estado);
  /*metemos en casa struct de cada estado sus transiciones, dependiendo del simbolo*/
  for (i = 0; i < num_estados_base; i++){
    /*Paca cada estado que esta en el estado combinado*/
    if(cod[i]){
      trans = get_transciones(get_estado_pos(estru, i));
      for(j = 0; j < num_simbolos; j++){
        for(k = 0; k < num_estados_base; k++){
          /*añadimos la transicion indicada.*/
          if (trans[j][k]){
            annadir_trans(estado, k, j);
          }
        }
      }
    }
  }
}

/*introducir en el estado las transiciones con sus simbolos y estados siguientes*/
/*cuidado no he mirado que desde el propio estado tenfa transicion lambda a alguno...xq no sabria como meterlo en el array*/
void buscar_simbolo(AFND * afnd, estado* estado, int n_estado2, int num_simbolos, int num_estados_base){
  int i,j = 0;
  int id_e = get_id(estado);
  if(id_e == -1){
    return;
  }
  for (i = 0; i < num_simbolos; i++){
    if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, id_e, i, n_estado2)){
      printf("\nestado1: %d estado2: %d simbolo: %d\n",id_e, n_estado2, i );
      /*añadimos la transicion indicada.*/
      annadir_trans(estado, n_estado2, i);
      /*en caso de que del segundo estado vaya a otro con lambda este tambien se incluiria*/
      /*no cubrimos el caso de que se vaya a dos encadenados con lambda*/
      for (j = 0; j < num_estados_base; j++){
        if(n_estado2 != j){
          if(AFNDCierreLTransicionIJ(afnd, n_estado2, j)){
            annadir_trans(estado, j, i);
          }
        }
      }
    }
  }
}

/*ver que el estado inicial tenga lambda y añadimos a la matriz el nuevo estado*/
void actualizar_ini(AFND * afnd, estructura* estru, int num_simbolos, int num_estados_base){
  int i;
  estado* est;
  int* codificacion;
  char* nombre = (char*)malloc(num_estados_base*sizeof(char));
  int n_est;
  int id = get_num_estados(estru);
  int tipo = INICIAL;
  est = get_estado_inicio(estru);
  n_est = get_id(est);
  codificacion = get_codificacion(est);
  strcpy(nombre,"");

  for (i = 0; i < num_estados_base; i++){
    if(AFNDCierreLTransicionIJ(afnd, n_est, i)){
      if (strcmp(nombre, AFNDNombreEstadoEn(afnd, i))!=0){
        strcat(nombre, AFNDNombreEstadoEn(afnd, i));
        codificacion[i] = 1;

        if(AFNDTipoEstadoEn(afnd, i) == FINAL || AFNDTipoEstadoEn(afnd, i) == INICIAL_Y_FINAL){
          tipo = INICIAL_Y_FINAL;
        }
      }
    }
  }
  est = crear_estado_combinado(nombre, tipo, num_simbolos, num_estados_base, id, codificacion);
  if (tipo == INICIAL_Y_FINAL){
    add_estado_fin(estru, est);
  }
  estados_contiguos_generados(estru, est, num_simbolos, afnd);/*Añadimos el nuevo estado a la estructura.*/
  add_estado(estru, est);
  free(nombre);
}

char* obtener_nombre(AFND * afnd, int* cod, int num_estados_base){
  int i;
  char* nombre = (char*)malloc(num_estados_base*sizeof(char));
  strcpy(nombre,"");
  for (i = 0; i < num_estados_base; i++){
    if(cod[i]){
      strcat(nombre, AFNDNombreEstadoEn(afnd, i));
    }
  }
  return nombre;
}

int estado_fin(int* codificacion, estructura* estru){
  int i, j;
  int num_estados_base = get_num_estados_base(estru);
  int num_finales = get_num_finales(estru);
  for(i = 0; i < num_estados_base; i++){
    if(codificacion[i]){
      for(j = 0; j < num_finales; j++){
        if(i == get_id(get_estados_fin(estru)[j])){
          return 1;
        }
      }
    }
  }
  return 0;
}



int estado_existente(char* nombre, estructura* estru){
  int i;
  int num_estados = get_num_estados(estru);
  for (i = 0; i < num_estados; i++){
    if(strcmp(nombre, get_nombre(get_estado_pos(estru, i))) == 0){
      return 1;
    }
  }
  return 0;
}

/*ver que el estado inicial tenga lambda y añadimos a la matriz el nuevo estado*/
void estado_matriz(AFND * afnd, estructura* estru){
  int i,j;
  int num_estados = get_num_estados(estru);
  int num_simbolos = get_num_simbolos(estru);
  int num_estados_base = get_num_estados_base(estru);
  estado* est;
  int** trans;
  char* nombre = (char*)malloc(MAX_CHAR*sizeof(char));
  int id = get_num_estados(estru);
  int tipo = NORMAL;

  est = ini_estado(num_simbolos, num_estados_base);

  trans = (int**)malloc(num_simbolos*(sizeof(int*)));
  for (i=0;i<num_simbolos;i++){
        trans[i] = (int*)malloc(num_estados_base*sizeof(int));
  }

  for (i = 0; i < num_estados; i++){
    tipo = NORMAL;
    est = get_estado_pos(estru, i);
    trans = get_transciones(est);
    for (j = 0; j < num_simbolos; j++){
      nombre = obtener_nombre(afnd, trans[j], num_estados_base);
      if(nombre){
        if(!estado_existente(nombre, estru)){
          if(estado_fin(trans[j], estru)){
            tipo = FINAL;
          }
          est = crear_estado_combinado(nombre, tipo, num_simbolos, num_estados_base, id, trans[j]);
          if(tipo == FINAL){
            add_estado_fin(estru, est);
          }
          estados_contiguos_generados(estru, est, num_simbolos, afnd);/*Añadimos el nuevo estado a la estructura.*/
          add_estado(estru, est);
          id = get_num_estados(estru);
        }
      }
    }
  }
  for (i=0;i<num_simbolos;i++){
        free(trans[i]);
  }
}



void funcion_probar(int num_simbolos, AFND* afnd, estructura* estru){
  int i,j,k = 0;
  int num_estados_base=get_num_estados_base(estru);
  int num_estados=get_num_estados(estru);
  int* ag = (int*) malloc(num_estados*sizeof(int));
  for (i = 0; i < num_estados; i++){
    estado* estadito = get_estado_pos(estru, i);
    printf("\n%d:\n", get_id(estadito));
    for (j = 0; j < num_simbolos; j++){
      ag = get_transicion_simbolo(estadito, j);
      for (k = 0; k < num_estados_base ; k++){
        printf("%d", ag[k]);
      }
      printf("\n");
    }
  }
  free(ag);
}

/*void funcion_probar(int num_estados_base, int num_simbolos, AFND* afnd, estructura* estru){
  int i,j,k = 0;
  int** ag;
  ag = (int**)malloc(num_simbolos*sizeof(int*));
  for (i = 0; i < num_estados_base; i++){
    estado* estadito = get_estado_pos(estru, i);
    printf("%d:\n", get_id(estadito));
    for (j = 0; j < num_simbolos; j++){
      ag[j] = (int*)malloc(num_estados_base*sizeof(int));
    }
    ag = get_transciones(estadito);
    for (j = 0; j < num_simbolos; j++){
      for (k = 0; k < num_estados_base; k++){
        printf("%d\n", ag[j][k]);
      }
      printf("\n");
    }
  }
}*/
