#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>
#include <limits.h>

void merge(int arr[], int start, int mid, int end)
{
	int start2 = mid + 1;
	// If the direct merge is already sorted
	if (arr[mid] <= arr[start2])
		return;

	// Two pointers to maintain start
	// of both arrays to merge
	while (start <= mid && start2 <= end)
	{
		// If element 1 is in right place
		if (arr[start] <= arr[start2])
		{
			start++;
		}
		else
		{
			int value = arr[start2];
			int index = start2;

			// Shift all the elements between element 1
			// element 2, right by 1.
			while (index != start)
			{
				arr[index] = arr[index - 1];
				index--;
			}
			arr[start] = value;

			// Update all the pointers
			start++;
			mid++;
			start2++;
		}
	}
}

/* l is for left index and r is right index of the 
sub-array of arr to be sorted */
void merge_sort(int arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l + r) / 2, but avoids overflow
		// for large l and r
		int m = l + (r - l) / 2;

		// Sort first and second halves
		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
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
	const int n = 1500000;
	int arr[n];
	int threads_n = 0;	// remember number of threads in parallel block
	int sumbef, sumaft; // checksums to compare

	fill_rand(arr, n);
	sumbef = arr_sum(arr, n);
	start = omp_get_wtime();

	/**
	 * Sort chunks in parallel
	 */
	#pragma omp parallel num_threads(4) shared(arr)
	{
		const int i = omp_get_thread_num();
		const int thr_n = omp_get_num_threads();
		const int share = n / thr_n;
		const int left = i * share;
		// if this is a last chunk, take all that remains
		const int right = (i == thr_n - 1) ? n - 1 : (i + 1) * share - 1;
		printf("thread #%d: indices %d to %d\n", i, left, right);

		#pragma omp single
			threads_n = thr_n;

		merge_sort(arr, left, right);
	}

	/**
	 * Merge sorted chunks
	 */
	const int share = (n / threads_n);
	int mid, right;
	for (int i = 1; i < threads_n; i++)
	{
		mid = i * share - 1;
		// if this is a last chunk, take all that remains
		right = (i == threads_n - 1) ? n - 1 : (i + 1) * share - 1;

		printf("merging arr[] left=%d, mid=%d, right=%d\n", 0, mid, right);
		merge(arr, 0, mid, right);
	}

	end = omp_get_wtime();
	sumaft = arr_sum(arr, n);

	if (test_sorted(arr, n)) printf("Test passed!\n");
	else printf("[!!!] Test failed!\n");

	if (sumbef == sumaft) printf("Sum not changed!\n");
	else printf("[!!!] Sum before = %d, after = %d!\n", sumbef, sumaft);

	printf("[Time passed]: %lf\n", end - start);

	return 0;
}
