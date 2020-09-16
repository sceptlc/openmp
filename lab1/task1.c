#include <stdio.h>
#include <omp.h>


int main ()
{
    printf("Последовательная область 1\n");

    #pragma omp parallel
    {
        printf("Параллельная область\n");
    }
    
    printf("Последовательная область 2\n");

    return 0;
}
