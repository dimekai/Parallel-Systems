# Procesos

Esta carpeta contiene el ejemplos y ejercicios utilizando procesos.

1. __Directorio `v1`__: Contiene un programa sencillo para generar proceso hijo y proceso padre para sumar y restar dos números. 
2. __Directorio `v2`__: Contiene un programa que calcula el valor mayor y menor de un arreglo, asignando un proceso para cada tarea.

## Descripción de procesos


- La vida del __proceso__ inicia con la llamada al sistema `fork()`.
- El proceso que llama a `fork()` es el __padre__, mientras que el proceso nuevo es el __hijo__.
- El padre reanuda la ejecución y el hijo inicia la ejecución en el mismo lugar donde devuelve la llamada a `fork()`.
- El proceso termina y libera sus recursos con la llamada al sistema `exit()`.
- El proceso puede __preguntar sobre el estado de un proceso hijo terminado__ con al llamada al sistema `wait()`.
- Cuando un proceso termina __se coloca en un estado zombie__ que representa el proceso terminado hasta que el padre llama a `wait()`.

Para tener más detalles de llamada al sistema `fork()`, se puede ejecutar el comando `man fork` en una terminal.

```bash
NAME
       fork - create a child process

SYNOPSIS
       #include <sys/types.h>
       #include <unistd.h>

       pid_t fork(void);
....
....
```

## Detalles de ejecución

* Para poder ejecutar el siguiente programa lo que se debe de hacer es crear un archivo makefile:
	- `makefile`: Alberga las instrucciones de compilación para que no tengas que escribirlas cada vez que quieres compilar un archivo.
	- `make clean`: Elimina todos los archivos objetos (\*.o) generados en la compilación de los archivos.
	- `make install`: Establece el archivo en una ruta general para ejecutarlo en cualquier parte del sistema
		```
		> make install
		> muestreo
		```
	- `make uninsatll`: Dehace la ejecución del objetivo falso `make install`.

### Explicación
* `-lm` : Al utilizar el comando `-lm` lo que hace es que _linkear_ los archivos para poder trabajar con ello y que no marque errores.
* `-Wall`: Al usar este comando, le dice al compilador que nos muestre todos aquellos __warnings__. Esto es útil para visualizar aquellas variables y/o espacios de memoria no usados

### Reglas de patrón
* `%.o: %.c` : genera todos los archivos `%.o` a partir de todos los archivos `%.c`

* __Variable automáticas__: Nos ayuda a eemplazar un valor específico dentro de los comandos. En el comando, vamos a poner el mismo nombre de la dependencia.

	* $< trae el nombre de la primera dependencia de la regla. Es algo parecido a hacer esto:

	```
	#target : dependency
	muestreo.o: muestreo.c
		$(CC) -c muestreo.c $(CFLAGS)
	procesamiento.o: procesamiento.c
		$(CC) -c procesamiento.c $(CFLAGS)
	archivos.o: archivos.c
		CC) -c archivos.c $(CFLAGS)
	```

	* ¿Pero que vamos a hacer en la siguiente __lista de dependencias__?

	``` $(PROYECTO): muestreo.o procesamiento.o archivos.o ```

	* Aqui se necesitan las tres dependencias en el comando. Para ello necesitamos utilizar `$^`, después de ello ponemos `$@`, el cuál hace referencia al nombre del objetivo.

	```
	$(PROYECTO): muestreo.o procesamiento.o archivos.o
		$(CC) $^ -o $@ $(LFLAGS)
	```

	* Ahora debemos de sustituir la lista de dependencias para: 

	``` muestreo.o procesamiento.o archivos.o ```

	Para poder realizar esto debemos hacer uso de __wildcards__.

		- __wildcards__: Para poder contemplar toda la lista de dependencias antes mostradas debemos utilizar nuestro __wildcard__ de la siguiente forma:

		`src = $(wildcard *.c)`

		Esto específica a todos los archivos .c sin importar que nombre tenga. Si aplicamos esta misma idea para nuestra __lista de dependencias__ vemos el antes y después:

		* Antes:

			``` 
			$(PROYECTO): muestreo.o procesamiento.o archivos.o
				$(CC) $^ -o $@ $(LFLAGS)
			```

		* Después:

		```
		src = $(wildcard *.c)
		...
		...
		$(PROYECTO): $(src:%.c=%.o)
			$(CC) $^ -o $@ $(LFLAGS)
		```

### Makefile
A continuación se muestra el makefile para generar poder correr nuestro programa.

```sh
# Archivo Makefile usando cadenas para ejecucion

PROYECTO=project_name
DESTDIR=/usr/local/bin
CFLAGS=-Wall
LFLAGS=-lm
CC=gcc

# Source or file name .c
src=$(wildcard *.c)

all: $(PROYECTO)

# target : dependency
%.o: %.c
	$(CC) -c $< $(CFLAGS)

#$(PROYECTO): DependenciesList
$(PROYECTO): $(src:%.c=%.o)
	$(CC) $^ -o $@ $(LFLAGS)

.PHONY: clean

install: all
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

clean:
	rm -f *.o $(PROYECTO)
```