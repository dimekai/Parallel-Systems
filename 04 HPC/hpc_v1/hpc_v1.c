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
int *A, *B, *C;

int * reservarMemoria();
void llenarArreglo(int *datos);
void imprimirArreglo(int *datos);

int main()
{
	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;

	A = reservarMemoria();  // Senoinda
	B = reservarMemoria();  // Ventana Hann
	C = reservarMemoria();

	llenarArreglo(A);
	llenarArreglo(B);

	imprimirArreglo(A);
	imprimirArreglo(B);

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

	imprimirArreglo(C);

	free(A);
	free(B);
	free(C);

	return 0;
}

void proceso_padre( int pipefd[NUM_PROC][2] )
{
	register int np;
	pid_t pid;
	int estado, numproc;
	int elem_bloque = N / NUM_PROC;
	int ini_bloque;

	for( np = 0; np < NUM_PROC; np++ )
	{
		pid = wait(&estado);		// Regresa en donde termina el bloque
		numproc = estado >> 8;		// Estado cacha el valor del nucleo
		close( pipefd[numproc][1] );

		ini_bloque = numproc * elem_bloque;
		read( pipefd[numproc][0], C + ini_bloque, sizeof(int) * elem_bloque);
		printf("Termino el proceso %d con pid: %d \n", numproc, pid);
		
		close( pipefd[numproc][0] );
	}
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

	// Paralelización a nivel de datos
	for (i = ini_bloque; i < fin_bloque; i++)
		C[i] = A[i] * B[i];
	
				// direccion del bloque
	write(pipefd[1], C + ini_bloque, sizeof(int) * elem_bloque);

	close( pipefd[1] );
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
