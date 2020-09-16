#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 10

void fill_v(int* vector)
{
    srand(rand() + time(NULL));
    for (int i = 0; i < SIZE; i++)
        vector[i] = rand() % 1000;
}

void print_v(int* vector)
{
    for (int i = 0; i < SIZE; i++)
        printf("%d\t", vector[i]);
    printf("\n");
}



int main ()
{
    int v1[SIZE], v2[SIZE];
    int sum = 0;

    fill_v(v1);
    fill_v(v2);

    omp_set_dynamic(1);

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < SIZE; i++)
    {
        sum += v1[i] * v2[i];
    }

    print_v(v1);
    print_v(v2);
    printf("Result = %d\n", sum);
}

