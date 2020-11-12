#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_HILOS 4

// Problema de condicion de carrera

void * funcHilo(void * arg);
int contador;

int main()
{	
	register int nh;
	pthread_t tids[NUM_HILOS];  // Arreglo de identificadores
	int *num_hilo, nhs[NUM_HILOS];
	
	printf("Ejemplo de hilos\n");

	contador = 0;

	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		nhs[nh] = nh;
		//nhs[0] = 0
		//nhs[1] = 1
		//nhs[2] = 2
		//nhs[3] = 3

		// tid, atributos, la funcion a ejecutar, parametros
		// Le mandamos el número del hilo
		pthread_create(&tids[nh], NULL, funcHilo, (void *)&nhs[nh]);

		// Cada llamada a funcion va a tener un indice diferente 
		// &nhs[nh]) a cada indice se le manda el indice de una varibale propia
		// 2a variable al 2o hilo

		// Si le mando solo una direccion
		//se queda con la ultima direccio o valor del ciclo


		// En hilos es paso por referencia y en tuberias es paso por direcciones

	}

	// , lo que retorna el valor del hilo

	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		pthread_join(tids[nh], (void **)&num_hilo);
		printf("Hilo %d terminado.\n", *num_hilo);	
	}

	return 0;
}

void * funcHilo(void * arg)
{
	// Primero casteo y luego obtengo su contenido
	int nh = *(int *)arg; 
	register int i = 0; 	// 32 bits  ->  1111 .... 1111 complemento a 2 (-1)

	contador++;
	printf("Hilo %d en ejecución con contador %d\n", nh, contador);
	
	//printf("Sleep de 1 segundo\n");
	//sleep(1); // es NO-REENTRANTE
	// Usamos la idea de los NOPS de Micros
	while((--i));   // Contará 4 GB de ciclo, 2^32 iteraciones    -> ON
	printf("Hilo %d en ejecución con contador %d\n", nh, contador);

	// Regreso cuál es el número de hilo que acaba
	pthread_exit(arg);
}