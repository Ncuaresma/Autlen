#ifndef TRANSFORMA_H
#define TRANSFORMA_H

#include <stdio.h>
#include "afnd.h"
#include "estructura.h"
#include "estado.h"

AFND * AFNDTransforma(AFND * afnd);
void introducir_estados(int num_estados, int num_simbolos, AFND * afnd, estructura* estru);
void introducir_simbolos(int num_simbolos, AFND * afnd, estructura* estru);
void estados_contiguos(estado* estado, int num_estados, int num_simbolos, AFND * afnd);
void buscar_simbolo(AFND * afnd, estado* estado, int estado2, int num_simbolos, int num_estados);

#endif
