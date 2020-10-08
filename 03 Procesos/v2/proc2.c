#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define NUM_PROC 2
#define N 32	// Numero de datos
#define EVER 1

void imprimirArreglo(int *datos);
void llenarArreglo(int *datos);
int * reservarMemoria();
void proceso_padre();
void proceso_hijo(int np, int *datos);
int buscarMayor(int * datos);
int buscarMenor(int * datos);


// Proceso hijo : suma
// Proceso padre: resta
int main()
{
	pid_t pid;
	register int np;
	int *datos;

	printf("Probando procesos\n");

	datos = reservarMemoria(N);
	// Llenar el arreglo con numeros aleatorios
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
	
	// Reservando la memoria
	free(datos);

	return 0;
}

void imprimirArreglo(int *datos)
{
	register int i = 0;
	for (i = 0; i < N; i++)
	{
		if (i%16 == 0)
		{
			printf("\n");
		}
		printf("%3d ", datos[i]);
	}
	printf("\n");
}

void llenarArreglo(int *datos)
{
	register int i;
	for (i = 0; i < N; i++)
	{
		datos[i] = rand()%256;  // entre 0-255
	}

}

int * reservarMemoria()
{
	int *mem;
	mem = (int * )malloc(N * sizeof(int));

	// verificar que esta asignada correctamente
	if (!mem)
	{
		perror("Error al asignar memoria...\n");
		exit(EXIT_FAILURE);
	}

	return mem;
}

void proceso_padre()
{
	register int np;
	pid_t pid;
	int estado;

	for (np = 0; np < NUM_PROC; np++)
	{
		pid = wait(&estado);
		printf("Proceso hijo %d\tPID: %d \t terminando\n", (estado>>8), pid);
	}
}

// Clave: Mandarle un indice
// Np es el indice que ayuda a la distribución de tareas y procesos
void proceso_hijo(int np, int *datos)
{
	int mayor, menor;

	//for (;EVER;);
	
	if (np == 0)
	{
		mayor = buscarMayor(datos);
		exit(mayor);
	}
	else if (np == 1)
	{
		menor = buscarMenor(datos);
		exit(menor);
	}
	//exit(np);  // Es el numero del proceso hijo que ha terminado
}

int buscarMayor(int * datos)
{
	int mayor = datos[0];
	register int i;

	for (i = 1; i < N; i++)
	{
		if (datos[i] > mayor)
		{
			mayor = datos[i];
		}
	}

	return mayor;
}

int buscarMenor(int * datos)
{
	int menor = datos[0];
	register int i;

	for (i = 1; i < N; i++)
	{
		if (datos[i] < menor)
		{
			menor = datos[i];
		}
	}
	return menor;
}
