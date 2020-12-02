#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "minimiza.h"

int main(int argc, char ** argv)
{

	AFND * p_afnd;
	AFND * afd;

	p_afnd = AFNDNuevo("afd_prueba3", 7, 2);

	AFNDInsertaSimbolo(p_afnd,"0");
	AFNDInsertaSimbolo(p_afnd,"1");


	AFNDInsertaEstado(p_afnd, "A", INICIAL);
	AFNDInsertaEstado(p_afnd, "B", NORMAL);
	AFNDInsertaEstado(p_afnd, "C", FINAL);
	AFNDInsertaEstado(p_afnd, "D", NORMAL);
	AFNDInsertaEstado(p_afnd, "E", NORMAL);
	AFNDInsertaEstado(p_afnd, "F", NORMAL);
	AFNDInsertaEstado(p_afnd, "G", FINAL);


	AFNDInsertaTransicion(p_afnd, "A", "0", "B");
	AFNDInsertaTransicion(p_afnd, "A", "1", "F");
	AFNDInsertaTransicion(p_afnd, "B", "0", "C");
	AFNDInsertaTransicion(p_afnd, "B", "1", "E");
	AFNDInsertaTransicion(p_afnd, "C", "0", "C");
	AFNDInsertaTransicion(p_afnd, "C", "1", "C");
	AFNDInsertaTransicion(p_afnd, "D", "0", "A");
	AFNDInsertaTransicion(p_afnd, "D", "1", "E");
	AFNDInsertaTransicion(p_afnd, "E", "0", "E");
	AFNDInsertaTransicion(p_afnd, "E", "1", "E");
	AFNDInsertaTransicion(p_afnd, "F", "0", "G");
	AFNDInsertaTransicion(p_afnd, "F", "1", "E");
	AFNDInsertaTransicion(p_afnd, "G", "0", "G");
	AFNDInsertaTransicion(p_afnd, "G", "1", "G");
	
	AFNDCierraLTransicion(p_afnd);

	afd = AFNDMinimiza(p_afnd);
	AFNDImprime(stdout,afd);
	AFNDADot(p_afnd);
	AFNDADot(afd);

	AFNDElimina(p_afnd);
	AFNDElimina(afd);

	return 0;
}