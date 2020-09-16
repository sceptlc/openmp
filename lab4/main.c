#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include "functions.c"


int main()
{
    omp_set_dynamic(1);

    #pragma omp parallel num_threads(5) 
    {   
        int i = omp_get_thread_num();
        double prev, sum = INFINITY;
        long steps = INIT_N;
        char *method_name;
        int iterations = 0;
        double (*method)(long);

        if (i == 0) {
            method = left_rect_method;
            method_name = "Left rectangles";
        } else if (i == 1) {
            method = mid_rect_method;
            method_name = "Midpoint";
        } else if (i == 2) {
            method = right_rect_method;
            method_name = "Right rectangles";
        } else if (i == 3) {
            method = trapezium_method;
            method_name = "Trapezuim";
        } else if (i == 4) {
            method = simpsons_method;
            method_name = "Simpson's";
        };
    
        do {
            prev = sum;
            sum = (*method)(steps);
            iterations++;
                        
            if (fabs(sum - prev) <= EPSILON)  {
                // got decision accurate enough!
                break;
            } else {
                // continue suffering...
                steps *= 2;
            }

        } while (1);

        printf ("%s, %d iterations (%4.10f)\n", method_name, iterations, sum);

    }

    return 0;
}

