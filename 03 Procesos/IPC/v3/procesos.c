/**
* @brief: procesos.c
* @desc: Funciones de procesos padre e hijo que se 
*		 encargar de realizar las operaciones dependiendo
*		 del número del proceso utilizando tuberías (pipes)
**/

#include <stdio.h>		// para printf
#include <stdlib.h>		// para exit
#include <sys/types.h>	// para wait
#include <sys/wait.h>	// para wait
#include <unistd.h>		// para pid_t

#include "defs.h"			// Contiene la definicion de constantes
#include "procesamiento.h"	// contiene las funciones de las operaciones
#include "helper.h"			// contiene la funcion para imprimirArreglo

/**
* @name: proceso_padre
* @params:
*		pipedf : int array 2D
*			- Representa el arreglo descriptores que mantendra
*			  el control por cada una de las tuberias asociadas
*			  a cada uno de los procesos generados (4 procesos).
* @return: 
*		void
* @desc: Asigna tiempo de cpu a cada uno de los procesos hijos
*		 para obtener el resultado de su operacion asignada. 
*		 Una vez hecho esto, utiliza el descriptor de lectura para obtener
*		 los resultados y/o modificaciones hechas por las operaciones
*/
void proceso_padre(int pipefd[NUM_PROC][2])
{
	register int np;
	pid_t pid;

	int estado, numproc, resultado, datos[N];

	for (np = 0; np < NUM_PROC; np++)
	{
		// Verificamos qué proceso hijo ya terminó
		pid = wait(&estado);

		// Obtenemos el numero de proceso que terminó
		numproc = estado >> 8;

		// Cerramos el descriptor de archivo de escritura de la tuberia
		close(pipefd[numproc][1]);

		printf("Termina el proceso %d con PID %d\t", numproc, pid);
		
		if (numproc == 0)
		{
			// Algoritmo de burbuja
			printf("Ordenamiento burbuja\n");
			// Usamos el descriptor de lectura
			read(pipefd[numproc][0], datos, (sizeof(int) * N));
			printf("======================= CONJUNTO ORDENADO ======================");
			imprimirArreglo(datos);
			printf("================================================================\n\n");
		
		}
		else if (numproc == 1)
		{
			// Calcular el promedio

			// Usamos el descriptor de lectura
			read(pipefd[numproc][0], &resultado, sizeof(int));
			printf("El promedio es: %d\n", resultado);

		}
		else if (numproc == 2)
		{
			// Conocer el numero de elementos pares

			// Usamos el descriptor de lectura
			read(pipefd[numproc][0], &resultado, sizeof(int));
			printf("Total de numeros pares: %d\n\n", resultado);
		}
		else if (numproc == 3)
		{
			// Multiplicar elementos del conjunto por una constante
			printf("Multiplicar por 10 el conjunto de datos\n");
			// Usamos el descriptor de lectura
			read(pipefd[numproc][0], datos, (sizeof(int) * N));
			printf("===================== CONJUNTO MULTIPLICADO ====================");
			imprimirArreglo(datos);
			printf("================================================================\n\n");
		}

		// Cerramos el descriptor de lectura de cada proceso
		close(pipefd[numproc][0]);
	}
}

/**
* @name: proceso_hijo
* @params:
*		pipedf : int array 
*			- Representa el archivo descriptor que mantendra
*			  el control para la tuberia asociadas a cada 
*			  uno de los procesos generados (4 procesos).
*		datos : int pointer
*			- 
* @return: 
*		void
* @desc: Verifica el número de proceso que se va a ejecutar
*		 y con base en ello realiza su operación correspondiente
*		 En cada uno de los procesos, dado que vamos a escribir
*		 sobre la tubería, cerramos el descriptor de lectura y 
*		 usamos el descriptor de escritura para mandar el resultado
*		 de la operación. Finalmente regresamos el número de proceso
*		 utilizando la función exit para saber qué proceso hijo terminó
*/

void proceso_hijo(int np, int pipefd[], int * datos)
{
	int promedio, nums_pares;

	// Cerramos el descriptor de archivo de lectura
	close(pipefd[0]);

	if (np == 0)
	{
		bubbleSort(datos);

		// Usamos el descriptor de escritura de la tuberia
		write(pipefd[1], datos, (sizeof(int) * N));
	}
	else if (np == 1)
	{
		promedio = calcularPromedio(datos);

		// Usamos el descriptor de escritura de la tuberia
		write(pipefd[1], &promedio, sizeof(int));
	}
	else if (np == 2)
	{
		nums_pares = cuantosPares(datos);

		// Usamos el descriptor de escritura de la tuberia
		write(pipefd[1], &nums_pares, sizeof(int));
	}
	else if (np == 3)
	{
		multiplicarArreglo(datos);

		// Usamos el descriptor de escritura de la tuberia
		write(pipefd[1], datos, (sizeof(int) * N));
	}

	// A traves de la tuberia mandamos el resultado
	close(pipefd[1]);

	// Regresamos el número de proceso para saber quién termina
	exit(np);
}