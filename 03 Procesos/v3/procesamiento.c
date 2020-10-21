/**
* @brief: procesamiento.c
* @desc: Este archivo contiene las funciones que
*		 realizan las operaciones de: búsqueda de
*		 mayor y menor en el arreglo, promedio del
*		 conjunto de datos y encontrar la cantidad
*		 de números pares en el conjunto de datos
**/

#include "defs.h"

int buscarMayor(int * datos)
{
	int mayor = datos[0];
	register int i;

	for (i = 1; i < N; i++)
	{
		if (datos[i] > mayor)
		{
			mayor = datos[i];
		}
	}

	return mayor;
}

int buscarMenor(int * datos)
{
	int menor = datos[0];
	register int i;

	for (i = 1; i < N; i++)
	{
		if (datos[i] < menor)
		{
			menor = datos[i];
		}
	}

	return menor;
}

int calcularPromedio(int * datos)
{
	long promedio = datos[0];
	register int i;

	for (i = 1; i < N; i++)
	{
		promedio += datos[i];
	}

	return (int)(promedio/N);
}

int cuantosPares(int * datos){
	int nums_pares = 0;
	register int i;

	for (i = 0; i < N; i++)
	{
		if (!(datos[i]&1))
		{
			nums_pares++;
		}
	}

	return nums_pares;
}
