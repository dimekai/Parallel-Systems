#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_PROC 4
#define N 16

// Alto rendimiento con Pipes a nivel de datos

void proceso_padre( int pipefd[NUM_PROC][2] );
void proceso_hijo( int np, int pipefd[] );

// Estas variables no son compartidas, sino que son copias.
int *A, promedio;

int * reservarMemoria();
void llenarArreglo(int *datos);
void imprimirArreglo(int *datos);

int main()
{
	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;

	A = reservarMemoria();  // Senoinda

	llenarArreglo(A);
	imprimirArreglo(A);

	printf("Probando procesos...\n");
	promedio = 0;

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

	printf("El promedio es: %d\n", promedio);

	free(A);

	return 0;
}

void proceso_padre( int pipefd[NUM_PROC][2] )
{
	register int np;
	pid_t pid;
	int estado, numproc;
	int suma_parcial = 0;

	for( np = 0; np < NUM_PROC; np++ )
	{
		pid = wait(&estado);		// Regresa en donde termina el bloque
		numproc = estado >> 8;		// Estado cacha el valor del nucleo
		close( pipefd[numproc][1] );

		read( pipefd[numproc][0], &suma_parcial, sizeof(int));
		// v.a promedio del papa (obtengo lo que los hijos regresa)
		promedio += suma_parcial;
		printf("Termino el proceso %d con pid: %d \n", numproc, pid);
		
		close( pipefd[numproc][0] );
	}
	promedio >>= 4;
}

/**
Debemos de regresar el resultado del producto con el pipe
Conviene procesar por bloques para poder procesar elementos consecutivos
y podemos retornar los bloques de 4 elementos.
**/
void proceso_hijo( int np, int pipefd[] )
{
	register int i;
	int elem_bloque = N / NUM_PROC;
	int ini_bloque = np * elem_bloque;
	int fin_bloque = ini_bloque + elem_bloque;

	close( pipefd[0] );

	// Esta variable es diferente en cada proceso.
	promedio = 0;

	// Paralelización a nivel de datos
	for (i = ini_bloque; i < fin_bloque; i++)
		promedio += A[i];
	
				// direccion del bloque
	write(pipefd[1], &promedio, sizeof(int));

	close( pipefd[1] );  // Cerramos descriptor de escritura
	exit( np );  // Regresa el nucleo al proceso padre
}

int * reservarMemoria()
{
	int *mem;

	mem = (int *)malloc(N * sizeof(int));

	if(!mem)
	{
		perror("Error al asignar memoria...\n");
		exit(EXIT_FAILURE);
	}

	return mem;
}

void llenarArreglo(int *datos)
{
	register int i = 0;
	for(i = 0; i < N; i++)
	{
		datos[i] = rand()%256;
	}
	
}

void imprimirArreglo(int *datos)
{
	register int i;
	for(i = 0; i < N; ++i)
	{
		if(!(i%16))
		{
			printf("\n");
		}
		printf("%3d ", datos[i]);
	}
	printf("\n");
}
