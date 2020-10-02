/**
* @brief: procesamiento.c
* @desc: Este programa genera una señal senoindal con 
*		 una frecuencia fundamental (f) y de muestreo (fs)
**/

#include <stdio.h>
#include <math.h>
#include "defs.h"

void generarSeno(float seno[])
{
	float f = 1000, fs = 45000;
	register int n;

	for (n = 0; n < MUESTRAS; n++)
	{
		seno[n] = sinf(2 * n * M_PI * f / fs);
	}
}
