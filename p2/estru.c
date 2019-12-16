#include "estru.h"

/*estructura para estado*/
struct _estru{
  int** matriz;
  par** pares;
  int num_pares;
  int num_accesibles; /*tam matriz+1*/
};

estru* ini_estru(int num_accesibles){
  int i,j;
  estru* estru_nueva;
  int** matriz = (int **)malloc((num_accesibles-1)*sizeof(int*));
  estru_nueva = (estru*)malloc(sizeof(estru));

  for (i = 0; i < (num_accesibles-1); i++){
    matriz[i] = (int *)malloc((num_accesibles-1)*sizeof(int));
    for (j = 0; j < num_accesibles-1; j++){
      matriz[i][j] = 0;
    }
  }

  estru_nueva->matriz = matriz;
  estru_nueva->pares = NULL;
  estru_nueva->num_pares = 0;
  estru_nueva->num_accesibles = num_accesibles;
  return estru_nueva;
}

void eliminar_estru(estru* estru_nueva){
  int i;
  if (!estru_nueva) return;
  for (i = 0; i < (estru_nueva->num_accesibles-1); i++){
    free(estru_nueva->matriz[i]);
  }
  free(estru_nueva->matriz);
  for(i = 0; i < estru_nueva->num_pares; i++){
    free(estru_nueva->pares[i]);
  }
  free(estru_nueva->pares);
}

/* añade un nuevo par a la lista de pares*/
void aniadir_par(estru* estru_nueva, par* par_nuevo){
  if(!par_nuevo || !estru_nueva) return;
  estru_nueva->num_pares++;
  estru_nueva->pares = realloc(estru_nueva->pares, (estru_nueva->num_pares)*sizeof(par*));
  estru_nueva->pares[estru_nueva->num_pares-1] = par_nuevo;
}

par* buscar_par(int id1, int id2, estru* estru_nueva){
  int i;
  if (!estru_nueva || id1 < 0 || id2 < 0) return NULL;
  for(i = 0; i < estru_nueva->num_pares; i++){
    if(id1 == get_id1(estru_nueva->pares[i]) && id2 == get_id2(estru_nueva->pares[i])){
      return estru_nueva->pares[i];
    }
  }
  return NULL;
}

void set_par_equivalente(estru* estru_nueva, par* par_nuevo, int equiv){
  int i;
  if (!estru_nueva || !par_nuevo) return;
  for(i = 0; i < estru_nueva->num_pares; i++){
    if(estru_nueva->pares[i] == par_nuevo){
      set_equivalente(estru_nueva->pares[i], equiv);
    }
  }
}

void aniadir_par_asociado(estru* estru_nueva, par* yo, par* par_nuevo){
  int i;
  if (!estru_nueva || !yo || !par_nuevo) return;
  for(i = 0; i < estru_nueva->num_pares; i++){
    if(estru_nueva->pares[i] == yo){
      aniadir_asociado(estru_nueva->pares[i], par_nuevo);
    }
  }
}

int get_num_accesibles(estru* estru_nueva){
  if (!estru_nueva) return -1;
  return estru_nueva->num_accesibles;
}

void marcar_matriz(estru* estru_nueva, int pos1, int pos2){
  if (!estru_nueva) return;
  estru_nueva->matriz[pos2-1][pos1] = 1;
}
