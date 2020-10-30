
#include "intermedia.h"

typedef struct _EstadoIntermedio {
	char nombre[MAX_NOMBRE];
	int *config_estado;
	int tipo_estado;
	int transiciones_guardadas;
	Transicion transiciones[MAX];

}_EstadoIntermedio;

typedef struct _Transicion{
	char operador;
	char destino[MAX_NOMBRE];
	int *config_estado_destino;

}Transicion;


Transicion *crear(int estado_posibles, char operador, char destino[MAX_NOMBRE], int *estado_final){
	Transicion *trans = NULL;

	//Reservamos memoria para la nueva transicion
	trans = (Transicion*) malloc(sizeof(Transicion));
	if (trans == NULL){
		printf("Error creando nueva transicion");
		return NULL;
	}

	trans.operador = operador;
	trans.destino = destino;

	//Reservamos memoria para la configuracion que tendra el estado al que se transita
	trans->config_estado_destino = (int *)malloc(sizeof(estado_posibles*(int)));
	if (trans->config_estado == NULL){
		printf("Error creando el estado de destino");
		return NULL;
	}

	for (int i=0; i < estado_posibles; i++) {
		trans->config_estado_destino[i] = estado_final[i]  //estado_final será un array de estados si hay + de 1
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

void eliminar_transicion(Transicion *trans) {
	if(!trans) {
		printf("No se pudo eliminar, argumento de entrada no válido");
		return NULL;
	}

	free(trans->config_estado_destino);
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

	estado.nombre = nombre;
	estado.tipo_estado = tipo_estado;

	//Reservamos memoria para la configuracion del estado nuevo
	estado->config_estado = (int *)malloc(estado_posibles*(int));

	for (int i = 0; i < estado_posibles; i++) {
		estado->config_estado[i] = estados[i]
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
		return NULL;
	}

	return estado->tipo;
}

int *get_configuracion_estado(EstadoIntermedio *estado) {
	if (!estado){
		printf("Argumento de entrada no válido");
		return NULL;
	}
	return estado->config_estado;
}

char *set_nombre_estado(EstadoIntermedio *estado, char nombre[MAX_NOMBRE]) {
	if(!estado || !nombre) {
		printf("Argumentos de entrada no válidos");
		return NULL;
	}

	estado.nombre = nombre;
}

void set_tipo_estado(EstadoIntermedio *estado, int tipo_estado){
	if(!estado || tipo < 0 || tipo > 3) {
		printf("Argumentos de entrada no válidos");
		return NULL;
	}

	estado.tipo_estado = tipo_estado;

}

void set_transicion(EstadoIntermedio *estado, int pos, Transicion *trans) {
	if (!estado || pos < 0 || !trans) {
		printf("Argumentos de entrada no válidos");
		return NULL;
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
		return NULL;
	}

	for (int i= 0; i <transiciones_guardadas; i++) {
		eliminar_transicion(estado->transiciones[i]);
	}

	free(estado->config_estado);
	free(estado);
}

void imprimir_trans(Transicion *trans, int estados) {
	if (!trans) {
		printf("Argumento de entrada no válido");
		return NULL;
	}

	printf("operador: %s\n", trans->operador);
	printf("Estado destino: %s\n", trans->destino);
	printf("Configuracion de estado destino:\n");

	for (int i= 0; i < estados; i++) {
		printf("-%d", trans->config_estado_destino[i]);
	}

}

void imprimir_estado(EstadoIntermedio *estado, int estados) {
	if (!trans) {
		printf("Argumento de entrada no válido");
		return NULL;
	}

	printf("Nombre del estado: %s\n", estado->nombre);
	printf("Tipo de estado: %d\n", estado->tipo_estado);
	printf("Configuración de estado:\n");

	for (int i=0; i <estados; i++) {
		printf("-%d", estado->config_estado[i]);
	}

	printf("\n");
	printf("Transiciones:\n");
	for (int j = 0;j < transiciones_guardadas; j ++){
		imprimir_trans(estado->transiciones[i]);
		printf("\n");
	}


}
