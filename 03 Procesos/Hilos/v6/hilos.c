/**
* @brief: hilos.c
* @desc: Función de hilo encargado de realizar las 
		 operaciones dependiendo del número del
		 proceso utilizando mutex
**/

#include <stdio.h>		// para printf
#include <stdlib.h>		// para exit
#include <pthread.h>	// para mutex

#include "procesamiento.h"	// contiene las funciones de las operaciones

extern int *datos;
extern pthread_mutex_t bloqueo;
extern int promedio, nums_pares, primos;

void * funcHilo(void *arg)
{
	int num_hilo = *(int *)arg;

	switch(num_hilo){
		case 0:
			//Definimos sección critica
			pthread_mutex_lock(&bloqueo);
			promedio = getAverage(datos);
			// Cerramos seccion critica
			pthread_mutex_unlock(&bloqueo);
			pthread_exit(&promedio);
			break;
		case 1:
			//Definimos sección critica
			pthread_mutex_lock(&bloqueo);
			nums_pares = countEvenNumbers(datos);
			// Cerramos seccion critica
			pthread_mutex_unlock(&bloqueo);
			pthread_exit(&nums_pares);
			break;
		case 2:
			//Definimos sección critica
			pthread_mutex_lock(&bloqueo);
			primos = countPrimes(datos);
			// Cerramos seccion critica
			pthread_mutex_unlock(&bloqueo);
			pthread_exit(&primos);
			break;
		case 3:
			//Definimos sección critica
			pthread_mutex_lock(&bloqueo);
			bubbleSort(datos);
			// Cerramos seccion critica
			pthread_mutex_unlock(&bloqueo);
			pthread_exit(arg);
			break;
		default:
			pthread_exit(arg);
			break;
	}
}