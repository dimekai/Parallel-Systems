#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_HILOS 4

void * funcHilo(void * arg);
int num1 = 20, num2 = 4;
int res_suma, res_resta, res_multi, res_divi;

int main()
{	
	register int nh;
	pthread_t tids[NUM_HILOS];  // Arreglo de identificadores
	int *num_hilo, nhs[NUM_HILOS];
	
	printf("Ejemplo de hilos\n");

	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		nhs[nh] = nh;
		//nhs[0] = 0
		//nhs[1] = 1
		//nhs[2] = 2
		//nhs[3] = 3

		// tid, atributos, la funcion a ejecutar, parametros
		// Le mandamos el número del hilo
		pthread_create(&tids[nh], NULL, funcHilo, (void *)&nhs[nh]);

		// Cada llamada a funcion va a tener un indice diferente 
		// &nhs[nh]) a cada indice se le manda el indice de una varibale propia
		// 2a variable al 2o hilo

		// Si le mando solo una direccion
		//se queda con la ultima direccio o valor del ciclo


		// En hilos es paso por referencia y en tuberias es paso por direcciones

	}

	// , lo que retorna el valor del hilo

	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		pthread_join(tids[nh], (void **)&num_hilo);

		if (*num_hilo == 0){
			printf("La suma es: %d\n", res_suma);
		}
		else if (*num_hilo == 1){
			printf("La resta es: %d\n", res_resta);
		}
		else if (*num_hilo == 2){
			printf("La multiplicacion es: %d\n", res_multi);
		}
		else if (*num_hilo == 3){
			printf("La division es: %d\n", res_divi);
		}
	}

	return 0;
}

void * funcHilo(void * arg)
{
	// Primero casteo y luego obtengo su contenido
	int nh = *(int *)arg; 

	printf("Hilo %d en ejecución.\n", nh);
	
	// Aqui hago la paralelización
	if (nh == 0){
		res_suma = num1 + num2;
	}
	else if (nh == 1){
		res_resta = num1 - num2;
	}
	else if (nh == 2){
		res_multi = num1 * num2;
	}
	else if (nh == 3){
		res_divi = num1 / num2;
	}

	// Regreso cuál es el número de hilo que acaba
	pthread_exit(arg);
}