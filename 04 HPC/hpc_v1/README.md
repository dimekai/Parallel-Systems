# Multiplicación de arreglos usando tuberías

- Vamos a realizar un HPC por bloques para poder mandar bloques de forma consecutivas.

> Conviene trabajar con el esquema por bloques cuando trabajamos con tuberías

1. Obtenemos el nucleo
El valor de np, ese será nuestor núcleo

2. Calculamos el inicio


Paralelización a nivel de tarea

```c
if( np == 0 )
	{
		suma = num1 + num2;
		write( pipefd[1], &suma, sizeof(int) );
	}else if( np == 1)
	{
		resta = num1 - num2;
		write( pipefd[1], &resta, sizeof(int) );
	}else if( np == 2 )
	{
		multi = num1 * num2;
		write( pipefd[1], &multi, sizeof(int) );
	}else if( np == 3 )
	{
		divi = num1 / num2;
		write( pipefd[1], &divi, sizeof(int) );
	}
```
Va a calcular o procesar solamente un bloque del arreglo, usando paralelización a nivel de datos

```c
for (i = ini_bloque; i < fin_bloque; i++)
	{
		C[i] = A[i] * B[i];
	}

```

> Recuerda que las variables **A,B,C no son variables compartidas, sino copias porque estamos trabajando con tuberías**.

Debemos de regresar en donde termina cada bloque procesado por cada nucleo o proceso. Y este indice nos lo da la variable ini_bloque:

```c
	C + ini_bloque
```

Y de igual forma determinamos cuantos bloques de codigo haremos, para eso debemos hacer:

```c
	sizeof(int) * elem_bloque
```

Finalmente, la sentencia completa sería:

```c
	write(pipefd[1], C + ini_bloque, sizeof(int) * elem_bloque);
```

Proceso padre

Nosotros debemos de establecer el resultado en el arreglo C.

```
	read( pipefd[numproc][0], &resultado, sizeof(int) );
```

Pero debo volver a acomodarlo en la posición que corresponde.

read( pipefd[numproc][0], C + ini_bloque, sizeof(int) * elem_bloque);

sizeof(int) * elem_bloque : cantidad de bytes que leeré.

Quizas podria pensarse que se está trabajando bajo un mismo arreglo y no tiene sentido leer este bloque: C + ini_bloque

Sin embargo, no es así

Supongamos lo siguiente

FOTO DE TABLA 


|proceso padre |     Hijo 0   |    Hijo 1    | Hijo 2 | Hijo 3 | 
|--------------|--------------|--------|--------|--------|
|*A = [3,5,6,8]| A = [3,5,6,8]| A = [3,5,6,8] |        |        |
|*B = [8,2,7,4]| B = []
|*C = [0,0,0,0]|
|-----------------------------------------------------------------
|*C = [0,0,0,0]| C= [24,0,0,0] | C = [0,10,0,0] | 
| Acomodo
|*C = []

Lo que haga el hijo solamente ese hilo lo sabe, nadie mas, por eso debo juntarlos

EL arregñp A y B se copian en cada proceso hijo

EN UN PROCESO NUNCA EXISTIRÁ UNA CONDICIÓN DE CARRERA