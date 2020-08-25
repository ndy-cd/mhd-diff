#include "structures.h"

void getFlow (double** U, double** F, parameters var, int N, int cases) {

    double mass = 0;                    //mass, G, ae - for collapse
    double G = 6.67 / 1000000000.0;
    double ae = 1.5 * 10000000000000 * 1000;

    switch (cases)
    {
    case 0:                         // transfer equation
        for (int i = 0; i < N; i++)             
        {
            F[0][i] = U[0][i] * var.velocity[i];
        }
        break;
    
    case 1:                         // classic hydrodynamics
        for (int i = 0; i < N; i++)             
        {
            F[0][i] = U[1][i];
            F[1][i] = U[1][i] * var.velocity[i] + var.pressure[i];
            F[2][i] = ( U[0][i] * var.energy[i] + U[1][i] * var.velocity[i] / 2
                        + var.pressure[i] ) * var.velocity[i];
        }
        break;
    case 2:                         // collapse
        for (int i = 0; i < N; i++)             
        {
            mass += U[0][i] * var.volume[i];
            F[0][i] = U[1][i];
            // F[1][i] = U[1][i] * var.velocity[i] + var.pressure[i] + G * mass / (((2 * i + 1) / 2.0) * ((2 * i + 1) / 2.0));
            // F[1][i] = U[1][i] * var.velocity[i] + var.pressure[i] + G * mass / ((i+1)*ae*(i+1)*ae);
            F[1][i] = U[1][i] * var.velocity[i] + var.pressure[i] + G * mass / (i+1) / ae;
            F[2][i] = ( U[0][i] * var.energy[i] + U[1][i] * var.velocity[i] / 2.0
                        + var.pressure[i] ) * var.velocity[i];
        }
        break;

    default:
        break;
    }
}