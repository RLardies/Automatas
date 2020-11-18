#include "minimiza.h"

int in_estadoscreados(int *estados, int nuevoestado, int numcreados){
    int i = 0;
    while(i < numcreados) {
        if (nuevoestado == estados[i])
            return 1;
    }
    return 0;

}

//Obtenemos una lista de los estados accesibles del autómata

int *accesibles(AFND *afnd){
    int inicial;
    int numestados;
    int numsimbolos;
    int *estados, *accesibles;
    int i, j;

    if (!afnd)
        return NULL;

    inicial = AFNDIndiceEstadoInicial(afnd);
    numestados = AFNDNumEstados(afnd);
    numsimbolos = AFNDNumSimbolos(afnd);

    estados = (int*) malloc(sizeof(int)*numestados);
    if (!estados)
        return NULL;
    
    for(i = 0; i < numestados; i++) {
        estados[i] = -1;
    }

    estados[0] = inicial;
    int numcreados = 1;
    int numcreados_bucle = 0;

    //lista de los estados para ir poniendo 1 en aquellos accesibles
    accesibles = (int*) malloc (sizeof(int)*numestados);
    if (!accesibles)
        return NULL;

    for(i = 0; i < numestados; i++) {
        accesibles[i] = 0;
    }

    accesibles[inicial] = 1;

    while(estados[numcreados_bucle] != -1){
        for (i = 0; i < numsimbolos; i++){
            for(j = 0; j < numestados; j++) {
                if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, estados[numcreados_bucle], i, j)== 1) {
                    if(in_estadoscreados(estados, j, numcreados_bucle) == 0){
                        accesibles[j] = 1;
                        estados[numcreados] = j;
                        numcreados ++;
                        
                    }
                    accesibles[j] = 1;
                }
            }
        }
        numcreados_bucle ++;
    }

    free(estados);
    return accesibles;
}

int ** distinguibles(AFND *afnd) {
    int **matriz;
    int numestados, numsimbolos, i, j, simbolo, estado;

    if(!afnd)
        return NULL;

    numestados = AFNDNumEstados(afnd);
    numsimbolos = AFNDNumSimbolos(afnd);
    
    //inicializamos matriz
    matriz = (int**) malloc (sizeof(int*)* numestados);
    if (!matriz)
        return NULL;
    
    for(i = 0; i<numestados; i++) {
        matriz[i] = (int*) calloc (numestados, sizeof(int));
    }

    for (i = 0; i < numestados; i++) {
        if (AFNDTipoEstadoEn(afnd, i) == FINAL || AFNDTipoEstadoEn(afnd, i) == INICIAL_Y_FINAL) {
            for (j = 0; j < numestados; j++) {
                matriz[i][j] = 1;
                matriz[j][i] = 1;
            }
        }
    }  

}

AFND *AFNDminimiza(AFND *afnd){
    return NULL;
}