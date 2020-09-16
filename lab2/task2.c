#include <stdio.h>
#include <omp.h>

int main()
{
    double start, end;
    start = omp_get_wtime();

    #pragma omp parallel num_threads(1)
    {
        // do nothing
    }

    end = omp_get_wtime();
    printf("It takes about %lf seconds to create a parallel region\n", end - start);
}
