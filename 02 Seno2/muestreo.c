/**
* @brief: muestreo.c
* @desc: Este programa genera una señal senoindal y 
*        la guarda en un archivo
**/

#include <stdio.h>
#include "archivos.h"        // Aqui se declara la funcion guardarDatos
#include "procesamiento.h"	 // Aqui se declara la funcion generarSeno
#include "defs.h"			 // Esta la definicion de MUESTRAS

int main(){

	float seno[MUESTRAS];
	generarSeno(seno);
	guardarDatos(seno);

	return 0;
}