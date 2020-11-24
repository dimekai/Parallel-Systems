/**
 * @brief: archivos.c
 * @desc: Este archivo contiene las funciones para leer
 *        los datos del archivo .dat de pulso cardiaco
 *        y para guardar el resultado del ventaneo.   
**/

#include <stdlib.h>
#include <stdio.h>
#include "defs.h"

void readHeartbeatData(float * heartbeat)
{
    FILE * archivo;
    register int i = 0;
    archivo = fopen("PulseSensor.dat", "r");

    // Verificamos que se haya abierto bien el programa
    if (!archivo)
    {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    } 

    for (i = 0; i < N; i++)
    {
        fscanf(archivo, "%f", &heartbeat[i]);
        heartbeat[i] -= 2200; // remover o no?
    }

    fclose(archivo);
}

void saveData(float * datos, char name[])
{
    FILE * archivo;
    register int i;

    archivo = fopen(name, "w");
    
    // Verificamos que se haya abierto bien el programa
    if (!archivo)
    {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < N; i++)
    {
        fprintf(archivo, "%f \n", datos[i]);
    }
    
    fclose(archivo);
}