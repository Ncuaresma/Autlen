#include "estado.h"

//estructura para estado
typedef struct _estado{
  char* nombre;
  int tipo; //puede ser INICIAL, FINAL, INICIAL_Y_FINAL O NORMAL
  int** transiciones; // array de arrasys con los estados a los quue se puede ir y con que simbolos
  int num_estados;
}estado;

//inicializando valores del estado
estado* crear_estado(char* nombre, int tipo, int num_simbolos, int num_estados){
  if (!nombre) return null;

  if (tipo > 3 || tipo < 0) return null;  }

  estado* state = malloc(sizeof(estado));
  if (!state) return NULL;

  state->tipo = tipo;
  state->nombre = (char*)malloc((strlen(nombre))*(sizeof(char)));
  if(!state->nombre){
    free(state);
    return null;
  }
  strcpy(state->nombre, nombre);





}


void eliminar_estado(estado* estado){

}
