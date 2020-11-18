#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "afnd.h"
#include "minimiza.h"

int main(int argc, char ** argv)
{
    int *res, i;
    AFND * p_afnd;
        AFND * afd;

        p_afnd= AFNDNuevo("afd_prueba_1", 3, 2);
        AFNDInsertaSimbolo(p_afnd, "0");
        AFNDInsertaSimbolo(p_afnd,"1");

        AFNDInsertaEstado(p_afnd, "q0",INICIAL);
        AFNDInsertaEstado(p_afnd, "q1", FINAL);
        AFNDInsertaEstado(p_afnd, "q2", NORMAL);


        AFNDInsertaTransicion(p_afnd, "q0", "0", "q1");
        AFNDInsertaTransicion(p_afnd, "q2", "1", "q1");

        AFNDCierraLTransicion(p_afnd);

        res = accesibles(p_afnd);
        for (i = 0; i < 3; i++) {
            printf("%d\n", res[i]);
        }

        AFNDADot(p_afnd);


        AFNDElimina(p_afnd);

        return 0;

}