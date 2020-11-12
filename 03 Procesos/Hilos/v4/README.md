Los datos normalmente vienen de un periferico
- Cámara
- UART: Tomando datos de una señal de pulso cardiaco y llena arreglo de forma continua
- Interfaz SPI: Para conectar sensores y obtener los datos

Estos periféricos necesitan un arreglo en donde puedan colocar la información que están recopilando.
Y posteriormente usar hilos para realizarlo y luego mandar otros hilos para su respectivo proceso.

Cuando manejamos hilos reentrancia de una función:
- Si tengo una función sleep, cuando entro por primera vez a ejecutar el primer hilo, cuenta 
- Seguramente el planificador va a mandar a mi hilo a dormir y le dara tiempo a otro proceso
- Y luego, el segundo hilo, también manda a llamar la función sleep

-> Tengo dos hilos que quieren usar la misma función


| Hilo1 | Hilo2 | Hilo3 | Hilo4 |
|-------|-------|-------|-------|
|sleep(1)| sleep(1)|sleep(1)|
| count_time++ (0...34872)| count_time++ (0...21732)| count_time(0...)


El contador sleep pierde o se va modificando su valor original, pero los otros dos o tres hilos ya modificaro a ese valor

La función es reentrante ya que PUEDE RECUPERARSE DE UNA INTERRUPCIÓN DESPUES DESCANSO, en ambientes de multiples procesos.

Y si no puede volver a su valor original, es una función no reentrante.

sleep() es NO REENTRANTE. No se puede usar con hilos.


0 - 1

0001  
1110	 complemento a 1
----

  1110
+ 0001
 -----
  1111	 complemento a 2
  
  1111 equivale a -1

Y si es 64

32 bits : 1111 1111 1111 1111 1111 1111 1111 1111	->	-1

CONDICION DE CARRERA
- CUANDO HAY VARIABLES COMPARTIDAS EN HILOS
UN HILO 1 ENTRA A MODIFICAR EL CONTADOR CUANDO EL HILO 0 AUN NO TERMINA DE USARLA
UN HILO 2 ENTRA A MODIFICAR EL CONTADOR CUANDO EL HILO 1 AUN NO TERMINA DE USARLA
Y ASI SUCESIVAMENTE (VER Hilo4.c)

Para evitar condiciones de carrera las variables compartidas deben de estar en exclusión mutua.
y igual forma, establecer una sección crítica (la sección del codigo que no debe de ser interrumpida por otro proceso/hilo
es en donde les digo NO ME MOLESTEN.)

CHECAR DIAPOSITIVA DE SINCRONIZACION


lock -> dice en donde empieza seccion criticva
