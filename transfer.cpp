#include <stdio.h>              // используется только в ConsoleGraph

#include "structures.h"
#include "Lax-Wendroff.h"
#include "allocate.h"
#include "interact-with-file-system.h"
#include "auxiliary-functions.h"

int consoleGraph(double[], int);

int main (int argc, char** argv){
    unsigned int N = 10, h = 0, cases;

    char fileName[20] = "file1.txt", add[2] = "a", create[2] = "w"; 
    double options[5], dt = 1;
    parameters var;
    
    //считываем параметры расчёта из файла
    readFile(fileName, options); 
    N = (int) options[0];                   // размер сетки
    cases = (int) options[1];                // выбор типа расчёта
    cases = 1;

    // выделение памяти в зависимости от типа расчёта
    // // инициализация массивов (указатель на указатель на double)
    double **U;                             // массив физических величин
    double **F;                             // массив потоков
    makeArray(U, N, cases);
    makeArray(F, N, cases);
    // // выделение памяти под структуру
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

    initCond(U, F, var, N, cases);              // начальные условия
    getFlow(U, F, var, N, cases);               // функция для потоков
    // consoleGraph(U[0], N);                      // график в консоль
    // writeFile(U[0], N, create);                 // вывод в новый файл
    writeMultiCols(U, var, dt, h, N, create);

    // вычисление нового временного слоя в цикле
    while (h < 80)
    {
        dt = 1 / maxVelOf(U, var, N);
        dt -= dt/100;                           // число куранта строго меньше 1

        // LW(U[0], F[0], 1, 1, 1, N);
        Lax_Wendroff(U, F, var, cases, dt, 1, N);

        // makeNewVariables(U, F, var, N); // BIG QUESTION (TO DO)
        makeNewVelAndState(U, F, var, N); // BIG QUESTION (TO DO)
        getFlow(U, F, var, N, cases);
        h++;

        // consoleGraph(U[0], N);
        // if (h%10 == 0) {
            // writeFile(U[0], N, add); // вывод в файл -> x; U(x) - append
        // }
        writeMultiCols(U, var, dt, h, N, add);
        
    }

    // высвобождение памяти
    deleteArray(U, N, cases);
    deleteArray(F, N, cases);
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

