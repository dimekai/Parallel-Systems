#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Proceso hijo : suma
// Proceso padre: resta
int main()
{
	float num1 = 45, num2 = 12, suma, resta;
	pid_t pid;
	int estado;

	printf("Ejemplo de procesos\n");

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
		printf("Proceso hijo en ejecución\t");
		printf("PID: %d\n", getpid());
		suma = num1 + num2;
		printf("La suma es: %f\n\n", suma);
		// 1 -> 256 -> 100000000 : desplazado 8 bits a la izq
		exit(27);  // Es el número que se regresa en estado
	}
	else
	{
		sleep(10);  // Forzamos un estado zombie: chismea el papá y se le olvida el hijo jaja
		printf("Proceso padre en ejecución\t");
		printf("PID: %d\n", getpid());
		resta = num1 - num2;
		printf("La resta es: %f\n", resta);
		// Espera a que el hijo termine su tarea y regresa el pid del procesos hijo
		pid = wait(&estado);
		//printf("El proceso hijo terminado es: %d, con estado: %d\n", pid, estado);
		printf("El proceso hijo terminado es: %d, con estado: %d\n", pid, (estado>>8));
	}

	return 0;
}
