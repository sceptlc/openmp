#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main ()
{
    omp_set_num_threads(128);
    omp_set_dynamic(1);

    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0)
            printf("Number of threads = %d\n", omp_get_num_threads());
        
    }

    
    return 0;
}
