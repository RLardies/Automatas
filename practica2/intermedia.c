#include "intermedia.h"



typedef struct _Transicion{
	char operador[MAX_NOMBRE];
	char destino[MAX_NOMBRE];
	int *config_estado_destino;

}Transicion;

typedef struct _EstadoIntermedio {
	char nombre[MAX_NOMBRE];
	int *config_estado;
	int tipo_estado;
	int transiciones_guardadas;
	Transicion **transiciones;

}EstadoIntermedio;


Transicion *crear(int estado_posibles, char *operador, char *destino, int *estado_final){
	Transicion *trans = NULL;

	//Reservamos memoria para la nueva transicion
	trans = (Transicion*) malloc(sizeof(Transicion));
	if (trans == NULL){
		printf("Error creando nueva transicion");
		return NULL;
	}

	strcpy(trans->operador, operador);
	strcpy(trans->destino, destino);

	//Reservamos memoria para la configuracion que tendra el estado al que se transita
	trans->config_estado_destino = estado_final;

	for (int i=0; i < estado_posibles; i++) {
		trans->config_estado_destino[i] = estado_final[i]; //estado_final será un array de estados si hay + de 1
	}

	return trans;

}

char *get_destino(Transicion *trans){
	if (!trans) {
		printf("Argumento de entrada no válido");
		return NULL;
	}
	return trans->destino;
}

char *get_operador(Transicion *trans) {
	if (!trans) {
		printf("Argumento de entrada no válido");
		return NULL;
	}
	return trans->operador;
}

int * get_configuracion(Transicion *trans){
	if (!trans) {
		printf("Argumento de entrada no válido");
		return NULL;
	}
	return trans->config_estado_destino;

}

int *inicializar_configuracion(int num_total_estados, int posicion_inicio){

	int * configuracion_inicio;

	configuracion_inicio = (int*) malloc (num_total_estados*sizeof(int));

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

void anadir_configuracion(int * conf, int num_total_estados, int posicion){

	for (int i=0; i < num_total_estados; i++) {
		if (i == posicion) conf[i] = 1;
	}

	return;
}

void eliminar_transicion(Transicion *trans) {
	if(!trans) {
		printf("No se pudo eliminar, argumento de entrada no válido");
		return;
	}
	free(trans);
}

EstadoIntermedio *crear_estado(char nombre[MAX_NOMBRE], int estado_posibles, int tipo_estado, int *estados) {
	EstadoIntermedio *estado = NULL;

	//reservamos memoria para la estructura

	estado = (EstadoIntermedio *)malloc(sizeof(EstadoIntermedio));
	if (!estado) {
		printf("Error creando nuevo estado");
		return NULL;
	}

	strcpy(estado->nombre, nombre);
	estado->tipo_estado = tipo_estado;
	estado->transiciones = NULL;
	estado->transiciones_guardadas = 0;


	estado->transiciones = (Transicion**)malloc(sizeof(Transicion*) * MAX);

	//Reservamos memoria para la configuracion del estado nuevo
	estado->config_estado = estados;

	for (int i = 0; i < estado_posibles; i++) {
		estado->config_estado[i] = estados[i];
	}

	return estado;

}

char *get_nombre_estado(EstadoIntermedio *estado){
	if (!estado) {
		printf("Argumento de entrada no válido");
		return NULL;
	}

	return estado->nombre;
}

int get_tipo_estado(EstadoIntermedio *estado) {
	if (!estado) {
		printf("Argumento de entrada no válido");
		return -1;
	}

	return estado->tipo_estado;
}

int get_transiciones_guardadas(EstadoIntermedio *estado) {
	if (!estado) {
		printf("Argumento de entrada no válido");
		return -1;
	}

	return estado->transiciones_guardadas;
}


int *get_configuracion_estado(EstadoIntermedio *estado) {
	if (!estado){
		printf("Argumento de entrada no válido");
		return NULL;
	}
	return estado->config_estado;
}

void set_nombre_estado(EstadoIntermedio *estado, char nombre[MAX_NOMBRE]) {
	if(!estado || !nombre) {
		printf("Argumentos de entrada no válidos");
		return ;
	}

	strcpy(estado->nombre, nombre);


}

void set_tipo_estado(EstadoIntermedio *estado, int tipo_estado){
	if(!estado || tipo_estado < 0 || tipo_estado > 3) {
		printf("Argumentos de entrada no válidos");
		return;
	}

	estado->tipo_estado = tipo_estado;

}

void set_transicion(EstadoIntermedio *estado, int pos, Transicion *trans) {
	if (!estado || pos < 0 || !trans) {
		printf("Argumentos de entrada no válidos");
		return;
	}
	estado->transiciones[pos] = trans;
	estado->transiciones_guardadas += 1;
}

Transicion *get_transicion(EstadoIntermedio *estado, int pos) {
	if (!estado || pos < 0) {
		printf("Argumentos de entrada no válidos");
		return NULL;
	}
	return estado->transiciones[pos];
}

void eliminar_estado(EstadoIntermedio *estado) {
	if (!estado) {
		printf("Argumento de entrada no válido");
		return ;
	}

	for (int i= 0; i < estado->transiciones_guardadas; i++) {
		eliminar_transicion(estado->transiciones[i]);

	}
	if(estado->config_estado) free(estado->config_estado);
	free(estado->transiciones);
	free(estado);
}

void imprimir_trans(Transicion *trans, int estados) {
	if (!trans) {
		printf("Argumento de entrada no válido");
		return;
	}

	printf("operador: %s\n", trans->operador);
	printf("Estado destino: %s\n", trans->destino);
	printf("Configuracion de estado destino:\n");

	for (int i= 0; i < estados; i++) {
		printf("-%d", trans->config_estado_destino[i]);
	}

}

void imprimir_estado(EstadoIntermedio *estado, int estados) {
	if (!estado) {
		printf("Argumento de entrada no válido");
		return ;
	}

	printf("\n\nNombre del estado: %s\n", estado->nombre);
	printf("Tipo de estado: %d\n", estado->tipo_estado);
	printf("Configuración de estado:\n");

	for (int i=0; i <estados; i++) {
		printf("-%d", estado->config_estado[i]);
	}

	printf("\n");
	printf("Transiciones:\n");
	for (int j = 0;j < estado->transiciones_guardadas; j ++){
		imprimir_trans(estado->transiciones[j], estados);
		printf("\n");
	}


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
