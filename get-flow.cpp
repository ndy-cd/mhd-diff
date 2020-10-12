#include "structures.h"

void getFlow (double** U, double** F, parameters var, int N, int cases) {

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
            F[0][i] = U[1][i];
            // F[1][i] = U[1][i] * var.velocity[i] + var.pressure[i] + G * mass / (i+1) / ae;
            // F[1][i] = U[1][i] * var.velocity[i] + var.pressure[i] - var.phi[i];
            F[1][i] = U[1][i] * var.velocity[i] + var.pressure[i] + U[0][i] * var.phi[i];
            F[2][i] = ( U[0][i] * var.energy[i] + U[1][i] * var.velocity[i] / 2.0
                        + var.pressure[i] + var.phi[i] ) * var.velocity[i];
        }
        break;

    case 3:                         // изотермический коллапс (сферические координаты)
        for (int i = 0; i < N; i++)
        {
            /* code */
            

        }
        

    default:
        break;
    }
}