#include "afnd.h"
#include "transforma.h"

int main(int argc, char ** argv)
{

        AFND * p_afnd;
        AFND * afd;

        p_afnd= AFNDNuevo("afd_prueba1", 3, 2);
        AFNDInsertaSimbolo(p_afnd, "0");
        AFNDInsertaSimbolo(p_afnd,"1");
        
        AFNDInsertaEstado(p_afnd, "q0",INICIAL);
        AFNDInsertaEstado(p_afnd, "q1", FINAL);
        AFNDInsertaEstado(p_afnd, "q2", NORMAL);

        
        AFNDInsertaTransicion(p_afnd, "q0", "0", "q1");
        AFNDInsertaTransicion(p_afnd, "q2", "1", "q1");
        
        AFNDCierraLTransicion(p_afnd);

        AFNDADot(p_afnd);

        
        AFNDElimina(p_afnd);
        
        return 0;
}
