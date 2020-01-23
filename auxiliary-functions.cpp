#include <stdio.h>
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

void initCond (double** U, double F[], int N, int cases) {
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