/**
* @brief: procesamiento.c
* @desc: Este archivo contiene las funciones que
*		 realizan las operaciones de: búsqueda de
*		 mayor y menor en el arreglo, promedio del
*		 conjunto de datos y encontrar la cantidad
*		 de números pares en el conjunto de datos
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "defs.h"

int getAverage(int *datos)
{
	register int i;
	int suma = 0;

	for(i = 0; i < N; i++)
	{
		suma += datos[i];
	}

	int promedio = (suma/N);
	return promedio;
}

int countEvenNumbers(int *datos)
{
	register int i;
	int nums_pares = 0;

	for (i = 0; i < N; i++)
	{
		if (!(datos[i]&1))
		{
			nums_pares++;
		}
	}

	return nums_pares;	
}

int countPrimes(int *datos)
{
	register int i, j;
	int primos = 0;
	bool isPrime = true;

	printf("Numeros primos: \t");
	for (i = 0; i < N; i++)
	{
		isPrime = true;
		if (datos[i] == 2)
		{
			primos++;
			continue;
		}
		else if (datos[i] < 2 || (!(datos[i]&1)))
		{
			isPrime = false;
			continue;
		}
		else
		{
			for (j = 3; j < datos[i]; j += 2)
			{
				// Comprobamos su divisibilidad
				if (!(datos[i] % j))
				{
					isPrime = false;
					continue;
				}
			}
		}

		if (isPrime)
		{
			primos++;
			printf("%d ", datos[i]);
		}
	}
	printf("\n\n");

	return primos;
}

void bubbleSort(int *datos)
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