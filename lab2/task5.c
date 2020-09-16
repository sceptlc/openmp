#include <stdio.h>
#include <omp.h>

int main()
{
    int n = 10;

    printf ("Последовательная область: n = %d\n", n);

    #pragma omp parallel num_threads(2) private(n)
    {
        int i = omp_get_thread_num();
        printf ("Параллельная область %d n = %d\n", i, n);
        n = omp_get_thread_num();
        printf ("Параллельная область %d n = %d\n", i, n);
    }

    printf ("Последовательная область: n = %d\n", n);
}

