#include <stdio.h>
#include <math.h>

#include "structures.h"

int consoleGraph (double Y[], int x) {
    for (int i = 0; i < x; i++)
    {
        if (Y[i]) {
            printf("|");
        }
        else
        {
            printf(".");
        }
        i++;
    }
    printf("\n");
    return 0;
}

double maxVelOf(double **U, parameters var, int N, int cases) {
    double max = 0, frac;

    if (cases == 2)
    {
        cases = 1;
    }

    switch (cases)
    {
    case 0:
        return 1;
        break;
    
    case 1:
        for (int i = 0; i < N; i++)
        {
            frac = fabs(var.velocity[i]) + sqrt(*var.gamma * var.pressure[i] / U[0][i]);
            if (max < frac)
            {
                max = frac;
            }
        }
        return max;
        break;

    default:
        return 0;
        break;
    }
}

void makeNewVariables(double **U, double **F, parameters var, int N) {
    for (int i = 0; i < N; i++)
    {
        var.velocity[i] = U[1][i] / U[0][i];
        var.pressure[i] = F[1][i] - U[1][i]*var.velocity[i];
        var.energy[i] = (U[2][i] - U[1][i]*var.velocity[i]/2)/U[0][i];
    }
}

void makeNewVelAndState(double **U, double **F, parameters var, int N, int cases) {

    for (int i = 0; i < N; i++)
    {
        var.velocity[i] = U[1][i] / U[0][i];
        var.pressure[i] = var.energy[i] * U[0][i] * (*var.gamma - 1);
        
        switch (cases)
        {
        case 1:
            var.energy[i] = (U[2][i] - U[1][i]*var.velocity[i]/2) / U[0][i];
            break;
        
        case 2:
            var.energy[i] = (U[2][i] - U[1][i] * var.velocity[i]/2 - U[0][i] * var.phi[i]) / U[0][i];
            break;
        
        default:
            break;
        }

        
        if (U[2][i] - U[1][i]*var.velocity[i]/2 < 0)
        { 
            printf("ATTENTION! Energy is lower that zero! energy[%d]\n", i);
        }
        if (var.pressure[i] < 0)
        {
            printf("ATTENTION! Pressure is lower that zero! pressure[%d]\n", i);
        }
    }
    
}

void boundaries(double **U, double *boundary, parameters var, int N) {

    for (int i = 0; i < 1; i++)
        {
            U[i][0] = U[i][1];
            // printf("%f\n", boundary[i]);
            // U[i][N-1] -= abs(boundary[i] - U[i][N-2]); 
            U[i][N-1] = U[i][N-2];
        }
    // var.pressure[0] = var.pressure[1];
    // var.velocity[0] = var.velocity[1];
    // var.energy[0] = var.energy[1];
    // var.pressure[N-2] = var.pressure[N-1];
    // var.velocity[N-2] = var.velocity[N-1];
    // var.energy[N-2] = var.energy[N-1];
}