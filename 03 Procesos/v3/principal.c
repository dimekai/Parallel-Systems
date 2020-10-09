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
	int *datos;

	printf("Probando procesos\n");

	datos = reservarMemoria(N);
	llenarArreglo(datos);
	imprimirArreglo(datos);

	for (np = 0; np < NUM_PROC; np++)
	{
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
			proceso_hijo(np, datos);
		}
	}
	proceso_padre();
	
	// Liberando la memoria
	free(datos);

	return 0;
}
