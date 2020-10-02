#  Aplicación para la función Seno con modulos

* La diferencia yace en que el código está en módulos, es decir, está contenido en distintos archivos para un mejor mantenimiento.

* En este ejemplo práctico generamos 512 muestras para la función `seno` con el fin de de poner visualizarlo utilizando la herramienta de `gnuplot`.
* Para poder ejecutar el siguiente programa lo que se debe de hacer es crear un archivo makefile:
	- `makefile`: Albergan instrucciones de compilación para que no tengas que escribirlas cada vez que quieres compilar un archivo.



## Explicación
* `-lm` : Al utilizar el comando `-lm` lo que hace es que _linkear_ los archivos para poder trabajar con ello y que no marque errores.
* `-Wall`: Al usar este comando, le dice al compilador que nos muestre todos aquellos __warnings__. Esto es útil para visualizar aquellas variables y/o espacios de memoria no usados