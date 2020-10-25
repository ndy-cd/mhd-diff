#include "structures.h"
#include "math.h"           // Volume -> M_PI
#include <cstdio>

void initCond (double** U, double** F, parameters var, int N, double dx, int cases) {

    double Gsgs = 6.67 / 100000000.0;           // 6.67259·10-8cm3/(g·sec2)
    double mass = 0;

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
        break;

    case 2:                                 // задача о свободном коллапсе
        *var.gamma = 1.23;
        
        for (int i = 0; i < N; i++)
        {
            var.velocity[i] = 0;
            
            U[0][i] = 1.5008279229518163 / 10000000000000.0;

            U[1][i] = U[0][i] * var.velocity[i];
            
            var.pressure[i] = 8.314 * 10000000 * 10 / 2.3 * U[0][i];    // rho c_s ^ 2
            var.energy[i] = var.pressure[i] / U[0][i] / (*var.gamma -1);

            var.volume[i] = 4.0 / 3.0 * M_PI * (pow((i + 1) * dx, 3.0) - pow(i * dx, 3.0));
            var.volume12[i] = 4.0 / 3.0 * M_PI * (pow((i + 1.5) * dx, 3.0) - pow((i + 0.5) * dx, 3.0));

            mass += U[0][i] * var.volume[i];
            var.phi[i] = - Gsgs * mass / (i + 1) / dx;

            U[2][i] = U[0][i] * var.velocity[i] * var.velocity[i] / 2 + U[0][i] * var.energy[i] + U[0][i] * var.phi[i];
        
        }
        // U[0][N-1] = U[0][N-1] / 1000.0;
        break;

    case 3:                                 // изотермический коллапс
        for (int i = 0; i < N; i++)
        {
            var.velocity[i] = 0;
            U[0][i] = 1.501 / 10000000000000.0; // 1.501e-13    rho = 1.501e-19 * et * (M/Mc)^-2 (T/10K)^3
            U[1][i] = 0;
            var.pressure[i] = 8.314 * 10000000 * 10 / 2.3 * U[0][i];    // rho c_s ^ 2
            var.volume[i] = 4.0 / 3.0 * M_PI * (pow((i + 1) * dx, 3.0) - pow(i * dx, 3.0));
            mass += U[0][i] * var.volume[i];
            // mass12 += U[]
            var.r[i] = dx * (i + 1);
            var.r12[i] = dx * (i + 1.5);
            var.phi[i] = - Gsgs * mass / var.r[i];
            var.phi12[i] = - Gsgs * mass / var.r12[i];
        }
        break;
    
    default:
        break;
    }
}
