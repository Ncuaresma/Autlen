#ifndef _MINIMIZA_H
#define _MINIMIZA_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "afnd.h"
#include "par.h"
#include "estado.h"
#include "estru.h"

#define MAX_CHAR 300

AFND * AFNDMinimiza(AFND * afd);
int* bfs(int estado, int num_simbolos, int num_estados, int* vistos, AFND* afd);
int* transiciones (int est, int num_estados, int num_simbolos, AFND* afd);
void imprimir_matriz(estru* estru_nueva);
/*int** ini_matriz(int n);*/
estru* estados_equivalentes(AFND* afd, int* visitados, estru* estru);
estru* equivalentes(AFND* afd, estru* estru_nueva, int estado, int pos, int* visitados);
void pares_asociados(estru* estru_nueva, par* par_nuevo, int estado1, int estado2, int pos, int i, int* visitados);
int** marcar_finales(int* visitados, int** matriz, int* finales, int n, int estados_fin);
void marcar(par* par_nuevo, estru* estru_nueva, int pos1, int pos2, int* visitados);
void nuevos_estados(estru* estru_nueva, AFND* afd, int* visitados);
void aniadir_trasicion(estado* state_nuevo, AFND* afnd, int estado, int num_estados, int num_simbolos);
#endif
