#include <stdio.h>
#include "afnd.h"
#include "minimiza.h"

int main(int argc, char ** argv)
{
  AFND * p_afnd;
  AFND * p_afnd_min;

  p_afnd = AFNDNuevo("af1",2,1);

  AFNDInsertaSimbolo(p_afnd,"1");

  AFNDInsertaEstado(p_afnd,"q0",INICIAL_Y_FINAL);
  AFNDInsertaEstado(p_afnd,"q1",INICIAL_Y_FINAL);

  AFNDInsertaTransicion(p_afnd, "q0", "1", "q1");
  AFNDInsertaTransicion(p_afnd, "q1", "1", "q0");

  p_afnd_min = AFNDMinimiza(p_afnd);

  AFNDADot(p_afnd_min);
  AFNDADot(p_afnd);
  AFNDImprime(stdout,p_afnd_min);
  AFNDElimina(p_afnd);
  AFNDElimina(p_afnd_min);
  return 0;
  }
