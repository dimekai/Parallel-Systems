# Archivo Makefile simple

all: muestreo

muestreo.o: muestreo.c
	gcc -c muestreo.c -Wall

procesamiento.o: procesamiento.c
	gcc -c procesamiento.c -Wall

archivos.o: archivos.c
	gcc -c archivos.c -Wall

muestreo: muestreo.o procesamiento.o archivos.o
	gcc muestreo.o procesamiento.o archivos.o -o muestreo -lm