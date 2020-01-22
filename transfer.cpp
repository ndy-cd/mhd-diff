#include <stdio.h>

#include "Lax-Wendroff.h"
#include "interact-with-file-system.h"

int consoleGraph(double[], int);

int main (int argc, char** argv){
    unsigned int N = 10, dt = 0;
    
    char fileName[20] = "file1.txt", add[2] = "a", create[2] = "w"; 
    double options[5], velocity = 1;

    //считываем параметры расчёта из файла
    readFile(fileName, options); 
    N = (int) options[0]; // размер сетки
    
    // инициализация массивов (указатель на указатель на double)
    // для величин и их потоков
    double **U;                             // массив физических величин
    U = new double * [3];             
    for (int i = 0; i < 2; i++) {   
        U[i] = new double [N];        
    }
    double **F;                             // массив потоков
    F = new double * [3];             
    for (int i = 0; i < 2; i++) {   
        F[i] = new double [N];        
    }

    //начальные условия (ступенька)
    for (int i = 0; i < N/10; i++) { 
        U[0][i] = 1;
        F[0][i] = velocity * U[0][i];
    }
    for (int i = N/10; i < N; i++) {
        U[0][i] = 0;
        F[0][i] = velocity * U[0][i];
    }

    consoleGraph(U[0], N);           // график в консоль
    writeFile(U[0], N, create);      // вывод в новый файл

    // вычисление нового временного слоя в цикле
    while (dt < 80)
    {
        LW(U[0], F[0], 1, 1, 1, N);
        dt++;
        consoleGraph(U[0], N);
        writeFile(U[0], N, add); // вывод в файл -> x; U(x) - append
    }
    
    // высвобождение памяти
    for (int i = 0; i < 3; i++) {
        delete [] U[i];
        delete [] F[i];
    }
    delete [] U;
    delete [] F;
    return 0;
}

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

