#ifndef ESTADO_H
#define ESTADO_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "afnd.h"

AFND * AFNDMinimiza(AFND * afd);
int* bfs(int estado, int num_simbolos, int num_estados, int* vistos, AFND* afd);
int* transiciones (int est, int num_estados, int num_simbolos, AFND* afd);
int** ini_matriz(int n);
#endif
