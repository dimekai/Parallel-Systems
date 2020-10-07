# Generando procesos: Proceso hijo y padre

* Para poder ejecutar el siguiente programa lo que se debe de hacer es crear un archivo makefile:
	- `makefile`: Alberga las instrucciones de compilación para que no tengas que escribirlas cada vez que quieres compilar un archivo.
	- `make clean`: Elimina todos los archivos objetos (\*.o) generados en la compilación de los archivos.
	- `make install`: Establece el archivo en una ruta general para ejecutarlo en cualquier parte del sistema
		```
		> make install
		> muestreo
		```
	- `make uninsatll`: Dehace la ejecución del objetivo falso `make install`.

## Explicación
* `-lm` : Al utilizar el comando `-lm` lo que hace es que _linkear_ los archivos para poder trabajar con ello y que no marque errores.
* `-Wall`: Al usar este comando, le dice al compilador que nos muestre todos aquellos __warnings__. Esto es útil para visualizar aquellas variables y/o espacios de memoria no usados

## Reglas de patrón
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
