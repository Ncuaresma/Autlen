#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "transforma.h"

int main(int argc, char ** argv)
{

	AFND * p_afnd;
	AFND * afd;

	p_afnd= AFNDNuevo("afnd_p1", 6, 3);

	AFNDInsertaSimbolo(p_afnd,"+");
	AFNDInsertaSimbolo(p_afnd, "0");
	AFNDInsertaSimbolo(p_afnd,".");

	AFNDInsertaEstado(p_afnd, "q0",INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", NORMAL);
	AFNDInsertaEstado(p_afnd, "q4", NORMAL);
	AFNDInsertaEstado(p_afnd, "q5", FINAL);

	AFNDInsertaTransicion(p_afnd, "q0", "+", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "0", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "0", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", ".", "q2");
	AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");
	AFNDInsertaTransicion(p_afnd, "q3", "0", "q2");
	AFNDInsertaTransicion(p_afnd, "q3", "0", "q3");
	AFNDInsertaTransicion(p_afnd, "q4", ".", "q3");

	/*son las de transicion lambda*/
	AFNDInsertaLTransicion(p_afnd, "q0", "q1");
	AFNDInsertaLTransicion(p_afnd, "q3", "q5");
	/*Para probar qeu puede anidar lambdas*/
	/*AFNDInsertaLTransicion(p_afnd, "q5", "q1");*/
	AFNDCierraLTransicion(p_afnd);
	/*Creando imagen del automata inicial*/
	AFNDADot(p_afnd);
	/*AFNDImprime(stdout,p_afnd);*/
	AFNDADot(p_afnd);

	/*Transformando el automata*/
	afd = AFNDTransforma(p_afnd);

	/* Imprimiendo el automata final*/
	 /*AFNDImprime(stdout,afd);*/
	/*Creando la imagen del automata final*/
	AFNDADot(afd);

	/*AFNDElimina(afd);*/
	AFNDElimina(p_afnd);
	printf("\n");
	return 0;
}
