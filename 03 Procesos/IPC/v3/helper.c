/**
* @brief: helper.c
* @desc: Este archivo contiene las funciones 
*   	 para reservar memoria oara el conjunto de
* 		 datos, llenar el conjunto de datos e 
*		 imprimir en pantalla el conjunto de datos
**/

#include <stdlib.h>  // Para malloc y exit
#include <stdio.h>	 // Para perror()
#include "defs.h"

int * reservarMemoria()
{
	int * mem = (int *)malloc(N * sizeof(int));

	// Verificamos si la memoria se asignó correctamente
	if (!mem)
	{
		perror("Error al asignar memoria...\n");
		exit(EXIT_FAILURE);
	}

	return mem;
}

void llenarArreglo(int * datos)
{
	register int i;
	for (i = 0; i < N; ++i)
	{
		// Generamos numeros aleatorios entre 0-255
		datos[i] = rand()%256;
	}
}

void imprimirArreglo(int * datos)
{
	register int i = 0;
	for (i = 0; i < N; ++i)
	{
		if (i%16 == 0)
		{
			printf("\n");
		}
		printf("%4d ", datos[i]);
	}
	printf("\n");
}