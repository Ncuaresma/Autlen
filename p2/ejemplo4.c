#include <stdio.h>

#include "minimiza.h"
#include "afnd.h"

int main(int argc, char ** argv){
  AFND * p_afnd;
  AFND * p_afnd_min;

  p_afnd = AFNDNuevo("af1",5,2);
  AFNDInsertaSimbolo(p_afnd,"0");
  AFNDInsertaSimbolo(p_afnd,"1");

  AFNDInsertaEstado(p_afnd,"q0",INICIAL_Y_FINAL);
  AFNDInsertaEstado(p_afnd,"q1",NORMAL);
  AFNDInsertaEstado(p_afnd,"q2",NORMAL);
  AFNDInsertaEstado(p_afnd,"q1_nohacenada",FINAL);
  AFNDInsertaEstado(p_afnd,"q3",FINAL);

  AFNDInsertaTransicion(p_afnd, "q0", "0", "q2");
  AFNDInsertaTransicion(p_afnd, "q0", "1", "q1");
  AFNDInsertaTransicion(p_afnd, "q1", "0", "q3");
  AFNDInsertaTransicion(p_afnd, "q1", "1", "q2");
  AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");
  AFNDInsertaTransicion(p_afnd, "q2", "1", "q1");
  AFNDInsertaTransicion(p_afnd, "q3", "0", "q1");
  AFNDInsertaTransicion(p_afnd, "q3", "1", "q0");

  AFNDInsertaTransicion(p_afnd, "q1_nohacenada", "1", "q0");
  AFNDInsertaTransicion(p_afnd, "q1_nohacenada", "0", "q1");

  AFNDADot(p_afnd);
  p_afnd_min = AFNDMinimiza(p_afnd);

  AFNDADot(p_afnd_min);
  /*AFNDImprime(stdout,p_afnd_min);*/

  AFNDElimina(p_afnd);
  AFNDElimina(p_afnd_min);
  printf("\n");
  return 0;
}
