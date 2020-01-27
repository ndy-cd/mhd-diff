#include "structures.h"

void getFlow (double** U, double** F, parameters var, int n, int cases) {
    switch (cases)
    {
    case 0:                         // transfer equation
        for (int i = 0; i < n; i++)             
        {
            F[0][i] = U[0][i] * var.velocity[i];
        }
        break;
    
    case 1:                         // classic hydrodynamics
        for (int i = 0; i < n; i++)             
        {
            F[0][i] = U[1][i];
            F[1][i] = U[1][i] * var.velocity[i] + var.pressure[i];
            F[2][i] = ( U[0][i] * var.energy[i] + U[1][i] * var.velocity[i] / 2
                        + var.pressure[i] ) * var.velocity[i];
        }
        break;
    
    default:
        break;
    }
}