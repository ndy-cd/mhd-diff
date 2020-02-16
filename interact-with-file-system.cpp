#include <stdio.h>

#include "structures.h"

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

int writeMultiCols (double** A, parameters var, double dt, int cases, int N, char* option) {
    FILE* file = fopen("output.txt", option);
    switch (cases)
    {
    case 0:
        if (*option == 'w') 
        {
            fprintf(file, "num\tU\tvelocity\ttime\n");
        }
        for (int i = 0; i < N; i++)
        {
            fprintf(file, "%d\t%.2f\t%.2f\t%f\n", 
                    i, A[0][i], var.velocity[i], dt);
        }
        break;

    case 1:
        if (*option == 'w') 
        {
            fprintf(file, "num\tU\tvelocity\tpressure\tenergy\ttime\n");
        }
        for (int i = 0; i < N; i++)
        {
            fprintf(file, "%d\t%.2f\t%.2f\t%.2f\t%.2f\t%f\n", 
                    i, A[0][i], var.velocity[i], var.pressure[i], var.energy[i], dt);
        }

    default:
        break;
    }
        
    fprintf(file, "\n");
    fclose(file);
    return 0;
}