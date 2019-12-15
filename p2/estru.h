#ifndef ESTRU_H
#define ESTRU_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "par.h"

typedef struct _estru estru;

estru* ini_estru(int num_accesibles);
void eliminar_estru(estru* estru);
void aniadir_par(estru* estru, par* par);
par* buscar_par(int id1, int id2, estru* estru);
void set_par_equivalente(estru* estru, par* par, int i);
void aniadir_par_asociado(estru* estru, par* yo, par* par);
int get_num_accesibles(estru* estru);
void marcar_matriz(estru* estru, int pos1, int pos2);

#endif
