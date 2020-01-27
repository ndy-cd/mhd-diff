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

double maxVelOf(double **U, parameters var, int N) {
    double max = 0, frac;
    for (int i = 0; i < N; i++)
    {
        frac = fabs(var.velocity[i]) + sqrt(*var.gamma * var.pressure[i] / U[0][i]);
        if (max < frac)
        {
            max = frac;
        }
    }
    return max;
}

void makeNewVariables(double **U, double **F, parameters var, int N) {
    for (int i = 0; i < N; i++)
    {
        var.velocity[i] = U[1][i] / U[0][i];
        var.pressure[i] = F[1][i] - U[1][i]*var.velocity[i];
        var.energy[i] = (U[2][i] - U[1][i]*var.velocity[i]/2)/U[0][i];
    }
}

void makeNewVelAndState(double **U, double **F, parameters var, int N) {
    for (int i = 0; i < N; i++)
    {
        var.velocity[i] = U[1][i] / U[0][i];
        var.energy[i] = (U[2][i] - U[1][i]*var.velocity[i]/2) / U[0][i];
        var.pressure[i] = var.energy[i] * U[0][i] * (*var.gamma - 1);
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