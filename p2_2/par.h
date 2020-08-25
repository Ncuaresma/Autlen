#ifndef _PAR_H
#define _PAR_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

typedef struct _par par;

par* ini_par(int id1, int id2);
void aniadir_asociado(par* yo, par* par_nuevo);
int get_n_asoc(par* par_nuevo);
par** get_asociados(par* par_nuevo);
void eliminar_par(par* par_nuevo);
void set_equivalente(par* par_nuevo, int i);
int get_equivalente(par* par_nuevo);
int get_id1(par* par_nuevo);
int get_id2(par* par_nuevo);

#endif
