#include <stdio.h>
#include "test.h"

#include "Lax-Wendroff.h"

int readFile (char*, double[]);
int consoleGraph(double[], int);
int writeFile (double[], int, char*);

int main (int argc, char** argv){
    unsigned int N = 10, dt = 0;
    
    char fileName[20] = "file1.txt", add[5] = "a", create[5] = "w"; 
    double options[5], velocity = 1;

    //считываем параметры расчёта из файла
    readFile(fileName, options); 
    N = (int) options[0]; // размер сетки
    
    double **U;
    U = new double * [3];             // массив указателей (2)
    for (int i = 0; i < 2; i++) {   
        U[i] = new double [N];        // инициализация указателей
    }

    double* F = new double [N];

    //начальные условия (ступенька)
    for (int i = 0; i < N/10; i++) { 
        U[0][i] = 1;
        F[i] = velocity * U[0][i];
    }
    for (int i = N/10; i < N; i++) {
        U[0][i] = 0;
        F[i] = velocity * U[0][i];
    }

    consoleGraph(U[0], N);      // график в консоль
    writeFile(U[0], N, create); // вывод в новый файл

    // вычисление нового временного слоя в цикле
    while (dt < 80)
    {
        LW(U[0], F, 1, 1, 1, N);
        dt++;
        consoleGraph(U[0], N);
        writeFile(U[0], N, add); // вывод в файл -> x; U(x) - append
    }
    
    // высвобождение памяти
    for (int i = 0; i < 3; i++) {
        delete [] U[i];
    }
    delete [] U;
    delete [] F;
    return 0;
}




int readFile (char* fileName, double initArray[]) {
    FILE* file = fopen(fileName, "r");
    struct params {
		char name[20]; 
		double value; 
	};
    struct params option[10];
	int n=0;
    if (file == NULL) {
        printf("File not found!");
    }
    else {
        while (fscanf (file, "%s%lf", option[n].name, &(option[n].value)) != EOF) {
		    printf("%s %.2f\n", option[n].name, option[n].value);
		    initArray[n] = option[n].value;
		    n++;
	    }
        fclose(file);
    }
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

int writeFile (double A[], int N, char* option) {
    FILE* file = fopen("output.txt", option);
    for (int i = 0; i < N; i++)
    {
        fprintf(file, "%d\t%f\n", i, A[i]);
    }
    fprintf(file, "\n");
    fclose(file);
    return 0;
}