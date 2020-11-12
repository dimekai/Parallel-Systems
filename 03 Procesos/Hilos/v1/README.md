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
Vamos a generar un un programa que ejecute, por cada hilo, una operación aritmética básica: Suma, Resta, Multiplicación y División. Por simplicidad, se va a realizar y explicar solamente para una sola operación. 

1. Hacemos la definición de la función para esa operación:

	```c
		void * suma(void * arg);
	```

2. Definimos el identificador del hilo para esa operación:

	```c
		pthread_t tid_suma;
	```

3. Creamos el hilo de ejecución, dentro del `main`para esa operación:

	```c
		//            (tid, atributos, la funcion a ejecutar, parametros)
		pthread_create(&tid_suma, NULL, suma, NULL);
	```

4. Una vez hecho esto, al acabar el tiempo de procesamiento del hilo, regresará un valor. Para ello debemos definir una variable que cache ese resultado.

	```c
		int * res_suma;
	```

5. Posteriormente, obtenemos lo que retorna el valor del hilo.

	```c
		// Lo que retorna el valor del hilo
		pthread_join(tid_suma, (void **)&res_suma);
	```

6. Podemos ver la definición la función `suma`.

	```c
		...
		...
		void * suma(void * arg){
			int res;
			res = num1 + num2;
			// Lo va a cachar la función join, y lo almacena en res_suma
			pthread_exit((void *)&res);
		}
	```

	> Usando la función `pthread_exit`, el resultado de la operación suma lo va a cachar la función `pthread_join` y lo almacenará en `res_suma`.

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