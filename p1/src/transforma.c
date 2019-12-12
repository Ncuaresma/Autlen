#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transforma.h"

AFND * AFNDTransforma(AFND * afnd){
  int num_estados_base;
  int num_simbolos;
  estructura* estru;
  int num_estados;
  estado** estados_afd;
  AFND * afd;
  int i;
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
  num_estados = get_num_estados(estru);
  for (i = 0; i < num_estados; i++){
    estado_matriz(afnd, estru, i);
    /* el numero de estados que tenemos ahora, por si ha añadido alguno mas*/
    num_estados = get_num_estados(estru);
  }
  /*Buscamos los estados que necesitamos para el AFD mediante busqueda en anchura*/
  estados_afd = visitados(estru, afnd);
  /*Crear un un automata nuevo determinista*/
  afd = actualizar_afnd(afnd, estru, estados_afd);
  /*Devuelvo esto para probar lo de imprimir matriz, luego habra que devolver el afnd resultante*/
  eliminar_estructura(estru);
  return afd;
}

/*Saca los estados del autómata y los introduce en la estductura creada
Obteniendo tambien el estado inicial y el final*/
void introducir_estados(int num_estados_base, int num_simbolos, AFND * afnd, estructura* estru){
  int i = 0;
  char* nombre_est;
  int tipo_est;
  estado* est;
  int ini;

  for (i = 0; i < num_estados_base; i++){
    nombre_est = AFNDNombreEstadoEn(afnd, i);
    tipo_est = AFNDTipoEstadoEn(afnd, i);

    /*Introducimos en la estructura todos los estados finales existentes*/
    est = crear_estado(nombre_est, tipo_est, num_simbolos, num_estados_base, i);
    if (tipo_est == FINAL || tipo_est == INICIAL_Y_FINAL){
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

/*Ver de cada estado a cual de los siguientes va y con que símbolo*/
/*crea la matriz de transiciones de estados*/
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
  char* nombre = (char*)malloc(MAX_CHAR*sizeof(char));
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
  cambiar_estado_inicio(estru, est);
  estados_contiguos_generados(estru, est, num_simbolos, afnd);/*Añadimos el nuevo estado a la estructura.*/
  add_estado(estru, est);
  free(nombre);
}

char* obtener_nombre(AFND * afnd, int* cod, int num_estados_base){
  int i;
  char* nombre = (char*)malloc(MAX_CHAR*sizeof(char));
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
void estado_matriz(AFND * afnd, estructura* estru, int n_estado){
  int i;
  int num_simbolos = get_num_simbolos(estru);
  int num_estados_base = get_num_estados_base(estru);
  estado* est;
  int** trans;
  char* nombre = (char*)malloc(MAX_CHAR*sizeof(char));
  int id = get_num_estados(estru);
  int tipo = NORMAL;

  est = get_estado_pos(estru, n_estado);
  /*Obtenemos las transiciones de ese estado para ver si va a algun estado nuevo*/
  trans = get_transciones(est);
  for (i = 0; i < num_simbolos; i++){
    /*Creamos el nombre para ese estado para ver si existe*/
    strcpy(nombre, "");
    nombre = obtener_nombre(afnd, trans[i], num_estados_base);
    if(nombre != NULL){
      if(!estado_existente(nombre, estru)){
        if(estado_fin(trans[i], estru)){
          tipo = FINAL;
        }
        est = crear_estado_combinado(nombre, tipo, num_simbolos, num_estados_base, id, trans[i]);
        if(tipo == FINAL || tipo == INICIAL_Y_FINAL){
          add_estado_fin(estru, est);
        }
        estados_contiguos_generados(estru, est, num_simbolos, afnd);/*Añadimos el nuevo estado a la estructura.*/
        add_estado(estru, est);
        /*Actualizamos el id*/
        id = get_num_estados(estru);
        free(nombre);
      }
    }
  }
}


estado** visitados(estructura *estru, AFND* afnd){
  estado* estado_ini_fin=get_estado_inicio(estru);
  int i;
  int pos = 0;
  int num_estados = get_num_estados(estru);
  int* vistos = (int*)malloc(num_estados*sizeof(int));
  estado** vecino = (estado**)malloc(num_estados*sizeof(estado*));
  for (i = 0; i < num_estados; i++){
    vistos[i] = 0;
  }
  vistos = bfs(estado_ini_fin, vistos, afnd, estru);
  for(i = 0; i < num_estados; i++){
    if(vistos[i]){
      vecino[pos] = get_estado_pos(estru, i);
      pos++;
    }
  }
  vecino[pos] = NULL;
  return vecino;
}

int* bfs(estado* est, int* vistos, AFND* afnd, estructura* estru){
  int** trans;
  int i;
  int num_simbolos = AFNDNumSimbolos(afnd);
  int num_estados_base = AFNDNumEstados(afnd);
  estado* vecino=ini_estado(num_estados_base,num_simbolos);
  trans = get_transciones(est);
  vistos[get_id(est)] = 1;
  for(i = 0; i < num_simbolos; i++){
    if(strcmp("", obtener_nombre(afnd, trans[i], num_estados_base)) != 0){
      vecino = get_estado_bynombre(estru, obtener_nombre(afnd, trans[i], num_estados_base));
      if(vecino){
        if(vistos[get_id(vecino)] == 0){
          bfs(vecino, vistos,  afnd, estru);
        }
      }
    }
  }
return vistos;
}

AFND* actualizar_afnd(AFND* afnd, estructura *estru, estado** visitados){
  AFND * afd;
  char* nombre = (char*)malloc(MAX_CHAR*sizeof(char));
  int** trans;
  int num_visitados = 0;
  int num_simbolos = get_num_simbolos(estru);
  int i, j;
  while (visitados[num_visitados] != NULL){
    num_visitados++;
  }
  /*Creamos el automata*/
  afd = AFNDNuevo("afd_p1", num_visitados, num_simbolos);
  /*Insertamos estados*/
  for(i = 0; i < num_visitados; i++){
    AFNDInsertaEstado(afd, get_nombre(visitados[i]), get_tipo(visitados[i]));
  }
  /*Insertamos simbolos*/
  for(i = 0; i < num_simbolos; i++){
    /*Obtenemos los símbolos del autómata no determinista*/
    AFNDInsertaSimbolo(afd, AFNDSimboloEn(afnd, i));
  }

  /*Insertar las transiciones entre los estados*/
  for(i = 0; i < num_visitados; i++){
    trans = get_transciones(visitados[i]);
    for(j = 0; j < num_simbolos; j++){
      nombre = obtener_nombre(afnd, trans[j], get_num_estados_base(estru));
      if(strcmp(nombre,"")!=0){
        AFNDInsertaTransicion(afd, get_nombre(visitados[i]),AFNDSimboloEn(afnd,j), nombre);
      }
    }
  }
  free(nombre);
  return afd;
}
