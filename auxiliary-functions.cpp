#include <stdio.h>

#include "structures.h"

void getFlow (double U[], double F[], int n, double velocity, int cases) {
    switch (cases)
    {
    case 0:                         // transfer equation
        for (int i = 0; i < n; i++)             
        {
            F[i] = U[i] * velocity;
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
        }
        for (int i = N/10; i < N; i++) {
            U[0][i] = 0;
        }
        break;

    case 1: 
        // {rho, v, P} = {1, 0, 3}, x < 0.5,
        // {rho, v, P} = {1, 0, 1}, x > 0.5.
        // Показатель адиабаты 5/3.
        *var.gamma = 5.0 / 3.0;
        for (int i = 0; i < N/2; i++)
        {   
            // вектор-столбец u
            var.velocity[i] = 0;
            var.pressure[i] = 3;
            U[0][i] = 1;
            U[1][i] = U[0][i] * var.velocity[i];
            var.energy[i] = var.pressure[i] / U[0][i] / (*var.gamma -1);
            U[2][i] = U[0][i] * var.velocity[i] * var.velocity[i] / 2 + U[0][i] * var.energy[i];
            // вектор-столбец F
            F[0][i] = U[1][i];
            F[1][i] = U[0][i] * var.velocity[i] * var.velocity[i] + var.pressure[i];
            F[2][i] = ( U[0][i] * var.energy[i] + U[0][i] * var.velocity[i] * var.velocity[i] / 2
                        + var.pressure[i] ) * var.velocity[i];
        }
        for (int i = N/2; i < N; i++)
        {
            var.velocity[i] = 0;
            var.pressure[i] = 1;
            U[0][i] = 1;
            U[1][i] = U[0][i] * var.velocity[i];
            var.energy[i] = var.pressure[i] / U[0][i] / (*var.gamma -1);
            U[2][i] = U[0][i] * var.velocity[i] * var.velocity[i] / 2 + U[0][i] * var.energy[i];
            // вектор-столбец F
            F[0][i] = U[1][i];
            F[1][i] = U[0][i] * var.velocity[i] * var.velocity[i] + var.pressure[i];
            F[2][i] = ( U[0][i] * var.energy[i] + U[0][i] * var.velocity[i] * var.velocity[i] / 2
                        + var.pressure[i] ) * var.velocity[i];
        }
            
    default:
        break;
    }
}

void test (double** U){
    printf("first %f\nlast %f", U[0][0], U[0][99]);
}

void makeArray (double** &A, unsigned int N, unsigned int cases) {
    unsigned int nEq; // количество уравнений (строк в вектор-столбце)
    
    switch (cases)
    {
    case 0:             // уравнение переноса
        nEq = 1;
        break;

    case 1:             // классическая гидродинамика
        nEq = 3;
        break;
    
    default:
        break;
    }

    A = new double * [nEq];             
    for (int i = 0; i < nEq; i++) {   
        A[i] = new double [N];        
    }
}