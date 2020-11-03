#include "transforma.h"

int nuevo_tipo_estado(AFND *afnd, int pos, int anterior);

int comparar_config(int *config1, int *config2, int num_estados){
  int i;

  /* Comprobamos los argumentos de entrada */
  if(!config1 || !config2){
    return -1;
  }

  /* Pasamos a comparar las codificaciones. En cuanto una posicion ya no sea igual indicaremos que son diferentes */
  for (i=0; i<num_estados; i++){
    if(config1[i] != config2[i]){
      return 1;
    }
  }

  /* si recorremos toda la lista y no hay diferencias, son iguales */
  return 0;
}

AFND* AFNDTransforma(AFND* afnd){
	AFND* afd;
	int tipo_estado = INICIAL;
	int posicion_inicio, estado_AFND, i, h, num_transis, num_intermedios, tam, num_estado, num_transis_existentes;
	int * configuracion_inicio, *conf_destino;
	char nombre_inicio[MAX_NOMBRE];
	char estado_destino[MAX_NOMBRE] = "";
	char estado_destino_existente[MAX_NOMBRE];
	char nombre_simbolo[MAX_NOMBRE];

	int num_total_estados = AFNDNumEstados(afnd);
	int num_total_simbolos = AFNDNumSimbolos(afnd);

	EstadoIntermedio **estados_intermedios;

	posicion_inicio = AFNDIndiceEstadoInicial(afnd);
	
	strcpy(nombre_inicio, AFNDNombreEstadoEn(afnd, posicion_inicio));



	configuracion_inicio = inicializar_configuracion(num_total_estados, posicion_inicio);
	

	

	//si no hay transiciones lambda cogemos el tipo de estado que tenga nuestro estado inicial en el afnd original (puede ser inicial o inicial y final)
	tipo_estado = AFNDTipoEstadoEn(afnd, posicion_inicio);

	
	//comprobamos si hay transiciones lambda
	for (int estado_AFND = 0; estado_AFND < num_total_estados; estado_AFND++) {
		if (AFNDCierreLTransicionIJ(afnd, posicion_inicio, estado_AFND) && (posicion_inicio != estado_AFND)) {

			strcat(nombre_inicio, AFNDNombreEstadoEn(afnd, estado_AFND));
			configuracion_inicio[estado_AFND] = 1;

			tipo_estado = nuevo_tipo_estado(afnd, estado_AFND, tipo_estado);
		}	
	}

	num_intermedios = 0;

	//Reservamos memoria para el estado intermedio y lo creamos
	estados_intermedios = (EstadoIntermedio**) malloc(sizeof(EstadoIntermedio*));

	estados_intermedios[num_intermedios] = crear_estado(nombre_inicio, num_total_estados, tipo_estado, configuracion_inicio);
	num_intermedios ++;

	//Añadimos las transiciones para el primer estado intermedio
	for(i=0; i < num_total_estados; i++){
		if( configuracion_inicio[i] == 1){
			
			for(int simbolo=0; simbolo < num_total_simbolos; simbolo++){


				for(estado_AFND=0; estado_AFND < num_total_estados; estado_AFND++){
					if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, simbolo, estado_AFND)){

						if(strcmp(estado_destino, "") == 0){
							strcpy(estado_destino, AFNDNombreEstadoEn(afnd, estado_AFND));
							conf_destino = inicializar_configuracion(num_total_estados, estado_AFND);
						} 
						else{
							strcat(estado_destino, AFNDNombreEstadoEn(afnd, estado_AFND));
							anadir_configuracion(conf_destino, num_total_estados, estado_AFND);
						}

						
						
					}

				}
				//Si se ha encontrado alguna la creamos
				if(strlen(estado_destino) > 0){
					num_transis_existentes = get_transiciones_guardadas(estados_intermedios[0]);
					set_transicion(estados_intermedios[0], num_transis_existentes, crear(num_total_estados, AFNDSimboloEn(afnd, simbolo), estado_destino, conf_destino));
					strcpy(estado_destino,"");
				}
			}
		}
	}

	//Iteramos sobre los estados intermedios, que se iran añadiendo progresivamente
	for(int j=0; j < num_intermedios; j++){
		printf("PASO %d\n\n", j);

		if(estados_intermedios[j] == NULL) break;

		num_transis = get_transiciones_guardadas(estados_intermedios[j]);



		//Para cada transición del estado intermedio explorado haremos un estado nuevo si es necesario
		for(int k=0; k < num_transis; k++){


			strcpy(nombre_inicio, get_destino(get_transicion(estados_intermedios[j], k)));
			configuracion_inicio = get_configuracion(get_transicion(estados_intermedios[j], k));

			//Vemos el tipo de estado destino mediante cada transicion
			tipo_estado = NORMAL;
			for(i=0; i < num_total_estados; i++){
				if(configuracion_inicio[i] == 1){
					tipo_estado =  nuevo_tipo_estado(afnd, i, tipo_estado);
				}
			}

			tam = sizeof(estados_intermedios);
			//Comprobamos si el estado ya existe
			for(i=0; i < num_intermedios; i++){
				if(comparar_config(configuracion_inicio,get_configuracion_estado(estados_intermedios[i]), num_intermedios) == 0) break;
			}

			//Si no existe lo creamos
			if(i == num_intermedios){

				estados_intermedios = (EstadoIntermedio**) realloc(estados_intermedios, tam+sizeof(EstadoIntermedio*) * num_intermedios);
				estados_intermedios[num_intermedios] = crear_estado(nombre_inicio, num_total_estados, tipo_estado, configuracion_inicio);
				num_estado = num_intermedios;
				 
			}
			else
				num_estado = i;


			
			//Añadimos las transiciones al nuevo estado
			for(int simbolo=0; simbolo < num_total_simbolos; simbolo++){


				for(estado_AFND=0; estado_AFND < num_total_estados; estado_AFND++){

					for(i=0; i < num_total_estados; i++){
						if( configuracion_inicio[i] == 1){
							if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, simbolo, estado_AFND)){

								if(strcmp(estado_destino, "") == 0){
									strcpy(estado_destino, AFNDNombreEstadoEn(afnd, estado_AFND));
									conf_destino = inicializar_configuracion(num_total_estados, estado_AFND);
									tipo_estado = AFNDTipoEstadoEn(afnd, estado_AFND);
								} 
								else if(conf_destino[estado_AFND] != 1){
									strcat(estado_destino, AFNDNombreEstadoEn(afnd, estado_AFND));
									anadir_configuracion(conf_destino, num_total_estados, estado_AFND);
									tipo_estado = nuevo_tipo_estado(afnd, estado_AFND, tipo_estado);
								}

							}
						}
						
					}

				}

				//Si hay alguna transicion posible, la analizamos
				if(strlen(estado_destino) > 0){

					//Añadimos sus transiciones landa
					for(i=0; i < num_total_estados; i++){

						if( conf_destino[i] == 1){

							for (estado_AFND = 0; estado_AFND < num_total_estados; estado_AFND++) {

								if (AFNDCierreLTransicionIJ(afnd, i, estado_AFND) && (i != estado_AFND) && (conf_destino[estado_AFND]!= 1)) {

									strcat(estado_destino, AFNDNombreEstadoEn(afnd, estado_AFND));
									conf_destino[estado_AFND] = 1;

									tipo_estado = nuevo_tipo_estado(afnd, estado_AFND, tipo_estado);
								}	
							}
						}
					}


				
					num_transis_existentes = get_transiciones_guardadas(estados_intermedios[num_estado]);

					
					//Comprobamos si la transicion ya existe
					for(h=0; h < num_transis_existentes; h++){

						strcpy(estado_destino_existente, get_destino(get_transicion(estados_intermedios[num_estado], h)));							
						
						if(strcmp(estado_destino, estado_destino_existente) == 0 &&
						strcmp(AFNDSimboloEn(afnd, simbolo) , get_operador(get_transicion(estados_intermedios[num_estado], h)))== 0) break;
						
					}
					

					//Si no existe la creamos y añadimos
					if(h == num_transis_existentes){
						set_transicion(estados_intermedios[num_estado], num_transis_existentes, crear(num_total_estados, AFNDSimboloEn(afnd, simbolo), estado_destino, conf_destino));
					}
					strcpy(estado_destino,"");
					
				}
			}
				
			
			
			//Si hemos creado un estado nuevo incrementamos el contador
			if(num_estado == num_intermedios){
				num_intermedios++;
			}
			
		}

	}

	//Construimos nuestro automata determinista
	afd = AFNDNuevo("AFD", num_intermedios, num_total_simbolos);
	
	for(i = 0; i < num_total_simbolos; i++){
		AFNDInsertaSimbolo(afd, AFNDSimboloEn(afnd, i));
	}

	for(i = 0; i < num_intermedios; i++){
		imprimir_estado(estados_intermedios[i], num_total_estados);
		strcpy(nombre_inicio, get_nombre_estado(estados_intermedios[i]));
		AFNDInsertaEstado(afd, nombre_inicio, get_tipo_estado(estados_intermedios[i]));
	}

	for(i = 0; i < num_intermedios; i++){
		num_transis_existentes = get_transiciones_guardadas(estados_intermedios[i]);
	
		for(h=0; h < num_transis_existentes; h++){
			strcpy(estado_destino_existente, get_destino(get_transicion(estados_intermedios[i], h)));	
			strcpy(nombre_simbolo, get_operador(get_transicion(estados_intermedios[i], h)));
			strcpy(nombre_inicio, get_nombre_estado(estados_intermedios[i]));		
			AFNDInsertaTransicion(afd, nombre_inicio, nombre_simbolo , estado_destino_existente);
		}

	}

	AFNDCierraLTransicion(afd);

	for(i = 0; i < num_intermedios; i++){
		eliminar_estado(estados_intermedios[i]);
	}

	free(estados_intermedios);
	free(conf_destino);
	
	return afd;
}


