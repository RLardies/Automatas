#ifndef MINIMIZA_H
#define MINIMIZA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "intermedia.h"

AFND *AFNDMinimiza(AFND *afnd);
int *accesibles(AFND *afnd);
int ** distinguibles(AFND *afnd);


#endif