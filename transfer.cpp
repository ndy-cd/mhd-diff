#include <stdio.h>              // используется только в ConsoleGraph
#include <stdlib.h>             // for strtol()

#include "structures.h"
#include "Lax-Wendroff.h"
#include "allocate.h"
#include "interact-with-file-system.h"
#include "initial-conditions.h"
#include "get-flow.h"
#include "auxiliary-functions.h"

int main (int argc, char** argv){
    unsigned int N = 10, h = 0, cases, H = 100;

    char fileName[20] = "file1.txt", add[2] = "a", create[2] = "w"; 
    double options[5], dt = 1;
    parameters var;

    // количество шагов из командной строки
    if (argv[1])
    {
        H = strtol(argv[1], NULL, 10);
    }

    //считываем параметры расчёта из файла
    readFile(fileName, options); 
    N = (int) options[0];                   // размер сетки
    cases = (int) options[1];                // выбор типа расчёта
    cases = 1;

    // выделение памяти в зависимости от типа расчёта
    double **U;                             // массив физических величин
    double **F;                             // массив потоков
    makeArray(U, N, cases);
    makeArray(F, N, cases);
    allocateStruct(var, N, cases);           // выделение памяти под структуру
    
    initCond(U, F, var, N, cases);              // начальные условия
    getFlow(U, F, var, N, cases);               // функция для потоков
    writeMultiCols(U, var, dt, h, N, create);

    // вычисление нового временного слоя в цикле
    while (h < H)
    {
        dt = 1 / maxVelOf(U, var, N);
        dt -= dt/100;                           // число куранта строго меньше 1
        Lax_Wendroff(U, F, var, cases, dt, 1, N);
        makeNewVelAndState(U, F, var, N);       // BIG QUESTION (TO DO)
        getFlow(U, F, var, N, cases);
        h++;
        writeMultiCols(U, var, dt, h, N, add);
    }

    // высвобождение памяти
    deleteArray(U, N, cases);
    deleteArray(F, N, cases);
    deleteStruct(var, N, cases);
    return 0;
}

