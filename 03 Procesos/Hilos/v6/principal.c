#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "defs.h"
#include "helper.h"
#include "hilos.h"

int *res, nhs[NUM_HILOS], *datos;
int promedio, nums_pares, primos;
pthread_mutex_t bloqueo;

int main()
{	
	register int nh;
	datos = reserveMemory();
	
	srand(getpid()); // Semilla aleatoria
	
	fillArray(datos);
	
	printf("======================== CONJUNTO DE DATOS ======================");
	printArray(datos);
	printf("=================================================================\n\n");

	// Arreglo de identificadores
	pthread_t tids[NUM_HILOS];

	// Inicializar el bloqueo
	pthread_mutex_init(&bloqueo, NULL);

	// Creacion de hilos
	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		nhs[nh] = nh;
		pthread_create(&tids[nh], NULL, funcHilo, (void *)&nhs[nh]);
	}

	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		pthread_join(tids[nh], (void **)&res);
		
		printf("Hilo %d terminado.\t", nh);

		// Mostramos los resultados
		switch(nh){
			case 0:
				printf("El promedio es: %d\n", *res);
				break;

			case 1:
				printf("Hay %d numeros pares\n", *res);
				break;

			case 2:
				printf("Hay %d numeros primos\n", *res);
				break;

			case 3:
				printf("Ordenamiento Burbuja\n");
				printf("======================= CONJUNTO ORDENADO ======================");
				printArray(datos);
				printf("================================================================\n\n");
				break;
		}

	}
	// Liberamos el objeto de bloqueo
	pthread_mutex_destroy(&bloqueo);

	return 0;
}
