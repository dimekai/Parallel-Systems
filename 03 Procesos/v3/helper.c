/**
* @brief: helper.c
* @desc: Este archivo contiene las funciones para
*		 reservar memoria para el conjunto de datos, 
*		 llenar el conjunto de datos e imprimir el 
*		 conjunto de datos 
**/

#include <stdlib.h>		// para malloc y exit
#include <stdio.h>		// para perror
#include "defs.h"

int * reservarMemoria()
{
	int *mem;
	mem = (int * )malloc(N * sizeof(int));

	// verificar que esta asignada correctamente
	if (!mem)
	{
		perror("Error al asignar memoria...\n");
		exit(EXIT_FAILURE);
	}

	return mem;
}

void llenarArreglo(int *datos)
{
	register int i;
	for (i = 0; i < N; i++)
	{
		datos[i] = rand()%256;  // entre 0-255
	}

}

void imprimirArreglo(int *datos)
{
	register int i = 0;
	for (i = 0; i < N; i++)
	{
		if (i%16 == 0)
		{
			printf("\n");
		}
		printf("%3d ", datos[i]);
	}
	printf("\n\n");
}
