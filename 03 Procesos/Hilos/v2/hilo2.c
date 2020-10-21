#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_HILOS 4

void * funcHilo(void * arg);

int main()
{	
	register int nh;
	pthread_t tids[NUM_HILOS];  // Arreglo de identificadores
	int *resultado;
	
	printf("Ejemplo de hilos\n");

	for (nh = 0; i < NUM_HILOS; nh++)
	{
		// tid, atributos, la funcion a ejecutar, parametros
		// Le mandamos el número del hilo
		pthread_create(&tids[nh], NULL, funcHilo, (void *)&nh);
	}

	// , lo que retorna el valor del hilo

	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		pthread_join(tids[nh], (void **)&resultado);
		printf("El resultado es: %d\n", *resultado);
	}

	return 0;
}

void * funcHilo(void * arg)
{
	// Primero casteo y luego obtengo su contenido
	int nh = *(int *)arg; 

	int num1 = 20, num2 = 4;
	static int res;

	printf("Hilo %d en ejecución.\n", nh);
	if (nh == 0)
	{
		res = num1 + num2;
	}
	else if (nh == 1)
	{
		res = num1 - num2;
	}
	else if (nh == 2)
	{
		res = num1 * num2;
	}
	else if (nh == 3)
	{
		res = num1 / num2;
	}

	pthread_exit((void *)&res);
}