int nuevo_tipo_estado(AFND *afnd, int pos, int anterior) {
	if (anterior == INICIAL) {
		if(AFNDTipoEstadoEn(afnd, pos) == INICIAL || AFNDTipoEstadoEn(afnd, pos) == NORMAL)
			return INICIAL;

		if(AFNDTipoEstadoEn(afnd, pos) == FINAL || AFNDTipoEstadoEn(afnd, pos) == INICIAL_Y_FINAL)
			return INICIAL_Y_FINAL;
	}

	if (anterior == FINAL) {
		if(AFNDTipoEstadoEn(afnd, pos) == INICIAL || AFNDTipoEstadoEn(afnd, pos) == INICIAL_Y_FINAL)
			return INICIAL_Y_FINAL;

		if(AFNDTipoEstadoEn(afnd, pos) == FINAL || AFNDTipoEstadoEn(afnd, pos) == NORMAL)
			return FINAL;
	}

	if (anterior == INICIAL_Y_FINAL) {
		return INICIAL_Y_FINAL;
	}

	if (anterior == NORMAL) {
		if(AFNDTipoEstadoEn(afnd, pos) == INICIAL)
			return INICIAL;
		if(AFNDTipoEstadoEn(afnd, pos) == FINAL)
			return FINAL;
		if(AFNDTipoEstadoEn(afnd, pos) == INICIAL_Y_FINAL)
			return INICIAL_Y_FINAL;
		
	}

	return NORMAL;

}