#include <stdio.h>
#include <omp.h>

int main ()
{
    #pragma omp parallel 
    {
        printf("First parallel region %d\n", omp_get_thread_num());
    }

    #pragma omp parallel num_threads(3)
    {
        printf("Second parallel region %d\n", omp_get_thread_num());
    }

    omp_set_num_threads(4);

    #pragma omp parallel 
    {
        printf("Third parallel region %d\n", omp_get_thread_num());
    }

}
