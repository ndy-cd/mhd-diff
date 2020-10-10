#include "structures.h"

int switchCase(int Case) {
    int n;

    switch (Case)
    {
    case 0:             // уравнение переноса
        n = 1;
        break;

    case 1:             // классическая гидродинамика
        n = 3;
        break;
    
    case 2:
        n = 3;
        break;

    default:
        break;
    }

    return n;   
}

void makeArray (double** &A, unsigned int N, unsigned int cases) {
    unsigned int nEq; // количество уравнений (строк в вектор-столбце)
    
    nEq = switchCase(cases);

    A = new double * [nEq];             
    for (int i = 0; i < nEq; i++) {   
        A[i] = new double [N];        
    }
}

void deleteArray (double** &A, unsigned int N, unsigned int cases) {
    unsigned int nEq; // количество уравнений (строк в вектор-столбце)
    
    nEq = switchCase(cases);
        
    for (int i = 0; i < nEq; i++) {   
        delete [] A[i];        
    }
    delete [] A;           
}

void allocateStruct(parameters &var, int N, int cases) {
    if (cases == 0)
    {
        var.velocity = new double [N];
    }
    if (cases == 1) {
        var.velocity = new double [N];
        var.pressure = new double [N];
        var.energy = new double [N];
        var.gamma = new double;
    }
    if (cases == 2) {
        var.velocity = new double [N];
        var.pressure = new double [N];
        var.energy = new double [N];
        var.gamma = new double;
        var.volume = new double [N];
        var.phi = new double [N];
    }
}

void deleteStruct(parameters &var, int N, int cases) {
    if (cases == 0)
    {
        delete [] var.velocity;
    }
    if (cases == 1) {
        delete [] var.velocity;
        delete [] var.pressure;
        delete [] var.energy;
        delete var.gamma;
    }
    if (cases == 2) {
        delete [] var.velocity;
        delete [] var.pressure;
        delete [] var.energy;
        delete var.gamma;
        delete [] var.volume;
    }
}