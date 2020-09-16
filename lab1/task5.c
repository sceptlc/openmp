#include <stdio.h>
#include <omp.h>
#include <string.h>

int do_stuff()
{
    printf("Doing stuff...\n");
}


int main (int argc, char *argv[])
{
    if (argc < 2) return 1;

    if (strcmp(argv[1], "serial") == 0)
    {
        printf("Serial mode\n");
        for (int i = 0; i < 5; i++)
            do_stuff();

    } else if (strcmp(argv[1], "parallel") == 0)
    {
        printf("Parallel mode\n");
        #pragma omp parallel num_threads(5)
        {
            do_stuff();
        }
    }
    else return 1;

    return 0;
}

