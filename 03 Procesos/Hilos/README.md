# Hilos (Threads)

__Hilos__: Son objetos dinámicos, cada uno de los cuáles ejecuta una secuencia de instrucciones y que comparten entre sí los recursos del proceos.

- Comparte los recursos del proceso padre
- Las varibales declaradas la pueden usar todos los hilos, por lo que __tiene memoria compartida__. Pero puede haber __problemas de condiciones de carrera__.


##Concurrencia
- Es el número máximo de hilos que podría estar ejecutando simultáneamente si dispusiera de un número ilimitado de procesadores y depende de la aplicación.

Paralelismo
- Es el número real de hilos que se están ejecutando simultáneamente en un momento determinado y por lo tanto está limitado por el número de procesadores y por la carga actual del sistema.


> La _principal diferencia_ entre __Paralelismo y Concurrencia__.

POner imagen de procesos pantalla negra con 2 procesos

Poner imagen de grafica paralelismo vs concurrencia

Con 8 procesos
No tengo 8 cores dedicados para cada proceso, sino menos.
1 core atendiendo a 2 procesos: DIvide su 100% en 2 y los atiende por pedazos de tiempo
- AQUI OCURRE CONCURRENCIA
- UN core tiene que atender a varios procesos y su tiempo de cpu lo divide
- Concurrencia. CUantos proesos llega a manejar un solo nucleo 

Ejemplo

CORE 1	- P1 (50%)
(100%)	- P2 (50%)

CORE 2	- P3 (50%)
(100%)	- P4 (50%)

CORE 3	- P5 (50%)
(100%)	- P6 (50%)

CORE 4	- P7 (50%)
(100%)	- P8 (50%)

Ejecución entre `cores` es __en forma paralela__, pero la ejecución entre procesos de un determinado core es __en concurrencia__.



