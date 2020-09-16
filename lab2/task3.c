#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel num_threads(3)
    {
        printf("Begin\n");

        #pragma omp single nowait
        printf("Single thread %d\n", omp_get_thread_num());

        printf("End\n");
    }
}
