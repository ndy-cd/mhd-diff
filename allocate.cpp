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

void deleteArray (double** &A, unsigned int N, unsigned int cases) {
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
    
    for (int i = 0; i < nEq; i++) {   
        delete [] A[i];        
    }
    delete [] A;           
}