#ifndef PAR_H
#define PAR_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

typedef struct _par par;

par* ini_par(int id1, int id2);
void aniadir_par(par* par);
par** get_asociados(par* par);

#endif
