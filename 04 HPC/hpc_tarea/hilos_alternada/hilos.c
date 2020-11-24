/**
 * @brief: procesos.c
 * @desc: Funciones de procesos padre e hijo que se
 *        encarga de realizar las operaciones dependiendo
 *        del número del procesos utilizando tuberías (pipes). 
**/

#include <stdio.h>		// para printf
#include <stdlib.h>		// para exit
#include <unistd.h>		// para pid_t
#include <pthread.h>    

#include "defs.h"			// Contiene la definicion de constantes

extern float *heartbeat, *windowHann, *result;

void * funcHilo(void * arg)
{
    register int i = 0;
    int nh = *(int *)arg;

    for (i = nh; i < N; i+=NUM_PROC)
    {
        result[i] = heartbeat[i] * windowHann[i];
    }
    pthread_exit(arg);
}
