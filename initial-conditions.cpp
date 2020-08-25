#include "structures.h"
#include "math.h"           // Volume -> M_PI

void initCond (double** U, double** F, parameters var, int N, int cases) {
    double ae = 1.5 * 10000000000000 * 1000;
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

    case 10:                                // ступенька №2 (case + 10); case = 0
        for (int i = 0; i < N*0.4; i++)
        {
            U[0][i] = 0.4; var.velocity[i] = 1;
        }
        for (int i = N*0.4; i < N*0.6; i++)
        {
            U[0][i] = 0.8; var.velocity[i] = 1;
        }
        for (int i = N*0.6; i < N; i++)
        {
            U[0][i] = 0.4; var.velocity[i] = 1;
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
            var.pressure[i] = 3;
            U[0][i] = 1;
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
    case 2:                                 // задача о свободном коллапсе
        *var.gamma = 5.0 / 3.0;
        for (int i = 0; i < N; i++)
        {
            var.velocity[i] = 0;
            var.pressure[i] = 5.7 / 1000.0 * 80.0;
            
            U[0][i] = 1.0 / 100000000000000.0;
            U[1][i] = U[0][i] * var.velocity[i];
            var.energy[i] = var.pressure[i] / U[0][i] / (*var.gamma -1);
            U[2][i] = U[0][i] * var.velocity[i] * var.velocity[i] / 2 + U[0][i] * var.energy[i];
            
            var.volume[i] = 4.0 / 3.0 * M_PI * ((i + 1)*ae * (i + 1)*ae * (i + 1)*ae - i*ae * i*ae * i*ae);
        }
        // U[0][N-1] = 1.0 /   10000000000000000.0;
        // U[0][0] = 1.0 /     1000000000000;
    default:
        break;
    }
}
