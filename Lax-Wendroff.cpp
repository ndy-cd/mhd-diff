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