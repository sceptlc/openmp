#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel num_threads(3)
    {
        int thr_num = omp_get_thread_num();
        
        printf("Start %d\n", thr_num);

        #pragma omp master
        printf("Master thread %d\n", thr_num);
        
        printf("Middle %d\n", thr_num);

        #pragma omp master
        printf("Master thread %d\n", thr_num);

        printf("End %d\n", thr_num);
    }
}
