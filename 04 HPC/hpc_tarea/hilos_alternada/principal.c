/**
 * @brief: principal.c
 * @desc: Programa con paralelismo a nivel de datos
 *        y alto rendimiento utilizando procesos con
 *        tuberias (pipes)      
**/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#include "defs.h"
#include "helper.h"
#include "hilos.h"
#include "procesamiento.h"
#include "archivos.h"

// Estas variables no son compartidas, sino que son copias.
float *heartbeat, *windowHann, *result;

int main()
{
	register int nh;
	pthread_t tids[NUM_PROC];
	int nhs[NUM_PROC], *hilo;
		
	heartbeat = reservarMemoria();  // Pulso cardiaco
    readHeartbeatData(heartbeat);   // Leemos los datos del archivo .dat
	saveData(heartbeat, "heartbeat.dat");
    //imprimirArreglo(heartbeat);

	windowHann = reservarMemoria(); // Ventana Hann
	HannWindow(windowHann); // Generamos los ventana
    saveData(windowHann, "windowHann.dat");
    //imprimirArreglo(windowHann);

    result = reservarMemoria();

	printf("Probando hilos...\n");

	for (nh = 0; nh < NUM_PROC; nh++)
	{
		nhs[nh] = nh;
		pthread_create(&tids[nh], NULL, funcHilo, (void *)&nhs[nh]);
	}
	
	for (nh = 0; nh < NUM_PROC; nh++)
	{
		pthread_join(tids[nh], (void **)&hilo);
		printf("Hilo %d ha terminado.\n", *hilo);
	}
	
	//imprimirArreglo(result);
    saveData(result, "resultVentana.dat");

	free(heartbeat);
	free(windowHann);
	free(result);

	return 0;
}

