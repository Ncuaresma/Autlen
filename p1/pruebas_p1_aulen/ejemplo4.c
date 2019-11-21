#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"

int main(int argc, char ** argv)
{

	AFND * p_afnd;

	p_afnd= AFNDNuevo("afnd_p1", 4, 2);

	AFNDInsertaSimbolo(p_afnd, "a");
	AFNDInsertaSimbolo(p_afnd,"b");

	AFNDInsertaEstado(p_afnd, "p", INICIAL_Y_FINAL);
	AFNDInsertaEstado(p_afnd, "q", NORMAL);
	AFNDInsertaEstado(p_afnd, "r", NORMAL);
	AFNDInsertaEstado(p_afnd, "s", NORMAL);

	AFNDInsertaTransicion(p_afnd, "p", "a", "q");
	AFNDInsertaTransicion(p_afnd, "q", "b", "p");
	AFNDInsertaTransicion(p_afnd, "q", "b", "r");
	AFNDInsertaTransicion(p_afnd, "r", "b", "p");
	AFNDInsertaTransicion(p_afnd, "r", "b", "s");
	AFNDInsertaTransicion(p_afnd, "r", "a", "r");

	/*son las de transicion lambda*/
	AFNDInsertaLTransicion(p_afnd, "q", "s");
	AFNDInsertaLTransicion(p_afnd, "s", "r");
	/*Para probar qeu puede anidar lambdas*/
	/*AFNDInsertaLTransicion(p_afnd, "q5", "q1");*/
	AFNDCierraLTransicion(p_afnd);
	/*Creando imagen del automata inicial*/
	AFNDADot(p_afnd);
	AFNDElimina(p_afnd);

	return 0;
}
