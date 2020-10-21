/**
* @brief: procesamiento.c
* @desc: Este archivo contiene las funciones 
*        que realizan las operaciones de: Ordenamiento
*		 de burbuja, calcular el promedio del conjunto
*		 de datos, encontrar el número de elementos pares
*		 y multiplicar los elementos por una constante 
*		 para posteriormente paralelizarlo
*/

#include "defs.h"

void bubbleSort(int * datos)
{
	register int i, j, tmp;

	for (i = 1; i < N; i++)
	{
		tmp = datos[i];
		j = i - 1;
		
		while ((datos[j] > tmp) && (j >= 0))
		{
			datos[j + 1] = datos[j];
			j--;
		}
		datos[j + 1] = tmp;
	}
}

int calcularPromedio(int * datos)
{
	long promedio = datos[0];
	register int i;
	for (i = 1; i < N; i++)
	{
		promedio += datos[i];
	}

	return (int)(promedio / N);
}

int cuantosPares(int * datos)
{
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

void multiplicarArreglo(int * datos)
{
	register int i;
	for (i = 0; i < N; i++)
	{
		datos[i] = datos[i] * C;
	}
}
