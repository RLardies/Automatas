#include "afnd.h"
#include "transforma.h"

int main(int argc, char ** argv)
{

        AFND * p_afnd;
        AFND * afd;

        p_afnd= AFNDNuevo("afd_prueba2", 5, 2);
        
        AFNDInsertaSimbolo(p_afnd,"+");
        AFNDInsertaSimbolo(p_afnd, "0");
        
        AFNDInsertaEstado(p_afnd, "q0",INICIAL);
        AFNDInsertaEstado(p_afnd, "q1", NORMAL);
        AFNDInsertaEstado(p_afnd, "q2", NORMAL);
        AFNDInsertaEstado(p_afnd, "q3", NORMAL);
        AFNDInsertaEstado(p_afnd, "q4", FINAL);

        
        AFNDInsertaTransicion(p_afnd, "q0", "0", "q1");
        AFNDInsertaTransicion(p_afnd, "q1", "+", "q1");
        AFNDInsertaTransicion(p_afnd, "q1", "0", "q2");
        AFNDInsertaTransicion(p_afnd, "q0", "+", "q3");
        AFNDInsertaTransicion(p_afnd, "q3", "+", "q4");
        AFNDInsertaTransicion(p_afnd, "q4", "+", "q2");

        AFNDInsertaLTransicion(p_afnd, "q0", "q1");
        AFNDInsertaLTransicion(p_afnd, "q1", "q0");
        AFNDInsertaLTransicion(p_afnd, "q1", "q3");
        AFNDInsertaLTransicion(p_afnd, "q4", "q1");
        
        AFNDCierraLTransicion(p_afnd);
        afd  = AFNDTransforma(p_afnd);


        AFNDImprime(stdout,afd);
        AFNDADot(afd);

        AFNDElimina(afd);
        AFNDElimina(p_afnd);
        
        return 0;
}
