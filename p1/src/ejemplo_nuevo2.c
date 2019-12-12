#include <stdio.h>
#include "afnd.h"
#include "transforma.h"

int main(int argc, char **argv) {
    AFND *p_afnd;
    AFND *afd;

    p_afnd = AFNDNuevo("afnd", 4, 3);

    AFNDInsertaSimbolo(p_afnd, "0");
    AFNDInsertaSimbolo(p_afnd, "1");
    AFNDInsertaSimbolo(p_afnd, "2");

    AFNDInsertaEstado(p_afnd, "primerEstadoMasLargo", INICIAL);
    AFNDInsertaEstado(p_afnd, "2", NORMAL);
    AFNDInsertaEstado(p_afnd, "tercerEstado", NORMAL);
    AFNDInsertaEstado(p_afnd, "4", NORMAL);

    AFNDInsertaTransicion(p_afnd, "primerEstadoMasLargo", "0", "primerEstadoMasLargo");
    AFNDInsertaTransicion(p_afnd, "primerEstadoMasLargo", "1", "2");
    AFNDInsertaTransicion(p_afnd, "primerEstadoMasLargo", "2", "tercerEstado");
    AFNDInsertaTransicion(p_afnd, "primerEstadoMasLargo", "0", "4");

    AFNDInsertaTransicion(p_afnd, "2", "0", "primerEstadoMasLargo");
    AFNDInsertaTransicion(p_afnd, "2", "0", "2");
    AFNDInsertaTransicion(p_afnd, "2", "0", "tercerEstado");
    AFNDInsertaTransicion(p_afnd, "2", "0", "4");

    AFNDInsertaTransicion(p_afnd, "2", "1", "primerEstadoMasLargo");
    AFNDInsertaTransicion(p_afnd, "2", "1", "2");
    AFNDInsertaTransicion(p_afnd, "2", "1", "tercerEstado");

    AFNDInsertaTransicion(p_afnd, "2", "2", "primerEstadoMasLargo");
    AFNDInsertaTransicion(p_afnd, "2", "2", "2");
    AFNDInsertaTransicion(p_afnd, "2", "2", "tercerEstado");

    AFNDInsertaTransicion(p_afnd, "tercerEstado", "0", "primerEstadoMasLargo");
    AFNDInsertaTransicion(p_afnd, "tercerEstado", "1", "2");
    AFNDInsertaTransicion(p_afnd, "tercerEstado", "2", "tercerEstado");
    AFNDInsertaTransicion(p_afnd, "tercerEstado", "0", "4");

    AFNDInsertaTransicion(p_afnd, "4", "0", "primerEstadoMasLargo");
    AFNDInsertaTransicion(p_afnd, "4", "1", "primerEstadoMasLargo");
    AFNDInsertaTransicion(p_afnd, "4", "2", "primerEstadoMasLargo");
    AFNDInsertaTransicion(p_afnd, "4", "0", "4");

    AFNDInsertaLTransicion(p_afnd, "primerEstadoMasLargo", "2");
    AFNDInsertaLTransicion(p_afnd, "2", "tercerEstado");

    AFNDCierraLTransicion(p_afnd);
    AFNDADot(p_afnd);

    afd = AFNDTransforma(p_afnd);
    AFNDImprime(stdout, afd);
    AFNDADot(afd);

    AFNDElimina(afd);
    AFNDElimina(p_afnd);

    return 0;
}
