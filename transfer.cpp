#include <stdio.h>

int readFile (char*, double[]);
int consoleGraph(double[], int);
int writeFile (double[], int, char*);
void LW (double U[], double F[], double fun, double dt, double dx, int N);

int main (int argc, char** argv){
    int N = 10, dt = 0;
    char fileName[20] = "file1.txt", add[5] = "a", create[5] = "w"; 
    double options[5], velocity = 1;

    //считываем параметры расчёта из файла
    readFile(fileName, options); 
    N = (int) options[0]; // размер сетки

    double* U = new double [N];
    double* F = new double [N];

    //начальные условия (ступенька)
    for (int i = 0; i < N/10; i++) { 
        U[i] = 1;
        F[i] = velocity * U[i];
    }
    for (int i = N/10; i < N; i++) {
        U[i] = 0;
        F[i] = velocity * U[i];
    }
    
    consoleGraph(U, N);      // график в консоль
    writeFile(U, N, create); // вывод в новый файл

    // вычисление нового временного слоя в цикле
    while (dt < 80)
    {
        LW(U, F, 1, 1, 1, N);
        dt++;
        consoleGraph(U, N);
        writeFile(U, N, add); // вывод в файл -> x; U(x) - append
    }

    delete [] U; U = NULL;
    delete [] F; F = NULL;
    return 0;
}


void LW (double U[], double F[], double fun, double dt, double dx, int N){
//Potter p.97                       
double* U12 = new double [N];
double* F12 = new double [N];

for (int i = 0; i < N-1; i++) {                     // вспомогательный шаг
	U12[i] = (U[i]+U[i+1])/2 - dt/2/dx*(F[i+1]-F[i]);
	F12[i] = fun*U12[i];
}
U[0] -= dt/dx*(F12[0]);
for (int i = 1; i < N-1; i++) {                     // основной шаг
	U[i] -= dt/dx*(F12[i]-F12[i-1]);
	F[i] = U[i]*fun;
}
U[N] -= dt/dx*(-F12[N-1]);

delete [] U12; U12 = NULL;
delete [] F12; F12 = NULL;
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