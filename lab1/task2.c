#include <stdio.h>
#include <omp.h>

int main ()
{
    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0)
            printf("Total number of threads: %d\n", omp_get_num_threads());
        else
            printf("I am thread number %d\n", omp_get_thread_num());
    }
    
    return 0;
}

