#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_HILOS 4
#define N 16

void * funHilo( void * arg );
int *A, promedio;
pthread_mutex_t bloqueo;

int * reservarMemoria();
void llenarArreglo( int *datos );
void imprimirArreglo( int *datos );

int main()
{
	int *hilo;
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS];
	register int nh;

	A = reservarMemoria();

//	srand( getpid() );
	llenarArreglo( A );
	imprimirArreglo( A );

	promedio = 0;

	// Inicializar el bloqueo
	pthread_mutex_init(&bloqueo, NULL);

	printf("Probando hilos...\n");

	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		//nhs[0] = 0;
		//nhs[1] = 1;
		//nhs[2] = 2;
		//nhs[3] = 3;
		nhs[nh] = nh;
		pthread_create( &tids[nh], NULL, funHilo, &nhs[nh] );
	}

	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		pthread_join( tids[nh],  (void **)&hilo);
		printf("El hilo %d termino \n", *hilo );
	}
	
	// 2^4 = 16 Corrimiento se ejecuta en 1 ciclo de reloj y la divison en N, depende la arquitectura
	promedio >>= 4;  // promedio /= 16

	printf("Promedio del arreglo A es %d\n", promedio);

	free(A);

	// Liberamos el objeto de bloqueo
	pthread_mutex_destroy(&bloqueo);

	return 0;
}

void * funHilo( void * arg )
{
	int nucleo = *(int *)arg;
	register int i;
	int suma_parcial;

	printf("Hilo %d en ejecucion \n", nucleo);
	suma_parcial = 0;  // Para la paralelización y evitar iterativo

	for( i = nucleo; i < N; i += NUM_HILOS )
	{
		// Realiza la suma acumulado de cada parte del arreglo
		suma_parcial += A[i];
	}

	pthread_mutex_lock(&bloqueo);
	promedio += suma_parcial;
	pthread_mutex_unlock(&bloqueo);

	pthread_exit( arg );
}

/*
void * funHilo( void * arg )
{
	int nucleo = *(int *)arg;
	int eleBloque = N / NUM_HILOS;	//tamaño de bloque
	int iniBloque = nucleo * eleBloque;
	int finBloque = iniBloque + eleBloque;
	register int i;

	printf("Hilo %d en ejecucion \n", nucleo);

	for( i = iniBloque; i < finBloque; i++)
	{
		C[i]  = A[i] * B[i];
	}

	pthread_exit( arg );
}*/

void imprimirArreglo( int *datos )
{
	register int i;

	for( i = 0; i < N; i++ )
	{
		if( !(i%16) )
			printf("\n");
		printf("%3d ", datos[i]);
	}
	printf("\n\n");
}

void llenarArreglo( int *datos )
{
	register int i;

	for( i = 0; i < N; i++ )
	{
		datos[i] = rand() % 256;
	}
}

int * reservarMemoria()
{
	int *mem;

	mem = (int *)malloc( N*sizeof(int) );
	if( !mem )
	{
		perror("Error al asignar memoria\n");
		exit(EXIT_FAILURE);
	}

	return mem;
}

