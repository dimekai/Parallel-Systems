/**
 * @brief: procesamiento.c
 * @desc: Este archivo contiene las funciones de generacion
 *        de señales para realizar el ventaneo. Las dos señales
 *        con las que se trabajan son el Seno y la la señal Hann 
 **/
#include <math.h>   // para coseno y seno
#include "defs.h"

void HannWindow(float * window)
{
    register int i;
    float a0 = 0.5, a1 = 0.5;
    for (i = 0; i < N; i++)
    {
        window[i] = a0 - (a1 * cosf((2 * M_PI * i)/(N - 1)));
    }
}

void SinusSignal(float * signal)
{
    register int i;
    float f = 1000, fs = 45000;
    for (i = 0; i < N; i++)
    {
        signal[i] = sinf((2 * i * M_PI * f)/fs);
    }
}