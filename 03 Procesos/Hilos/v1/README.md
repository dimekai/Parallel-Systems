pthread_t : es un identificador del hilo. Es análogo al pid_t

pthread_join: Espera a que se temrine el hilo que se está ejecutando. Es el análogo al __wait__.

`**retval`: es como el status pero del hilo
pthread_exit(); equivalente al exit en procesos

Agregamos la bandera para compilación de hilos: -lpthread

static mantiene el valor de res a pesar de que ha muerto la funcion 