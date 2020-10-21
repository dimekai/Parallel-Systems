#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "defs.h"
#include "helper.h"
#include "procesos.h"

int main()
{	
	// Para la semilla será el pid del proceso padre
	srand(getpid());

	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2];  // File descriptor
	int edo_pipe;

	int *datos = reservarMemoria(N);
	llenarArreglo(datos);
	printf("======================== CONJUNTO DE DATOS ======================");
	imprimirArreglo(datos);
	printf("=================================================================\n\n");


	printf("Probando procesos\n");

	for (np = 0; np < NUM_PROC; np++)
	{
		edo_pipe = pipe(&pipefd[np][0]);  // Estamos en la direccion del primer elemento de la tuberia correspondiente

		if (edo_pipe == -1)
		{
			perror("Error al crear la tuberia (pipe)...\n");
			exit(EXIT_FAILURE);
		}

		pid = fork();

		// Verificamos si hay un error
		if (pid == -1)
		{
			perror("Error al crear el proceso\n");
			exit(EXIT_FAILURE);
		}

		// Si pid es 0 : es el hijo
		if (!pid)
		{
			// le pasamos el numero de proceso (np)
			proceso_hijo(np, &pipefd[np][0], datos);   // Aqui hacemos la tubería dedicada
		}
	}
	proceso_padre(pipefd);

	// Liberamos la memoria
	free(datos);

	return 0;
}

