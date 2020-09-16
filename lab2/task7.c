#include <stdio.h>
#include <omp.h>
#include <time.h>

int main()
{
    int count = 0;

    #pragma omp parallel reduction(+:count)
    {
        printf ("I am thread number %d, count = %d\n", omp_get_thread_num(), count);
        count += 1;
    }

    printf("Count: %d\n", count);

    return 0;
}

