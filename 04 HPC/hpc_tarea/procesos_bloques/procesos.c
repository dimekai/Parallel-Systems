/**
 * @brief: procesos.c
 * @desc: Funciones de procesos padre e hijo que se
 *        encarga de realizar las operaciones dependiendo
 *        del número del procesos utilizando tuberías (pipes). 
**/

#include <stdio.h>		// para printf
#include <stdlib.h>		// para exit
#include <sys/wait.h>	// para wait
#include <unistd.h>		// para pid_t

#include "defs.h"			// Contiene la definicion de constantes
#include "procesamiento.h"	// contiene las funciones de las operaciones
#include "helper.h"			// contiene la funcion para imprimirArreglo

extern float *heartbeat, *windowHann, *result;

void proceso_padre(int pipefd[NUM_PROC][2])
{
    register int np;
    int numproc, ini_bloque;
    int elem_bloque = N / NUM_PROC;
    pid_t pid;

    printf("Proceso padre ejecutado con PID %d\n", getpid());

    for (np = 0; np < NUM_PROC; np++)
    {
        // Regresa en donde termina el bloque
        pid = wait(&numproc);
        // numproc cacha el valor del nucleo
        numproc >>= 8;  // numproc = numproc >> 8;
        close(pipefd[numproc][1]);

        ini_bloque = numproc * elem_bloque;
        read(pipefd[numproc][0], result + ini_bloque, sizeof(int) * elem_bloque);
		printf("Termino el proceso %d con pid: %d \n", numproc, pid);
		
		close(pipefd[numproc][0]);
    }     
}

void proceso_hijo(int np, int pipefd[])
{
    register int i;
    int elem_bloque = N / NUM_PROC;
    int ini_bloque = np * elem_bloque;
	int fin_bloque = ini_bloque + elem_bloque;

    close(pipefd[0]);

    // Paralelización a nivel de datos
    for (i = ini_bloque; i < fin_bloque; i++)
        result[i] = heartbeat[i] * windowHann[i];
    
    // Dirección del bloque
    write(pipefd[1], result + ini_bloque, sizeof(int) * elem_bloque);
    
    close(pipefd[1]);
    exit(np);   // Regresa el nucleo al proceso padre
}