#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "transforma.h"

int main(int argc, char ** argv)
{

	AFND * p_afnd;
	AFND * afd;

	p_afnd= AFNDNuevo("afnd_p1", 4, 3);

	AFNDInsertaSimbolo(p_afnd, "+");
	AFNDInsertaSimbolo(p_afnd,"-");
	AFNDInsertaSimbolo(p_afnd,"*");

	AFNDInsertaEstado(p_afnd, "q0",INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", FINAL);

	AFNDInsertaTransicion(p_afnd, "q0", "+", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "+", "q2");
	AFNDInsertaTransicion(p_afnd, "q1", "-", "q2");
	AFNDInsertaTransicion(p_afnd, "q1", "*", "q2");
	AFNDInsertaTransicion(p_afnd, "q2", "-", "q3");

	/*son las de transicion lambda*/
	AFNDInsertaLTransicion(p_afnd, "q1", "q2");
	/*Para probar qeu puede anidar lambdas*/
	/*AFNDInsertaLTransicion(p_afnd, "q5", "q1");*/
	AFNDCierraLTransicion(p_afnd);
	/*Creando imagen del automata inicial*/
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
