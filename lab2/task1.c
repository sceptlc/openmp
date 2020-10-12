#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define REP 5000000000

int main()
{
    double start, end;
    double a, b;

    printf("Enter numbers (space separated): \n");
    scanf("%lf %lf", &a, &b);

    printf("Parallel computation: \n");
    start = omp_get_wtime();

    #pragma omp parallel for num_threads(2)
    for (long i = 0; i < REP; i+=1) 
        a * b;

    end = omp_get_wtime();
    printf("Time = %lf\n", end - start);


    printf("Serial computation: \n");
    start = omp_get_wtime();

    for (long i = 0; i < REP; i+=1) 
        a * b;

    end = omp_get_wtime();
    printf("Time = %lf\n", end - start);
}

