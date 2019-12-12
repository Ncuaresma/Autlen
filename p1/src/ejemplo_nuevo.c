#include <stdio.h>
#include "afnd.h"
#include "transforma.h"

int main(int argc, char **argv) {
    AFND *p_afnd;
    AFND *afd;

    p_afnd = AFNDNuevo("afdnd", 4, 2);

    AFNDInsertaSimbolo(p_afnd, "a");
    AFNDInsertaSimbolo(p_afnd, "b");

    AFNDInsertaEstado(p_afnd, "q0", NORMAL);
    AFNDInsertaEstado(p_afnd, "q1", INICIAL);
    AFNDInsertaEstado(p_afnd, "q2", NORMAL);
    AFNDInsertaEstado(p_afnd, "q3", FINAL);

    AFNDInsertaTransicion(p_afnd, "q0", "a", "q0");
    AFNDInsertaTransicion(p_afnd, "q0", "b", "q0");

    AFNDInsertaTransicion(p_afnd, "q1", "a", "q0");
    AFNDInsertaTransicion(p_afnd, "q1", "a", "q2");
    AFNDInsertaTransicion(p_afnd, "q1", "b", "q2");

    AFNDInsertaTransicion(p_afnd, "q2", "a", "q1");
    AFNDInsertaTransicion(p_afnd, "q2", "b", "q0");
    AFNDInsertaTransicion(p_afnd, "q2", "b", "q3");

    AFNDInsertaTransicion(p_afnd, "q3", "a", "q0");
    AFNDInsertaTransicion(p_afnd, "q3", "b", "q0");

    AFNDInsertaLTransicion(p_afnd, "q3", "q0");
    AFNDInsertaLTransicion(p_afnd, "q1", "q3");

    AFNDCierraLTransicion(p_afnd);

    afd = AFNDTransforma(p_afnd);
    AFNDImprime(stdout, afd);
    AFNDADot(afd);

    AFNDElimina(afd);
    AFNDElimina(p_afnd);

    return 0;
}
