#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_HILOS 4
#define NUM_ELEM 16

void *funHilo( void *arg );
int * reservarMemoria();
void llenarArreglo(int *datos);
void imprimirArreglo(int *datos);

int *A, *B, *C;

int main()
{
	register int nh;
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS];
	int *n_hilo_terminado;

	printf("Ejemplo HPC\n");

	A = reservarMemoria();
	B = reservarMemoria();
	C = reservarMemoria();

	srand(getpid());
	llenarArreglo(A);
	llenarArreglo(B);

	imprimirArreglo(A);
	imprimirArreglo(B);

	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		nhs[nh] = nh;
		//nhs[0] = 0;
		//nhs[1] = 1;
		//nhs[2] = 2;
		//nhs[3] = 3;
		pthread_create( &tids[nh] , NULL, funHilo, (void *)&nhs[nh] );
	}

	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		pthread_join( tids[nh], (void **) &n_hilo_terminado );
		printf("El hilo %d termino\n", *n_hilo_terminado);
	}

	imprimirArreglo(C);

	free(A);
	free(B);
	free(C);

	return 0;
}

void *funHilo( void *arg )
{
	int numero_hilo = *(int *) arg;

	register int i;

	printf("Hilo %d en ejecución \n", numero_hilo);

	for(i = numero_hilo; i < NUM_ELEM; i += NUM_HILOS)
	{
		C[i] = A[i] * B[i];
	}

	pthread_exit( arg );
}

int * reservarMemoria()
{
	int *mem;

	mem = (int *)malloc(NUM_ELEM*sizeof(int));

	if(!mem)
	{
		perror("Error al asignar memoria...\n");
		exit(EXIT_FAILURE);
	}

	return mem;
}

void llenarArreglo(int *datos)
{
	for(register int i; i < NUM_ELEM; i++)
		datos[i] = rand() % 256;
	
}

void imprimirArreglo(int *datos)
{
	for( register int i = 0; i < NUM_ELEM; ++i)
	{
		if(!(i%16))
			printf("\n");
		printf("%3d ", datos[i]);
	}
	printf("\n");
}
