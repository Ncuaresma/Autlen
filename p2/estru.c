#include "estru.h"

/*estructura para estado*/
struct _estru{
  int** matriz
  par** pares;
  int num_pares;
  int num_accesibles; /*tam matriz+1*/
};

estru* ini_estru(int num_accesibles){
  estru* estru;
  int i,j;
  int** matriz = (int **)malloc((num_accesibles-1)*sizeof(int*));
  estru = (estru*)malloc(sizeof(estru));

  for (i = 0; i < (num_accesibles-1); i++){
    matriz[i] = (int *)malloc((num_accesibles-1)*sizeof(int));
    for (j = 0; j < num_accesibles-1; j++){
      matriz[i][j] = 0;
    }
  }

  estru->matriz = matriz;
  estru->pares = NULL;
  estru->num_pares = 0;
  estru->num_accesibles = num_accesibles;
  return estru;
}

void eliminar_estru(estru* estru){
  int i;
  for (i = 0; i < (num_accesibles-1); i++){
    free(estru->matriz[i]);
  }
  free(estru->matriz);
  for(i = 0; i < estru->num_pares; i++){
    free(estru->pares[i]);
  }
  free(estru->pares);
}

/* añade un nuevo par a la lista de pares*/
void aniadir_par(estru* estru, par* par){
  if(!par || !estru) return NULL;
  estru->num_pares++;
  estru->pares = realloc(estru->pares, (estru->num_pares)*sizeof(par*));
  estru->pares[estru->num_pares-1] = par;
}

par* buscar_par(int id1, int id2, estru* estru){
  int i;
  int id1;
  int id2;

  for(i = 0; i < estru->num_pares, i++){
    if(id1 == get_id1(estru->pares[i]) && id2 == get_id2(estru->pares[i])){
      return estru->pares[i];
    }
  }
  return NULL;
}

void set_par_equivalente(estru* estru, par* par, int i){
  int i;
  for(i = 0; i < estr->num_pares; i++){
    if(estru->pares[i] == par){
      set_equivalente(estru->pares[i], i);
    }
  }
}

void aniadir_par_asociado(estru* estru, par* yo, par* par){
  int i;
  for(i = 0; i < estru->num_pares; i++){
    if(estru->pares[i] == yo){
      aniadir_asociado(estru->pares[i], par);
    }
  }
}

int get_num_accesibles(estru* estru){
  return estru->num_accesibles;
}

void marcar_matriz(estru* estru, int pos1, int pos2){
  estru->matrz[pos2-1][pos1] = 1;
}
