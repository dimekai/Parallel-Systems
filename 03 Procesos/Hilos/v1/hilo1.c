#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int num1 = 20, num2 = 4;

void * suma(void * arg);
void * resta(void * arg);
void * multi(void * arg);
void * divi(void * arg);

int main()
{	
	int * res_suma, *res_resta, *res_multi, *res_divi;
	pthread_t tid_suma, tid_resta, tid_multi, tid_divi;
	
	printf("Probando procesos\n");

				// tid, atributos, la funcion a ejecutar, parametros
	pthread_create(&tid_suma, NULL, suma, NULL);
	pthread_create(&tid_resta, NULL, resta, NULL);
	pthread_create(&tid_multi, NULL, multi, NULL);
	pthread_create(&tid_divi, NULL, divi, NULL);

	// , lo que retorna el valor del hilo
	pthread_join(tid_suma, (void **)&res_suma);
	pthread_join(tid_resta, (void **)&res_resta);
	pthread_join(tid_multi, (void **)&res_multi);
	pthread_join(tid_divi, (void **)&res_divi);

	printf("Hilo de suma es: %d\n", *res_suma);
	printf("Hilo de resta es: %d\n", *res_resta);
	printf("Hilo de multiplicacion es: %d\n", *res_multi);
	printf("Hilo de division es: %d\n", *res_divi);
	
	free(res_multi);
	free(res_divi);

	return 0;
}


void * suma(void * arg){
	static int res;

	res = num1 + num2;

	pthread_exit((void *)&res);   // Lo va a cachar la función join, y lo almacena en res_suma
}

void * resta(void * arg){
	static int res;

	res = num1 - num2;

	pthread_exit((void *)&res);   // Lo va a cachar la función join
}

void * multi(void * arg){
	int * res = (int *)malloc(sizeof(int));

	*res = num1 * num2;

	pthread_exit((void *)res);   // Lo va a cachar la función join
}

void * divi(void * arg){
	int * res = (int *)malloc(sizeof(int));

	*res = num1 / num2;

	pthread_exit((void *)res);   // Lo va a cachar la función join
}
