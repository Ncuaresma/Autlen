#ifndef _ESTRU_H
#define _ESTRU_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "par.h"

typedef struct _estru estru;

estru* ini_estru(int num_accesibles);
void eliminar_estru(estru* estru_nueva);
void aniadir_par(estru* estru_nueva, par* par_nuevo);
par* buscar_par(int id1, int id2, estru* estru_nueva);
void set_par_equivalente(estru* estru_nueva, par* par_nuevo, int i);
void aniadir_par_asociado(estru* estru_nueva, par* yo, par* par_nuevo);
int get_num_accesibles(estru* estru_nueva);
void marcar_matriz(estru* estru_nueva, int pos1, int pos2);

#endif
