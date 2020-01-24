void LW (double U[], double F[], double fun, double dt, double dx, int N);
// подпрограмма, вычисляющая один шаг по времени методом Лакса-Вендроффа
// принимает массивы значений физической величины, массив потоков, 
// вспомогательную фунцию (константа для одного шага по времени), 
// шаг по времени, шаг по координате, размер сетки
void Lax_Wendroff (double** U, double** F, parameters var, int cases, double dt, double dx, int N);