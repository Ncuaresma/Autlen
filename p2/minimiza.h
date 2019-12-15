#ifndef ESTADO_H
#define ESTADO_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "afnd.h"
#include "estru.h"
#include "par.h"

AFND * AFNDMinimiza(AFND * afd);
int* bfs(int estado, int num_simbolos, int num_estados, int* vistos, AFND* afd);
int* transiciones (int est, int num_estados, int num_simbolos, AFND* afd);
int** ini_matriz(int n);
estru* estados_equivalentes(AFND* afd, int* visitados, estru* estru);
estru* equivalentes(AFND* afd, estru* estru, int estado, int pos, int* visitados);
int** marcar_finales(int* visitados, int** matriz, int* finales, int n, int estados_fin);
int** marcar(int* visitados, int** matriz, int n);
#endif
