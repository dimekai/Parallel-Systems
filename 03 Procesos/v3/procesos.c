/**
* @brief: procesos.c
* @desc: Contiene las funciones de proceso_padre y 
*		 proceso_hijo con el fin de realizar las 
* 		 operacion según el número de proceso.
**/

#include <sys/types.h>	// Para wait
#include <sys/wait.h>	// Para wait
#include <stdio.h>	 // Para printf
#include <stdlib.h>  // Para exit

#include "defs.h"
#include "procesamiento.h"   // contiene las funciones de las operaciones

void proceso_padre()
{
	register int np;
	pid_t pid;
	int estado;

	for (np = 0; np < NUM_PROC; np++)
	{
		pid = wait(&estado);
		printf("Proceso con PID: %d ", pid);

		if (np == 0)
		{
			printf("y el numero mayor es: %d\n", (estado>>8));
		}
		else if (np == 1)
		{
			printf("y el numero menor es: %d\n", (estado>>8));	
		}
		else if (np == 2)
		{
			printf("y el promedio es: %d\n", (estado>>8));
		}
		else if (np == 3)
		{
			printf("y hay %d numeros pares\n", (estado>>8));
		}
		//printf("Proceso con PID: %d y retorno %d \n", pid, (estado>>8));
	}
}

void proceso_hijo(int np, int *datos)
{
	int mayor, menor, promedio, nums_pares;
	
	if (np == 0)
	{
		mayor = buscarMayor(datos);
		exit(mayor);
	}
	else if (np == 1)
	{
		menor = buscarMenor(datos);
		exit(menor);
	}
	else if (np == 2)
	{
		promedio = calcularPromedio(datos);
		exit(promedio);
	}
	else if (np == 3)
	{
		nums_pares = cuantosPares(datos);
		exit(nums_pares);
	}
}