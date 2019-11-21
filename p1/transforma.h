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
void actualizar_ini(AFND * afnd, estructura* estru, int num_simbolos, int num_estados_base);
void estados_contiguos_generados(estructura* estru, estado* estado, int num_simbolos, AFND * afnd);
char* obtener_nombre(AFND * afnd, int* cod, int num_estados_base);
int estado_existente(char* nombre, estructura* estru);
int estado_fin(int* codificacion, estructura* estru);
void estado_matriz(AFND * afnd, estructura* estru);

void funcion_probar(int num_simbolos, AFND* afnd, estructura* estru);

#endif
