#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main ()
{
    omp_set_num_threads(9);

    #pragma omp parallel for ordered
    for (int i = 1; i < 10; i++)
    {
        char str[512];
        char *result = str;

        for (int j = 1; j < 10; j++)
            result += sprintf(result, "%dx%d=%d\t", i, j, i*j);
        result = str;

        #pragma omp ordered
            printf("%s\n", result);
    }

}
