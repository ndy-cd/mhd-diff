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

    if ( (cases == 2) )
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

    case 3:
        for (int i = 0; i < N; i++)
        {
            frac = fabs(var.velocity[i]) + 19012.581646624563; // ... + RT/mu
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

void makeNewVelAndState(double **U, double **F, parameters var, int N, double dx, int cases) {

    double mass = 0;

    for (int i = 0; i < N; i++)
    {
        var.velocity[i] = U[1][i] / U[0][i];
        
        switch (cases)
        {
        case 1:
            var.energy[i] = (U[2][i] - U[1][i]*var.velocity[i]/2) / U[0][i];
            break;
        
        case 2:
            mass += U[0][i] * var.volume[i];
            var.phi[i] = - 6.67 / 100000000.0 * mass / (i + 1) / dx;
            var.energy[i] = (U[2][i] - U[1][i] * var.velocity[i] / 2.0 - U[0][i] * var.phi[i]) / U[0][i];
            var.pressure[i] = var.energy[i] * U[0][i] * (*var.gamma - 1);
            break;
        
        case 3:
            mass += U[0][i] * var.volume[i];
            var.phi[i] = - 6.67 / 100000000.0 * mass / (i + 1) / dx;
            var.pressure[i] = U[0][i] * 361478260.86956525; // rho cs^2
        
        default:
            break;
        }

        
        
        // if (U[2][i] - U[1][i]*var.velocity[i]/2 < 0)
        // { 
        //     printf("ATTENTION! Energy is lower that zero! energy[%d]\n", i);
        // }
        // if (var.pressure[i] < 0)
        // {
        //     printf("ATTENTION! Pressure is lower that zero! pressure[%d]\n", i);
        // }
    }
    
}

void boundaries(double **U, parameters var, int N, int cases) {
    
    switch (cases)
    {
    case 2:
        U[0][0] = U[0][1];
        U[1][0] = 0;
        // U[2][0] = U[2][1] - U[1][1] * var.velocity[1] / 2;
        break;
        
    case 3:
        U[0][0] = U[0][1];
        U[1][0] = 0;
        break;
    
    default:
        break;
    }
    


}