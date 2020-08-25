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
  par* par_nuevo;
  if (id1 < 0 || id2 < 0) return NULL;
  if(id1 > id2) return NULL;

  par_nuevo = (par*)malloc(sizeof(par));
  par_nuevo->id1 = id1;
  par_nuevo->id2 = id2;
  par_nuevo->n_asoc = 0;
  par_nuevo->asociados = NULL;
  par_nuevo->equivalente = 0;

  if(!par_nuevo) return NULL;

  return par_nuevo;
}

/* añade un nuevo par a la lista de asociados */
void aniadir_asociado(par* yo, par* par_nuevo){
  if(!par_nuevo || !yo) return;
  yo->n_asoc++;
  yo->asociados = realloc(yo->asociados, (yo->n_asoc)*sizeof(par*));
  yo->asociados[yo->n_asoc-1] = par_nuevo;
}

int get_n_asoc(par* par_nuevo){
  if (!par_nuevo) return -1;
  return par_nuevo->n_asoc;
}

par** get_asociados(par* par_nuevo){
  if(!par_nuevo) return NULL;
  return par_nuevo->asociados;
}

/*Elimina la estructura par*/
void eliminar_par(par* par_nuevo){
  int i;
  if (!par_nuevo || par_nuevo->asociados == NULL) return;
  for (i = 0; i < par_nuevo->n_asoc; i++){
    free(par_nuevo->asociados[i]);
  }
  free(par_nuevo->asociados);
}

void set_equivalente(par* par_nuevo, int i){
  if ((i != 0 && i != 1) ||!par_nuevo){
    return;
  }
  par_nuevo->equivalente = i;
}

int get_equivalente(par* par_nuevo){
  if (!par_nuevo) return -1;
  return par_nuevo->equivalente;
}

int get_id1(par* par_nuevo){
  if (!par_nuevo) return -1;
  return par_nuevo->id1;
}

int get_id2(par* par_nuevo){
  if (!par_nuevo) return -1;
  return par_nuevo->id2;
}
