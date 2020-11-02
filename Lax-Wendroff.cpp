#include <cstdio> /// to delete

#include "structures.h"
#include "allocate.h"
#include "get-flow.h"
#include "auxiliary-functions.h" // makeNewVar //

void LW (double U[], double F[], double fun, double dt, double dx, int N){
//Potter p.97                       
double* U12 = new double [N];
double* F12 = new double [N];

for (int i = 0; i < N; i++) {                     // вспомогательный шаг
	U12[i] = (U[i]+U[i+1])/2 - dt/2/dx*(F[i+1]-F[i]);
	F12[i] = fun*U12[i];
}

for (int i = 1; i < N-1; i++) {                     // основной шаг
	U[i] -= dt/dx*(F12[i]-F12[i-1]);
	F[i] = U[i]*fun;
}

delete [] U12;
delete [] F12;
}

void Lax_Wendroff (double** U, double** F, parameters var, int cases, double dt, double dx, int N){            
double **U12;                             // массив физических величин
double **F12;                             // массив потоков
makeArray(U12, N, cases);
makeArray(F12, N, cases);
int nEq;
double mass;
double Gsgs = 6.67 / 100000000.0;


//............... вспомогательный шаг ...............//
switch (cases)
{
	case 0:			 // уравнение переноса
		nEq = 1;
		for (int i = 0; i < N-1; i++) {     
			U12[0][i] = (U[0][i] + U[0][i+1])/2 - dt/2/dx*(F[0][i+1] - F[0][i]);                
		}
		getFlow(U12, F12, var, N, cases);
		break;

	case 1:			 // классическая гидродинамика
		nEq = 3;
		for (int j = 0; j < nEq; j++) {                     
			for (int i = 0; i < N-1; i++)
			{
				U12[j][i] = (U[j][i] + U[j][i+1])/2 - dt/2/dx*(F[j][i+1] - F[j][i]);
			}		
		}
		makeNewVelAndState(U12, F12, var, N-1, dx, cases);
		getFlow(U12, F12, var, N-1, cases);
		break;
		
	case 2:			// collapse
		nEq = 3;
		for (int j = 0; j < nEq; j++) 
		{           
			for (int i = 0; i < N-1; i++)
			{
				U12[j][i] = (U[j][i] + U[j][i+1])/2 - dt/2/dx*(F[j][i+1] - F[j][i]);
			}	    
		}
		makeNewVelAndState(U12, F12, var, N-1, dx, cases);
		getFlow(U12, F12, var, N-1, cases);
		break;
	
	case 3:			// isothermal collapse (spherical coordinates)
		mass = 0;
		mass += U[0][0]*4/3*3.14*(var.r[0] * var.r[0] * var.r[0]);

		// вспомогательный шаг
		for (int i = 0; i < N-1; i++)
		{
			U12[0][i] = (U[0][i] + U[0][i+1])/2 - 3*dt/2/var.spc[i] * (F[0][i+1] - F[0][i]);

			U12[1][i] = (U[1][i] + U[1][i+1])/2 - 3*dt/2/var.spc[i] * (F[1][i+1] - F[1][i]) 
												+ U12[0][i] * Gsgs * mass / (var.r12[i] * var.r12[i]);

			mass += U12[0][i] * var.volume12[i];
		}	    

		makeNewVelAndState(U12, F12, var, N-1, dx, cases);
		// getFlow12
		for (int i = 0; i < N-1; i++)
        {
            F12[0][i] = U12[1][i] * var.r12[i] * var.r12[i];
            F12[1][i] = (U12[1][i] * var.velocity[i] + var.pressure[i]) * var.r12[i] * var.r12[i];         
        }
		// getFlow(U12, F12, var, N-1, cases);

		mass = U[0][0]*4/3*3.14*(var.r12[0] * var.r12[0] * var.r12[0]);
		// основной шаг
		for (int i = 1; i < N-1; i++)
		{
			U[0][i] -= 3*dt/var.spc12[i]*(F12[0][i]-F12[0][i-1]);

			U[1][i] -= 3*dt/var.spc12[i]*(F12[1][i]-F12[1][i-1])
												+ U[0][i] * Gsgs * mass / (var.r[i] * var.r[i]);

			mass += U[0][i] * var.volume[i];
		}
		break;
		
	default:
		break;
}
if (cases != 3)
{
	//............... основной шаг ...............//
	for (int j = 0; j < nEq; j++)
	{
		for (int i = 1; i < N-1; i++)
		{
			U[j][i] -= dt/dx*(F12[j][i]-F12[j][i-1]);
		}
	}
}
deleteArray(U12, N, cases);
deleteArray(F12, N, cases);
}

// void spatial_derivative(double** U, double** F, parameters var, int cases, double dt, double dx, int N){

// }