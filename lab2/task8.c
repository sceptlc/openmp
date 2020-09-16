#include <stdio.h>
#include <omp.h>


int main()
{
    int sum = 0;

    #pragma omp parallel num_threads(4) reduction(+:sum)
    {
        int thr = omp_get_thread_num();
        sum += thr;

        printf("Here thread number is %d, sum is %d\n", thr, sum);
    }

    printf("Sum is %d\n", sum);
}


