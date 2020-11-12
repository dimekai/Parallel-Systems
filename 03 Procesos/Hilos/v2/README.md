# Hilos de Linux
> Para el `kernel` de Linux, no hay concepto de hilo. Linux implementa todos los hilos como procesos estándar.

El `kernel` de Linux no proporciona ninguna semántica de planificación especial o estructuras de datos para representar hilos.

> Un **hilo** es simplemente **un proceso que comparte ciertos recursos con otros proceso**.

## Creación de Hilos
 - Cada hilo tiene una **`task_struct`** única y aparece en el kernel como un proceso normal.
 - Los hilos se crean igual que las tareas normales, con la excepción de que en la llamada al sistema `clone()` se pasan banderas correspondientes a los recursos específicos que se van a compartir.

	```c
	clone(CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND, 0); 
	```
- Para una llamada al sistema `fork()` se tiene: 
	```c
		clone(SIGCHLD, 0);
	```
- `pthread_create`: Función para crear los hilos en espacio de usuario:
	```c
	#include <pthread.h>
	int pthread_create(
		pthread_t *thread, 
		const pthread_attr_t *attr,
		void *(*start_routine)(void *),
		void *arg);
	```
- `pthread_t`: Ayuda a conocer el **identificador del hilo**. Es análogo al `pid_t`.
- `pthread_join`: Espera a que se termine el hilo que se está ejecutando. Es el análogo al **wait**.
	```c
	int pthread_join(pthread_t thread, void **retval);
	``` 
- `**retval`: Sirve para **tener el status del hilo**.
- `pthread_exit`: Esta función termina la llamada al código del hilo y se retorna un valor en `retval`. Es la función equivalente al `exit` en procesos.


## Desarrollo
* Vamos a generar un un programa que ejecute, por cada hilo, una operación aritmética básica: Suma, Resta, Multiplicación y División. Por simplicidad, se va a realizar y explicar solamente para una sola operación. 
* Para la versión de este programa lo que haremos es generar una función global llamada `funcHilo` la cual **realizará cada una de las operación de forma paralela usando 4 hilos**.

1. Hacemos la definición de la función para esa operación:

	```c
		#define NUM_HILOS 4
		void * funcHilo(void * arg);
	```

2. Vamos a definir un **arreglo de identificadores de los hilos**. Considerando que habrá 4 hilos quedaría de la siguiente forma:

	```c
		// Arreglo de identificadores
		pthread_t tids[NUM_HILOS];
	```

3. Almacenaremos cada número de hilo, para esto vamos a **crear un arreglo que controlará la operación por cada número de hilo**. De esta forma mandaremos cada variable para cada número de hilo en específico. 

	```c
	int nhs[NUM_HILOS];
	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		// Le mandamos cada variable para cada numero de hilo
		nhs[nh] = nh;
		...
	}
	```

4. Posteriormente, creamos el iésimo hilo de ejecución, dentro del `main`para esa operación, considerando.

	```c
		for (nh = 0; nh < NUM_HILOS; nh++)
		{
			...
			//            (tid, atributos, la funcion a ejecutar, parametros)
			// Le mandamos el número del hilo
			pthread_create(&tids[nh], NULL, funcHilo, (void *)&nhs[nh]);
			...
		}
	```

En cada llamada la función va a tener un índice diferente. Es decir, `&nhs[nh]` a cada índice se le manda el índice de la variable propia:

	```c
		for (nh = 0; nh < NUM_HILOS; nh++)
		{
			/*
				nhs[0] = 0;	Para el primer hilo
				nhs[1] = 1; Para el segundo hilo
				nhs[2] = 2; Para el tercer hilo
				nhs[3] = 3; Para el cuarto hilo
			*/
		}
	```

**Nota 01:**
> Si se le manda una sóla dirección, **el valor de `res` se quedará con la ultima dirección o valor del ciclo**.

**Nota 02:**
> En **hilos** es **paso por referencia** y en **tuberias es paso por direcciones**.


4. Una vez hecho esto, al acabar el tiempo de procesamiento del hilo, regresará un valor. Para ello debemos definir una variable que cache ese resultado. Para ello iteraremos por el número de hilos.

	```c
		int * res_suma;
	```

5. Posteriormente, obtenemos lo que retorna el valor por cada hilo.

	```c
		for (nh = 0; nh < NUM_HILOS; nh++)
		{
			pthread_join(tids[nh], (void **)&resultado);
			printf("El resultado es: %d\n", *resultado);
		}
	```

6. Podemos ver la definición la función `funcHilo`.

	```c
		void * funcHilo(void * arg)
		{
			// Primero casteo y luego obtengo su contenido
			int nh = *(int *)arg; 
			int num1 = 20, num2 = 4;
			int *res = malloc(sizeof(int));
			printf("Hilo %d en ejecución.\n", nh);
			// Aqui hago la paralelización
			if (nh == 0)
			{
				*res = num1 + num2;
			}
			...
			pthread_exit((void *)res);
		}
	```

	* El valor de `arg` contendrá el número de hilo. Para poder obtener su valor, vamos a castearlo y luego obtenemos su contenido:

	```c
		int nh = *(int *)arg; 
	```

	* El resultado de cada operación
	* Usando la función `pthread_exit`, el resultado de la operación suma lo va a cachar la función `pthread_join` y lo almacenará en `res_suma`.

Sin embargo, después de que se ejecuta la función `suma` el valor del resultado, en la variable `res`, desaparecerá. Para poder evitar esto, hay dos opciones:

1. Usando `static`: Al usar la palabra reservada `static`, se mantiene el valor de `res` a pesar de que ha muerto la función. 

	```c
		...
		...
		void * suma(void * arg){
			static int res;
			res = num1 + num2;
			// Lo va a cachar la función join, y lo almacena en res_suma
			pthread_exit((void *)&res);
		}
	```

2. Usando `malloc`: Al reservar memoria, ésta permanecerá aún después de haber muerto la función.

	```c
		...
		...
		void * suma(void * arg){
			int * res = (int *)malloc(sizeof(int));
			*res = num1 + num2;
			// Lo va a cachar la función join, y lo almacena en res_suma
			pthread_exit((void *)&res);
		}
	```

	> Si utilizamos esta forma, al final debemos de liberar memoria con la función `free()`.
