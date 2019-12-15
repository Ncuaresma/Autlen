#include "par.h"

/*estructura para par*/
struct _par{
  int id1;
  int id2;
  int n_asoc;
  par** asociados;
  int equivalente;
};

/*inicializando valores del par*/
par* ini_par(int id1, int id2){
  if(id1 > id2) return NULL; // --> mjor ponerla en la otra
  par* par;
  par = (par*)malloc(sizeof(par));
  par->id1 = id1;
  par->id2 = id2;
  par->n_asoc = 0;
  par->asociados = NULL;
  par->equivalente = 0;

  if(!par) return NULL;

  return par;
}

/* añade un nuevo par a la lista de asociados */
void aniadir_asociado(par* yo, par* par){
  if(!par || !yo) return NULL;
  yo->n_asoc++;
  yo->asociados = realloc(yo->asociados, (yo->n_asoc)*sizeof(par*));
  yo->asociados[yo->n_asoc-1] = par;
}

int get_n_asoc(par* par){
  return par->n_asoc;
}

par** get_asociados(par* par){
  if(!par) return NULL;
  return par->asociados;
}

/*Elimina la estructura par*/
void eliminar_par(par* par){
  int i;
  for (i = 0; i < n_asoc; i++){
    free(par->asociados[i]);
  }
  free(par->asociados);
}

void set_equivalente(par* par, int i){
  if (i != 0 || i != 1){
    return;
  }
    par->equivalente = i;
}
int get_equivalente(par* par){
  return par->equivalente;
}

int get_id1(par* par){
  return par->id1;
}
int get_id2(par* par){
  return par->id2;
}
