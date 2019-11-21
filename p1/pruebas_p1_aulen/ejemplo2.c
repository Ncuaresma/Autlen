#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"

int main(int argc, char ** argv)
{

	AFND * p_afnd;

	p_afnd= AFNDNuevo("afnd_p1", 8, 4);

	AFNDInsertaSimbolo(p_afnd, "+");
	AFNDInsertaSimbolo(p_afnd, "-");
	AFNDInsertaSimbolo(p_afnd, "*");
	AFNDInsertaSimbolo(p_afnd, "n");

	AFNDInsertaEstado(p_afnd, "q0",INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", NORMAL);
	AFNDInsertaEstado(p_afnd, "q4", NORMAL);
	AFNDInsertaEstado(p_afnd, "q5", FINAL);
	AFNDInsertaEstado(p_afnd, "q6", NORMAL);
	AFNDInsertaEstado(p_afnd, "q7", NORMAL);

	AFNDInsertaTransicion(p_afnd, "q0", "+", "q1");
	AFNDInsertaTransicion(p_afnd, "q0", "-", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "n", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "n", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", "n", "q2");
	AFNDInsertaTransicion(p_afnd, "q2", "n", "q3");
	AFNDInsertaTransicion(p_afnd, "q3", "n", "q3");
  AFNDInsertaTransicion(p_afnd, "q4", "*", "q3");

	/*son las de transicion lambda*/
	AFNDInsertaLTransicion(p_afnd, "q0", "q1");
	AFNDInsertaLTransicion(p_afnd, "q4", "q6");
	AFNDInsertaLTransicion(p_afnd, "q6", "q7");
	AFNDInsertaLTransicion(p_afnd, "q7", "q4");
	AFNDInsertaLTransicion(p_afnd, "q3", "q5");
	/*Para probar qeu puede anidar lambdas*/
	/*AFNDInsertaLTransicion(p_afnd, "q5", "q1");*/
	AFNDCierraLTransicion(p_afnd);
	/*Creando imagen del automata inicial*/
	AFNDADot(p_afnd);
	AFNDElimina(p_afnd);

	return 0;
}
