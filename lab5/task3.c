#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>


void quicksort(int number[], int first, int last)
{
    int i, j, pivot, temp;

    if (first < last)
    {
        pivot = first;
        i = first;
        j = last;

        while (i < j)
        {
            while (number[i] <= number[pivot] && i < last)  
                i++;
            while (number[j] > number[pivot])
                j--;
            if (i < j)
            {
                temp = number[i];
                number[i] = number[j];
                number[j] = temp;
            }
        }

        temp = number[pivot];
        number[pivot] = number[j];
        number[j] = temp;
        quicksort(number, first, j - 1);
        quicksort(number, j + 1, last);
    }
}

/**
 *    Like a first step of quicksort
 */
int split(int number[], int n)
{
    int i, j, pivot, temp;

    pivot = i = 0;
    j = n - 1;

    while (i < j)
    {
        while (number[i] <= number[pivot] && i < n - 1)
            i++;
        while (number[j] > number[pivot])
            j--;
        if (i < j)
        {
            temp = number[i];
            number[i] = number[j];
            number[j] = temp;
        }
    }

    temp = number[pivot];
    number[pivot] = number[j];
    number[j] = temp;
    return j;
}

void fill_rand(int *arr, int n)
{
	srand(time(0));
	for (int i = 0; i < n; i++)
		arr[i] = rand() % 1000 - 300;
}

bool test_sorted(int *arr, int n)
{
	for (int i = 1; i < n; i++)
		if (arr[i] < arr[i - 1])
			return false;
	return true;
}

int arr_sum(int *arr, int n) {
    int res = 0;
	for (int i = 0; i < n; res += arr[i], i++)
		;
    return res;
}

void print_arr(int *arr, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main()
{
    double start, end;
	const int n = 2000000;
	int arr[n];
	int threads_n = 0;	// remember number of threads in parallel block
    int pivot;
	int sumbef, sumaft; // checksums to compare

	fill_rand(arr, n);
    sumbef = arr_sum(arr, n);
    start = omp_get_wtime();

    pivot = split(arr, n);
    
    #pragma omp parallel num_threads(2) shared(arr)
    {
        int idx = omp_get_thread_num();
        int first = (idx == 0) ? 0 : pivot + 1;
        int last = (idx == 0) ? pivot - 1 : n - 1;

        quicksort(arr, first, last);
    }

    end = omp_get_wtime();
    sumaft = arr_sum(arr, n);

    if (test_sorted(arr, n)) printf("Test passed!\n");
	else printf("[!!!] Test failed!\n");

	if (sumbef == sumaft) printf("Sum not changed!\n");
	else printf("[!!!] Sum before = %d, after = %d!\n", sumbef, sumaft);

	printf("[Time passed]: %lf\n", end - start);


}
