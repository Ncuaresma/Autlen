#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define INICIAL 0
#define FINAL   1
#define INICIAL_Y_FINAL 2
#define NORMAL 3

typedef struct _estructura estructura;
estado* crear_estructura(char* nombre, int tipo);
void eliminar_estructura(estado* est);


#endif
