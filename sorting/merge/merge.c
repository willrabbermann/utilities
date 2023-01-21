#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void merge(int array[], int l, 
		   int m, int r)
// merge two subarrays of array[]
// First subarray is array[l..m]
// Second subarray is array[m+l..r]
{
	int i, j, k, s1, s2;
	s1 = m - l + 1;
	s2 = r - m;

	int L[s1], R[s2];

	// Copy array's data to temp arrays,
	for (i = 0; i < s1; i++)
		L[i] = array[l + i];
	for (j = 0; j < s2; j++)
		R[j] = array[m + 1 + j];

	i = j = 0;
	k = l;
	
	// Sort array by checking if L <= R and 
	// merging either the left or right's element
	// in order to merge from least to greatest
	while (i < s1 && j < s2)
	{
		if (L[i] <= R[j])
		{
			array[k] = L[i];
			i++;
		}
		else
		{
			array[k] = R[j];
			j++;
		}
		k++;
	}
	
	// Copy remaining elements of L[] if there are any
	while (i < s1)
	{	
		array[k] = L[i];
		i++;
		k++;
	}

	// Copy remaining elements of R[] if there are any
	while (j < s2)
	{
		array[k] = R[j];
		j++;
		k++;
	}
}

void merge_sort(int array[], int l, int r)
// l = left index, r = right index 
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		// Sort first and second halves
		merge_sort(array, l, m);
		merge_sort(array, m + 1, r);

		merge(array, l, m, r);
	}
}

void printArray(int a[], size_t size)
{
	printf("[ ");
	for (size_t i = 0; i < size; i++)
	{
		if (i == size - 1)
			printf("%d ]\n", a[i]);
		else
			printf("%d, ", a[i]);
	}
}

int main()
{
	int a[] = { 7, 3, 4, 9, 2, 0, 1, 6, 5, 8 };
	int size = sizeof(a)/sizeof(a[0]);
	printf("Original array:\n");
	printArray(a, size);
	printf("Sorted array:\n");
	merge_sort(a, 0, size-1);
	printArray(a, size);
}
