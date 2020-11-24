/**
* @brief: procesos.h
**/

#ifndef PROCESOS_H
#define PROCESOS_H

void proceso_padre(int pipefd[NUM_PROC][2]);
void proceso_hijo(int np, int pipefd[]);

#endif