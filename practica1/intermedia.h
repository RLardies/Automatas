
#ifndef INTERMEDIA_H
#define INTERMEDIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"

#define MAX_NOMBRE 200
#define MAX 200

Transicion *crear(int estado_posibles, char operador, char destino[MAX_NOMBRE], int *estado_final);
char *get_destino(Transicion *trans);
char *get_operador(Transicion *trans);
void eliminar_transicion(Transicion *trans);
Estado *crear_estado(char nombre[MAX_NOMBRE], int estado_posibles, int tipo_estado, int *estados);
char *get_nombre_estado(Estado *estado);
int get_tipo_estado(Estado *estado);
char *set_nombre_estado(Estado *estado, char nombre[MAX_NOMBRE]);
void set_tipo_estado(Estado *estado, int tipo_estado);
void set_transicion(Estado *estado, int pos, Transicion *trans);
Transicion *get_transicion(Estado *estado, int pos);
void eliminar_estado(Estado *estado);

#endif
