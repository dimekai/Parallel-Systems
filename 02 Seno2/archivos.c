#include <stdlib.h>
#include <stdio.h>
#include "defs.h"	// Esta la definicion de MUESTRAS

void guardarDatos(float datos[])
{
	FILE *archivo;
	register int n;

	archivo = fopen("seno.dat", "w");

	// Verificamos que se haya abierto bien el programa
	if (!archivo)
	{
		perror("Error al abrir el arhcivo");
		exit(EXIT_FAILURE);
	}

	for (n = 0; n < MUESTRAS; n++)
	{
		fprintf(archivo, "%f \n", datos[n]);
	}

	// Cerramos el archivo
	fclose(archivo);
}