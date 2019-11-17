#ifndef ESTADO_H
#define ESTADO_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define INICIAL 0
#define FINAL   1
#define INICIAL_Y_FINAL 2
#define NORMAL 3

typedef struct _estado estado;
estado* crear_estado(char* nombre, int tipo);
void eliminar_estado(estado* est);


#endif
