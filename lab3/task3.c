#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int n;
int *vector;
int **matrix;

void read_data()
{
    FILE *file = fopen("data.txt", "r");
    int i, j;

    fscanf(file, "%d", &n);
    matrix = malloc(n * sizeof(int *));
    vector = malloc(n * sizeof(int *));

    for (i = 0; i < n; i++)
        matrix[i] = malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (!fscanf(file, "%d", &matrix[i][j]))
                break;

    for (i = 0; i < n; i++)
        if (!fscanf(file, "%d", &vector[i]))
            break;

    fclose(file);
}

void print_matrix()
{
    printf("Матрица: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void print_v()
{
    printf("Вектор: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", vector[i]);
    printf("\n");
}

int main()
{
    read_data();
    print_v();
    print_matrix();

    int *result = malloc(n * sizeof(int));

    #pragma omp parallel num_threads(n)
    {
        int thr_i = omp_get_thread_num();
        int part_sum = 0;

        for (int j = 0; j < n; j++)
            part_sum += matrix[thr_i][j] * vector[j];

        result[thr_i] = part_sum;
    }

    printf("Результат: ");
    for (int i = 0; i < n; i++)
        printf("%d ", result[i]);
    printf("\n");

    return 0;
}

