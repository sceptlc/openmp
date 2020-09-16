#include <stdio.h>
#include <omp.h>


int main()
{
    int m[5] = {0};

    printf("Array before =");
    for (int i = 0; i < 5; i++) printf(" %d", m[i]);
    printf("\n");

    #pragma omp parallel num_threads(2) shared(m)
    {
        int t = omp_get_thread_num();
        m[t] = 1;
    }

    printf("Array after  =");
    for (int i = 0; i < 5; i++) printf(" %d", m[i]);
    printf("\n");
}
