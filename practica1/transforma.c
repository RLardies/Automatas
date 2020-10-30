
#include "transforma.h"

AFND* AFNDTransforma(AFND* afnd){
	AFND* det;
	EstadoIntermedio **lista_intermedios = NULL;
	int tipo_estado = INICIAL;

	int num_total_estados = AFNDNumEstados(afnd);
	int num_total_simbolos = AFNDNumSimbolos(afnd);


	posicion_inicio = AFNDIndiceEstadoInicial(afnd);
	char nombre_inicio[MAX_NOMBRE] = AFNDNombreEstadoEn(afnd, posicion_inicio);

	configuracion_inicio = inicializar_configuracion(num_total_estados, posicion_inicio);

	//comprobamos si hay transiciones lambda
	for (int estado_AFND = 0; estado_AFND < num_total_estados; estado_AFND++) {
		if (AFNDCierreLTransicionIJ(afnd, estado_AFND, posicion_inicio) && (posicion_inicio != estado_AFND)) {
			strcat(nombre_inicio, AFNDNombreEstadoEn(afnd, estado_AFND));
			configuracion_inicio[estado_AFND] = 1;

			tipo_estado = tipo_estado(afnd, estado_AFND, tipo_estado);
		}

		//si no hay transiciones lambda cogemos el tipo de estado que tenga nuestro estado inicial en el afnd original (puede ser inicial o inicial y final)
		if(posicion_inicio == estado_AFND)
			tipo_estado = AFNDTipoEstadoEn(afnd, estado_AFND);
		
	}

	//inicializamos nuestra lista de estados intermedios
}

int *inicializar_configuracion(int num_total_estados, int posicion_inicio){
	configuracion_inicio = (int*) malloc (num_total_estados*(int));
	if (!configuracion_inicio) {
		return NULL;
	}

	for (int i=0; i < num_total_estados; i++) {
		if (i == posicion_inicio)
			configuracion_inicio[i] = 1;

		else
			configuracion_inicio[i] = 0;
	}

	return configuracion_inicio;
}

int tipo_estado(AFND *afnd, int pos, int anterior) {
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
		
		return NORMAL;
	}

}