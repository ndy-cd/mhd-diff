#include <stdio.h>

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
            F[1][i] = U[0][i] * var.velocity[i] * var.velocity[i] + var.pressure[i];
            F[2][i] = ( U[0][i] * var.energy[i] + U[0][i] * var.velocity[i] * var.velocity[i] / 2
                        + var.pressure[i] ) * var.velocity[i];
        }
        break;
    
    default:
        break;
    }
}

void initCond (double** U, double** F, parameters var, int N, int cases) {
    switch (cases)
    {
    case 0:                                 // ступенька
        for (int i = 0; i < N/10; i++) { 
            U[0][i] = 1;
            var.velocity[i] = 1;
        }
        for (int i = N/10; i < N; i++) {
            U[0][i] = 0;
            var.velocity[i] = 1;
        }
        break;

    case 1:                                 // задача о ГД разрыве
        // {rho, v, P} = {1, 0, 3}, x < 0.5,
        // {rho, v, P} = {1, 0, 1}, x > 0.5.
        // Показатель адиабаты 5/3.
        *var.gamma = 5.0 / 3.0;
        for (int i = 0; i < N/2; i++)
        {   
            // вектор-столбец u
            var.velocity[i] = 0;
            var.pressure[i] = 3*1000000;
            U[0][i] = 1*1000000;
            U[1][i] = U[0][i] * var.velocity[i];
            var.energy[i] = var.pressure[i] / U[0][i] / (*var.gamma -1);
            U[2][i] = U[0][i] * var.velocity[i] * var.velocity[i] / 2 + U[0][i] * var.energy[i];
        }
        for (int i = N/2; i < N; i++)
        {
            var.velocity[i] = 0;
            var.pressure[i] = 1;
            U[0][i] = 1;
            U[1][i] = U[0][i] * var.velocity[i];
            var.energy[i] = var.pressure[i] / U[0][i] / (*var.gamma -1);
            U[2][i] = U[0][i] * var.velocity[i] * var.velocity[i] / 2 + U[0][i] * var.energy[i];
        }
            
    default:
        break;
    }
}

void makeNewVariables(double **U, double **F, parameters var, int N) {
    for (int i = 0; i < N; i++)
    {
        var.velocity[i] = U[1][i] / U[0][i];
        var.pressure[i] = F[1][i] - U[1][i]*var.velocity[i];
        var.energy[i] = (U[2][i] - U[1][i]*var.velocity[i]/2)/U[0][i];
        // printf("new vel[%d] = %f\n", i, var.velocity[i]);
    }
    
    
}