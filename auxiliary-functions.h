int consoleGraph (double Y[], int x);
double maxVelOf(double **U, parameters var, int N, int cases);

void makeNewVariables(double** U, double** F, parameters var, int N);
void makeNewVelAndState(double **U, double **F, parameters var, int N, int cases);
void boundaries(double **U, double *boundary, parameters var, int N);
