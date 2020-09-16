#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 20

void fill_arr(int* arr)
{
    srand(rand() + time(NULL));
    for (int i = 0; i < SIZE; i++)
        arr[i] = rand() % 1000;
}

void print_arr(int* arr)
{
    for (int i = 0; i < SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");
}



int main ()
{
    int arr1[SIZE], arr2[SIZE];
    int result[SIZE];
    fill_arr(arr1);
    fill_arr(arr2);

    omp_set_dynamic(1);

    #pragma omp parallel for shared(result)
    for (int i = 0; i < SIZE; i++)
    {
        printf("Thread #%d, calculating element #%d\n", omp_get_thread_num(), i);
        result[i] = arr1[i] + arr2[i];
    }
    
    print_arr(arr1);
    print_arr(arr2);
    print_arr(result);
}
