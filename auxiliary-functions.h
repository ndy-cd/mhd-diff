void getFlow (double**, double**, parameters, int , int );
void initCond (double**, double**, parameters, int , int );

void makeNewVariables(double** U, double** F, parameters var, int N);
void makeNewVelAndState(double **U, double **F, parameters var, int N);
double maxVelOf(double **U, parameters var, int N);
