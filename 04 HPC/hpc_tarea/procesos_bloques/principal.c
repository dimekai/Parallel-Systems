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

#include "defs.h"
#include "helper.h"
#include "procesos.h"
#include "procesamiento.h"
#include "archivos.h"

// Estas variables no son compartidas, sino que son copias.
float *heartbeat, *windowHann, *result;

int main()
{
	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;

	heartbeat = reservarMemoria();  // Pulso cardiaco
    readHeartbeatData(heartbeat);   // Leemos los datos del archivo .dat
	saveData(heartbeat, "heartbeat.dat");
    //imprimirArreglo(heartbeat);

	windowHann = reservarMemoria(); // Ventana Hann
	HannWindow(windowHann); // Generamos los ventana
    saveData(windowHann, "windowHann.dat");
    //imprimirArreglo(windowHann);

    result = reservarMemoria();

	printf("Probando procesos...\n");

	for( np = 0; np < NUM_PROC; np++ )
	{
		edo_pipe = pipe( &pipefd[np][0] );
		if( edo_pipe == -1 )
		{
			perror("Error al crear la tuberia...\n");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if( pid == -1 )
		{
			perror("Error al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		if( !pid )
		{
			proceso_hijo( np, &pipefd[np][0] );
		}
	}
	proceso_padre( pipefd );

	//imprimirArreglo(result);
    saveData(result, "resultVentana.dat");

	free(heartbeat);
	free(windowHann);
	free(result);

	return 0;
}

