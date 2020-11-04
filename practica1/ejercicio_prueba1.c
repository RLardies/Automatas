#include "afnd.h"
#include "transforma.h"

int main(int argc, char ** argv)
{

        AFND * p_afnd;
        AFND * afd;

        p_afnd= AFNDNuevo("afd_prueba1", 4, 3);
        
        AFNDInsertaSimbolo(p_afnd,"+");
        AFNDInsertaSimbolo(p_afnd, "0");
        AFNDInsertaSimbolo(p_afnd,"1");
        
        AFNDInsertaEstado(p_afnd, "q1",INICIAL);
        AFNDInsertaEstado(p_afnd, "q2", NORMAL);
        AFNDInsertaEstado(p_afnd, "q3", NORMAL);
        AFNDInsertaEstado(p_afnd, "q4", FINAL);

        
        AFNDInsertaTransicion(p_afnd, "q1", "0", "q1");
        AFNDInsertaTransicion(p_afnd, "q1", "1", "q1");
        AFNDInsertaTransicion(p_afnd, "q1", "1", "q2");
        AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");
        AFNDInsertaTransicion(p_afnd, "q2", "1", "q3");
        AFNDInsertaTransicion(p_afnd, "q3", "0", "q4");
        AFNDInsertaTransicion(p_afnd, "q3", "1", "q4");
        
        AFNDCierraLTransicion(p_afnd);
        afd  = AFNDTransforma(p_afnd);


        AFNDImprime(stdout,afd);
        AFNDADot(afd);
        AFNDADot(p_afnd);

        AFNDElimina(afd);
        AFNDElimina(p_afnd);
        
        return 0;
}
