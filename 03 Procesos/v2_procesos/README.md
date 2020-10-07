
# Generación de procesos v2: Proceso hijo y padre

## Descripción.
Este programa genera **`N`** elementos aleatorios y los guarda en un arreglo **`datos`**. Las tareas principales son crear dos procesos distintos para:
	1. Encontrar __el número mayor__ del arreglo.
	2. Encontrar __el número menor__ del arreglo.

## Estructura del código
Para empezar vamos a utilizar como plantilla el código de `proc1.c`, con algunas modificaciones realizadas. Este código lo llamaremos `proc2.c`, el cuál contendrá las siguientes funciones:
* `función main()`: Contiene la lógica de ejecución del programa principal.
* `función proceso_padre()`: Da una descripción de cada hijo, mostrando su `estado` y `PID` asociado. 
* `función proceso_hijo(np, datos)`: Dependiendo del número de proceso (**`np`**) que sea, llama a la función para encontrar el __mayor o menor número__ en el arreglo **`datos`**.
	* `np = 0`: Llama a la función `encontrarMayor(datos)`.
	* `np = 1`: Llama a la función `encontrarMenor(datos)`.
* `función reservarMemoria()`: Reserva memoria para el arreglo de enteros llamado _`datos`_.
* `función llenarArreglo(datos)`: Genera números entre 0 y 256 para los almacenarlos en el arreglo antes creado __`datos`__.
* `función imprimirArreglo(datos)`: Imprime los valores del arreglo __`datos`__ por filas (cada 16 elementos).
* `función encontrarMayor(datos)`: 	Encuentra el valor máximo en el arreglo __`datos`__.
* `función encontrarMenor(datos)`: Encuentra el valor mínimo en el arreglo __`datos`__.

### Ejecutar programa
Para poder ejecutar este programa es suficiente con ejecutar el comando __`make`__ en una terminal en la ruta donde tienes guardado el archivo __`proc2.c`__.

```
> user@computer:~/path $ make
> gcc -c proc2.c -Wall
> gcc proc2.o -o proc2 -lm
```

## Desarrollo
Vamos a ir definiendo cada una de las funciones tal y como se vio en clase. En un principio nuestro codigo [aquí](https://gist.github.com/JesusDiaz08/6703c5121482ad4d33ed24505476c608) se muestra.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Proceso hijo : suma
// Proceso padre: resta
int main()
{
	pid_t pid;
	int estado;

	printf("Probando procesos\n");

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
		exit(27);  // Es el número que se regresa en estado
	}
	else
	{
		sleep(10);  // Forzamos un estado zoombie: chismea el papá y se le olvida el hijo jaja
		printf("Proceso padre en ejecución\t");
		printf("PID: %d\n", getpid());
		// Espera a que el hijo termine su tarea y regresa el pid del procesos hijo
		pid = wait(&estado);
		//printf("El proceso hijo terminado es: %d, con estado: %d\n", pid, estado);
		printf("El proceso hijo terminado es: %d, con estado: %d\n", pid, (estado>>8));
	}

	return 0;
}

```

Ahora vamos a ir desarrollando cada una de las funciones.

### Función `proceso_hijo`
En un principio esta función solamente hace una llamada a la función `exit()`, pasándole el __número del proceso hijo que ha terminado__.

```c
void proceso_hijo(int np){
	for (;EVER;);
	// Es el numero del proceso hijo que ha terminado
	exit(np);
}
```

Sin embargo, al momento de ir desarrollando un poco más el programa, el contenido de esta función cambió con el fin de __encontrar el mayor o menor número del arreglo__ `datos` dependiendo del valor del índice.
En este caso el párametro __`np`__ actúa como nuestro índice para __ayudar a la distribución de tareas y procesos__.

```c
void proceso_hijo(int np, int *datos) {
	int mayor, menor;	
	if (np == 0){
		mayor = buscarMayor(datos);
		exit(mayor);
	}else if (np == 1){
		menor = buscarMenor(datos);
		exit(menor);
	}
}
```

### Función `proceso_padre`
El objetivo de esta función es saber qué proceso hijo se está ejecutando a partir de su `PID` y conocer su estado. Este estado es determinado gracias a la función `exit()` que se usa dentro de cada bloque en la función `proceso_hijo`.
Es importante mencionar que al momento de retornar el valor la función `exit()`, este valor se regresa __con un corrimiento de 8 bits a la izquierda__. 

Es decir, si nosotros hacemos lo siguiente: `exit(1)`, la salida será __256__.


|--------| 2^10 | 2^9 | 2^8 | 2^7 | 2^6 | 2^5 | 2^4 | 2^3 | 2^2 | 2^1 | 2^0|
|--------|------|---------|---------|---------|---------|---------|---------|---------|---------|---------|--------|
|        | 1024 | 512     | 256     | 128     | 64      |    32   |    16   |    8    |    4    |    2    |    1   |
|exit(1) |      |         |         |         |         |         |         |         |         |         |    1   |
|output  |      |         |  1      | 0       | 0       |    0    |    0    |    0    |    0    |    0    |    0   |


Si nosotros hacemos ahora `exit(2)`, ¿qué valor sería? Nos daría como salida el __512__.


|--------| 2^10 | 2^9 | 2^8 | 2^7 | 2^6 | 2^5 | 2^4 | 2^3 | 2^2 | 2^1 | 2^0|
|--------|------|---------|---------|---------|---------|---------|---------|---------|---------|---------|--------|
|        | 1024 | 512     | 256     | 128     | 64      |    32   |    16   |    8    |    4    |    2    |    1   |
|exit(2) |      |         |         |         |         |         |         |         |         |    2    |        |
|output  |      |    1    |  0      | 0       | 0       |    0    |    0    |    0    |    0    |    0    |    0   |


Siempre serán 8 bits recorridos a la izquierda. Por tanto, para recuperar el valor original lo que se debe hacer es recorrer el valor de retorno 8 bits hacia la derecha. En este caso, la variable `estado` contiene el valor de retorno de `exit()`, y es a esta variable a la que se le hace el corrimiento: `(estado>>8)`.

```c
void proceso_padre() {
	register int np;
	pid_t pid;
	int estado;
	
	for (np = 0; np < NUM_PROC; np++) {
		pid = wait(&estado);
		printf("Proceso hijo %d\tPID: %d \t terminando\n", (estado>>8), pid);
	}
}
```

### Función `main`
Si ahora nosotros reacomodamos el código un poco, nuestro código con estas dos nuevas funciones, se vería como [aquí](https://gist.github.com/JesusDiaz08/1ef6a2fdf5c502ceb26f294d54f9c56c):

```c 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROC 2
#define EVER 1

void proceso_padre();
void proceso_hijo(int np);

int main() {
	pid_t pid;
	register int np;
  
	printf("Probando procesos...\n");

	for (np = 0; np < NUM_PROC; np++) {
		pid = fork();

		// Verificamos si hay un error
		if (pid == -1) {
			perror("Error al crear el proceso\n");
			exit(EXIT_FAILURE);
		}

		// Si pid es 0 : es el hijo
		if (!pid) {
			// le pasamos el numero de proceso (np)
			proceso_hijo(np);
		}
	}
	proceso_padre();
  
	return 0;
}

void proceso_padre() {
	register int np;
	pid_t pid;
	int estado;

	for (np = 0; np < NUM_PROC; np++) {
		pid = wait(&estado);
		printf("Proceso hijo %d\tPID: %d \t terminando\n", (estado>>8), pid);
	}
}

void proceso_hijo(int np) {
	for (;EVER;);
	exit(np);  // Es el numero del proceso hijo que ha terminado
}
```