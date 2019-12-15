#include "par.h"

/*estructura para estado*/
struct _par{
  int id1;
  int id2;
  int n_asoc;
  par** asociados;
};

/*inicializando valores del estado*/
par* ini_par(int id1, int id2){
  if(id1 > id2) return NULL; // --> mjor ponerla en la otra
  par* par;
  par = (par*)malloc(sizeof(par));
  par->id1 = id1;
  par->id2 = id2;
  par->n_asoc = 0;
  par->asociados = NULL;

  if(!par) return NULL;

  return par;
}

/* añade un nuevo par a la lista de asociados */
void aniadir_asociado(par* par){
  if(!par) return NULL;
  par->n_asoc++;
  par->asociados = realloc(par->asociados, (par->n_asoc)*sizeof(par*));
  par->asociados[n_asoc-1] = par;
}

par** get_asociados(par* par){
  if(!par) return NULL;
  return par->asociados;
}

/*Elimina par de la lista de sociados*/
void eliminar_asociado(){

}

/*Elimina la estructura par*/
void eliminar_par(par* par){
  int i;
  for (i = 0; i < n_asoc; i++){
    free(par->asociados[i]);
  }
  free(par->asociados);
}
