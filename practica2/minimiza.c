#include "minimiza.h"

int in_estadoscreados(int *estados, int nuevoestado, int numcreados){
    int i = 0;
    while(i < numcreados) {
        if (nuevoestado == estados[i]) return 1;
        i++;
    }
    return 0;

}

//Obtenemos una lista de los estados accesibles del autómata

int *accesibles(AFND *afnd){
    int inicial;
    int numestados;
    int numsimbolos;
    int *estados, *accesibles;
    int i, j, h;

    if (!afnd)
        return NULL;    

    inicial = AFNDIndiceEstadoInicial(afnd);
    numestados = AFNDNumEstados(afnd);
    numsimbolos = AFNDNumSimbolos(afnd);

    estados = (int*) malloc(sizeof(int)*(numestados + 1));
    if (!estados)
        return NULL;
    
    for(i = 0; i < numestados + 1; i++) {
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

    while(estados[numcreados_bucle] != -1 && numcreados_bucle < numestados){
        
        for(j = 0; j < numestados; j++) {
            for (i = 0; i < numsimbolos; i++){
                if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, estados[numcreados_bucle], i, j)== 1) {
                    
                    if(in_estadoscreados(estados, j, numcreados_bucle) == 0){
                        for(h=0; h < numestados; h++){
                            if(estados[h] == j) break;
                        }
                        if(h == numestados){
                            estados[numcreados] = j;
                            numcreados ++;
                        }
                        
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

int ** distinguibles(AFND *afnd, int * estados_accesibles) {
    int **matriz;
    int numestados, numsimbolos, i, j, simbolo, estado1;
    int destino1, destino2, cambio = 1;

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

    for(i=0; i < numestados; i++){
        if(estados_accesibles[i] == 0){
            for (j = 0; j < numestados; j++){
                matriz[i][j] = 2;
                matriz[j][i] = 2;
            }

        }
    }

    for (i = 0; i < numestados; i++) {
        if(estados_accesibles[i] == 1){
            if (AFNDTipoEstadoEn(afnd, i) == FINAL || AFNDTipoEstadoEn(afnd, i) == INICIAL_Y_FINAL) {
                for (j = 0; j < numestados; j++) {
                    if(AFNDTipoEstadoEn(afnd, j) == FINAL || AFNDTipoEstadoEn(afnd, j) == INICIAL_Y_FINAL){
                        matriz[i][j] = 0;
                        matriz[j][i] = 0;
                    } else {
                        matriz[i][j] = 1;
                        matriz[j][i] = 1;
                    }
                }
            }
        }
    }    

    while(cambio){
        cambio = 0;
        for (i = 0; i < numestados; i++){
           
            for (j = 0; j < i; j++) {
                if (matriz[i][j] == 0){
                    for (simbolo = 0; simbolo < numsimbolos; simbolo ++){
                        for (estado1 = 0; estado1 < numestados; estado1 ++){
                            
                            if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, simbolo, estado1) == 1){
                                destino1 = estado1;
                            }
                            if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, j, simbolo, estado1) == 1){
                                destino2 = estado1;
                            }
                        }
                        if (destino1 != destino2 && matriz[destino1][destino2] == 1){
                            matriz[i][j] = 1;
                            matriz[j][i] = 1;
                            cambio = 1;
                        }
                    }
                }
            }
            
        }
    }

    return matriz; 

}

AFND *AFNDMinimiza(AFND *afnd){
    int * estados_accesibles;
    int ** estados_distinguibles;
    AFND * afnd_min;
    int numestados, numsimbolos, i, j, k, m, n, num_intermedios = 0, tipo_estado, num_transis;
    char nombre_estado[MAX_NOMBRE], nombre_estado_aux[MAX_NOMBRE], nombre_simbolo[MAX_NOMBRE];
    int * config_estado, * conf, * conf_dest;
    EstadoIntermedio **estados_intermedios;

    numsimbolos = AFNDNumSimbolos(afnd);

    numestados = AFNDNumEstados(afnd);

    estados_accesibles = accesibles(afnd);
    estados_distinguibles = distinguibles(afnd, estados_accesibles);

    estados_intermedios = (EstadoIntermedio**) malloc(sizeof(EstadoIntermedio*)*numestados);
   

    //obtenemos las clases de equivalencia de la matriz de estados distinguibles que conformaran
    //un estado en nuestro nuevo autómata

    //Creamos los estados intermedios
    for (i=0; i < numestados; i++) {
        
        if (estados_accesibles[i]== 1){ //entonces es accesible
            config_estado = inicializar_configuracion(numestados, i);
            tipo_estado = AFNDTipoEstadoEn(afnd, i);
            for (j = 0; j < numestados; j++){
                if (estados_distinguibles[i][j] == 0 && j != i){ //entonces pertenecen a la misma clase de equivalencia
                   
                    anadir_configuracion(config_estado, numestados, j);
                    tipo_estado = nuevo_tipo_estado(afnd, j, tipo_estado);
                }
            }

            strcpy(nombre_estado, "");
            for (int j=0; j < numestados; j++) {
                if (config_estado[j] == 1) {
                    strcat(nombre_estado, AFNDNombreEstadoEn(afnd, j));
                }
            }
            
            for(k = 0; k < num_intermedios; k++){
                
                conf = get_configuracion_estado(estados_intermedios[k]);
                
                for (j=0; j < numestados; j++) {
                    if (conf[j] != config_estado[j]) {
                        break;
                    }
                }

                if(j == numestados){
                    break;
                }
                
            }

            if(k == num_intermedios){
                estados_intermedios[num_intermedios] = crear_estado(nombre_estado, numestados, tipo_estado, config_estado);
	            num_intermedios ++;
            } else{
                free(config_estado);
            }
            
            
        }
    }

    // Hallamos las transiciones de cada estado intermedio
    for(i=0; i < num_intermedios; i++){
        
        conf = get_configuracion_estado(estados_intermedios[i]);

        for(j = 0; j < numestados; j++){
            if(conf[j] == 1){
                for(int h = 0; h < numsimbolos; h++){
                    for(k = 0; k < numestados; k++){
                        if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, j, h, k)){

                            num_transis = get_transiciones_guardadas(estados_intermedios[i]);
                            
                            for(n = 0; n < num_transis; n++){
                                conf_dest = get_configuracion(get_transicion(estados_intermedios[i], n));
                                strcpy(nombre_simbolo, get_operador(get_transicion(estados_intermedios[i], n)));
                                if(h != AFNDIndiceDeSimbolo(afnd, nombre_simbolo)){
                                    n = num_transis;
                                    break;
                                }
                                for(m = 0; m < numestados; m++){
                                    if(conf_dest[m] == 1 && m == k) break;
                                }

                                if(m != numestados) break;
                            }

                            if(n == num_transis){
                                
                                for(n = 0; n < num_intermedios; n++){
                                    
                                    conf_dest = get_configuracion_estado(estados_intermedios[n]);
                                    
                                    for(m = 0; m < numestados; m++){                                 
                                        if(conf_dest[m] == 1 && m == k)break;
                                    }

                                    if(m != numestados && num_transis < numsimbolos){
                                        strcpy(nombre_estado, get_nombre_estado(estados_intermedios[n]));
                                        set_transicion(estados_intermedios[i], num_transis, crear(numestados, AFNDSimboloEn(afnd, h), nombre_estado, conf_dest));
                                        break;                                        
                                    }
                                }

                            }
                            
                        }
                    }
                }
                //Basta con observar a que clase va a parar las transiciones de uno de los estados que formar nuestro estado intermedio
                break;
            }
        }
    }

    //Construimos nuestro automata

    afnd_min = AFNDNuevo("AFD_MIN", num_intermedios, numsimbolos);
	
	for(i = 0; i < numsimbolos; i++){
		AFNDInsertaSimbolo(afnd_min, AFNDSimboloEn(afnd, i));
	}

	for(i = 0; i < num_intermedios; i++){
		imprimir_estado(estados_intermedios[i], numestados);
		strcpy(nombre_estado, get_nombre_estado(estados_intermedios[i]));
		AFNDInsertaEstado(afnd_min, nombre_estado, get_tipo_estado(estados_intermedios[i]));
	}

	for(i = 0; i < num_intermedios; i++){
		num_transis = get_transiciones_guardadas(estados_intermedios[i]);
	
		for(int h=0; h < num_transis; h++){
			strcpy(nombre_estado_aux, get_destino(get_transicion(estados_intermedios[i], h)));	
			strcpy(nombre_simbolo, get_operador(get_transicion(estados_intermedios[i], h)));
			strcpy(nombre_estado, get_nombre_estado(estados_intermedios[i]));	
			AFNDInsertaTransicion(afnd_min, nombre_estado, nombre_simbolo , nombre_estado_aux);
		}

	}

	AFNDCierraLTransicion(afnd_min);

    for(i=0; i < num_intermedios; i++){ 
        eliminar_estado(estados_intermedios[i]);
    }
    
    
    free(estados_intermedios);
    free(estados_accesibles);

    for(j=0; j < numestados; j++){
        free(estados_distinguibles[j]);
    }

    free(estados_distinguibles);
    

    return afnd_min;
}
