
#ifndef INTERMEDIA_H
#define INTERMEDIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"

#define MAX_NOMBRE 200
#define MAX 200

typedef struct _EstadoIntermedio EstadoIntermedio;
typedef struct _Transicion Transicion;

Transicion *crear(int estado_posibles, char *operador, char *destino, int *estado_final);
char *get_destino(Transicion *trans);
char *get_operador(Transicion *trans);
int * get_configuracion(Transicion *trans);
void eliminar_transicion(Transicion *trans);
EstadoIntermedio *crear_estado(char nombre[MAX_NOMBRE], int estado_posibles, int tipo_estado, int *estados);
char *get_nombre_estado(EstadoIntermedio *estado);
int get_tipo_estado(EstadoIntermedio *estado);
int get_transiciones_guardadas(EstadoIntermedio *estado);
void set_nombre_estado(EstadoIntermedio *estado, char nombre[MAX_NOMBRE]);
void set_tipo_estado(EstadoIntermedio *estado, int tipo_estado);
void set_transicion(EstadoIntermedio *estado, int pos, Transicion *trans);
Transicion *get_transicion(EstadoIntermedio *estado, int pos);
void eliminar_estado(EstadoIntermedio *estado);
void imprimir_estado(EstadoIntermedio *estado, int estados);

#endif
