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
    unsigned int    N = 100, 
                    h = 0, 
                    cases, 
                    initCase,
                    write_every,     
                    H = 100;

    char fileName[20] = "file1.txt", add[2] = "a", create[2] = "w"; 
    double  options[5],
            boundary[3], // ??
            dt = 1, 
            courant, 
            T = 0;
    double ae = 1.5 * 10000000000000 * 1000; // ??
    parameters var;

    // количество шагов из командной строки
    if (argv[1])
    {
        H = strtol(argv[1], NULL, 10);
    }

    //считываем параметры расчёта из файла
    readFile(fileName, options); 
    N = (int) options[0];                   // размер сетки
    cases = (int) options[1];               // выбор типа расчёта
    initCase = (int) options[2];            // выбор начальных условий
    courant = (float) options[3];           // число Куранта
    write_every = (int) options[4];         // запись в файл каждые .. шагов 

    if (initCase)
    {
        initCase = cases + 10;
    }
    else initCase = cases;

    // выделение памяти в зависимости от типа расчёта
    double **U;                             // массив физических величин
    double **F;                             // массив потоков
    makeArray(U, N, cases);
    makeArray(F, N, cases);
    allocateStruct(var, N, cases);           // выделение памяти под структуру
    
    initCond(U, F, var, N, initCase);               // начальные условия
    getFlow(U, F, var, N, cases);                   // функция для потоков
    writeMultiCols(U, var, T, cases, N, create);    // запись в файл

    // вычисление нового временного слоя в цикле
    while (h < H)
    {
        dt = 1*ae / maxVelOf(U, var, N, cases);                     
        dt *= courant;                                 // число куранта строго меньше 1
        T += dt;

        // Запишем предыдущее значение на предграничной ячейке, чтобы вычесть разницу из граничной.
        for (int i = 0; i < 3; i++)
        {
            // boundary[i] = U[i][N-2];                // only for collapse
        }
        Lax_Wendroff(U, F, var, cases, dt, ae, N);
    
        // U[0][0] -= F[0][1] / (F[1][1] / U[0][1]);
        // U[0][N-1] = U[0][N-2];
        

        if (cases)
        {
            makeNewVelAndState(U, F, var, N);      
            // boundaries(U, boundary, var, N);             // only for collapse
        }
        getFlow(U, F, var, N, cases);
        h++;
        if (h % write_every == 0)
        { 
            writeMultiCols(U, var, T, cases, N, add);
        }        
    }

    // высвобождение памяти
    deleteArray(U, N, cases);
    deleteArray(F, N, cases);
    deleteStruct(var, N, cases);
    return 0;
}

