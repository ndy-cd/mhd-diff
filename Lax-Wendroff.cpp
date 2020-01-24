#include "structures.h"
#include "allocate.h"
#include "auxiliary-functions.h" //getFlow


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
//Potter p.97                       
double **U12;                             // массив физических величин
double **F12;                             // массив потоков
makeArray(U12, N, cases);
makeArray(F12, N, cases);
int nEq;
//...............// вспомогательный шаг
switch (cases)
{
case 0:
	nEq = 1;
	for (int i = 0; i < N; i++) {     
		U12[0][i] = (U[0][i] + U[0][i+1])/2 - dt/2/dx*(F[0][i+1] - F[0][i]);                
		getFlow(U12, F12, var, N, cases);
	}
	break;

case 1:
	nEq = 3;
	for (int j = 0; j < 3; j++) {                     
		for (int i = 0; i < N; i++)
		{
			U12[j][i] = (U[j][i] + U[j][i+1])/2 - dt/2/dx*(F[j][i+1] - F[j][i]);
			getFlow(U12, F12, var, N, cases);
		}
	}

default:
	break;
}
//...............// основной шаг
for (int j = 0; j < nEq; j++)
{
	for (int i = 1; i < N; i++)
	{
		U[j][i] -= dt/dx*(F12[j][i]-F12[j][i-1]);
		getFlow(U, F, var, N, cases);
	}
	
}
deleteArray(U12, N, cases);
deleteArray(F12, N, cases);
}